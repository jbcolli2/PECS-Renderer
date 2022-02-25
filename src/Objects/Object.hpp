//
// Created by Jeb Collins on 2/24/22.
//

#ifndef PECS_RENDERER_OBJECT_HPP
#define PECS_RENDERER_OBJECT_HPP

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
    std::vector<std::shared_ptr<Component>> m_components;

public:
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
    void AddComponent(const CompT& component)

};



}
#endif //PECS_RENDERER_OBJECT_HPP
