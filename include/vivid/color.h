#pragma once

#include <glm/vec3.hpp>

namespace tq {


//  xyz \in [ ( 0, 0, 0 ), ( 1, 1, 1 ) ]
//  lab \in [ ( 0, -86.1827, -107.86 ), ( 100, 98.2343, 94.478 ) ]
//  lch \in [ ( 0, 0, -2 PI ), ( 100, 133.808, 2 PI ) ]

glm::vec3 ciexyz_to_cielab( const glm::vec3& xyz );
glm::vec3 cielab_to_cielch( const glm::vec3& lab );
glm::vec3 cielch_to_cielab( const glm::vec3& lch );
glm::vec3 cielab_to_ciexyz( const glm::vec3& lab );
void log_rgb_to_cielch( const glm::vec3& rgb );

namespace rgb {


glm::vec3 saturate( const glm::vec3& rgb );
glm::vec3 from_hsv( float h, float s, float v );
glm::vec3 from_hsv( const glm::vec3& hsv );
glm::vec3 from_ciexyz( const glm::vec3& xyz );
glm::vec3 from_cielch( const glm::vec3& lch );  //  convenience function
glm::vec3 to_hsv( float r, float g, float b );
glm::vec3 to_hsv( const glm::vec3& rgb);
glm::vec3 to_ciexyz( const glm::vec3& rgb );
glm::vec3 to_cielch( const glm::vec3& rgb );    //  convenience function
glm::vec3 rainbow( const int c );
glm::vec3 lerp_hsv( const glm::vec3& rgb1, const glm::vec3& rgb2, const float t );
glm::vec3 lerp_cielch( const glm::vec3& rgb1, const glm::vec3& rgb2, const float t );


}   //  ::tq::rgb


}   //  ::tq
