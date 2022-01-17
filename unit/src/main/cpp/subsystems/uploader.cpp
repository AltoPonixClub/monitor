#include "utils/restclient.h"
#include <config/configs.h>
#include <config/secrets.h>
#include <spdlog/spdlog.h>
#include <subsystems/uploader.h>
#include <utils/json.h>
#include <vector>

using Json = json11::Json;

Uploader::Uploader(State *state, Commands *commands, Outputs *outputs) {
    state->measurementPointers = std::vector<float *>{
        &state->atmosphericTemp,        &state->reservoirTemp,
        &state->lightIntensity,         &state->soilMoisture,
        &state->electricalConductivity, &state->pH,
        &state->dissolvedOxygen,        &state->airFlow};
    state->lastUploadTimes =
        std::vector<long>(state->measurementPointers.size(), 0);
    Json data = Json::object{{"monitor_id", Configs::Uploader::kMonitorId},
                             {"password", Secrets::Uploader::kMonitorPassword},
                             {"persist", true}};
    RestClient::Response r = RestClient::post(
        Configs::Uploader::kEndpoint + Configs::Uploader::kLoginMethod,
        "application/json", data.dump());
    if (r.code != 200) {
        spdlog::error("Uploader: Logging in code failed with code " +
                      std::to_string(r.code) + "");
        if (r.code != 403) {
            std::string err;
            Json response = Json::parse(r.body, err);
            spdlog::error("Uploader: Cause: " +
                          response["cause"].string_value());
        }
    } else {
        std::string err;
        Json response = Json::parse(r.body, err);
        state->authToken = response["data"]["token"].string_value();
        spdlog::info("Uploader: Logged in! Token: " + state->authToken);
    }
}

void Uploader::read(State *state) {}

void Uploader::calculate(State *state, Commands *commands, Outputs *outputs) {
    if (state->authToken == "")
        return;

    outputs->jsonMeasurementData =
        R"({"monitor_id": ")" + Configs::Uploader::kMonitorId +
        R"(", "token": ")" + state->authToken + R"(", )";
    int valuesUploaded = 0;
    for (auto wantedState : commands->uploadWantedStates) {
        if (state->timeS - state->lastUploadTimes[wantedState.first] >
            wantedState.second) {
            state->lastUploadTimes[wantedState.first] = state->timeS;
            valuesUploaded++;
            outputs->jsonMeasurementData +=
                "\"" + Configs::Uploader::kMeasurementNames[wantedState.first] +
                "\": " +
                std::to_string(*state->measurementPointers[wantedState.first]) +
                ",";
        }
    }
    outputs->jsonMeasurementData.pop_back();
    outputs->jsonMeasurementData += "}";

    // If we don't have anything to upload, abort
    if (valuesUploaded == 0)
        outputs->jsonMeasurementData = "";
}

void Uploader::write(Outputs *outputs) {
    if (outputs->jsonMeasurementData != "") {
        spdlog::info("Uploader: Uploading " + outputs->jsonMeasurementData);
        RestClient::Response r = RestClient::post(
            Configs::Uploader::kEndpoint + Configs::Uploader::kUploadMethod,
            "application/json", outputs->jsonMeasurementData);
        if (r.code != 200) {
            spdlog::error("Uploader: Upload to database failed with code " +
                          std::to_string(r.code) + "!");
            if (r.code == 401) {
                spdlog::error("Uploader: Auth token invalid! Restart monitor "
                              "to reauthenticate!");
            }
            if (r.code != 403) {
                std::string err;
                Json response = Json::parse(r.body, err);
                spdlog::error("Uploader: Cause: " +
                              response["cause"].string_value());
            }
        } else {
            spdlog::info("Uploader: Upload succeeded!");
        }
    }
}

Uploader *Uploader::instance(State *state, Commands *commands,
                             Outputs *outputs) {
    if (Uploader::pInstance == nullptr) {
        Uploader::pInstance = new Uploader(state, commands, outputs);
    }
    return Uploader::pInstance;
}

std::string Uploader::name() { return std::string("uploader"); }

bool Uploader::threaded() { return true; }
