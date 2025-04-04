#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>
#include "rt_constance.h"

/**
 * vec3 class basic contain simple +,-,*,/ operater,
 * indexer, constructor, deconstructor
 */
class vec3 {
  public:
    /* Storage coordinate */
    double e[3];
    /* default ctor */
    vec3();
    /* coordinate constructor */
    vec3(double x, double y, double z);
    /* Negetive the vector */
    vec3 operator -() const; 
    /* the indexer */
    double operator[](int i) const;
    /* vector addition */
    vec3& operator+=(const vec3& v);
    /* get the length of the vector */
    double length() const;
    
    double length_squared() const;
    /// @brief Make the vector self unit vector
    void normalize_vec();
    /// @brief print this vector
    void stream_out();
    /// @brief Generate a vector[0-1]
    /// @return 
    static vec3 random();
    /// @brief Generate vector in some domain
    /// @param min 
    /// @param max 
    /// @return 
    static vec3 random(double min, double max);

    double x() const;
    double y() const;
    double z() const;
};

using point = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v){
  return out<<v.e[0]<<' '<<v.e[1]<<' '<<v.e[2];
};

inline vec3 operator+(const vec3& u, const vec3& v){
  return vec3(u.e[0]+v.e[0], u.e[1]+v.e[1], u.e[2]+v.e[2]);
};

inline vec3 operator-(const vec3& u, const vec3& v){
  return vec3(u.e[0]-v.e[0], u.e[1]-v.e[1], u.e[2]-v.e[2]);
};

inline vec3 operator*(double t, const vec3& v){
  return vec3(v.e[0]*t, v.e[1]*t, v.e[2]*t);
};

inline vec3 operator*(const vec3& u, const vec3& v){
  return vec3(v.e[0]*u.e[0], v.e[1]*u.e[1], v.e[2]*u.e[2]);
};

inline vec3 operator*(const vec3& v, double t){
  return t*v;
};

inline vec3 operator/(const vec3& v, double t){
  return (1/t)*v;
}

inline double dot(const vec3& u, const vec3& v){
  return u.e[0] * v.e[0] +
         u.e[1] * v.e[1] +
         u.e[2] * v.e[2];
}

inline vec3 cross(const vec3& u, const vec3& v){
  return vec3(
    u.e[1] * v.e[2] - u.e[2] * v.e[1],
    u.e[2] * v.e[0] - u.e[0] * v.e[2],
    u.e[0] * v.e[1] - u.e[1] * v.e[0]
  );
}

inline vec3 unit_vec(const vec3& v){
  return v/v.length();
}

inline vec3 random_unit_vector(){
  while (true) {
    auto p = vec3::random(-1,1);
    auto lensq = p.length_squared();
    if (1e-160 < lensq && lensq <= 1)
      return p / sqrt(lensq);
    }
}

inline vec3 random_unit_vector_hemisphere(const vec3& normal){
  vec3 random_vec = random_unit_vector();
  if (dot(normal, random_vec)>0.0){
    return random_vec;
  } else {
    return -random_vec;
  }
}

inline vec3 reflect(vec3 inject_vec, vec3 normal){
  return inject_vec-2*dot(inject_vec, normal)*normal;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat){
  // TODO understand what doing here
  double cos_theta = std::fmin(dot(-uv, n), 1.0);
  vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
  vec3 r_out_parallel = -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_perp + r_out_parallel;
}

#endif