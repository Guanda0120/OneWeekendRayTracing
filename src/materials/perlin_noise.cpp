#include "materials/perlin_noise.h"

perlin_noise::perlin_noise(double scale):scale_(scale){
  for (int i=0; i<point_count; i++){
    this->randfloat_[i] = random_double();
  }
  perlin_generate_perm(this->perm_x_);
  perlin_generate_perm(this->perm_y_);
  perlin_generate_perm(this->perm_z_);
}

double perlin_noise::noise(const point& p)const{
  int i=int(this->scale_*p.x())&255;
  int j=int(this->scale_*p.y())&255;
  int k=int(this->scale_*p.z())&255;

  return randfloat_[perm_x_[i]^perm_y_[j]^perm_z_[k]];
}

void perlin_noise::perlin_generate_perm(int* p){
  for (int i=0; i<point_count; i++){
    p[i] = i;
  }
  permute(p);
}

void perlin_noise::permute(int* p){
  // Random Swap the Index from i to before
  for (int i=point_count-1; i>0; i--){
    int target = random_int(0,i);
    int tmp_int = p[target];
    p[target] = p[i];
    p[i] = tmp_int; 
  }
}