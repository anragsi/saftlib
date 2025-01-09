#include "sdb_blinky_standalone.hpp"
#include <saftlib/BlinkySDB.hpp>
#define DEV_PATH "dev/ttyUSB0"


int main(int argc, char const *argv[])
{
	try {
		/* instantiate socket and device */
		etherbone::Socket socket;
		socket.open();
		etherbone::Device device;
		device.open(socket, DEV_PATH);

		saftlib::BlinkySDB blinky_sdb(device);

		saftlib::BlinkySDB::Blinking blink_mode;
		blink_mode = saftlib::BlinkySDB::FAST;
		blinky_sdb.SetBlinkMode(blink_mode);

	} catch(etherbone::exception_t &e) {
		std::cerr << "Error: " << e << std::endl;
		return 1;
	}

	return 0;
}
