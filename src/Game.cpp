#include <GLTools.h>
#include <GL/freeglut.h>
#include <vector>

#include <Scene.h>
#include <Actor.h>
#include <Wizard.h>

#define NUM_OF_PLAYERS 2

// Describe the scene
Scene *gameScene;
Wizard *wizards[NUM_OF_PLAYERS];
M3DVector4f vLightPos = { 0.0f, 10.0f, 5.0f, 1.0f };
GLfloat floorColor[] = {1.0f, 0.0f, 0.0f, 1.0f}; 
float floorWidth = 40.0f;
float floorHeight = 40.0f;

// Prototypes for GLUT
void reshapeFunc(int newW, int newH);
void renderFunc();
void mouseMove(int x, int y);
void specialKey(int key, int x, int y);
void specialUpKey(int key, int x, int y);

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

	GLenum err = glewInit();

	if (GLEW_OK != err) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		return 1;
	}

	// Build a scene
	gameScene = new Scene(vLightPos, floorColor, floorWidth, floorHeight);

		// wizards
	wizards[0] = new Wizard(gameScene, 0);

	wizards[0]->setOrigin(0.0f, -2.0f, -30.0f);

	gameScene->addActor(wizards[0]);

	wizards[1] = new Wizard(gameScene, 1);

	wizards[1]->setOrigin(0.0f, -2.0f, -5.0f);

	gameScene->addActor(wizards[1]);

		// spells

		// lights

	// Start GLUT main loop
	glutMainLoop();

	// Cleanup

	return 0;
}

void reshapeFunc(int newW, int newH){
	// Center the cursor
	glutWarpPointer(newW/2, newH/2);
	gameScene->reshape(newW, newH);
}

void renderFunc(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gameScene->render();
	glutSwapBuffers();
	glutPostRedisplay();
}

void mouseMove(int x, int y){
	// update deltaAngle
	gameScene->mouseMove(x, y);
	// glutWarpPointer(gameScene->windowW/2, gameScene->windowH/2);
}

void specialKey(int key, int x, int y){
	gameScene->specialKey(key, x, y, false);
}

void specialUpKey(int key, int x, int y){
	gameScene->specialKey(key, x, y, true);
}