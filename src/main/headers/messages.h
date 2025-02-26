#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdint>
#include "constants.h"

namespace u2f {
    response_t register_request( hash_t challenge, hash_t application );
    response_t authenticate_request( hash_t challenge, hash_t application, std::uint8_t* handle, std::uint8_t handle_length, std::uint8_t control );
    response_t version_request( );
}

#endif
