#include "headers/requests.h"
#include "hid/channels.h"

bool get_available_packets( );

int loop( ) {

    hid::channel_manager* manager = new hid::channel_manager{ };

    while ( true ) {       
        auto packet = get_available_packets( );
        manager->update_transaction( reinterpret_cast< hid::packet* >( &packet ) );
        if ( manager->is_transaction_ready( ) ) 
            manager->process_transaction( );
    }
    hid::init_packet data;
}