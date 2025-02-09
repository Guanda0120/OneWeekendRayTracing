#include "hittable_list.h"

hittable_list::hittable_list(){
  this->objects=std::vector<std::shared_ptr<hittable>>();
};

void hittable_list::add(std::shared_ptr<hittable> hittable_obj){
  this->objects.push_back(hittable_obj);
  this->b_box_ = bounding_box(b_box_, hittable_obj->b_box());
};

void hittable_list::clear(){
  this->objects.clear();
};

bool hittable_list::hit(const ray& r, interval domain, hit_record& rec) const {
  double dist=domain.max;
  bool is_hit=false;
  hit_record tmp_rec;
  for(const auto& hittable_obj: this->objects){
    bool is_hit_inside = hittable_obj->hit(r, domain, tmp_rec);
    if (is_hit_inside && tmp_rec.t<=dist){
      rec = tmp_rec;
      is_hit = true;
      dist = rec.t;
    }
  }
  return is_hit;
};

bounding_box hittable_list::b_box() const{
  return this->b_box_;
}

// hittable_list::~hittable_list(){
//   for (auto& hittable_obj: this->objects)
//   {
//     delete hittable_obj;
//   }
  
// }