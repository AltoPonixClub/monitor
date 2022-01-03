#include <config/constants.h>
#include <utils/utils.h>
#include <subsystems/uploader.h>
#include "restclient-cpp/restclient.h"

//Update values using:
//state->monitorMeasurements[constants::general::Measurements::ATMOSPHERIC_TEMP] = 1;
//Add a new value by doing:
//1. Update kNumMeasurements in constants::general
//2. Add the new measurement in constants::general::Measurements
//3. Add the string name (the json key that is used) to kMeasurementNames in upload.h

Uploader::Uploader(State *state, Commands *commands, Outputs *outputs) {
    state->lastTimeS = Utils::getUnixTimestamp();
}

void Uploader::read(State *state) {
    //Timer
    long now = Utils::getUnixTimestamp();
    if (now - state->lastTimeS > constants::uploader::kUploadInterval) {
        state->lastTimeS = now;
        state->doUpload = true;
    } else {
        state->doUpload = false;
    }
}

void Uploader::calculate(State *state, Commands *commands, Outputs *outputs) {
    outputs->jsonString = "";

    //Generate JSON String
    if (state->doUpload) {
        outputs->jsonString = "{\"monitor_id\": \"" + constants::uploader::kMonitorId + "\",";
        int valuesUploaded = 0;
        for (int i = 0; i < constants::general::kNumMeasurements; i++) {
            if (state->uploadValues[i]) {
                outputs->jsonString += "\"" + constants::uploader::kMeasurementNames[i] + "\": " +
                                       std::to_string(state->monitorMeasurements[i]) + ",";
                valuesUploaded++;
            }
        }
        outputs->jsonString.pop_back();
        outputs->jsonString += "}";
        //If we don't have anything to upload, abort
        if (valuesUploaded == 0)
            outputs->jsonString = "";
    }
}

void Uploader::write(Outputs *outputs) {
    if (outputs->jsonString != "") {
        std::cout << "Uploading " << outputs->jsonString << std::endl;
        RestClient::Response r = RestClient::post(constants::uploader::kUploadUrl, "application/json", outputs->jsonString);
        if (r.code != 200)
            std::cout << "Upload to database failed with code " << r.code << "!" << std::endl;
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
