#include "interval.h"

interval::interval():max(+infinity),min(-infinity){};

interval::interval(double min, double max)
  :max(max), min(min){};

double interval::size() const{
  return this->max-this->min;
};

bool interval::contains(double t) const{
  return this->min<= t && t<=this->max;
};

bool interval::surrounds(double t) const{
  return this->min<t && t<this->max;
}

void interval::expand(double epsilon){
  this->min-=epsilon/2;
  this->max+=epsilon/2;
}