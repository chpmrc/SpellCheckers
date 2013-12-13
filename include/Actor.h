#ifndef ACTOR_H
#define ACTOR_H

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

class Scene;

class Actor {

	protected:
		Scene* scene;

		GLFrame* frame;
		GLTriangleBatch* model;
        M3DVector3f position;


	public:
		Actor(Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin);
		~Actor();

		virtual void render(GLShaderManager *shaderManager, GLMatrixStack *modelViewMatrix, GLMatrixStack *projectionMatrix,
                    GLFrustum *viewFrustum, GLGeometryTransform *transformPipeline);
        virtual void lookAt(M3DVector3f location);
        virtual void getLookAt(M3DVector3f destination); // Just return the forward vector of the frame
        virtual void setOrigin(M3DVector3f position);
        virtual GLFrame *getFrame();
};

#endif
