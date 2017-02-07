class ActorProperties {
private:
    bool keyboardEvents;
    bool mouseEvents;
public:
    ActorProperties(bool keyboardEvents = false, bool mouseEvents = false)
    :   keyboardEvents(keyboardEvents),
        mouseEvents(mouseEvents) { }

    bool needKeyboardEvents() { return keyboardEvents; }
    bool needMouseEvents() { return mouseEvents; }

};

std::ostream & operator<<(std::ostream & os, ActorProperties ap) {
    os  << "keyboardEvents:\t" << ap.needMouseEvents() << '\n'
        << "mouseEvents:\t" << ap.needMouseEvents() << '\n';
    return os;
}
