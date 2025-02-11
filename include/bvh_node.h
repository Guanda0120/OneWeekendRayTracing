#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "hittable.h"

class bvh_node : public hittable{
  public: 
    bvh_node();

    ~bvh_node();
  private:
    bounding_box b_box_;
};

#endif