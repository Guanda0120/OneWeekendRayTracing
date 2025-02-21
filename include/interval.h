#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>
#include <limits>
#define infinity std::numeric_limits<double>::infinity()

class interval{
  public:
    double min, max;
    interval();
    interval(double min, double max);
    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    void expand(double epsilon);
    static const interval universe, empty;
};

inline const interval universe = interval(-infinity, +infinity);
inline const interval empty = interval(+infinity, -infinity);

#endif