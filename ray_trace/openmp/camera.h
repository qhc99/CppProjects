//
// Created by QC on 2022-12-11.
//

#ifndef DEV_QHC_CPP_PROJECTS_CAMERA_H
#define DEV_QHC_CPP_PROJECTS_CAMERA_H
#include "rtweekend.h"

class Camera {
public:
    Camera(
        Point3 lookfrom,
        Point3 lookat,
        Vec3   vup,
        double vfov, // vertical field-of-view in degrees
        double aspect_ratio,
        double aperture,
        double focus_dist
    ) {
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2.0 * h;
        auto viewport_width = aspect_ratio * viewport_height;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        origin = lookfrom;
        horizontal = focus_dist * viewport_width * u;
        vertical = focus_dist * viewport_height * v;
        lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

        lens_radius = aperture / 2;
    }


    Ray get_ray(double s, double t) const {
        Vec3 rd = lens_radius * random_in_unit_disk();
        Vec3 offset = u * rd.x() + v * rd.y();

        return Ray(
            origin + offset,
            lower_left_corner + s*horizontal + t*vertical - origin - offset
        );
    }

private:
    Point3 origin;
    Point3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u, v, w;
    double lens_radius;
};

class VirtualCamera {
    public:
        VirtualCamera(
            Point3 lookfrom,
            Point3 lookat,
            Vec3   vup,
            double vfov, // vertical field-of-view in degrees
            double aspect_ratio
        ) {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_height = 2.0 * h;
            auto viewport_width = aspect_ratio * viewport_height;

            auto w = unit_vector(lookfrom - lookat);
            auto u = unit_vector(cross(vup, w));
            auto v = cross(w, u);

            origin = lookfrom;
            horizontal = viewport_width * u;
            vertical = viewport_height * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - w;
        }

        Ray get_ray(double s, double t) const {
            return Ray(origin, lower_left_corner + s*horizontal + t*vertical - origin);
        }

    private:
        Point3 origin;
        Point3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};

#endif //DEV_QHC_CPP_PROJECTS_CAMERA_H
