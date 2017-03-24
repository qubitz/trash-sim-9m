#ifndef GFK_GROUPMANAGER_INCLUDED
#define GFK_GROUPMANAGER_INCLUDED

#include <map>
#include "Group.hpp"

class GroupManager
{
 public:
  /**
  *
  */
  GroupManager();

  /**
  *
  */
  ~GroupManager();

  /**
  *
  */
  void add(Group* newGroup);

  /**
  *
  */
  void create_new(const std::string& newGroupName);

  /**
  *
  */
  Group& get(const std::string& groupName);

  /**
  *
  */
  Group& operator[](const std::string& groupName);

 private:
  /// The map containing the groups
  std::map<std::string, Group*> m_groups;
};

#endif
