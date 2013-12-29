#ifndef SPELL_H
#define SPELL_H

#include <Actor.h>
#include <string>

using std::string;

class Spell : public Actor {
    private:
        string name;
        int damage;

        M3DVector3f color;

    public:
        Spell(string name, int damage, Scene *scene, GLTriangleBatch *model, GLFrame *frame, M3DVector3f origin);
        virtual ~Spell();

        int getDamage();
        string getName();
        void setColor(float r, float g, float b);

        void render(GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp);
        void render(M3DVector3f from, M3DVector3f to, float seconds, GLShaderManager *sm, GLMatrixStack *mvm, GLMatrixStack *pm, GLFrustum *f, GLGeometryTransform *tp);
};

#endif
