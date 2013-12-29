#include <Actor.h>
#include <OrientedBoundingBox.h>

Actor::Actor(Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin){
    this->scene = scene;
    this->model = model;
    this->frame = frame;
    memcpy(this->position, origin, 3 * sizeof(float));
    m3dLoadVector3(this->velocity, 0.0f, 0.0f, 0.0f); // Actor is static by default
    colliders = new std::vector<Actor *>();
}

Actor::~Actor(){
    delete frame;
    delete model;
}

void Actor::render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp){

}

void Actor::lookAt(M3DVector3f location){
    frame->SetForwardVector(location);
}

void Actor::getLookAt(M3DVector3f destination){
    frame->GetForwardVector(destination);
}

void Actor::setOrigin(M3DVector3f position){
    frame->SetOrigin(position);
}

void Actor::getOrigin(M3DVector3f position){
    M3DVector3f curPos;
    frame->GetOrigin(curPos);
    memcpy(position, curPos, sizeof(M3DVector3f));
}

GLFrame *Actor::getFrame(){
    return frame;
}

void Actor::setVelocity(float x, float y, float z){
    velocity[0] = x;
    velocity[1] = y;
    velocity[2] = z;
}

void Actor::move(M3DVector3f from, int steps, char axis){

}

void Actor::addCollider(Actor *c){
    colliders->push_back(c);
}

bool Actor::areColliding(Actor *a1, Actor *a2){
    M3DVector3f pos1, pos2;
    a1->getFrame()->GetOrigin(pos1);
    a2->getFrame()->GetOrigin(pos2);
    float distance = m3dGetDistance3(pos1, pos2);
    if (a1->obb != NULL && a2->obb != NULL && a1->obb->collidesWith(a2->obb, distance)){
        return true;
    }
    return false;
}

void Actor::setBoundingBox(OrientedBoundingBox *o){
    this->obb = o;
}
