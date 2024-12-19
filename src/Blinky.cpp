#include "Blinky.hpp"


namespace saftlib {

BlinkySDB::BlinkySDB(etherbone::Device &device)
	: SdbDevice(device, BLINKY_VENDOR_ID, BLINKY_PRODUCT_ID)
{
	start_addr = adr_first;
}

}