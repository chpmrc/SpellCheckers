#include <iostream>

#include <Wizard.h>
#include <Spell.h>

Wizard::Wizard(int initialHealth, string name, Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin):
    Actor(scene, model, frame, origin)
{

}

Wizard::~Wizard(){

}

void Wizard::cast(Spell *s){

}
