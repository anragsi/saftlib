#ifndef saftlib_SDB_STANDALONE_BLINKY_HPP_
#define saftlib_SDB_STANDALONE_BLINKY_HPP_

#define BLINKY_PRODUCT_ID        0x434E5452
#define BLINKY_VENDOR_ID         0x0000000000000651

#include <etherbone.h>

#include "SdbDevice.hpp"

namespace saftlib {

class BlinkySDB : public SdbDevice {

public:
	BlinkySDB(etherbone::Device &device);
	etherbone::address_t get_start_adr();

};

}

#endif
