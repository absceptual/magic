#include "headers/requests.h"

response_t requests::signup( hash_t challenge_hash, hash_t application_parameter ) {
    // No test-of-user-presence could be obtained by the hardware key.
    //return SW_CONDITIONS_NOT_SATISFIED;

    return nullptr;
}

response_t requests::authenticate( hash_t challenge, hash_t application, std::uint8_t* handle, std::uint8_t handle_length, std::uint8_t control ) {

    // return SW_CONDITIONS_NOT_SASTIFIED; test-of-user-presence being required
    // return SW_WRONG_DATA; invalid key handle
}

response_t requests::version( ) {

}

