#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <chrono>

using namespace std::chrono;

using status_t = std::uint32_t;
using hash_t = std::uint32_t;
using response_t = std::uint8_t*;

using command_t = std::uint32_t;

// User Defined Constants
constexpr duration U2FHID_TIMEOUT = seconds( 15 );

// U2F Command Constants
constexpr int U2F_REGISTER      = 0x01;
constexpr int U2F_AUTHENTICATE  = 0x02;
constexpr int U2F_VERSION       = 0x3;

// U2FHID Constants
constexpr command_t U2FHID_PING           = 0;
constexpr command_t U2FHID_ERROR          = 1;
constexpr command_t U2FHID_WINK           = 2;
constexpr command_t U2FHID_LOCK           = 3;
constexpr command_t U2FHID_INIT           = 4;
constexpr command_t U2FHID_MSG            = 5;
constexpr int MAX_PACKET_SIZE       = 64;
constexpr int POLL_INTERVAL         = 5; 
constexpr int CID_BROADCAST         = 0xffffffff;
constexpr int U2FHID_IF_VERSION     = 2;  
constexpr int CAPABILITY_WINK          = 0x01;	
constexpr int CAPFLAG_LOCK          =  0x02;	
constexpr int TYPE_INIT             = 0x80; 

// U2FHID Error Status Codes
constexpr int ERR_INVALID_CMD = 0;
constexpr int ERR_INVALID_PAR = 0;
constexpr int ERR_INVALID_LEN = 0;
constexpr int ERR_INVALID_SEQ = 0;
constexpr int ERR_MSG_TIMEOUT = 0;
constexpr int ERR_CHANNEL_BUSY = 0;
constexpr int ERR_NONE = 0;
constexpr int ERR_LOCK_REQUIRED = 0;
constexpr int ERR_INVALID_CID = 0;
constexpr int ERR_OTHER = 0;

// U2F Status Codes
constexpr int SW_NO_ERROR                 = 0x9000;
constexpr int SW_CONDITIONS_NOT_SATISFIED = 0x6985;
constexpr int SW_WRONG_DATA               = 0x6A80;
constexpr int SW_WRONG_LENGTH             = 0x6700;
constexpr int SW_CLA_NOT_SUPPORTED        = 0x6E00;
constexpr int SW_INS_NOT_SUPPORTED        = 0x6D00;

// Authentication Request Control Values
constexpr int CHECK_ONLY                         = 0x7;
constexpr int ENFORCE_USER_PRESENCE_AND_SIGN     = 0x3;
constexpr int DONT_EFORCE_USER_PRESENCE_AND_SIGN = 0x8;

#endif