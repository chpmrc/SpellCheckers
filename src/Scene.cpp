#include <iostream>
#include <Actor.h>
#include <Scene.h>

using std::cerr;

Scene::Scene(){
    shaderManager = new GLShaderManager();
    modelViewMatrix = new GLMatrixStack();
    projectionMatrix = new GLMatrixStack();
    viewFrustum = new GLFrustum();
    transformPipeline = new GLGeometryTransform();

    shaderManager->InitializeStockShaders();
}

Scene::~Scene(){}

void Scene::addActor(Actor *a){}

void Scene::addInteractive(Interactive *i){}

void Scene::removeActor(Actor *a){}

void Scene::removeInteractive(Interactive *i){}

void Scene::showActor(Actor *a){}

void Scene::hideActor(Actor *a){}

void Scene::setCamera(Camera *c){
    this->camera = c;
}

void Scene::setStage(Stage *s){
    this->stage = s;
}

void Scene::render(){
    if (camera == NULL || stage == NULL){
        cerr << "ERROR: You cannot render a scene without a camera and a stage\n";
    }

    // Render the camera and the stage
    modelViewMatrix->PushMatrix();
    M3DMatrix44f cameraMatrix;
    (camera->getFrame())->GetCameraMatrix(cameraMatrix);

    modelViewMatrix->PushMatrix(cameraMatrix);

    stage->render(shaderManager, modelViewMatrix, projectionMatrix, viewFrustum, transformPipeline);

    modelViewMatrix->PopMatrix();
    modelViewMatrix->PopMatrix(); // Remove camera matrix
}

void Scene::reshape(int newW, int newH){
    viewFrustum->SetPerspective(35.0f, float(newW)/float(newH), 1.0f, 1000.0f);
	projectionMatrix->LoadMatrix(viewFrustum->GetProjectionMatrix());
	transformPipeline->SetMatrixStacks(*modelViewMatrix, *projectionMatrix);
}
