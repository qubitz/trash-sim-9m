#include "Property.hpp"

///////////////////////////
// IPROPERTY DEFINITIONS //
///////////////////////////
IProperty::IProperty(std::string theType, const std::string thePropertyID)
    : _type(theType), _propertyID(thePropertyID)
{
}

IProperty::~IProperty() {}
IProperty::Type_t* IProperty::get_type() { return &_type; }
const std::string  IProperty::get_ID() const { return _propertyID; }
void IProperty::set_type(std::string theType) { _type = Type_t(theType); }
