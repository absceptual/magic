#include "hid/channels.h"

void hid::init( std::uint8_t* nonce ) {
    if ( !hid::manager )
        return;

    // Allocate a new channel 
    int channel_id = hid::manager->allocate_channel( );
    
    // Prepare a response
    hid::manager->prepare_response( );
    hid::manager->add_to_response( U2FHID_INIT );
    hid::manager->add_to_response( 17 );
    hid::manager->add_to_response( nonce );
    hid::manager->add_to_response( channel_id );
    hid::manager->add_to_response( 0xA );
    hid::manager->add_to_response( 0xB );
    hid::manager->add_to_response( 0xC );
    // To be enabled at a later date add_to_response( CAPABILITY_WINK );
} 

void hid::ping( std::uint8_t* data, std::uint16_t length ) { 
    if ( !hid::manager )
        return;

    hid::manager->prepare_response( );
    hid::manager->add_to_response( U2FHID_PING );
    hid::manager->add_to_response( length );
    hid::manager->add_to_response( data );
}

void hid::wink( ) {

}

void hid::lock( std::int32_t time ) {

}

void hid::channel_manager::update_transaction( hid::packet* packet ) {
    auto now = std::chrono::steady_clock::now();

    // Terminate the current transaction if it exceeds the timeout period
    if (now - m_transaction.m_start > U2FHID_TIMEOUT) {
        prepare_response( U2FHID_ERROR, 1 );

        add_to_response( ERR_MSG_TIMEOUT );

        send_response( );
        return;
    }

    // Don't do anything if we haven't received a new packet
    if ( !packet )
        return;

    if ( m_transaction.m_active ) {
        // Ignore the packet if it is from a different channel that is not currently active
        if ( packet->cid != m_transaction.m_channel ) {
            prepare_response( U2FHID_ERROR, 1 );
    
            add_to_response( ERR_CHANNEL_BUSY );

            send_response( );
            return;
        }

        // Terminate the transaction if we receive a initialization packet instead of a continuation packet
        if ( packet->cmd & ( 1 << 7 ) ) {
            prepare_response( U2FHID_ERROR, 1 );

            add_to_response( ERR_INVALID_CMD );

            send_response( );   
            return;
        }

        auto cont_packet = reinterpret_cast< hid::continuation_packet* >( packet );
        
        // Terminate the transaction if we receive packets out of order
        if ( cont_packet->seq != m_transaction.m_packet_count ) {
            prepare_response( U2FHID_ERROR, 1 );

            add_to_response( ERR_INVALID_SEQ );

            send_response( );
            return;
        }

        // Update our transaction data buffer
        memcpy( reinterpret_cast< void* >( reinterpret_cast< std::uintptr_t >( m_transaction.m_data ) + m_transaction.m_offset ), cont_packet->data, PAYLOAD_MAX_LENGTH - 5 );
        m_transaction.m_offset += PAYLOAD_MAX_LENGTH - 5;
        ++m_transaction.m_packet_count;
        return;
    } 
    
    // Start a new transaction if one is not already active
    if ( !m_transaction.m_active ) {
        // Cleanup any leftover data from our last transaction
        cleanup_transaction( );

        // Ignore the packet if it is a continuation packet instead of an initalization packet
        if ( (packet->cmd & ( 1 << 7 ) ) == 0 ) {
            prepare_response( U2FHID_ERROR, 1 );
            
            add_to_response( ERR_INVALID_CMD );

            send_response( );
            return;
        }

        auto init_packet = reinterpret_cast< hid::init_packet* >( packet );
        m_transaction = hid::transaction{
            .m_start = steady_clock::now( ),
            .m_offset = 0,
            .m_channel = init_packet->cid,
            .m_command = init_packet->cmd,
            .m_packet_count = 0,
            .m_data_length = init_packet->bcnt
        };

        // No additional packets are expected if it can fit into the initalization packet
        if ( init_packet->bcnt <= MAX_PACKET_SIZE - 7 )
            m_transaction.m_expected_packet_count = 0;

        if ( init_packet->bcnt > MAX_PACKET_SIZE - 7 ) {
            std::uint32_t remaining = init_packet->bcnt - ( MAX_PACKET_SIZE - 7 );
            std::uint32_t packets = remaining / (MAX_PACKET_SIZE - 5);
            m_transaction.m_expected_packet_count = packets;
            if ( remaining % ( MAX_PACKET_SIZE - 5 ) )
                ++m_transaction.m_expected_packet_count;
        }
    }



}
void hid::channel_manager::process_transaction(  ) {
   
    switch ( m_transaction.m_command ) {
        case U2FHID_INIT: {
            auto nonce = m_transaction.m_data;
            hid::init( nonce );
            break;
        }
        case U2FHID_MSG: {
            // To be added
            break;
        }
        case U2FHID_PING: {
            auto data = m_transaction.m_data;
            hid::ping( data, m_transaction.m_data_length );
            break;
        }
    }    

    cleanup_transaction( );
}

void hid::channel_manager::cleanup_transaction( ) {
    m_transaction = { };
}

void hid::channel_manager::prepare_response( std::uint8_t cmd, std::uint16_t bcnt ) {
    if ( m_response.data )
        delete[ ] m_response.data;

    m_response.cmd  = cmd;
    m_response.bcnt = bcnt;
    m_response.data = new std::uint8_t[ bcnt ];
}

void hid::channel_manager::send_response( ) {
    
    // Code for writing to out..

    m_response.cmd = m_response.bcnt = 0;
    delete[ ] m_response.data;
    m_response.data = nullptr;
    cleanup_transaction( );
}

bool hid::channel_manager::is_locked( ) {
    return m_locked;
}

int hid::channel_manager::allocate_channel( ) {
    int id = m_count++;
    m_channels[ id ] = true;

    return id;
}