//
// Created by Jeb Collins on 2/24/22.
//

#ifndef PECS_RENDERER_OBJECT_HPP
#define PECS_RENDERER_OBJECT_HPP

#include "Util.hpp"
#include "Components/Component.hpp"
#include "Components/ComponentManager.hpp"


#include <memory>
#include <vector>
#include <iostream>

namespace pecs
{


// ///////////// CLASS: Object   ////////////////
/**
 \brief Most general 

 \param  -

 \returns
 */
class Object
{
private:
    // all the components that make up the object
    std::unordered_map<const char*, std::shared_ptr<Component>> m_components{};

    // Signature listing what components are attached
    Signature m_signature;

public:
    /***************** Object ctor  ******************
     * @brief Constructor that by default will add a Pipeline component to the object.
     *      If ctor is passed false, it will do nothing.
     *
     * @param pipeline Determines whether to add pipeline component to object.
     *      True by default.
    ******************************************************************/
    Object(bool pipeline = true)
    {
        if(!pipeline)
            return;

        AddComponent(Pipeline());
    };

    //***********************************************************
    //       Getters and Setters
    //***********************************************************
    Signature GetSignature() const {return m_signature;};


    // ///////////// GetComponent<T>   ////////////////
    /**
     @brief Returns the component T if it exists in `m_components`.  For now
        we assume there only exists one of each component in an object.
        TODO: Return vector of components if object has more than one of a component type.

     @template Component type

     @returns Component
     */
    template <typename CompT>
    std::shared_ptr<CompT> GetComponent();



    /***************** AddComponent  ******************
     * @brief Add a component to the object.  If a component of that type already exists, then it
     *  will not be added.
     *  TODO: Modify if code changes to allow multiple of the same component to an object.
     *
     * @template Component type
     *
     * @param component The component to be added.
    ***************************************///
    template <typename CompT>
    void AddComponent(const CompT& component);

    // This < operator is only used to allow objects to be put into an std::set
    bool operator< (const Object& obj) const
    {
        return true;
    };


}; // End Object class



// ///////////// GetComponent<T>   ////////////////
/**
 @brief Returns the component T if it exists in `m_components`.  For now
    we assume there only exists one of each component in an object.
    TODO: Return vector of components if object has more than one of a component type.
 */
template <typename CompT>
std::shared_ptr<CompT> Object::GetComponent()
{
//    std::shared_ptr<CompT> component = m_components.find(typeid(CompT).name())->second;
    std::shared_ptr<CompT> component = std::dynamic_pointer_cast<CompT>(m_components.find(typeid(CompT).name())->second);

    return component;
}







template <typename CompT>
void Object::AddComponent(const CompT& component)
{
    m_components.insert({typeid(CompT).name(), std::make_shared<CompT>(component)});

    m_signature |= ComponentManager::GetSignature<CompT>();
}







/***************** HasComponent  ******************
 * @brief Returns true if passed object has component in its signature.
 *
 * @param object Object to check for component.
******************************************************************/
template<typename CompT>
bool HasComponent(const Object &object)
{
    return ((object.GetSignature() & ComponentManager::GetSignature<CompT>()) != 0);
}

template<typename CompT>
bool HasComponent(const Object *object)
{
    return ((object->GetSignature() & ComponentManager::GetSignature<CompT>()) != 0);
}


/***************** HasSignature  ******************
 * @brief Returns true if passed object contains a list of components
 *      denoted by \p signature within the objects signature.
 *
 * @param object Object to check for signature.
 * @param signature Signature representing a list of components to check for
******************************************************************/
bool HasSignature(Object &object, const Signature &signature);

bool HasSignature(const Object *object, const Signature &signature);

} // End pecs namespace
#endif //PECS_RENDERER_OBJECT_HPP
