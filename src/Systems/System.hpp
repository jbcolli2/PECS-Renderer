//
// Created by Jeb Collins on 3/5/22.
//

#ifndef PECS_RENDERER_SYSTEM_HPP
#define PECS_RENDERER_SYSTEM_HPP

#include "Util.hpp"
#include "Objects/Object.hpp"
#include "Components/ComponentManager.hpp"






namespace pecs
{
class System
{
protected:
    // Signature of all objects that this system will act on
    Signature m_signature;
    // Vector of all entities attached to this system
    std::vector<Object*> m_objects;

public:
    /***************** SetSignature  ******************
     * @brief Adds a component to the signature of the system.
    ***************************************///
    template<typename CompT>
    void SetSignature();

    /***************** AddObjSameSignature  ******************
     * @brief Add the @object if it has the same signature as the system.
     *      This object will be stored in the system and will be acted automatically upon whenever
     *      a method in the system is called.
     *
     * @param object The object to possibly be stored in the system if signature same
     *
     * @returns Return true if object was added, false if not
    ***************************************///
    bool AddObjSameSignature(Object &object);
    bool AddObjSameSignature(Object* object);
};




/***************** SetSignature  ******************
 * @brief Use the ComponentManager to update the signature of the system.
 *      When system is created, it will call this for each component it wants in
 *      its signature, using only the template argument.
***************************************///
template <typename CompT>
void System::SetSignature()
{
    m_signature |= ComponentManager::GetSignature<CompT>();
}








} // End namespace pecs


#endif //PECS_RENDERER_SYSTEM_HPP
