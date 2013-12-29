#include <Spell.h>
#include <Scene.h>
#include <iostream>

Spell::Spell(string name, int damage, Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin) :
    Actor(scene, model, frame, origin)
{
    this->name = name;
    this->damage = damage;
    m3dLoadVector3(velocity, 0.0f, 0.0f, 10.0f);
    m3dLoadVector3(color, 0.0f, 1.0f, 0.0f);
}

Spell::~Spell(){}

int Spell::getDamage(){
    return damage;
}

string Spell::getName(){
    return name;
}

void Spell::setColor(float r, float g, float b){
    color[0] = r;
    color[1] = g;
    color[2] = b;
}

void Spell::render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp){

    float dt = scene->getTimeFromLastFrame();
    float step = velocity[2] * dt;
    bool collision = false;

    // std::cout << "Rendering " << name << ", elapsed time: " << dt << ", stepSize: " << step << "\n";

    frame->MoveForward(step);

    mvm->PushMatrix();
    mvm->MultMatrix(*frame);

    sm->UseStockShader(GLT_SHADER_FLAT, tp->GetModelViewProjectionMatrix(), color);
    model->Draw();

    mvm->PopMatrix();

    // Detect collisions
    for (std::vector<Actor *>::iterator c = colliders->begin(); c != colliders->end(); ++c){
        if (Actor::areColliding(this, (*c))){
            std::cout << "COLLISION DETECTED!\n";
        }
    }

}
