#include "materials/perlin_noise.h"

perlin_noise::perlin_noise(){
  for (int i=0; i<point_count; i++){
    this->randvec_[i] = vec3::random(-1, 1);
    this->randvec_[i].normalize_vec();
  }
  perlin_generate_perm(this->perm_x_);
  perlin_generate_perm(this->perm_y_);
  perlin_generate_perm(this->perm_z_);
}

double perlin_noise::noise(const point& p)const{
  // int i=int(this->scale_*p.x())&255;
  // int j=int(this->scale_*p.y())&255;
  // int k=int(this->scale_*p.z())&255;

  // return randfloat_[perm_x_[i]^perm_y_[j]^perm_z_[k]];

  auto u = p.x() - std::floor(p.x());
  auto v = p.y() - std::floor(p.y());
  auto w = p.z() - std::floor(p.z());
  u = u*u*(3-2*u);
  v = v*v*(3-2*v);
  w = w*w*(3-2*w);
  auto i = int(std::floor(p.x()));
  auto j = int(std::floor(p.y()));
  auto k = int(std::floor(p.z()));
  vec3 c[2][2][2];
  for (int di=0; di < 2; di++)
    for (int dj=0; dj < 2; dj++)
      for (int dk=0; dk < 2; dk++)
        c[di][dj][dk] = this->randvec_[
          perm_x_[(i+di) & 255] ^
          perm_y_[(j+dj) & 255] ^
          perm_z_[(k+dk) & 255]
        ];       
  return perlin_interp(c, u, v, w);
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

double perlin_noise::turb(const point& p, int depth) const {
  auto accum = 0.0;
  auto temp_p = p;
  auto weight = 1.0;

  for (int i = 0; i < depth; i++) {
    accum += weight * noise(temp_p);
    weight *= 0.5;
    temp_p = point(temp_p.x()*2, temp_p.y()*2, temp_p.z()*2);
  }

  return std::fabs(accum);
}

double perlin_noise::perlin_interp(const vec3 c[2][2][2], double u, double v, double w){
  auto uu = u*u*(3-2*u);
  auto vv = v*v*(3-2*v);
  auto ww = w*w*(3-2*w);
  auto accum = 0.0;
  for (int i=0; i < 2; i++){
    for (int j=0; j < 2; j++) {
      for (int k=0; k < 2; k++) {
        vec3 weight_v(u-i, v-j, w-k);
        accum += (i*uu + (1-i)*(1-uu))
          * (j*vv + (1-j)*(1-vv))
          * (k*ww + (1-k)*(1-ww))
          * dot(c[i][j][k], weight_v);
      }
    }
  }
  return accum;
}