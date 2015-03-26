#include <stdlib.h>
#include <iostream>

#include "BMPImage.h"
#include "scene.h"
#include "view.h"

using namespace std;

struct ray {
    Vector3 position; // Position vector
    Vector3 direction;    // Direction vector
    float t_0;    // Distance at which Ray intersects. Infinity if it doesnt
} RAY;

void pnl(){
    printf("\n");
}

double triangleIntersect(triangle triangle, unsigned long row, unsigned long col, BMPImage &theImage, ray &ray){
        if (ray.position.dot(triangle.getNormal()) == 0){
            // Intersection is not happening
            return -1;
        }

        Vector3 intersect;
        Vector3 normal = triangle.getNormal();
        Color color = triangle.getColor();

        double d = ray.position.dot(normal);
        double t_0 = -(normal.dot(triangle.getA() - RAY.position) + d) / (RAY.direction.dot(normal));
        double scalarAB, scalarBC, scalarCA;

        intersect = ray.direction * t_0 + RAY.position;

        scalarAB = (triangle.getAB().cross(intersect - triangle.getA())).dot(normal);
        scalarBC = (triangle.getBC().cross(intersect - triangle.getB())).dot(normal);
        scalarCA = (triangle.getCA().cross(intersect - triangle.getC())).dot(normal);

        if(scalarAB >= 0 && scalarBC >= 0 && scalarCA >= 0){
            return 1;
        } else {
            return -1;
        }
}

double sphereIntersect(circle currSphere, unsigned long row, unsigned long col, BMPImage &theImage, ray &ray){

        Color color = currSphere.getColor();
        Vector3 w = currSphere.getC() - ray.position;

        double a = ray.direction.dot(ray.direction);
        double b = -2 * ray.direction.dot(w);
        double c = w.dot(w) - pow(currSphere.getRadius(),2);

        double delta = (b*b) - (4*a*c);

        if ( delta > 0) {
            // Check rather ray originate inside or outside the sphere
            double sign = (c < -0.00001) ? -1 : 1;
            double distance = (-b + sign*(delta*delta))/(2*a);

            if(distance < ray.t_0 && distance > 0.0){
                ray.t_0 = distance;
                theImage.writePixel(row, col, color.getR(), color.getG(), color.getB());
            }

            return 1;
        } else {
            return -1;
        }
}

//argv[0] - program name
//argv[1] - scene file name
//argv[2] - image file name
//argv[3] - image pixel width
//argv[4] - image pixel height
int main (int argc, char** argv) {
	if (argc != 5) {
		cout << "Usage: " << argv[0] << " inputFile outputFile imageWidth imageHeight" << endl;
		return 1;
	}

	int imageWidth = atoi(argv[3]);
	int imageHeight = atoi(argv[4]);

	Scene theScene;
	if (theScene.parse(argv[1]) != 1) {
		return 1;
	}

	BMPImage theImage(imageWidth, imageHeight);

	//TODO
	//raytrace the scene
    long n_rows = theImage.getXSize();
    long n_cols = theImage.getYSize();

    double theta_Y = (M_PI * theScene.getFieldOfViewY()) / 180.0;
    double aspectRatio = (double) n_rows / n_cols;
    double height = tan(theta_Y/2.0);
    double width = height * aspectRatio;

    printf("aspect ratio: %f \n", aspectRatio);
    printf("width: %f, height: %f, theta_y: %f\n", width, height, theta_Y);

    double a_x, a_y;
    int row, col;

    Vector3 view_x, view_y, view_z, p_rc, u_rc;
    Vector3 eye = theScene.getEyePosition();

    std::vector<triangle> triangles = theScene.getTriangles();
    std::vector<circle> circles = theScene.getCircles();
    Color color;

    view_z = theScene.getEyeDirection() * -1;

    view_x = theScene.getEyeDirection().cross(theScene.getEyeUp());
    view_x.normalize();

    view_y = view_z.cross(view_x);

    printf("View x: %f, %f, %f\n", view_x.getX(), view_x.getY(), view_x.getZ());
    printf("View y: %f, %f, %f\n", view_y.getX(), view_y.getY(), view_y.getZ());
    printf("View z: %f, %f, %f\n", view_z.getX(), view_z.getY(), view_z.getZ());

    for (row = 0; row < n_rows; row++){
        for (col = 0; col < n_cols; col++){
            // [-h/2, h/2]
            a_y = -height * ((double)row/n_rows - .5);

            // [-w/2, w/2]
            a_x = width * ((double)col/n_cols - .5);
            //printf("a_x: %f, a_y: %f\n", a_x, a_y);

            // p_rc + t * u_rc (p + tu, representation of ray)
            p_rc = eye + (view_x * a_x) + (view_y * a_y) - view_z;
            //printf("Position:(%f,%f,%f)\n", p_rc.getX(), p_rc.getY(), p_rc.getZ());

            u_rc = (p_rc - eye);
            u_rc.normalize();

            RAY.position = p_rc;
            RAY.direction = u_rc;
            RAY.t_0 = INFINITY;

            /* Ray-Sphere Interception */
            /* Dealing with multiple spheres */
            for (unsigned long i=0; i<circles.size(); i++) {
                if(sphereIntersect(circles[i], row, col, theImage, RAY) > 0){
                    color = circles[i].getColor() * theScene.getAmbientLight();
                    theImage.writePixel(row,col, color.getR(), color.getG(), color.getB());
                }
            }

            /* Ray-Triangle Intersection */
            /* Dealing with multiple triangles */
            for (unsigned long i=0; i<triangles.size(); i++) {
                if(triangleIntersect(triangles[i], row, col, theImage, RAY) > 0){
                     color = triangles[i].getColor() * theScene.getAmbientLight();
                     theImage.writePixel(row,col, color.getR(), color.getG(), color.getB());
                }
             }
        }
    }


	if (theImage.save(argv[2]) != 1) {
		return 1;
	}

	return 0;
}

