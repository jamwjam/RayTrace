#include "view.h"
#include "vector3.h"

view::view()
{

}

view::view(Vector3 v, Vector3 up){
    this->v = v;
    this->up = up;
}

Vector3 view::getX(){
    Vector3 view_x = this->getView().cross(this->getUp());
    view_x.normalize();
    return view_x;
}

Vector3 view::getY(){
    return this->getZ().cross(this->getX());
}

Vector3 view::getZ(){
    return this->getView() * (-1);
}

view::~view()
{

}

