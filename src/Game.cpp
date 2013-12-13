#include <GLTools.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>

#include <Scene.h>
#include <Actor.h>
#include <Wizard.h>

#define NUM_OF_PLAYERS 2

// Describe the scene
void reshapeFunc(int newW, int newH);
void renderFunc();
void mouseMove(int x, int y);
void specialKey(int key, int x, int y);
void specialUpKey(int key, int x, int y);
void keyFunc(unsigned char key, int x, int y);
void keyUpFunc(unsigned char key, int x, int y);

Scene *scene;

// Main
int main(int argc, char **argv){

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Initialize GLUT and GLEW
	gltSetWorkingDirectory(argv[0]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Spell Checkers");
	glutReshapeFunc(reshapeFunc);
	glutDisplayFunc(renderFunc);
	glutPassiveMotionFunc(mouseMove);
	glutSpecialFunc(specialKey);
	glutSpecialUpFunc(specialUpKey);
	glutKeyboardFunc(keyFunc);
	glutKeyboardUpFunc(keyUpFunc);

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	// Build a scene
	GLFrame *cameraFrame = new GLFrame();
	GLFrame *stageFrame = new GLFrame();
    M3DVector3f cameraOrigin = {0.0f, 0.0f, 0.0f};
    M3DVector3f stageOrigin = {0.0f, 0.0f, -30.0f};
    GLTriangleBatch *stageModel = new GLTriangleBatch();
    gltMakeDisk(*stageModel, 5.0f, 10.0f, 20, 20);
    stageFrame->RotateLocalX(1.0f);

	scene = new Scene();
    Camera *camera = new Camera(scene, cameraFrame, cameraOrigin);
    Stage *stage = new Stage(scene, stageModel, stageFrame, stageOrigin);
    stage->setOrigin(stageOrigin);
    scene->setCamera(camera);
    scene->setStage(stage);

	// Start GLUT main loop
	glutMainLoop();

	// Cleanup

	return 0;
}

void reshapeFunc(int newW, int newH){
    glViewport(0, 0, newW, newH);
	// Center the cursor
	glutWarpPointer(newW/2, newH/2);
	scene->reshape(newW, newH);
}

void renderFunc(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->render();

	glutSwapBuffers();
	glutPostRedisplay();
}

void mouseMove(int x, int y){
}

void keyFunc(unsigned char key, int x, int y){
}

void keyUpFunc(unsigned char key, int x, int y){
}

void specialKey(int key, int x, int y){
}

void specialUpKey(int key, int x, int y){
}
