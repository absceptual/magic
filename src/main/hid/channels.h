#ifndef CHANNEL_H
#define CHANNEL_H

#include <cstdint>
#include "hid/structure.h"

namespace hid {

    class channel_manager {
    private:
        bool m_channels[ UINT32_MAX ];
        bool m_busy{ false };

    public:
        channel_manager( ) : m_busy{ false } {

        }

        void process_request( ) { };

        bool is_busy( ) {
            return m_busy;
        }
    };

    void init( std::uint8_t* nonce );
    void ping( std::uint8_t* data ) ;
    void wink( );
    void lock( std::int32_t time );
};

#endif