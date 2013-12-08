#ifndef WIZARD_H
#define WIZARD_H

#include <Actor.h>
#include <Scene.h>

class Wizard : public Actor {
	// TODO

	float height;
	M3DVector4f color;

public:
	Wizard(Scene *scene, int id);
	~Wizard();

	void render();
	void setModel(GLBatch *model);
	void setFrame(GLFrame *frame);
	void getOrigin();
	void setOrigin(float x, float y, float z);
};

#endif