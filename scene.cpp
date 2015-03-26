#include "scene.h"
#include <string.h>

#include <iostream>
#include <fstream>

#include <vector>

using namespace std;

struct material {
    Color color;
    float phong_exponent;
    float specular_fraction;
} MATERIAL;

Scene::Scene() :
    eyePosition(0, 0, 0),
    eyeDirection(0, 0, -1),
    eyeUp(0, 1, 0),
    fieldOfViewY(20),
    ambientLight(0, 0, 0) {
}

int Scene::parse(const char *inputFileName) {
    fstream inputFile;

    inputFile.open(inputFileName, fstream::in);

    if (!inputFile.is_open()) {
        cout << "Error opening input file " << inputFileName << endl;
        return 0;
    }

    int lineNum = 0;

    //parse file
    while (!inputFile.eof()) {
        const int bufferSize = 256;
        char command[bufferSize];
        inputFile.getline(command, bufferSize); ++lineNum;
        if (command[0] =='\r'){
                    *command=command[1];
        }

        //skip comments
        if (command[0] == '#') {
        }

        //skip blank lines
        else if (strcmp(command,"") == 0) {
        }

        //read viewing parameters
        else if (strcmp(command, "camera\r") == 0) {
            float eyePositionX, eyePositionY, eyePositionZ;
            float eyeLookAtX, eyeLookAtY, eyeLookAtZ;
            float eyeUpX, eyeUpY, eyeUpZ;

            inputFile >> eyePositionX >> eyePositionY >> eyePositionZ; ++lineNum;
            inputFile >> eyeLookAtX >> eyeLookAtY >> eyeLookAtZ; ++lineNum;
            inputFile >> eyeUpX >> eyeUpY >> eyeUpZ; ++lineNum;
            inputFile >> fieldOfViewY; ++lineNum;

            inputFile.ignore(); //extract final newline

            eyePosition.setXYZ(eyePositionX, eyePositionY, eyePositionZ);

            Vector3 eyeLookAt(eyeLookAtX, eyeLookAtY, eyeLookAtZ);
            eyeDirection = eyeLookAt - eyePosition;
            eyeDirection.normalize();

            eyeUp.setXYZ(eyeUpX, eyeUpY, eyeUpZ);
            eyeUp.normalize();

            eyeRight = eyeDirection.cross(eyeUp);
        }

        //read ambient light
        else if (strcmp(command, "ambientLight\r") == 0) {
            float r, g, b;

            inputFile >> r >> g >> b; ++lineNum;

            inputFile.ignore(); //extract final newline

            ambientLight.setRGB(r, g, b);
        }

        //read direction light
        else if (strcmp(command, "directionLight\r") == 0) {
            float r, g, b;
            float x, y, z;

            inputFile >> r >> g >> b; ++lineNum;
            inputFile >> x >> y >> z; ++lineNum;

            inputFile.ignore(); //extract final newline

            //TODO
            //add direction lights
            directionLights.push_back(directionLight(Color(r,g,b), Vector3(x,y,z)));
        }

        //read point light
        else if (strcmp(command, "pointLight\r") == 0) {
            float r, g, b;
            float x, y, z;

            inputFile >> r >> g >> b; ++lineNum;
            inputFile >> x >> y >> z; ++lineNum;

            inputFile.ignore(); //extract final newline

            //TODO
            //add point lights
            pointLights.push_back(pointLight(Color(r,g,b), Vector3(x,y,z)));
        }

        //read material
        else if (strcmp(command, "material\r") == 0) {
            float r, g, b;
            float phongExponent;
            float specularFraction;

            inputFile >> r >> g >> b; ++lineNum;
            inputFile >> phongExponent; ++lineNum;
            inputFile >> specularFraction; ++lineNum;

            inputFile.ignore(); //extract final newline

            //TODO
            //store current material setting
            MATERIAL.color = Color(r,g,b);
            MATERIAL.phong_exponent = phongExponent;
            MATERIAL.specular_fraction = specularFraction;
        }

        //read triangle
        else if (strcmp(command, "triangle\r") == 0) {
            float x1, y1, z1;
            float x2, y2, z2;
            float x3, y3, z3;

            inputFile >> x1 >> y1 >> z1; ++lineNum;
            inputFile >> x2 >> y2 >> z2; ++lineNum;
            inputFile >> x3 >> y3 >> z3; ++lineNum;

            inputFile.ignore(); //extract final newline

            triangles.push_back(triangle(MATERIAL.color, MATERIAL.phong_exponent, MATERIAL.specular_fraction, Vector3(x1, y1, z1), Vector3(x2, y2, z2), Vector3(x3, y3, z3) ));
        }

        //read sphere
        else if (strcmp(command, "sphere\r") == 0) {
            float x, y, z;
            float radius;

            inputFile >> x >> y >> z; ++lineNum;
            inputFile >> radius; ++lineNum;

            inputFile.ignore(); //extract final newline

            //TODO
            //add spheres
            circles.push_back(circle(MATERIAL.color, MATERIAL.phong_exponent, MATERIAL.specular_fraction, Vector3(x,y,z), radius));
        }

        else {
            cout << "Line " << lineNum << ": Unexpected command " << command << endl;
            inputFile.close();
            return 0;
        }
    }

    inputFile.close();

    return 1;
}
