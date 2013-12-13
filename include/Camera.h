#ifndef CAMERA_H
#define CAMERA_H

#include <Actor.h>
#include <Interactive.h>

class Camera : public Actor
{
    public:
        Camera(Scene *scene, GLFrame *frame, M3DVector3f origin);
        virtual ~Camera();

    protected:
    private:
};

#endif // CAMERA_H
