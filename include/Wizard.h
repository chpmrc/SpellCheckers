#ifndef WIZARD_H
#define WIZARD_H

#include <string>

#include <Actor.h>
#include <Scene.h>

#define MAX_SPELLS 10

using std::string;

class Spell;

class Wizard : public Actor, public Interactive {
private:
    int health;
    string name;
    vector<Spell *> *spells;
    string spellBuffer;
    bool toCast[MAX_SPELLS];
    bool casting[MAX_SPELLS];

    float distanceToCenter;

public:
	Wizard(int initialHealth, string name, float distanceToCenter, Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin);
	~Wizard();

    void addSpell(Spell *s);
    void cast(int index);
    void render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp);

    void onKeyPressed(char key, int x, int y);
    void onKeyReleased(char key, int x, int y);
    void onSpecialKeyPressed(int key, int x, int y);
    void onSpecialKeyReleased(int key, int x, int y);

    void clearSpellBuffer();
    void addCharToBuffer(char c);

};

#endif
