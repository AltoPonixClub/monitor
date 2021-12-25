#ifndef MONITOR_COMMANDS_H
#define MONITOR_COMMANDS_H

class Commands {
public:
    static Commands *instance();

    enum VisionState {
        STREAMING, STOPPED
    };

    VisionState visionWantedState;
private:
    static inline Commands *pInstance = nullptr;
};

#endif //MONITOR_COMMANDS_H
