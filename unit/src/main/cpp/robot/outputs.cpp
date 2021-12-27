#include <robot/outputs.h>

Outputs *Outputs::instance() {
    if (Outputs::pInstance == nullptr) {
        Outputs::pInstance = new Outputs();
    }
    return Outputs::pInstance;
}


