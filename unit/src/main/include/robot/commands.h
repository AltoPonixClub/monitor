#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

class Commands {
public:
    Commands();

    static Commands *instance();

    enum VisionState {
        STREAMING, STOPPED
    };
    enum DisplayState {
        ON, OFF
    };

    VisionState visionWantedState;
    DisplayState displayWantedState;
private:
    static inline Commands *pInstance = nullptr;
};

#endif //MONITOR_COMMANDS_H
