#include <Camera.h>

Camera::Camera(Scene *scene, GLFrame *frame, M3DVector3f origin) : Actor(scene, NULL, frame, origin){
    GLFrame *noModel = NULL; // Do not render the camera
}

Camera::~Camera(){

}
