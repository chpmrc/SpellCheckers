#ifndef WIZARD_H
#define WIZARD_H

#include <string>

#include <Actor.h>
#include <Scene.h>

using std::string;

class Spell;

class Wizard : public Actor {
private:
    int health;
    string name;
    vector<Spell *> *spells;

public:
	Wizard(int initialHealth, string name, Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin);
	~Wizard();

    void cast(Spell *s);
};

#endif
