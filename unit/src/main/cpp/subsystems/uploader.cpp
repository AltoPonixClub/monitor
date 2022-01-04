#include <config/constants.h>
#include <utils/utils.h>
#include <spdlog/spdlog.h>
#include <subsystems/uploader.h>
#include "restclient-cpp/restclient.h"

Uploader::Uploader(State *state, Commands *commands, Outputs *outputs) {
    measurementPointers[0] = &State::atmosphericTemp;
    measurementPointers[1] = &State::reservoirTemp;
    measurementPointers[2] = &State::lightIntensity;
    measurementPointers[3] = &State::soilMoisture;
    measurementPointers[4] = &State::electricalConductivity;
    measurementPointers[5] = &State::pH;
    measurementPointers[6] = &State::dissolvedOxygen;
    measurementPointers[7] = &State::airFlow;
}

void Uploader::read(State *state) {
}

void Uploader::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->jsonMeasurementData = "{\"monitor_id\": \"" + constants::uploader::kMonitorId + "\",";
    long now = Utils::getUnixTimestamp();
    int valuesUploaded = 0;
    for ( auto wantedState : commands->uploadWantedStates) {
        if (now - lastUploadTimes[wantedState.first] > wantedState.second) {
            lastUploadTimes[wantedState.first] = now;
            valuesUploaded++;
            outputs->jsonMeasurementData += "\"" + constants::uploader::kMeasurementNames[wantedState.first] + "\": " +
                                            std::to_string(*state.*measurementPointers[wantedState.first]) + ",";
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
        RestClient::Response r = RestClient::post(constants::uploader::kUploadUrl, "application/json", outputs->jsonMeasurementData);
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
