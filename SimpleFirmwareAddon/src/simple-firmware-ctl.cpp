
#include <memory>

#include <SAFTd_Proxy.hpp>
#include <TimingReceiver_Proxy.hpp>
#include "SimpleFirmware_Proxy.hpp"

#include <saftbus/loop.hpp>
#include <saftlib.h>


// #include <ltdl.h> // need libltdl for this
// #include <dlfcn.h>


void on_MSI(uint32_t value) {
	std::cerr << "got MSI " << value << std::endl;
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "usage: " << argv[0] << " <saft-device>" << std::endl;
		std::cerr << "   example: " << argv[0] << " tr0" << std::endl;
		return 1;
	} 

	try {

		auto simple_fw = saftlib::SimpleFirmware_Proxy::create("/de/gsi/saftlib/tr0/simple-fw");

		simple_fw->MSI.connect(sigc::ptr_fun(on_MSI));
		simple_fw->start();

		for (;;) {
			saftlib::wait_for_signal();
		}


	} catch (std::runtime_error &e ) {
		std::cerr << "exception: " << e.what() << std::endl;
	}

	return 0;

}