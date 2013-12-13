#include <iostream>

#include <Stage.h>

using std::cout;

Stage::Stage(Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin) : Actor(scene, model, frame, origin)
{

}

Stage::~Stage()
{
    //dtor
}

void Stage::render(GLShaderManager *shaderManager, GLMatrixStack *modelViewMatrix, GLMatrixStack *projectionMatrix,
                    GLFrustum *viewFrustum, GLGeometryTransform *transformPipeline){
    modelViewMatrix->PushMatrix();
    modelViewMatrix->MultMatrix(*frame);

    M3DVector4f color = {1.0f, 0.0f, 0.0f, 1.0f};

    // Draw
    shaderManager->UseStockShader(GLT_SHADER_FLAT,
		transformPipeline->GetModelViewProjectionMatrix(), color);
    model->Draw();

    modelViewMatrix->PopMatrix();
}
