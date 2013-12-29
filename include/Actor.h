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
#include <vector>

class Scene;
class OrientedBoundingBox;

class Actor {

	protected:
		Scene* scene;
		GLFrame* frame;
		GLTriangleBatch *model;
        OrientedBoundingBox *obb; // NULL by default, not collideable

		std::vector<Actor *> *colliders;

        // Physics
        M3DVector3f velocity;
        M3DVector3f position;

	public:
		Actor(Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin);
		~Actor();

		virtual void render(GLShaderManager *shaderManager, GLMatrixStack *modelViewMatrix, GLMatrixStack *projectionMatrix,
                    GLFrustum *viewFrustum, GLGeometryTransform *transformPipeline);
        virtual void lookAt(M3DVector3f location);
        virtual void getLookAt(M3DVector3f destination); // Just return the forward vector of the frame
        virtual void setOrigin(M3DVector3f position);
        virtual void getOrigin(M3DVector3f position);
        virtual GLFrame *getFrame();
        virtual void setVelocity(float x, float y, float z);
        virtual void move(M3DVector3f from, int steps, char axis); // axis == 0 | 1 | 2, (x | y | z - local)

        // Collision detection
        virtual void addCollider(Actor *c);
        virtual bool areColliding(Actor *a1, Actor *a2);
        void setBoundingBox(OrientedBoundingBox *o);
};

#endif
