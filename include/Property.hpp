#ifndef IPROPERTY_HPP
#define IPROPERTY_HPP

#include <string>
#include <typeinfo>
#include "Types.hpp"

class IProperty
{
 public:
  /// Class that represents the type for this class
  class Type_t
  {
   private:
    // The name of this class
    std::string _name;

   public:
    // Constructor for this class
    explicit Type_t(std::string theName) : _name(theName) {}
    // Returns the name of this class
    std::string name() const { return _name; };
  };

  /**
  * IProperty default constructor
  * @param[in] theType of the property this property represents
  * @param[in] thePropertyID to use for this property
  */
  IProperty(std::string theType, const std::string thePropertyID);

  /**
  * IProperty Deconstructor
  */
  virtual ~IProperty();

  /**
  * get_type will return the Type_t type for this property
  * @return the Type_t class for this property
  */
  Type_t* get_type();

  const std::string get_ID() const;

  /**
  * Update will be called for each IProperty registered with Entity
  * and enable each IProperty derived class to perfrom update related
  * tasks (e.g. frame counter, timer update, decreate in shields, etc)
  */
  virtual void update() = 0;

  /**
  * make_clone is responsible for creating a clone of this IProperty
  * derived class and returning it as part of the Prototype and
  * instance system. The value of the property will also be copied into
  * the clone.
  * @return pointer to the IProperty derived class clone that was created
  */
  virtual IProperty* make_clone() = 0;

 protected:
  /**
  * set_type is responsible for setting the type of class this
  * IProperty class represents and is usually called by the
  * IProperty derived class to set theType
  * @param[in] theType to set for this IProperty derived class
  */
  void set_type(std::string theType);

 private:
  /// The type that represents this class
  Type_t _type;

  /// The propertyID assigned to this IProperty derived class
  const std::string _propertyID;
};  // class IProperty

template <class TYPE = unsigned int>
class TProperty : public IProperty
{
 public:
  /**
  * TProperty default constructor
  * @param[in] thePropertyID to use for this property
  */
  TProperty(const std::string thePropertyID)
      : IProperty(typeid(TYPE).name(), thePropertyID)
  {
  }

  /**
  * get_value will return the property value
  */
  TYPE get_value() { return _value; }
  /**
  * set_value will set the property value to theValue provided
  */
  void set_value(TYPE theValue) { _value = theValue; }
  /**
  * Update will be called giving each property a chance to change
  * itself during the update phase of the gameloop (see Entity::update)
  */
  void update() {}
  /**
  * make_clone is responsible for creating a clone of this IProperty
  * derived class and returning it as part of the prototype and
  * instance system. The value of the property will also be copied into
  * the clone.
  * @return pointer to the IProperty derived class clone that was
  * created
  */
  IProperty* make_clone()
  {
    TProperty<TYPE>* aProperty = new (std::nothrow) TProperty<TYPE>(get_ID());

    // Make sure new didn't fail before setting the value for this property
    if (NULL != aProperty)
    {
      aProperty->set_value(_value);
    }

    // Return cloned aProperty or NULL if none was created
    return aProperty;
  }

 private:
  TYPE _value;
};

#endif
