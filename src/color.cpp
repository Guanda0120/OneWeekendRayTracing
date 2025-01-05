#include "color.h"

color::color():r(0),g(0),b(0){};

color::color(double r_ratio, double g_ratio, double b_ratio){
    this->r = int(r_ratio * 255.999);
    this->g = int(g_ratio * 255.999);
    this->b = int(b_ratio * 255.999);
}

void color::write_color(std::ostream& out){
    out<<this->r<<' '<<this->g<<' '<<this->b<<'\n';
}