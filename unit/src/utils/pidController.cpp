
#include "pidController.h"

PIDController::PIDController(float kF, float kP, float kI, float kD, float kFF,
                             float kIZone, float dt) {
    this->kF = kF;
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->kFF = kFF;
    this->kIZone = kIZone;
    this->dt = dt;
    integAccum = 0;
    prevError = 0;
}

float PIDController::calculate(float SP, float PV, float dt) {
    float error = SP - PV;
    integAccum += (std::abs(error) <= kIZone) ? dt * error : -integAccum;
    return SP * kF + error * kP + integAccum * kI +
           (error - prevError) * kD / dt + kFF;
}

float PIDController::calculate(float SP, float PV) {
    return calculate(SP, PV, dt);
}

std::array<float, 6> PIDController::getGains() {
    return std::array<float, 6>{kF, kP, kI, kD, kFF, kIZone};
}

void PIDController::setGains(float kF, float kP, float kI, float kD, float kFF,
                             float kIZone) {
    this->kF = kF;
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
    this->kFF = kFF;
    this->kIZone = kIZone;
}

void PIDController::zeroIntegrator() { integAccum = 0; }

std::string PIDController::toString() {
    return "kF: " + std::to_string(kF) + " kP: " + std::to_string(kP) +
           " kI: " + std::to_string(kI) + " kD: " + std::to_string(kD);
}
