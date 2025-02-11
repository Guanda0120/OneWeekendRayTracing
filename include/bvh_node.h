#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <algorithm>
#include "hittable.h"
#include "hittable_list.h"

using std::vector;
using std::shared_ptr;

class bvh_node : public hittable{
  public: 
    
    bvh_node(hittable_list list):bvh_node(list.objects){};

    bvh_node(vector<shared_ptr<hittable>>list);

    bool hit(const ray& r, interval domain, hit_record& rec) const override;

    ~bvh_node();

  private:
    bounding_box b_box_;
    shared_ptr<hittable> left_;
    shared_ptr<hittable> right_;
    static bool box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, axis axis_index); 
    static bool box_x_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b);
    static bool box_y_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b);
    static bool box_z_compare (const shared_ptr<hittable> a, const shared_ptr<hittable> b);
};

#endif