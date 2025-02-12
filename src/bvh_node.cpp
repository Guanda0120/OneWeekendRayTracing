#include "bvh_node.h"

bvh_node::bvh_node(vector<shared_ptr<hittable>>list){
  // Construct Bounding box
  this->b_box_ = bounding_box(list[0]->b_box());
  if (list.size()==1){
    this->left_ = list[0];
    this->right_ = list[0];
    return;
  }
  for(size_t i=1; i<list.size(); i++){
    this->b_box_ = bounding_box(this->b_box_, list[i]->b_box());
  }
  axis axis = this->b_box_.longest_axis();
  // Choose the longest axis to split
  auto comparator = (axis == 0) ? box_x_compare
    : (axis == 1) ? box_y_compare
      : box_z_compare;

  // Sort by Longset Axis
  std::sort(list.begin(), list.end(), comparator);
  auto mid = list.size() / 2;
  vector<shared_ptr<hittable>> left_list(list.begin(), list.begin() + mid);
  vector<shared_ptr<hittable>> right_list(list.begin() + mid, list.end());
  this->left_ = make_shared<bvh_node>(left_list);
  this->right_ = make_shared<bvh_node>(right_list);

}

bool bvh_node::hit(const ray& r, interval domain, hit_record& rec)const{
  if (!this->b_box_.hit(r)){
    return false;
  }
  interval left_interval, right_interval;
  hit_record left_rec, right_rec;
  bool hit_left = this->left_->hit(r, left_interval, left_rec);
  bool hit_right = this->right_->hit(r, right_interval, right_rec);
  
  // Important Both hit 
  if (hit_left && hit_right){
    rec = left_rec.t<right_rec.t? left_rec : right_rec;
    domain = left_rec.t<right_rec.t? left_interval : right_interval;
    return true;
  }

  // Just hit one
  if (hit_left){
    rec = left_rec;
    domain = left_interval;
    return true;
  } else {
    rec = right_rec;
    domain = right_interval;
    return true;
  }

  // Donnot Hit
  return false;
}

bvh_node::~bvh_node(){

}

bounding_box bvh_node::b_box() const{
  return this->b_box_;
}

bool bvh_node::box_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b, axis axis_index){
  auto a_axis_interval = a->b_box().axis_interval(axis_index);
  auto b_axis_interval = b->b_box().axis_interval(axis_index);
  return a_axis_interval.min < b_axis_interval.min;
}

bool bvh_node::box_x_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b){
  return box_compare(a, b, axis::X);
}

bool bvh_node::box_y_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b){
  return box_compare(a, b, axis::Y);
}

bool bvh_node::box_z_compare(const shared_ptr<hittable> a, const shared_ptr<hittable> b){
  return box_compare(a, b, axis::Z);
}