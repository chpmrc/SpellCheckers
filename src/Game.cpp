#include <GLTools.h>
#include <GL/freeglut.h>
#include <vector>
#include <iostream>

#include <Scene.h>
#include <Actor.h>
#include <Wizard.h>
#include <Spell.h>
#include <OrientedBoundingBox.h>

#define NUM_OF_PLAYERS 2

// Global variables
const float distanceToCenter = 7.5f;
const float spellRadius = 0.4f;
const float wizardRadius = 1.0f;

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

    // Frames
	GLFrame *cameraFrame = new GLFrame();
	// Correctly orient the camera
	cameraFrame->SetForwardVector(0.0f, 1.0f, 0.0f);
	cameraFrame->SetUpVector(0.0f, 0.0f, -1.0f);
	GLFrame *stageFrame = new GLFrame();
	GLFrame *firstWizardFrame = new GLFrame();
	// Correctly orient the first wizard
	firstWizardFrame->SetForwardVector(0.0f, 1.0f, 0.0f);
	firstWizardFrame->SetUpVector(0.0f, 0.0f, -1.0f);
	GLFrame *secondWizardFrame = new GLFrame();
	// Correctly orient the second wizard (facing the first one)
	secondWizardFrame->SetForwardVector(0.0f, -1.0f, 0.0f);
	secondWizardFrame->SetUpVector(0.0f, 0.0f, -1.0f);
	GLFrame *fireSpellFrame = new GLFrame();
	GLFrame *waterSpellFrame = new GLFrame();
	fireSpellFrame->SetForwardVector(0.0f, -1.0f, 0.0f);
	fireSpellFrame->SetUpVector(0.0f, 0.0f, -1.0f);
	waterSpellFrame->SetForwardVector(0.0f, -1.0f, 0.0f);
	waterSpellFrame->SetUpVector(0.0f, 0.0f, -1.0f);

	// Origins
    M3DVector3f cameraOrigin = {0.0f, 0.0f, 0.0f};
    M3DVector3f stageOrigin = {0.0f, 0.0f, 0.0f};
    M3DVector3f firstWizardOrigin = {0.0f, -distanceToCenter, 0.0f};
    M3DVector3f secondWizardOrigin = {0.0f, distanceToCenter, 0.0f};

    // Models
    GLTriangleBatch *stageModel = new GLTriangleBatch();
    GLTriangleBatch *wizardModel = new GLTriangleBatch();
    GLTriangleBatch *spellModel = new GLTriangleBatch();

    // Models creation
    gltMakeDisk(*stageModel, 5.0f, 10.0f, 20, 20);
    gltMakeSphere(*wizardModel, wizardRadius, 20, 20);
    gltMakeSphere(*spellModel, spellRadius, 10, 10);

    // Building the scene
	scene = new Scene();

    Camera *camera = new Camera(scene, cameraFrame, cameraOrigin);
    Stage *stage = new Stage(scene, stageModel, stageFrame, stageOrigin);
    stage->setOrigin(stageOrigin);

    string firstWizardName = "Marco";
    string secondWizardName = "Simone";
    Wizard *firstWizard = new Wizard(100, firstWizardName, distanceToCenter, scene, wizardModel, firstWizardFrame, firstWizardOrigin);
    Wizard *secondWizard = new Wizard(100, secondWizardName, distanceToCenter, scene, wizardModel, secondWizardFrame, secondWizardOrigin);

    firstWizard->setOrigin(firstWizardOrigin);
    secondWizard->setOrigin(secondWizardOrigin);

    scene->setCamera(camera);
    scene->setStage(stage);
    scene->addActor(firstWizard);
    scene->addActor(secondWizard);

    OrientedBoundingBox *firstWizardObb = new OrientedBoundingBox(wizardRadius);
    firstWizard->setBoundingBox(firstWizardObb);

    OrientedBoundingBox *secondWizardObb = new OrientedBoundingBox(wizardRadius);
    secondWizard->setBoundingBox(secondWizardObb);


    // Add local controlled actors
    scene->addInteractive(firstWizard);

    // Build spells
    Spell *fire = new Spell("fire", 10, scene, spellModel, fireSpellFrame, firstWizardOrigin);
    fire->setColor(1.0f, 0.5f, 0.0f);
    Spell *water = new Spell("water", 5, scene, spellModel, waterSpellFrame, firstWizardOrigin);
    water->setColor(0.0f, 0.2f, 1.0f);
    water->setVelocity(0.0f, 0.0f, 30.0f);
    firstWizard->addSpell(fire);
    firstWizard->addSpell(water);

    // Set bounding boxes
    OrientedBoundingBox *spellObb = new OrientedBoundingBox(spellRadius);
    fire->setBoundingBox(spellObb);
    water->setBoundingBox(spellObb);

    // Initialize collision detection system
    fire->addCollider(secondWizard);
    water->addCollider(secondWizard);

    // Initial transformations
    cameraFrame->RotateWorld(1.0f, 1, 0, 0); // Rotate 90 degrees
    cameraFrame->TranslateLocal(0.0f, 0.0f, -30.0f); // Move everything in the visible space

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
    scene->onKeyPressed(key, x, y);
}

void keyUpFunc(unsigned char key, int x, int y){
    scene->onKeyReleased(key, x, y);
}

void specialKey(int key, int x, int y){
    scene->onSpecialKeyPressed(key, x, y);
}

void specialUpKey(int key, int x, int y){
    scene->onSpecialKeyReleased(key, x, y);
}
