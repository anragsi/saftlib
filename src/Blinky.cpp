#include "Blinky.hpp"


namespace saftlib {

	BlinkySDB::BlinkySDB(etherbone::Device &device)
		: SdbDevice(device, BLINKY_VENDOR_ID, BLINKY_PRODUCT_ID)
	{
		etherbone::address_t get_start_adr()
		{
			return adr_first;
		}

	}

	BlinkySDB::~BlinkySDB() {
	}

}