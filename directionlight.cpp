#include "directionlight.h"

directionLight::directionLight()
{

}

directionLight::directionLight(Color color, Vector3 position){
    this->color = color;
    this->position = position;
}

directionLight::~directionLight()
{

}

