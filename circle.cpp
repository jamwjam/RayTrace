#include "circle.h"
#include "color.h"

circle::circle()
{

}

circle::circle(Color color, float phong_exponent, float specular_fraction, Vector3 c_p, float radius){
    this->color = color;
    this->phong_exponent = phong_exponent;
    this->specular_fraction = specular_fraction;
    this->c_position = c_p;
    this->radius = radius;
}

circle::~circle()
{

}


