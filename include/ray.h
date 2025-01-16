#ifndef RAY
#define RAY

#include "vec3.h"

class ray{
  public:

    ray();
    /// @brief Constructor
    /// @param origin The origin point
    /// @param direc The direction
    ray(const vec3& origin, const vec3& direc);
    /// @brief Destructot
    ~ray();
    /// @brief Get Origin Attr
    /// @return vec3 it self
    vec3 origin() const;
    /// @brief 
    /// @return 
    vec3 direction() const;
    /// @brief 
    /// @param t 
    /// @return 
    vec3 at(double t) const;
  private:
    /// @brief The Origin and Direction of Ray
    vec3 origin_;
    vec3 direc_;
};

#endif