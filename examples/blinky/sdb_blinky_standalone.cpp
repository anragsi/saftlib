#include <iostream>

#include <Blinky.hpp>

#define DEV_PATH "dev/ttyUSB0"


int main(int argc, char const *argv[])
{
	// if (argc != 2 && argc != 4) {
	// 	std::cerr << "usage: " << argv[0] << " eb-path [ <io-name> <freq[Hz]> ]" << std::endl;
	// 	return 0;
	// }


		/* instantiate socket and device */
		etherbone::Socket socket;
		socket.open();
		etherbone::Device device;
		device.open(socket, "dev/ttyUSB0");


		saftlib::BlinkySDB blinky_sdb(device);
		etherbone::address_t addr;

		blinky_sdb.start_addr;

		std::cout << &addr;

	return 0;
}