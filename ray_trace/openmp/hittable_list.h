//
// Created by Nathan on 2022-12-11.
//

#ifndef DEV_QHC_CPP_PROJECTS_HITTABLELIST_H
#define DEV_QHC_CPP_PROJECTS_HITTABLE_LIST_H

#include "hittable.h"

#include "../../../../usr/include/c++/11/memory"
#include "../../../../usr/include/c++/11/vector"

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
    HittableList() {}

    HittableList(shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }

    void add(shared_ptr<Hittable> object) { objects.push_back(object); }

    bool hit(
        const Ray &r, double t_min, double t_max, HitRecord &rec) const override;

public:
    std::vector<shared_ptr<Hittable>> objects{};
};

bool HittableList::hit(const Ray &r, double t_min, double t_max, HitRecord &rec) const {
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto &object: objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

#endif //DEV_QHC_CPP_PROJECTS_HITTABLELIST_H
