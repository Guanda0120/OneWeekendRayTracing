#ifndef RAY
#define RAY

#include "vec3.h"

class ray{
  public:
    /// @brief Constructor
    /// @param origin The origin point
    /// @param direc The direction
    ray(vec3& origin, vec3& direc);
    /// @brief Destructot
    ~ray();
    /// @brief Get Origin Attr
    /// @return vec3 it self
    const vec3& origin();
    /// @brief 
    /// @return 
    const vec3& direction();
    /// @brief 
    /// @param t 
    /// @return 
    const vec3 at(double t);
  private:
    /// @brief The Origin and Direction of Ray
    vec3& origin_;
    vec3& direc_;
};

#endif