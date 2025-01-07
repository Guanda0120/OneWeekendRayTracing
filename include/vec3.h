#ifndef VEC3_H
#define VEC3_H

#include <iostream>
#include <cmath>

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
    /// @brief Make the vector self unit vector
    void normalize_vec();
    /// @brief print this vector
    void stream_out();

    double x();
    double y();
    double z();
};

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

#endif