#include <iostream>
#include <GLTools.h>
#include <GL/freeglut.h>
#include <cmath>

#include <Utils.h>
#include <Wizard.h>
#include <Spell.h>

Wizard::Wizard(int initialHealth, string name, float distanceToCenter, Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin):
    Actor(scene, model, frame, origin)
{
    this->health = initialHealth;
    this->name = name;
    this->distanceToCenter = distanceToCenter;
    Actor::setVelocity(0.2f, 0.2f, 0.2f);

    spells = new vector<Spell *>();
    memset(toCast, 0, MAX_SPELLS * sizeof(bool));
    memset(casting, 0, MAX_SPELLS * sizeof(bool));
}

Wizard::~Wizard(){

}

void Wizard::addSpell(Spell *s){
    M3DVector3f wizForwardVector;
    M3DVector3f wizUpVector;

    GLFrame *spellFrame;

    frame->GetForwardVector(wizForwardVector);
    frame->GetUpVector(wizUpVector);

    spellFrame = s->getFrame();
    spellFrame->SetForwardVector(wizForwardVector);
    spellFrame->SetUpVector(wizUpVector);

    spells->push_back(s);
}

void Wizard::cast(int index){
    // TODO
    toCast[index] = true;
    casting[index] = false;
}

void Wizard::render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp){
    float diff = 0.0f;
    GLFrame *camFrame = scene->getCamera()->getFrame();
    M3DVector3f origin = {0.0f, 0.0f, 0.0f};
    M3DVector3f fv;
    M3DVector3f camFv;
    M3DVector3f wizardOrigin;
    M3DVector3f camOrigin;
    Spell *currentSpell;

    frame->GetOrigin(wizardOrigin);
    frame->WorldToLocal(origin, fv);
    camFrame->WorldToLocal(origin, camFv);
    m3dNormalizeVector3(fv);

    mvm->PushMatrix();
    mvm->MultMatrix(*frame);

    float linearSpeed = m3dGetMagnitude3(velocity);

    if (keyPressed[Interactive::KEY_RIGHT_INDEX]){
        frame->MoveRight(-linearSpeed);
        camFrame->MoveRight(-linearSpeed);
        diff = sqrt( pow(linearSpeed, 2) + pow(distanceToCenter, 2) ) - distanceToCenter;
        cout << "Offset: " << diff << "\n";
    }
    if (keyPressed[Interactive::KEY_LEFT_INDEX]){
        frame->MoveRight(linearSpeed);
        camFrame->MoveRight(linearSpeed);
    }
    if (keyPressed[Interactive::KEY_UP_INDEX]){
        frame->MoveForward(linearSpeed);
    }
    if (keyPressed[Interactive::KEY_DOWN_INDEX]){
        frame->MoveForward(-linearSpeed);
    }

    frame->SetForwardVector(fv[0], fv[2], fv[1]);
    frame->GetOrigin(wizardOrigin); // Get new wiz position
    camFrame->GetOrigin(camOrigin); // Get new cam position
    m3dSubtractVectors3(camFv, wizardOrigin, camOrigin);
    frame->MoveForward(diff);

    M3DVector4f color = {0.0f, 0.0f, 1.0f, 1.0f};

    // Draw
    sm->UseStockShader(GLT_SHADER_FLAT,
		tp->GetModelViewProjectionMatrix(), color);

    model->Draw();

    mvm->PopMatrix();

    // Render spells
    for (int i = 0; i < spells->size(); i++){
        if (toCast[i]){
            // Render the spell
            currentSpell = spells->at(i);
            if (!casting[i]){ // only set the position if not already set
                currentSpell->setOrigin(wizardOrigin);
                casting[i] = true;
            }
            currentSpell->render(sm, mvm, pm, f, tp);
        }
    }

}

void Wizard::onSpecialKeyPressed(int key, int x, int y) {
    Interactive::onSpecialKeyPressed(key, x, y);
    switch(key){
        case GLUT_KEY_RIGHT:
            // TODO: set movinaag direction to true
            break;

        case GLUT_KEY_LEFT:
            // TODO: move along the circle
            break;

        case GLUT_KEY_SHIFT_R:
            clearSpellBuffer();
            break;
    }
}

void Wizard::onSpecialKeyReleased(int key, int x, int y){
    Interactive::onSpecialKeyReleased(key, x, y);
    switch(key){
        case GLUT_KEY_RIGHT:
            // TODO: set moving direction to true
            break;

        case GLUT_KEY_LEFT:
            // TODO: move along the circle
            break;
    }
}

void Wizard::onKeyPressed(char key, int x, int y){
    addCharToBuffer(key);
    for (std::vector<Spell *>::iterator s = spells->begin(); s != spells->end(); ++s){
        if ((*s)->getName() == spellBuffer){
            cout << "Casting " << s - spells->begin() << " - " << (*s)->getName() << "\n";
            cast(s - spells->begin());
            clearSpellBuffer();
        }
    }
}

void Wizard::onKeyReleased(char key, int x, int y){}


void Wizard::clearSpellBuffer(){
    spellBuffer.erase(spellBuffer.begin(), spellBuffer.end());
}

void Wizard::addCharToBuffer(char c){
    spellBuffer.push_back(c);
}

