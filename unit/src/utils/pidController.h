
#ifndef MONITOR_PIDCONTROLLER_H
#define MONITOR_PIDCONTROLLER_H

#include <array>
#include <string>

class PIDController {
  private:
    float kF, kP, kI, kD, kFF, kIZone, dt;
    float integAccum, prevError;

  public:
    PIDController(float kF, float kP, float kI, float kD, float kFF,
                  float kIZone, float dt);

    float calculate(float SP, float PV, float dt);

    float calculate(float SP, float PV);

    std::array<float, 6> getGains();

    void setGains(float kF, float kP, float kI, float kD, float kFF,
                  float kIZone);

    void zeroIntegrator();

    std::string toString();
};

#endif // MONITOR_PIDCONTROLLER_H
