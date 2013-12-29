#include <iostream>
#include <Actor.h>
#include <Scene.h>

using std::cerr;
using std::vector;

Scene::Scene(){
    shaderManager = new GLShaderManager();
    modelViewMatrix = new GLMatrixStack();
    projectionMatrix = new GLMatrixStack();
    viewFrustum = new GLFrustum();
    transformPipeline = new GLGeometryTransform();

    shaderManager->InitializeStockShaders();

    actors = new vector<Actor *>();
    interactives = new vector<Interactive *>();

    // Physics
    time = 0.0f;
    deltaTime = 0.0f;
}

Scene::~Scene(){}

void Scene::addActor(Actor *a){
    actors->push_back(a);
}

void Scene::addInteractive(Interactive *i){
    interactives->push_back(i);
}

void Scene::removeActor(Actor *a){}

void Scene::removeInteractive(Interactive *i){}

void Scene::showActor(Actor *a){}

void Scene::hideActor(Actor *a){}

void Scene::setCamera(Camera *c){
    this->camera = c;
}

Camera *Scene::getCamera(){
    return camera;
}

void Scene::setStage(Stage *s){
    this->stage = s;
}

void Scene::render(){
    if (camera == NULL || stage == NULL){
        cerr << "ERROR: You cannot render a scene without a camera and a stage\n";
    }

    float currentTime = getTime();
    deltaTime = currentTime - time;
    time = getTime();

    // Render the camera and the stage
    modelViewMatrix->PushMatrix();
    M3DMatrix44f cameraMatrix;
    (camera->getFrame())->GetCameraMatrix(cameraMatrix);

    modelViewMatrix->PushMatrix(cameraMatrix);

    stage->render(shaderManager, modelViewMatrix, projectionMatrix, viewFrustum, transformPipeline);

    for (std::vector<Actor *>::iterator a = actors->begin(); a != actors->end(); ++a){
        (*a)->render(shaderManager, modelViewMatrix, projectionMatrix, viewFrustum, transformPipeline);
    }

    modelViewMatrix->PopMatrix();
    modelViewMatrix->PopMatrix(); // Remove camera matrix
}

float Scene::getTime(){
    static CStopWatch timer;
    return timer.GetElapsedSeconds();
}

float Scene::getTimeFromLastFrame(){
    return deltaTime;
}

void Scene::reshape(int newW, int newH){
    viewFrustum->SetPerspective(35.0f, float(newW)/float(newH), 1.0f, 1000.0f);
	projectionMatrix->LoadMatrix(viewFrustum->GetProjectionMatrix());
	transformPipeline->SetMatrixStacks(*modelViewMatrix, *projectionMatrix);
}

// Interaction methods
void Scene::onKeyPressed(char key, int x, int y){
    for (std::vector<Interactive *>::iterator i = interactives->begin(); i != interactives->end(); ++i){
        (*i)->onKeyPressed(key, x, y);
    }
}

void Scene::onKeyReleased(char key, int x, int y){
    for (std::vector<Interactive *>::iterator i = interactives->begin(); i != interactives->end(); ++i){
        (*i)->onKeyReleased(key, x, y);
    }
}

void Scene::onSpecialKeyPressed(int key, int x, int y){
    for (std::vector<Interactive *>::iterator i = interactives->begin(); i != interactives->end(); ++i){
        (*i)->onSpecialKeyPressed(key, x, y);
    }
}

void Scene::onSpecialKeyReleased(int key, int x, int y){
    for (std::vector<Interactive *>::iterator i = interactives->begin(); i != interactives->end(); ++i){
        (*i)->onSpecialKeyReleased(key, x, y);
    }
}
