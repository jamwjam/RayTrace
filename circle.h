#ifndef CIRCLE_H
#define CIRCLE_H
#include "vector3.h"
#include "color.h"

class circle
{
public:
    circle();
    circle(Color color, float phong_exponent, float specular_fraction, Vector3 c_a, float radius);
    ~circle();
    const Color &getColor() const {return color;}
    const float &getPhongExponent() const {return phong_exponent;}
    const float &getSpecularFraction() const {return specular_fraction;}
    const Vector3 &getC() const {return c_position;}
    const float &getRadius() const {return radius;}
    void print();
private:
    Color color;
    float phong_exponent;
    float specular_fraction;
    Vector3 c_position;
    float radius;
};

#endif // CIRCLE_H
