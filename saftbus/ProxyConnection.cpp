#include "ProxyConnection.h"

#include <iostream>
#include <sstream>
#include <iomanip>


namespace saftbus
{

ProxyConnection::SaftbusObject::SaftbusObject()
	: object_path("")
	, interface_info()
	, vtable(InterfaceVTable::SlotInterfaceMethodCall())
{}

ProxyConnection::SaftbusObject::SaftbusObject(const std::string &object, const Glib::RefPtr<InterfaceInfo> &info, const InterfaceVTable &table)
	: object_path(object)
	, interface_info(info)
	, vtable(table)
{}

ProxyConnection::SaftbusObject::SaftbusObject(const SaftbusObject &rhs)
	: object_path(rhs.object_path)
	, interface_info(rhs.interface_info)
	, vtable(rhs.vtable)
{}

ProxyConnection::ProxyConnection(bool server)
	: _saftbus_objects(1, ProxyConnection::SaftbusObject())
{
	std::cerr << "ProxyConnection::ProxyConnection(" << server << ") called" << std::endl;
	if (server)
	{
		for (int i = 0; i < 16; ++i)
		{
			std::ostringstream name;
			name << "/tmp/saftbus.socket.";
			name << i;
			_sockets.push_back(UnSocket(name.str(),server));
		}
	} else {
		for (int i = 0; i < 16; ++i)
		{
			std::ostringstream name;
			name << "/tmp/saftbus.socket.";
			name << i;
			try {
				UnSocket socket = UnSocket(name.str(), server);
				break;
			}
			catch(...)
			{
				std::cerr << "caught an expected exception" << std::endl;
			}
		}
	}
}


guint ProxyConnection::register_object (const Glib::ustring& object_path, const Glib::RefPtr< InterfaceInfo >& interface_info, const InterfaceVTable& vtable)
{
	std::cerr << "ProxyConnection::register_object("<< object_path <<") called" << std::endl;
	//_saftbus_objects[object_path] = counter++;
	guint result = _saftbus_objects.size();
	SaftbusObject object(object_path, interface_info, vtable);
	_saftbus_objects.push_back(object);
	// for(auto iter = _saftbus_objects.begin(); iter != _saftbus_objects.end(); ++iter)
	// {
	// 	std::cerr << *iter << std::endl;
	// }
	return result;
}
bool ProxyConnection::unregister_object (guint registration_id)
{
	if (registration_id < _saftbus_objects.size())
	{
		_saftbus_objects[registration_id].object_path = "";
		return true;
	}
	return false;
}


guint ProxyConnection::signal_subscribe 	( 	const SlotSignal&  	slot,
										const Glib::ustring&  	sender,
										const Glib::ustring&  	interface_name,
										const Glib::ustring&  	member,
										const Glib::ustring&  	object_path,
										const Glib::ustring&  	arg0//,
										)//SignalFlags  	flags)
{
	std::cerr << "ProxyConnection::signal_subscribe(" << sender << "," << interface_name << "," << member << "," << object_path << ") called" << std::endl;
	return 0;
}

void ProxyConnection::signal_unsubscribe 	( 	guint  	subscription_id	) 
{
	std::cerr << "ProxyConnection::signal_unsubscribe() called" << std::endl;
}


void 	ProxyConnection::emit_signal (const Glib::ustring& object_path, const Glib::ustring& interface_name, const Glib::ustring& signal_name, const Glib::ustring& destination_bus_name, const Glib::VariantContainerBase& parameters)
{
	std::cerr << "ProxyConnection::emit_signal(" << object_path << "," << interface_name << "," << signal_name << "," << destination_bus_name << ") called" << std::endl;
	for (unsigned n = 0; n < parameters.get_n_children(); ++n)
	{
		Glib::VariantBase child;
		parameters.get_child(child, n);
		std::cerr << "parameter[" << n << "].type = " << child.get_type_string() << std::endl;
	}
}


Glib::VariantContainerBase ProxyConnection::call_sync (const Glib::ustring& object_path, const Glib::ustring& interface_name, const Glib::ustring& method_name, const Glib::VariantContainerBase& parameters, const Glib::ustring& bus_name, int timeout_msec)
{
	std::cerr << "ProxyConnection::call_sync(" << object_path << "," << interface_name << "," << method_name << ") called" << std::endl;
	return Glib::VariantContainerBase();
}



}
