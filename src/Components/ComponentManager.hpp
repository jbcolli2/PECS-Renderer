//
// Created by Jeb Collins on 2/27/22.
//

#ifndef PECS_RENDERER_COMPONENTMANAGER_HPP
#define PECS_RENDERER_COMPONENTMANAGER_HPP

#include "Util.hpp"


namespace pecs {
class ComponentManager {
private:
    // hash table to store each component type name with its integer identifier
    static std::vector<const char *> m_componentList;

public:
    ComponentManager() = default;

    /***************** RegisterComponent  ******************
     * @brief Static method that adds a component to the `m_componentList` hash table
     *
     * @param componentType The name of the component obtained from typeof(___).name()
    ***************************************///
    template <typename CompT>
    static int RegisterComponent();

    /***************** GetComponentID  ******************
     * @brief Returns the id of the component to be used in a signature.  Used especially
     *      for adding to the signature of a system.
    ***************************************///
    template <typename CompT>
    static int GetComponentID();



};  // End of ComponentManager class






template <typename CompT>
int ComponentManager::RegisterComponent()
{
    int index = FindIndex(m_componentList, typeid(CompT).name());
    if(index >= 0)
    {
        return index;
    }
    // else

    m_componentList.push_back(typeid(CompT).name());

    return m_componentList.size() - 1;
}




/***************** GetComponentID  ******************
 * @brief Returns the id of the component to be used in a signature.  Used especially
 *      for adding to the signature of a system.
***************************************///
template <typename CompT>
int ComponentManager::GetComponentID()
{
    return FindIndex(m_componentList, typeid(CompT).name());
}


} // end of pecs namespace
#endif //PECS_RENDERER_COMPONENTMANAGER_HPP
