#include <Scene.h>
#include <iostream>
#include <Actor.h>

Scene::Scene(M3DVector4f lightPosition, GLfloat *color, float floorWidth, float floorHeight){

	floorY = -2.0f; // Default value

	// Build the stage
	stage = new GLBatch();
	stage->Begin(GL_QUADS, 4);
	stage->Vertex3f(floorWidth/2, floorY, 0.0f);
	stage->Vertex3f(floorWidth/2,  floorY, -floorHeight*2);
	stage->Vertex3f(-floorWidth/2,  floorY, -floorHeight*2);
	stage->Vertex3f(-floorWidth/2, floorY, 0.0f);
	stage->End();

	this->color = color;

	for (int i = 0; i < 4; i++){
		this->lightPosition[i] = lightPosition[i];
	}

	shaderManager.InitializeStockShaders();
	actors = new std::vector<Actor *>();

}

Scene::~Scene(){
	// TODO
}

void Scene::render(){

	modelViewMatrix.PushMatrix();

	// Move camera according to user's input
	moveCamera();

	// Set the camera viewpoint
	M3DMatrix44f mCamera;
    cameraFrame.GetCameraMatrix(mCamera);
    modelViewMatrix.PushMatrix(mCamera);

	shaderManager.UseStockShader(GLT_SHADER_FLAT,
		transformPipeline.GetModelViewProjectionMatrix(),
		color);
	stage->Draw();

	// Render actors
	for (std::vector<Actor *>::iterator it = actors->begin() ; it != actors->end(); ++it){
		(*it)->render();
	}

	modelViewMatrix.PopMatrix();
	modelViewMatrix.PopMatrix(); // Identity	
}

void Scene::reshape(int newW, int newH){

	windowW = newW;
	windowH = newH;

	// Save mouse coordinates
	lastMouseXY[0] = windowW/2;
	lastMouseXY[1] = windowH/2;

	glViewport(0, 0, newW, newH);
	
    // Create the projection matrix, and load it on the projection matrix stack
	viewFrustum.SetPerspective(35.0f, float(newW)/float(newH), 1.0f, 100.0f);
	projectionMatrix.LoadMatrix(viewFrustum.GetProjectionMatrix());

    // Set the transformation pipeline to use the two matrix stacks 
	transformPipeline.SetMatrixStacks(modelViewMatrix, projectionMatrix);

}

void Scene::mouseMove(int x, int y){

	int deltaX = x - lastMouseXY[0];
	int deltaY = y - lastMouseXY[1];

	lastMouseXY[0] = x;
	lastMouseXY[1] = y;

	float angularX = float(m3dDegToRad(deltaX/5.0f));
	float angularY = float(m3dDegToRad(deltaY/5.0f));

	cameraFrame.RotateWorld(-angularX, 0.0f, 1.0f, 0.0f);
	cameraFrame.RotateWorld(-angularY, 1.0f, 0.0f, 0.0f);

}

void Scene::specialKey(int key, int x, int y, bool released){
	std::cout << "Key pressed: " << key << "\n";
	setKeyPressed(key, x, y, released);
}

void Scene::addActor(Actor *a){
	if (a != NULL)
		actors->push_back(a);
}

void Scene::setKeyPressed(int key, int x, int y, bool released){
	switch(key){
		case 101:
			keyPressed[ARROW_UP] = !released; 
 			break;
		case 102:
			keyPressed[ARROW_RIGHT] = !released; 
			break;
		case 103:
			keyPressed[ARROW_DOWN] = !released; 
			break;
		case 100:
			keyPressed[ARROW_LEFT] = !released; 
			break;
	}
}

void Scene::moveCamera(){
	if (keyPressed[ARROW_UP]){
		cameraFrame.MoveForward(cameraStep);
	}
	if (keyPressed[ARROW_DOWN]){
		cameraFrame.MoveForward(-cameraStep);
	}
	if (keyPressed[ARROW_LEFT]){
		cameraFrame.MoveRight(cameraStep);
	}
	if (keyPressed[ARROW_RIGHT]){
		cameraFrame.MoveRight(-cameraStep);
	}
}