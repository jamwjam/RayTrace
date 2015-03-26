#ifndef LIGHT_H
#define LIGHT_H

#include "vector3.h"
#include "color.h"

class light
{
public:
    light(Color c);
    const Color &getColor() const {return color;}

private:
    Color color;
};

class ambientLight : light {
public:
    ambientLight(Color color): light(color){
        this->color = color;
    }

private:
    Color color;
};

class directionLight : light {
public:
    directionLight(Color color, Vector3 position) : light(color){
        this->position = position;
    }
    const Vector3 &getPosition() const {return position;}

private:
    Vector3 position;
};

class pointLight : light {
public:
    pointLight(Color color, Vector3 position) : light(color){
        this->position = position;
    }
    const Vector3 &getPosition() const {return position;}

private:
    Vector3 position;
};

#endif // LIGHT_H
