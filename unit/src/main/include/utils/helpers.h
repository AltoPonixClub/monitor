/**
 * @file helpers.h
 * @brief header file for restclient-cpp helpers
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 * @version
 * @date 2010-10-11
 */

#ifndef INCLUDE_RESTCLIENT_CPP_HELPERS_H_
#define INCLUDE_RESTCLIENT_CPP_HELPERS_H_

#include <algorithm>
#include <cctype>
#include <functional>
#include <string>

/**
 * @brief namespace for all RestClient definitions
 */
namespace RestClient {

/**
 * @brief: namespace for all helper functions
 */
namespace Helpers {

/** @struct UploadObject
 *  @brief This structure represents the payload to upload on POST
 *  requests
 *  @var UploadObject::data
 *  Member 'data' contains the data to upload
 *  @var UploadObject::length
 *  Member 'length' contains the length of the data to upload
 */
typedef struct {
    const char *data;
    size_t length;
} UploadObject;

// writedata callback function
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

// header callback function
size_t header_callback(void *ptr, size_t size, size_t nmemb, void *userdata);
// read callback function
size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userdata);

// trim from start
static inline std::string &ltrim(std::string &s) { // NOLINT
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    [](int c) { return !std::isspace(c); }));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) { // NOLINT
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         [](int c) { return !std::isspace(c); })
                .base(),
            s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) { // NOLINT
    return ltrim(rtrim(s));
}
}; // namespace Helpers

}; // namespace RestClient

#endif // INCLUDE_RESTCLIENT_CPP_HELPERS_H_
