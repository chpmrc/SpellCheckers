#ifndef INTERACTIVE_H
#define INTERACTIVE_H

class Interactive
{
    public:
        Interactive();
        virtual ~Interactive();

        virtual void onKeyPressed(char key, int x, int y);
        virtual void onKeyReleased(char key, int x, int y);
        virtual void onSpecialKeyPressed(int key, int x, int y);
        virtual void onSpecialKeyReleased(int key, int x, int y);

    protected:
        static const int NUM_KEYS = 4;
        static const int KEY_RIGHT_INDEX = 0;
        static const int KEY_LEFT_INDEX = 1;
        static const int KEY_UP_INDEX = 2;
        static const int KEY_DOWN_INDEX = 3;
        bool keyPressed[NUM_KEYS] = {0};

    private:
};

#endif // INTERACTIVE_H
