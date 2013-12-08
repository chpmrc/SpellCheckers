MAIN = Game
SRCPATH = ./
SHAREDPATH = ./GLTools/src/
SHAREDINCPATH = ./GLTools/include/
LIBDIRS = -L/usr/X11R6/lib -L/usr/X11R6/lib64 -L/usr/local/lib
INCDIRS = -I/usr/include -I/usr/local/include -I/usr/include/GL -I$(SHAREDINCPATH)  -I$(SHAREDINCPATH)GL -I$(SRCPATH)

CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCDIRS)
LIBS = -lX11 -lglut -lGL -lGLU -lm

prog : $(MAIN)

$(MAIN).o :
	$(CC) $(CFLAGS) -c $(SRCPATH)$(MAIN).cpp $(LIBDIRS) $(LIBS)

Objects :
	$(CC) $(CFLAGS) -c Scene.cpp $(LIBDIRS) $(LIBS)
	$(CC) $(CFLAGS) -c Actor.cpp $(LIBDIRS) $(LIBS)
	$(CC) $(CFLAGS) -c Wizard.cpp $(LIBDIRS) $(LIBS)


glew.o    : $(SHAREDPATH)glew.c
GLTools.o    : $(SHAREDPATH)GLTools.cpp
GLBatch.o    : $(SHAREDPATH)GLBatch.cpp
GLTriangleBatch.o    : $(SHAREDPATH)GLTriangleBatch.cpp
GLShaderManager.o    : $(SHAREDPATH)GLShaderManager.cpp
math3d.o    : $(SHAREDPATH)math3d.cpp

$(MAIN) : Objects
	$(CC) $(CFLAGS) -o $(MAIN) $(MAIN).cpp $(SHAREDPATH)glew.c $(SHAREDPATH)GLTools.cpp $(SHAREDPATH)GLBatch.cpp $(SHAREDPATH)GLTriangleBatch.cpp $(SHAREDPATH)GLShaderManager.cpp $(SHAREDPATH)math3d.cpp $(LIBDIRS) $(LIBS) *.o

clean:
	rm -f *.o
	rm $(MAIN)
