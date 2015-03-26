#ifndef SCENE_H
#define SCENE_H

#include "vector3.h"
#include "color.h"

#include <vector>
#include "triangle.h"
#include "circle.h"
#include "pointlight.h"
#include "directionlight.h"

class Scene {
public:
    Scene();

    //Returns 1 on success, 0 on failure
    int parse(const char *inputFileName);

    const Vector3 &getEyePosition() const {return eyePosition;}
    const Vector3 &getEyeDirection() const {return eyeDirection;}
    const Vector3 &getEyeUp() const {return eyeUp;}
    const Vector3 &getEyeRight() const {return eyeRight;}
    float getFieldOfViewY() const {return fieldOfViewY;}

    const Color &getAmbientLight() const {return ambientLight;}

    const std::vector<triangle> &getTriangles() const {return triangles;}
    const std::vector<circle> &getCircles() const {return circles;}
    const std::vector<directionLight> &getDirectionLights() const {return directionLights;}
    const std::vector<pointLight> &getPointLights() const {return pointLights;}

private:
    Vector3 eyePosition;
    Vector3 eyeDirection;
    Vector3 eyeUp;
    Vector3 eyeRight;
    float fieldOfViewY;

    Color ambientLight;

    std::vector<Vector3> trianglePosition;
    std::vector<triangle> triangles;
    std::vector<circle> circles;
    std::vector<directionLight> directionLights;
    std::vector<pointLight> pointLights;
};


#endif
