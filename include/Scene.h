#ifndef SCENE_H
#define SCENE_H

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#include <vector>

#define TOTAL_KEYS 4

#define ARROW_LEFT 0
#define ARROW_UP 1
#define ARROW_RIGHT 2
#define ARROW_DOWN 3

class Actor;

class Scene {

public:
	// Transformation pipeline and shaders manager
	GLShaderManager		shaderManager;			// Shader Manager
	GLMatrixStack		modelViewMatrix;		// Modelview Matrix
	GLMatrixStack		projectionMatrix;		// Projection Matrix
	GLFrustum			viewFrustum;			// View Frustum
	GLGeometryTransform	transformPipeline;		// Geometry Transform Pipeline

	// Actors metaphore
	GLFrame cameraFrame;
	std::vector<Actor *> *actors;
	GLBatch* stage;
	M3DVector4f lightPosition;
	GLfloat *color;

	// Graphics details
	float floorWidth;
	float floorHeight;
	float floorY;
	int windowW, windowH;
	float lastMouseXY[2];
	bool keyPressed[TOTAL_KEYS];
	static const float cameraStep = 0.5f;

	Scene(M3DVector4f lightPosition, GLfloat *color, float floorWidth, float floorHeight);
	~Scene();

	void render();
	void addActor(Actor *a);
	void hideActor(Actor *a);
	void showActor(Actor *a);
	void reshape(int newW, int newH);
	void mouseMove(int x, int y);
	void specialKey(int key, int x, int y, bool released);
	void moveCamera();
	void setKeyPressed(int key, int x, int y, bool released);

};

#endif
