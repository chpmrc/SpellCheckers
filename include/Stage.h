#ifndef STAGE_H
#define STAGE_H

#include <Actor.h>

class Stage : public Actor
{
    public:
        Stage(Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin);
        virtual ~Stage();

        void render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp);
    protected:
    private:
};

#endif // STAGE_H
