#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/epsilon.hpp>


namespace vivid {


////////////////////////////////////////////////////////////////////////////////
template<glm::length_t L, glm::qualifier Q>
inline bool fuzzyEqual(
    const glm::vec<L, float, Q>& v1,
    const glm::vec<L, float, Q>& v2,
    const float eps = 0.004f )
{
    return glm::all( glm::epsilonEqual( v1, v2, eps ) );
}


////////////////////////////////////////////////////////////////////////////////
inline bool fuzzyEqual(
    const glm::mat3& m1,
    const glm::mat3& m2,
    const float eps = 0.004f )
{
    return (
        fuzzyEqual( m1[ 0 ], m2[ 0 ], eps ) &&
        fuzzyEqual( m1[ 1 ], m2[ 1 ], eps ) &&
        fuzzyEqual( m1[ 2 ], m2[ 2 ], eps )
    );
}


}
