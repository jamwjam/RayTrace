#include "pointlight.h"

pointLight::pointLight()
{

}

pointLight::pointLight(Color color, Vector3 position)
{
    this->color = color;
    this->position = position;
}

pointLight::~pointLight()
{

}

