enum ActorConfig {
    KEYBOARD_INPUT = 0x1,
    MOUSE_INPUT = 0x2,
    COLLISION_OFF = 0x4,
    COLLISION_ROUGH = 0x8,
    COLLISION_DETAILED = 0x16,
};

enum CollisionStatus {
    OFF,
    ROUGH,
    DETAILED
};

class ActorProperties {
private:
    bool keyboardEvents;
    bool mouseEvents;
    CollisionStatus collisionStatus;
public:
    ActorProperties(unsigned int actorConfig) {
        collisionStatus = OFF;
        if (actorConfig >= COLLISION_DETAILED) { 
            collisionStatus = DETAILED;
            actorConfig -= COLLISION_DETAILED;
        } else if (actorConfig >= COLLISION_ROUGH) {
            collisionStatus = ROUGH;
            actorConfig -= COLLISION_ROUGH;
        } else if (actorConfig >= COLLISION_OFF) {
            collisionStatus = OFF;
            actorConfig -= COLLISION_OFF;
        }

        mouseEvents = false;
        if (actorConfig >= MOUSE_INPUT) {
            mouseEvents = true;
            actorConfig -= MOUSE_INPUT;
        }

        keyboardEvents = false;
        if (actorConfig >= KEYBOARD_INPUT) {
            keyboardEvents = true;
            actorConfig -= KEYBOARD_INPUT;
        }
    }

    bool needKeyboardEvents() { return keyboardEvents; }
    bool needMouseEvents() { return mouseEvents; }
    CollisionStatus needCollision() { return collisionStatus; }

};

std::ostream & operator<<(std::ostream & os, ActorProperties ap) {
    os  << "keyboardEvents:\t" << ap.needMouseEvents() << '\n'
        << "mouseEvents:\t" << ap.needMouseEvents() << '\n';
    return os;
}

