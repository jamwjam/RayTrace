#ifndef DIRECTIONLIGHT_H
#define DIRECTIONLIGHT_H
#include "color.h"
#include "vector3.h"

class directionLight
{
public:
    directionLight();
    directionLight(Color color, Vector3 position);
    ~directionLight();
    const Color &getColor() const {return color;}
    const Vector3 &getPosition() const {return position;}
private:
    Color color;
    Vector3 position;
};

#endif // DIRECTIONLIGHT_H
