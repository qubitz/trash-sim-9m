#include "PropertyManager.hpp"

PropertyManager::PropertyManager() {}
PropertyManager::~PropertyManager()
{
  // Remove all registered Properties
  std::map<const std::string, IProperty*>::iterator propIter;

  for (propIter = _propertyList.begin(); propIter != _propertyList.end();
       ++propIter)
  {
    IProperty* aProperty = propIter->second;
    delete aProperty;
    aProperty = NULL;
  }
}

bool PropertyManager::has_ID(const std::string thePropertyID)
{
  return _propertyList.find(thePropertyID) != _propertyList.end();
}

void PropertyManager::add(IProperty* theProperty)
{
  if (_propertyList.find(theProperty->get_ID()) == _propertyList.end())
    _propertyList[theProperty->get_ID()] = theProperty;
}

void PropertyManager::clone(const PropertyManager& thePropertyManager)
{
  // Make sure to remove all registered properties on destruction
  std::map<const std::string, IProperty*>::const_iterator propIter;
  for (propIter = thePropertyManager._propertyList.begin();
       propIter != thePropertyManager._propertyList.end(); ++propIter)
  {
    IProperty* aProperty = propIter->second;
    add(aProperty->make_clone());
  }
}
