#ifndef HITTABLE_h
#define HITTABLE_h

#include "ray.h"
#include "interval.h"
#include "hit_record.h"


class hittable{
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval domain, hit_record& rec) const = 0;
};

#endif