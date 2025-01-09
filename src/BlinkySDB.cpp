#include "BlinkySDB.hpp"


namespace saftlib {

	BlinkySDB::BlinkySDB(etherbone::Device &device)
		: SdbDevice(device, BLINKY_VENDOR_ID, BLINKY_PRODUCT_ID)
	{
		_blinky_addr = adr_first;
	}

	void BlinkySDB::WriteBlinkMode( BlinkySDB::Blinking mode)
	{
		switch(mode){
			case STATIC: 
				_data = A_ON;
				break;
			case SLOW: 
				_data = B_ON;
				break;
			case FAST: 
				_data = C_ON;
				break;
			case OFF:
			default:
				_data = ALL_OFF;
				break;
		}

		_cycle.open(device);
		_cycle.write(_blinky_addr, EB_DATA32|EB_BIG_ENDIAN, _data);
		_cycle.close();

	}

	void BlinkySDB::SetBlinkMode( BlinkySDB::Blinking mode)
	{
		if (mode != -mode){
			_mode = mode;
			WriteBlinkMode(mode);
		}
	}

}