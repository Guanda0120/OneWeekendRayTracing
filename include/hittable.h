#ifndef HITTABLE_h
#define HITTABLE_h

#include "ray.h"
#include "interval.h"
#include "hit_record.h"
#include "bounding_box.h"


class hittable{
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval domain, hit_record& rec) const = 0;
    virtual bounding_box b_box() const = 0;
};

#endif 