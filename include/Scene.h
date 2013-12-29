#ifndef SCENE_H
#define SCENE_H

#include <GLTools.h>
#include <GLShaderManager.h>
#include <GLFrustum.h>
#include <GLBatch.h>
#include <GLFrame.h>
#include <GLMatrixStack.h>
#include <GLGeometryTransform.h>
#include <StopWatch.h>
#include <vector>

#include <Actor.h>
#include <Camera.h>
#include <Stage.h>

using std::vector;
using std::iterator;

class Scene : public Interactive {

    private:
        Camera *camera;
        vector<Actor *> *actors;
        vector<Interactive *> *interactives;
        Stage *stage;

        // Transformation pipeline and shaders manager
        GLShaderManager		*shaderManager;			// Shader Manager
        GLMatrixStack		*modelViewMatrix;		// Modelview Matrix
        GLMatrixStack		*projectionMatrix;		// Projection Matrix
        GLFrustum			*viewFrustum;			// View Frustum
        GLGeometryTransform	*transformPipeline;		// Geometry Transform Pipeline

        // Physics
        float time;
        float deltaTime; // time between frames

    public:
        Scene();
        ~Scene();

        void addActor(Actor *a);
        void addInteractive(Interactive *i);
        void removeActor(Actor *a);
        void removeInteractive(Interactive *i);
        void showActor(Actor *a);
        void hideActor(Actor *a);
        void setCamera(Camera *c);
        Camera *getCamera();
        void setStage(Stage *s);
        void render();
        void reshape(int newW, int newH);
        float getTime();
        float getTimeFromLastFrame();

        void onKeyPressed(char key, int x, int y);
        void onKeyReleased(char key, int x, int y);
        void onSpecialKeyPressed(int key, int x, int y);
        void onSpecialKeyReleased(int key, int x, int y);
};

#endif
