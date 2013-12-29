#include <GLTools.h>
#include <GL/freeglut.h>
#include <iostream>

#include <Interactive.h>

Interactive::Interactive()
{
    //ctor
}

Interactive::~Interactive()
{
    //dtor
}

void Interactive::onKeyPressed(char key, int x, int y){}

void Interactive::onKeyReleased(char key, int x, int y){}

void Interactive::onSpecialKeyPressed(int key, int x, int y){
    std::cout << "Key " << key << " pressed\n";
    switch(key){
        case GLUT_KEY_RIGHT:
            keyPressed[Interactive::KEY_RIGHT_INDEX] = true;
            break;

        case GLUT_KEY_LEFT:
            keyPressed[Interactive::KEY_LEFT_INDEX] = true;
            break;

        case GLUT_KEY_DOWN:
            keyPressed[Interactive::KEY_DOWN_INDEX] = true;
            break;

        case GLUT_KEY_UP:
            keyPressed[Interactive::KEY_UP_INDEX] = true;
            break;
    }
}
void Interactive::onSpecialKeyReleased(int key, int x, int y){
    std::cout << "Key " << key << " released\n";
    switch(key){
        case GLUT_KEY_RIGHT:
            keyPressed[Interactive::KEY_RIGHT_INDEX] = false;
            break;

        case GLUT_KEY_LEFT:
            keyPressed[Interactive::KEY_LEFT_INDEX] = false;
            break;

        case GLUT_KEY_DOWN:
            keyPressed[Interactive::KEY_DOWN_INDEX] = false;
            break;

        case GLUT_KEY_UP:
            keyPressed[Interactive::KEY_UP_INDEX] = false;
            break;

    }

}
