#ifndef saftlib_SDB_STANDALONE_BLINKY_HPP_
#define saftlib_SDB_STANDALONE_BLINKY_HPP_

#define BLINKY_PRODUCT_ID        0x434E5452
#define BLINKY_VENDOR_ID         0x0000000000000651

#include <etherbone.h>

#include "SdbDevice.hpp"

namespace saftlib {

class BlinkySDB :public SdbDevice {

public:
	etherbone::address_t start_addr;
	BlinkySDB(etherbone::Device &device);

};

}

#endif
