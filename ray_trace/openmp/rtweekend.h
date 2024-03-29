//
// Created by QC on 2022-12-11.
//

#ifndef DEV_QHC_CPP_PROJECTS_RTWEEKEND_H
#define DEV_QHC_CPP_PROJECTS_RTWEEKEND_H
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <iostream>
// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}


inline double random_double() {
    return rand() /( RAND_MAX + 1.);
}

inline double random_double(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common Headers

#include "ray.h"
#include "vec3.h"
#endif //DEV_QHC_CPP_PROJECTS_RTWEEKEND_H
