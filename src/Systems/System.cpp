//
// Created by Jeb Collins on 3/5/22.
//

#include "System.hpp"



using namespace pecs;
/***************** AddObjSameSignature  ******************
 * @brief Add the @object if it has the same signature as the system.
 *      This object will be stored in the system and will be acted automatically upon whenever
 *      a method in the system is called.
***************************************///
bool System::AddObjSameSignature(Object &object)
{
    if(HasSignature(object, m_signature))
    {
        m_objects.push_back(&object);
        return true;
    }

    return false;
}


bool System::AddObjSameSignature(Object* object)
{
    return AddObjSameSignature(*object);
}