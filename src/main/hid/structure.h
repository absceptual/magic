#ifndef HIDSTRUCTURE_H
#define HIDSTRUCTURE_H

#include <cstdint>
#include <vector>

#include "headers/constants.h"

namespace hid {

    struct packet {
        // Channel identifer
        std::uint32_t cid;

        // Command identifer
        std::uint8_t cmd;
    };

    struct init_packet {
        // Channel identifier
        std::uint32_t cid;
    
        // Command identifer (bit 7 always set)
        std::uint8_t cmd;
    
        // Payload length
        std::uint8_t bcnt;
    
        // Payload data (s is equal to the fixed packet size)
        std::uint8_t data[ MAX_PACKET_SIZE - 7 ];
    };
    
    struct continuation_packet {
        // Channel identifier
        std::uint32_t cid;
    
        // Packet sequence 0x00..0x7f (bit 7 is always cleared)
        std::uint8_t seq;
    
        // Payload data (s is equal to the fixed packet size)
        std::uint8_t data[ MAX_PACKET_SIZE - 5 ];
    };

    struct message {
        // Command identifer
        std::uint32_t cmd;

        // Payload length
        std::uint16_t bcnt;
    };

    struct response {
        // Command indetifer
        std::uint32_t cmd;
        
        // Payload length
        std::uint16_t bcnt;

        // Payload data
        std::uint8_t* data;

        std::uint16_t offset;
    };
};

#endif