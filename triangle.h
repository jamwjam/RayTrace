#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "color.h"
#include <vector>
#include "vector3.h"

class triangle
{
public:
    triangle();
    triangle(Color color, float phong_exponent, float specular_fraction, Vector3 p_a, Vector3 p_b, Vector3 p_c);
    ~triangle();
    const Color &getColor() const {return color;}
    const float &getPhongExponent() const {return phong_exponent;}
    const float &getSpecularFraction() const {return specular_fraction;}
    const Vector3 &getA() const {return A;}
    const Vector3 &getB() const {return B;}
    const Vector3 &getC() const {return C;}
    const Vector3 &getAB() const {return AB;}
    const Vector3 &getBC() const {return BC;}
    const Vector3 &getCA() const {return CA;}

    void print(){
        printf("{(%f, %f, %f), (%f, %f, %f), (%f, %f, %f)}\n", this->getA().getX(), this->getA().getY(), this->getA().getZ(),
               this->getB().getX(), this->getB().getY(), this->getB().getZ(), this->getC().getX(), this->getC().getY(), this->getC().getZ());
    };
    float getD();
    Vector3 getNormal();
private:
    Color color;
    float phong_exponent;
    float specular_fraction;
    std::vector<Vector3> triangle_positions;
    Vector3 A, B, C, AB, BC, CA;
};

#endif // TRIANGLE_H
