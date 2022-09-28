#ifndef EB_PLUGIN_ECA_DRIVER_HPP_
#define EB_PLUGIN_ECA_DRIVER_HPP_


#ifndef ETHERBONE_THROWS
#define ETHERBONE_THROWS 1
#define __STDC_FORMAT_MACROS
#define __STDC_CONSTANT_MACROS
#endif
#include <etherbone.h>

#include <saftbus/service.hpp>

#include <memory>

namespace eb_plugin {

class SAFTd;
class SoftwareActionSink;
class OpenDevice;

class ECA {
	struct Impl; std::unique_ptr<Impl> d;

	friend class SoftwareActionSink;
	friend class ActionSink;

	uint16_t getMostFull(int channel);	
	eb_address_t get_base_address();
	const std::string &get_object_path();
	etherbone::Device &get_device();
	void compile();

public:

	ECA(SAFTd &saftd, etherbone::Device &device, const std::string &object_path, saftbus::Container *container);
	virtual ~ECA();


	void removeSowftwareActionSink(SoftwareActionSink *sas);

	/// @brief The current time of the timingreceiver.
	/// @return     the current time of the timingreceiver
	///
	/// The result is the WhiteRabbit timesamps in nanoseconds.
	/// It is not checked if WhiteRabbit core is locked or not.
	///
	// @saftbus-export
	uint64_t ReadRawCurrentTime();
	
	/// @brief        Create a new SoftwareActionSink.
	/// @param name   A name for the SoftwareActionSink. Can be left blank.
	/// @return       Object path to the created SoftwareActionSink.
	///
	/// SoftwareActionSinks allow a program to create conditions that match
	/// incoming timing events.  These conditions may have callback methods
	/// attached to them in order to receive notification.  The returned
	/// path corresponds to a SoftwareActionSink that is owned by the
	/// process which claimed it, and can thus be certain that no other
	/// processes can interfere with the results.
	///
	// @saftbus-export	
	std::string NewSoftwareActionSink(const std::string& name);

	/// @brief        Simulate the receipt of a timing event
	/// @param event  The event identifier which is matched against Conditions
	/// @param param  The parameter field, whose meaning depends on the event ID.
	/// @param time   The execution time for the event, added to condition offsets.
	///
	/// Sometimes it is useful to simulate the receipt of a timing event. 
	/// This allows software to test that configured conditions lead to the
	/// desired behaviour without needing the data master to send anything.
	///
	// @saftbus-export
	void InjectEventRaw(uint64_t event, uint64_t param, uint64_t time);

	/// @brief A list of all current SoftwareActionSinks.
	/// @return A list of all current SoftwareActionSinks.
	///
	/// Typically, these SoftwareActionSinks will be owned by their
	/// processes and not of much interest to others.  Therefore, many of
	/// the entries here may be of no interest to a particular client. 
	/// However, it is possible for a SoftwareActionSink to be Disowned, in
	/// which case it may be persistent and shared between programs under a
	/// well known name.
	///
	// @saftbus-export
	std::map< std::string, std::string > getSoftwareActionSinks() const;

	/// @brief get a pointer to a SoftwareActionSink in a stand-alone application
	/// @param sas_obj_path Object path of the SoftwareActionSink
	/// @return pointer to a SoftwareActionSink 
	///
	SoftwareActionSink *getSoftwareActionSink(const std::string & sas_obj_path);
};


} // namespace 

#endif

