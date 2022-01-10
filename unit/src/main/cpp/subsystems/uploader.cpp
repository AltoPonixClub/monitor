#include <config/configs.h>
#include <utils/utils.h>
#include <spdlog/spdlog.h>
#include <subsystems/uploader.h>
#include <vector>
#include "utils/restclient.h"

Uploader::Uploader(State *state, Commands *commands, Outputs *outputs) {
    state->measurementPointers = std::vector<float *>{
            &state->atmosphericTemp, &state->reservoirTemp, &state->lightIntensity, &state->soilMoisture,
            &state->electricalConductivity, &state->pH, &state->dissolvedOxygen, &state->airFlow
    };
    state->lastUploadTimes = std::vector<long>(state->measurementPointers.size(), 0);
}

void Uploader::read(State *state) {
}

void Uploader::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->jsonMeasurementData = "{\"monitor_id\": \"" + Configs::Uploader::kMonitorId + "\",";
    long now = Utils::getUnixTimestamp();
    int valuesUploaded = 0;
    for ( auto wantedState : commands->uploadWantedStates) {
        if (now - state->lastUploadTimes[wantedState.first] > wantedState.second) {
            state->lastUploadTimes[wantedState.first] = now;
            valuesUploaded++;
            outputs->jsonMeasurementData += "\"" + Configs::Uploader::kMeasurementNames[wantedState.first] + "\": " +
                                            std::to_string(*state->measurementPointers[wantedState.first]) + ",";
        }
    }
    outputs->jsonMeasurementData.pop_back();
    outputs->jsonMeasurementData += "}";

    //If we don't have anything to upload, abort
    if (valuesUploaded == 0)
        outputs->jsonMeasurementData = "";
}

void Uploader::write(Outputs *outputs) {
    if (outputs->jsonMeasurementData != "") {
        spdlog::info("Uploader: Uploading " + outputs->jsonMeasurementData);
        RestClient::Response r = RestClient::post(Configs::Uploader::kUploadUrl,
                                                  "application/json", outputs->jsonMeasurementData);
        if (r.code != 200)
            spdlog::error("Uploader: Upload to database failed with code " + std::to_string(r.code) + "!");
    }
}

Uploader *Uploader::instance(State *state, Commands *commands, Outputs *outputs) {
    if (Uploader::pInstance == nullptr) {
        Uploader::pInstance = new Uploader(state, commands, outputs);
    }
    return Uploader::pInstance;
}

std::string Uploader::name() {
    return std::string("uploader");
}
