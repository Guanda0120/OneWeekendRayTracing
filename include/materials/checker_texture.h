#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "texture.h"
#include "solid_color.h" 

/// @brief This is not a uniform checker generater, This means divide 3d space into scale_factor steps. and reflect to sphere is non uniform 
class checker_texture: public texture
{
	private:
    texture* odd_t_;
		texture* even_t_;
		double scale_factor_;

	public:
    checker_texture(double scale, const color& odd_c, const color& even_c);
    color value(double u, double v, const point& p) const override; 
		~checker_texture();
};

#endif