#ifndef ACTOR_H
#define ACTOR_H

class Actor {
public:
    virtual void onDraw() = 0;
    virtual void onQuit() = 0;
};

#endif
