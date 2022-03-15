//
// Created by Jeb Collins on 2/25/22.
//

#include "Objects/Object.hpp"

using namespace pecs;


/***************** HasSignature  ******************
 * @brief Returns true if passed object contains a list of components
 *      denoted by \p signature within the objects signature.
******************************************************************/
bool pecs::HasSignature(Object &object, const Signature &signature)
{
    return ((object.GetSignature() & signature) != 0);
}

bool pecs::HasSignature(const Object *object, const Signature &signature)
{
    return ((object->GetSignature() & signature) != 0);
}
