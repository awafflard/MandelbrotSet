#ifndef CONTEXT_H
#define CONTEXT_H

class Context {

    public:
        Context();
        int getWidth();
        int getHeight();

    private:
        int width;
        int height;
};

#endif