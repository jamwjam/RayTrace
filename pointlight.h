#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "color.h"
#include "vector3.h"

class pointLight
{
public:
    pointLight();
    pointLight(Color color, Vector3 position);
    ~pointLight();
    const Color &getColor() const {return color;}
    const Vector3 &getPosition() const {return position;}

private:
    Color color;
    Vector3 position;
};

#endif // POINTLIGHT_H
