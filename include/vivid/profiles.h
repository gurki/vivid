#pragma once

#include "vivid/types.h"
#include <glm/gtx/matrix_operation.hpp>

namespace vivid {


namespace profiles
{
    //  c.f.
    //    [1] https://en.wikipedia.org/wiki/Illuminant_D65
    //    [2] http://brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html

    //  chromaticity coordinates using standard 2° observer
    static const glm::vec2 xy_d50 = { 0.3457f, 0.3585f };
    static const glm::vec2 xy_d55 = { 0.3324f, 0.3474f };
    static const glm::vec2 xy_d65 = { 0.312713f, 0.329016f };
    static const glm::vec2 xy_d75 = { 0.2990f, 0.3149f };
    static const glm::vec2 xy_d93 = { 0.2848f, 0.2932f };

    //  pre-computed tristimulus values
    static const glm::vec3 tri_d65 = { 0.95047f, 1.f, 1.08883f };

    //  gammas
    static const float gamma_adobe = 2.19921875f;
}


namespace matrices
{
    //  NOTE(tgurdan):
    //    transposed init for readability due to column-major order

    //  srgb <-> xyz, d65

    static const auto xyz_to_rgb = glm::transpose( glm::mat3{
        3.2404542f,-1.5371385f,-0.4985314f,
       -0.9692600f, 1.8760108f, 0.0415560f,
        0.0556434f,-0.2040259f, 1.0572252f
    });

    static const auto rgb_to_xyz = glm::transpose( glm::mat3{
        0.4124564f, 0.3575761f, 0.1804375f,
        0.2126729f, 0.7151522f, 0.0721750f,
        0.0193339f, 0.1191920f, 0.9503041f
    });

    //  adobe <-> xyz, d65

    static const auto xyz_to_adobe = glm::transpose( glm::mat3{
        2.0413690f,-0.5649464f,-0.3446944f,
       -0.9692660f, 1.8760108f, 0.0415560f,
        0.0134474f,-0.1183897f, 1.0154096f,
    });

    static const auto adobe_to_xyz = glm::transpose( glm::mat3{
        0.5767309f, 0.1855540f, 0.1881852f,
        0.2973769f, 0.6273491f, 0.0752741f,
        0.0270343f, 0.0706872f, 0.9911085f
    });

    //  chromatic adaptation

    static const glm::mat3 bradford = {
        0.8951f,-0.7502f, 0.0389f,
        0.2664f, 1.7135f, 0.0685f,
       -0.1614f, 0.0367f, 1.0296f
    };

    static const glm::mat3 invBradford = {
        0.9869929f, 0.4323053f,-0.0085287f,
       -0.1470543f, 0.5183603f, 0.0400428f,
        0.1599627f, 0.0492912f, 0.9684867f
    };
}


inline glm::vec3 tristimulus( const float xw, const float yw ) {
    static const float Y = 1.f;
    const float k = Y / yw;
    return { k * xw, Y, k * ( 1.f - xw - yw ) };
}


inline glm::vec2 chromaticity( const float X, const float Y, const float Z ) {
    const float sum = X + Y + Z;
    return { X / sum, Y / sum };
}


inline glm::mat3 workingSpaceMatrix(
    const glm::vec2& xy,
    const glm::vec3& ciex,
    const glm::vec3& ciey )
{
    const glm::mat3 K = {
        ciex.r / ciey.r, 1.f, ( 1.f - ciex.r - ciey.r ) / ciey.r,
        ciex.g / ciey.g, 1.f, ( 1.f - ciex.g - ciey.g ) / ciey.g,
        ciex.b / ciey.b, 1.f, ( 1.f - ciex.b - ciey.b ) / ciey.b,
    };

    const glm::vec3 XYZ = tristimulus( xy.x, xy.y );
    const glm::vec3 S = glm::inverse( K ) * XYZ;

    return K * glm::diagonal3x3( S );
}


inline xyz_t chromaticAdaptation(
    const xyz_t& src,
    const glm::vec2& srcRef,
    const glm::vec2& dstRef )
{
    const glm::vec3 srcTri = tristimulus( srcRef.x, srcRef.y );
    const glm::vec3 dstTri = tristimulus( dstRef.x, dstRef.y );
    const glm::vec3 srcCone = matrices::bradford * srcTri;
    const glm::vec3 dstCone = matrices::bradford * dstTri;

    const glm::mat3 M = (
        matrices::invBradford *
        glm::diagonal3x3( dstCone / srcCone ) *
        matrices::bradford
    );

    return static_cast<xyz_t>( M * src );
}


}   //  ::vivid
