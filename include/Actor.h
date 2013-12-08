#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>

#ifndef ACTOR_H
#define ACTOR_H

class Scene;

class Actor {

	protected:
		int id;
		GLFrame* frame;
		GLTriangleBatch* model;
		Scene* scene;

	public:
		Actor(Scene *scene, int id);
		~Actor();

		virtual void render() = 0;
		virtual void setModel(GLBatch *model) = 0;
		virtual void setFrame(GLFrame *frame) = 0;

};

#endif