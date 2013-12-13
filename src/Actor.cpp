#include <Actor.h>

Actor::Actor(Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin){
    this->scene = scene;
    this->model = model;
    this->frame = frame;
    memcpy(this->position, origin, 3*sizeof(float));
}

Actor::~Actor(){
    delete frame;
    delete model;
}

void Actor::render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp){

}

void Actor::lookAt(M3DVector3f location){

}

void Actor::getLookAt(M3DVector3f destination){
    frame->GetForwardVector(destination);
}

void Actor::setOrigin(M3DVector3f position){
    frame->SetOrigin(position);
}

GLFrame *Actor::getFrame(){
    return frame;
}
