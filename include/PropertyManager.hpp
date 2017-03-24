#ifndef PROPERTYMANAGER_INCLUDED_H
#define PROPERTYMANAGER_INCLUDED_H

#include <map>
#include <typeinfo>
#include "Property.hpp"
#include "Types.hpp"

/// Provides the PropertyManager class for managing IProperty classes
class PropertyManager
{
 public:
  /**
  * PropertyManager default constructor
  */
  PropertyManager();

  /**
  * PropertyManager Deconstructor
  */
  virtual ~PropertyManager();

  /**
  * HasProperty returs true if thePropertyID specified exists in this
  * PropertyManager.
  * @param[in] thePropertyID to lookup in this PropertyManager
  * @return true if thePropertyID exists, false otherwise
  */
  bool has_ID(const std::string thePropertyID);

  /**
  * GetProperty returns the property as type with the ID of thePropertyID.
  * @param[in] propertyID is the ID of the property to return.
  * @return the value stored in the found propery in the form of TYPE. If no
  * Property was found it returns the default value the type constructor.
  */
  template <class TYPE>
  TYPE get(const std::string propertyID)
  {
    if (_propertyList.find(propertyID) != _propertyList.end())
    {
      if (_propertyList.at(propertyID)->get_type()->name() ==
          typeid(TYPE).name())
        return static_cast<TProperty<TYPE>*>(_propertyList[propertyID])
            ->get_value();
    }
    else
    {
      // TODO: log that the PropertyManager is returning a blank
      // property
    }

    TYPE tReturn = TYPE();
    return tReturn;
  }

  /**
  * SetProperty sets the property with the ID of propertyID to value
  * @param[in] thePropertyID is the ID of the property to set.
  * @param[in] theValue is the value to set.
  */
  template <class TYPE>
  void set(const std::string propertyID, TYPE theValue)
  {
    if (_propertyList.find(propertyID) != _propertyList.end())
    {
      if (_propertyList.at(propertyID)->get_type()->name() ==
          typeid(TYPE).name())
        static_cast<TProperty<TYPE>*>(_propertyList[propertyID])
            ->set_value(theValue);
    }
    else
    {
      // TODO: log that the property manager was unable to find the
      // property
    }
  }

  /**
  * AddProperty creates a property and adds it to this entity
  * @param[in] thePropertyID is the ID of the property to create.
  * @param[in] theValue is the inital value to set.
  */
  template <class TYPE>
  void add(const std::string thePropertyID, TYPE theValue)
  {
    // Only add the property if it doesn't exist already
    if (_propertyList.find(thePropertyID) == _propertyList.end())
    {
      TProperty<TYPE>* aProperty =
          new (std::nothrow) TProperty<TYPE>(thePropertyID);
      aProperty->set_value(theValue);
      _propertyList[aProperty->get_ID()] = aProperty;
    }
  }

  /**
  * AddProperty gets a premade property and adds it to this entity
  * @param[in] theProperty is a pointer to a pre exisiting property.
  */
  void add(IProperty* theProperty);

  /**
  * Clone is responsible for making a clone of each property in the
  * PropertyManager provided.
  * @param[in] thePropertyManager to clone into ourselves
  */
  void clone(const PropertyManager& thePropertyManager);

 private:
  /// A map of all Properties available for this PropertyManager class
  std::map<const std::string, IProperty*> _propertyList;
};  // PropertyManager class

#endif
