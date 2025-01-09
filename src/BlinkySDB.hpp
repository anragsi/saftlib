#ifndef saftlib_BLINKY_SDB_HPP_
#define saftlib_BLINKY_SDB_HPP_

#ifndef ETHERBONE_THROWS
#define ETHERBONE_THROWS 1
#endif

#define BLINKY_PRODUCT_ID        0x434E5452
#define BLINKY_VENDOR_ID         0x0000000000000651

#define ALL_OFF 0x00000000
#define A_ON 	0x00000001
#define B_ON 	0x00000005
#define C_ON 	0x00000007

#include "SdbDevice.hpp"

namespace saftlib {

class BlinkySDB : public SdbDevice {

public:
	BlinkySDB(etherbone::Device &device);
	eb_address_t get_start_adr();

	enum Blinking
	{
		OFF,
		STATIC,
		SLOW,
		FAST
	};

	void WriteBlinkMode( BlinkySDB::Blinking mode);
	void SetBlinkMode( BlinkySDB::Blinking mode);

private:
	BlinkySDB::Blinking _mode;
	etherbone::address_t _blinky_addr;
	etherbone::data_t _data;
	etherbone::Cycle _cycle;
	etherbone::exception_t _e;
};

}

#endif
