#include "triangle.h"
#include "color.h"

triangle::triangle()
{

}

triangle::triangle(Color color, float phong_exponent, float specular_fraction, Vector3 p_a, Vector3 p_b, Vector3 p_c){
    this->color = color;
    this->phong_exponent = phong_exponent;
    this->specular_fraction = specular_fraction;
    this->A = p_a;
    this->B = p_b;
    this->C = p_c;
    this->AB = B - A;
    this->BC = C - B;
    this->CA = A - C;
    triangle_positions.push_back(p_a);
    triangle_positions.push_back(p_b);
    triangle_positions.push_back(p_c);
}

triangle::~triangle()
{

}

float triangle::getD(){
    return getNormal().dot(this->getA());
}

Vector3 triangle::getNormal() {
    return (this->getB() - this->getA()).cross(this->getC() - this->getA());
}
