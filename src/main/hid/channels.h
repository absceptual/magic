#ifndef CHANNEL_H
#define CHANNEL_H

#include <cstdint>
#include <cstring>
#include <chrono>

#include "hid/structure.h"

namespace hid {
    using namespace std::chrono;

    hid::channel_manager* manager;

    enum channel_state {
        idle, locked, max_states
    };

    struct transaction;
    class channel_manager {
    public:
        static const std::uint32_t PAYLOAD_MAX_LENGTH{ 7609 };

    private:
        std::uint16_t m_count{ };
        bool m_channels[ UINT32_MAX ];
        bool m_locked{ false };
        hid::response m_response{ };
        hid::transaction m_transaction{ };


    public:
        channel_manager( );

        void prepare_response( std::uint8_t cmd, std::uint16_t bcnt );
        void send_response( ); 

        void update_transaction( hid::packet* packet );
        void process_transaction( );
        void cleanup_transaction( );

        bool is_locked( );
        bool is_transaction_ready( );

        int allocate_channel( );


        template <typename T>
        bool add_to_response( T source ) { 

            // Dont perform any response tasks if we don't have a transaction open
            if ( !current_transaction.m_active )
                return false;

            // Don't add to the response if it will result in an overflow
            if ( m_response.m_offset <= PAYLOAD_MAX_LENGTH && m_response.m_offset + sizeof( T ) > PAYLOAD_MAX_LENGTH )
                return false;

            memcpy( static_cast< std::uintptr_t >( m_response.m_data ) + m_response.m_offset, &source, sizeof( T ) );
            m_response.offset += sizeof( T );
            return true;
        }
    };

    struct transaction {
        // Transaction is marked active when a succesful initalization packet is sent and processed
        bool m_active{ };
        bool m_ready{ };

        time_point< steady_clock > m_start{ };
        std::uint16_t m_packet_count{ };
        std::uint16_t m_expected_packet_count{ };
        std::uint16_t m_offset{ };
        std::uint32_t m_channel{ };
        std::uint8_t m_command{ };

        std::uint8_t m_data[ channel_manager::PAYLOAD_MAX_LENGTH ]{ };
        std::uint8_t m_data_length{ };
    };

    void init( std::uint8_t* nonce );
    void ping( std::uint8_t* data, std::uint16_t length ) ;
    void wink( );
    void lock( std::int32_t time );
};

#endif