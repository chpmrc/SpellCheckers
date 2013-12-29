#ifndef UTILS_H
#define UTILS_H

#include <iostream>

using std::cout;

void printVector3f(M3DVector3f v){
    cout << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")\n";
}

void renderBitmapString(float x,float y,float z,void *font,	char *astring, int size) {
  char *c;
  c=astring;
  glRasterPos3f(x, y,z);
  for (int count=0; count <= size; count++) {
    glutBitmapCharacter(font, c[count]);
  }
}

#endif // UTILS_H
