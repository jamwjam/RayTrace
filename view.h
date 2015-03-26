#ifndef VIEW_H
#define VIEW_H
#include "vector3.h"

class view
{
public:
    view();
    view(Vector3 view, Vector3 up);
    ~view();
    Vector3 getX();
    Vector3 getY();
    Vector3 getZ();
    const Vector3 &getUp() const {return up;}
    const Vector3 &getView() const {return v;}

private:
    Vector3 v;
    Vector3 up;
};

#endif // VIEW_H
