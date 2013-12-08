#include <Wizard.h>
#include <iostream>

Wizard::Wizard(Scene *scene, int id) : Actor(scene, id) {

	// Let's build the batch proportionally
	float floorSide = scene->floorWidth;
	float floorY = scene->floorY;
	float scale = 10.0f;

	height = floorSide/5.0f;
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 1.0f;
	color[3] = 1.0f;

	// Build and store model (depending on the frame origin)
	model = new GLTriangleBatch();
	gltMakeCylinder(*model, floorSide/scale, floorSide/scale, height, 20, 10);

	// Build and store frame
	frame = new GLFrame();
	frame->SetUpVector(0.0f, 0.0f, 1.0f);
	frame->SetForwardVector(0.0f, 1.0f, 0.0f);
}

Wizard::~Wizard(){
	// TODO
}

void Wizard::render(){

	(scene->modelViewMatrix).PushMatrix();
	(scene->modelViewMatrix).MultMatrix(*frame);

	(scene->shaderManager).UseStockShader(GLT_SHADER_FLAT,
		(scene->transformPipeline).GetModelViewProjectionMatrix(), color);
	model->Draw();

	(scene->modelViewMatrix).PopMatrix();
}

void Wizard::setModel(GLBatch *model){
	// TODO
}

void Wizard::setFrame(GLFrame *frame){
	// TODO
}

void Wizard::setOrigin(float x, float y, float z){
	frame->SetOrigin(x, y, z);
}