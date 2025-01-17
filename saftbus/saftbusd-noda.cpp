/** Copyright (C) 2021-2022 GSI Helmholtz Centre for Heavy Ion Research GmbH
 *
 *  @author Michael Reese <m.reese@gsi.de>
 *
 *******************************************************************************
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 3 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library. If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************
 */

#include "loop.hpp"
#include "server.hpp"
#include "client.hpp"
#include "service.hpp"

#include <cerrno>
#include <cstring>
#include <sstream>


std::string print_fillstate();

void usage(char *argv0) {
		std::cout << "saftbusd version " << VERSION << std::endl;
		std::cout << std::endl;
		std::cout << "usage: " << argv0 << " [OPTIONS] { <plugin.so> { <plugin-arg> } }" << std::endl;
		std::cout << std::endl;
		std::cout << "  <plugin.so>        is the name of a shared object files, it must have" << std::endl;
		std::cout << "                     contain a function with name \"create_services\"." << std::endl;
		std::cout << std::endl;
		std::cout << "  <plugin-arg>       one or more strings can be passed as arguments" << std::endl;
		std::cout << "                     to each plugin. They are arguments of the " << std::endl;
		std::cout << "                     \"create_services\" function in the shared library." << std::endl;
		std::cout << std::endl;
		std::cout << "options: " << std::endl;
		std::cout << std::endl;
		std::cout << " -h | --help         print this help and exit." << std::endl;
		std::cout << std::endl;
}


static bool saftd_already_running()
{
  // if ClientConnection can be established, saftbus is already running
  try {
  	saftbus::ClientConnection test_connection;
    return true;
  } catch (...) {
    return false;
  }
  return false;
}

static bool is_int(const std::string &name) {
	std::istringstream in(name);
	unsigned i;
	in >> i;
	if (!in) return false;
	char ch;
	in >> ch; // nothing must follow the integer
	if (in) return false;
	return true;
}

static bool detect_version(const std::string &name) {
	if (name.size() < 2) return false;
	if (name[0] != '.') return false;
	auto pos = name.substr(1).find(".");
	if (pos == name.npos) return is_int(name.substr(1));
	if (!is_int(name.substr(1,pos))) return false;
	return detect_version(name.substr(pos+1));
}

static bool detect_so_file(const std::string &name) {
	const std::string so_ending = ".so";
	if (name.size() < so_ending.size()) return false;
	auto pos = name.find(so_ending);
	if (pos == name.size()-so_ending.size()) return true;
	if (pos == name.npos) return false;
	auto rest = name.substr(pos+so_ending.size()); // rest must be a version (dots and numbers) for example like this ".10" or ".10.0.0"
	if (rest[0] != '.') return false;
	return detect_version(rest);
}

int main(int argc, char *argv[]) {
	try {

		std::vector<std::pair<std::string, std::vector<std::string> > > plugins_and_args;
		for (int i = 1; i < argc; ++i) {
			std::string argvi(argv[i]);
			if (argvi == "-h" || argvi == "--help") {
				usage(argv[0]);
				return 0;
			}
			if (detect_so_file(argvi)) {
				std::cerr << argvi << " is plugin" << std::endl;
				plugins_and_args.push_back(std::make_pair(argvi, std::vector<std::string>()));
			} else {
				std::cerr << argvi << " is argument" << std::endl;
				if (plugins_and_args.empty()) {
					std::cerr << "Error: no plugin specified (these are files ending with .so) before argument " << argvi << std::endl;
					return 1;
				} else {
					plugins_and_args.back().second.push_back(argvi);
				}
			}
		}

		if (saftd_already_running()) {
			std::cerr << "Cannot start: saftbusd already running" << std::endl;
			return 1;
		}

		saftbus::ServerConnection server_connection(plugins_and_args);

		// add allocator fillstate as additional info to be reported by Container::get_status()
		if (print_fillstate().size()) server_connection.get_container()->add_additional_info_callback("allocator", &print_fillstate);

		saftbus::Loop::get_default().run();

		// delete all remaining source from Loop before the plugins are unloaded
		saftbus::Loop::get_default().clear();

	} catch (std::runtime_error &e) {
		std::cerr << "Error: " << e.what() << std::endl;
		saftbus::Loop::get_default().clear();
		return 1;
	}

	return 0;
}
