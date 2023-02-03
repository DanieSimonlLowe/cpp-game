#include "consonants.hpp"

float inverse_rsqrt( float number )
{
    const float threehalfs = 1.5F;

    float x2 = number * 0.5F;
    float y = number;

    // evil floating point bit level hacking
    long i = * ( long * ) &y;

    // value is pre-assumed
    i = 0x5f3759df - ( i >> 1 );
    y = * ( float * ) &i;

    // 1st iteration
    y = y * ( threehalfs - ( x2 * y * y ) );

    // 2nd iteration, this can be removed
    // y = y * ( threehalfs - ( x2 * y * y ) );

    return y;
}

void malt(vec2d *v, float factor) {
    v->x = v->x*factor;
    v->y = v->y*factor;
}

float lensq(vec2d *v) {
    return v->x*v->x + v->y*v->y;
}

void normalize(vec2d *v) {
    float factor = inverse_rsqrt(lensq(v));
    malt(v,factor);
}



