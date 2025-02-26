#ifndef HIDSTRUCTURE_H
#define HIDSTRUCTURE_H

#include <cstdint>
#include "headers/constants.h"

namespace hid {
    struct init_packet {
        // Channel identifier
        std::uint32_t cid;
    
        // Command identifer (bit 7 always set)
        std::uint8_t cmd;
    
        // High part of payload length
        std::uint8_t bcnth;
    
        // Low part of payload length
        std::uint8_t bcntl;
    
        // Payload data (s is equal to the fixed packet size)
        std::uint8_t data[ MAX_PACKET_SIZE - 7 ];
    };
    
    struct continuation_packet {
        // Channel identifier
        std::uint32_t cid;
    
        // Packet sequence 0x00..0x7f (bit 7 is always cleared)
        std::uint8_t seq;
    
        // Payload data (s is equal to the fixed packet size)
        std::uint8_t data[ MAX_PACKET_SIZE - 7];
    };
}

#endif