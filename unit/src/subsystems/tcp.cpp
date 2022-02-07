#include "tcp.h"
#include "config/configs.h"
#include "config/secrets.h"
#include "spdlog/spdlog.h"
#include "utils/json.h"
#include "utils/zmq.h"
#include <vector>

using Json = json11::Json;

TCP::TCP(State *state, Commands *commands, Outputs *outputs) {
    state->lastTCPTime = 0;
    commands->tcpWantedState = Commands::TCPState::ON;
    context = zmq::context_t(1);
    publisher = zmq::socket_t(context, ZMQ_PUB);
    publisher.bind("tcp://*:5555");
    spdlog::info("TCP: Successful Initialization");
}

void TCP::read(State *state, Commands *commands) {}

void TCP::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->tcpData = "";
    if (state->timeS - state->lastTCPTime >= Configs::TCP::kUploadFrequency &&
        commands->tcpWantedState == Commands::TCPState::ON) {
        state->lastTCPTime = state->timeS;
        outputs->tcpData = "test";
    }
}

void TCP::write(Outputs *outputs) {
    if (outputs->tcpData != "") {
        std::string msg1_str = outputs->tcpData;
        zmq::message_t msg1(msg1_str.size());
        memcpy(msg1.data(), msg1_str.c_str(), msg1_str.size());
        publisher.send(msg1);
    }
}

TCP *TCP::instance(State *state, Commands *commands, Outputs *outputs) {
    if (TCP::pInstance == nullptr) {
        TCP::pInstance = new TCP(state, commands, outputs);
    }
    return TCP::pInstance;
}

std::string TCP::name() { return std::string("tcp"); }

bool TCP::threaded() { return true; }
