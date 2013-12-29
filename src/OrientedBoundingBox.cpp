#include <OrientedBoundingBox.h>

OrientedBoundingBox::OrientedBoundingBox(float radius)
{
    this->radius = radius;
}

OrientedBoundingBox::~OrientedBoundingBox()
{
    //dtor
}

bool OrientedBoundingBox::collidesWith(OrientedBoundingBox *otherObb, float distance){
    float sumOfTheRadiuses = this->radius + otherObb->radius;
    if (distance < sumOfTheRadiuses) return true;
    return false;
}
