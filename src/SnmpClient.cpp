/*----- PROTECTED REGION ID(SnmpClient.cpp) ENABLED START -----*/
static const char *RcsId = "$Id:  $";
//=============================================================================
//
// file :        SnmpClient.cpp
//
// description : C++ source for the SnmpClient class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               SnmpClient are implemented in this file.
//
// project :     Snmp proxy interface
//
// This file is part of Tango device class.
// 
// Tango is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// Tango is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with Tango.  If not, see <http://www.gnu.org/licenses/>.
// 
// $Author:  $
//
// $Revision:  $
// $Date:  $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <SnmpClient.h>
#include <SnmpClientClass.h>

/*----- PROTECTED REGION END -----*/	//	SnmpClient.cpp

/**
 *  SnmpClient class description:
 *    
 */

//================================================================
//  The following table gives the correspondence
//  between command and method names.
//
//  Command name  |  Method name
//================================================================
//  State         |  Inherited (no method)
//  Status        |  Inherited (no method)
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace SnmpClient_ns
{
/*----- PROTECTED REGION ID(SnmpClient::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	SnmpClient::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : SnmpClient::SnmpClient()
 *	Description : Constructors for a Tango device
 *                implementing the classSnmpClient
 */
//--------------------------------------------------------
SnmpClient::SnmpClient(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(SnmpClient::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::constructor_1
}
//--------------------------------------------------------
SnmpClient::SnmpClient(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(SnmpClient::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::constructor_2
}
//--------------------------------------------------------
SnmpClient::SnmpClient(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(SnmpClient::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : SnmpClient::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void SnmpClient::delete_device()
{
	DEBUG_STREAM << "SnmpClient::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(SnmpClient::delete_device) ENABLED START -----*/
	
	//	Delete device allocated objects
	if (device_proxy)
		delete device_proxy;
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : SnmpClient::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void SnmpClient::init_device()
{
	DEBUG_STREAM << "SnmpClient::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(SnmpClient::init_device_before) ENABLED START -----*/
	
	//	Initialization before get_device_property() call
	device_proxy = NULL;
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	//	No longer if mandatory property not set. 
	if (mandatoryNotDefined)
		return;

	/*----- PROTECTED REGION ID(SnmpClient::init_device) ENABLED START -----*/
	
	//	Initialize device
	try
	{
		device_proxy = new Tango::DeviceProxy(deviceName);
	}
	catch(...)
	{}
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::init_device
}

//--------------------------------------------------------
/**
 *	Method      : SnmpClient::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void SnmpClient::get_device_property()
{
	/*----- PROTECTED REGION ID(SnmpClient::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::get_device_property_before

	mandatoryNotDefined = false;

	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DeviceName"));
	dev_prop.push_back(Tango::DbDatum("Timeout"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on SnmpClientClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		SnmpClientClass	*ds_class =
			(static_cast<SnmpClientClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize DeviceName from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  deviceName;
		else {
			//	Try to initialize DeviceName from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  deviceName;
		}
		//	And try to extract DeviceName value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  deviceName;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

		//	Try to initialize Timeout from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  timeout;
		else {
			//	Try to initialize Timeout from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  timeout;
		}
		//	And try to extract Timeout value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  timeout;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

	}

	/*----- PROTECTED REGION ID(SnmpClient::get_device_property_after) ENABLED START -----*/
	
	//	Check device property data members init
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::get_device_property_after
}
//--------------------------------------------------------
/**
 *	Method      : SnmpClient::check_mandatory_property()
 *	Description : For mandatory properties check if defined in database.
 */
//--------------------------------------------------------
void SnmpClient::check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop)
{
	//	Check if all properties are empty
	if (class_prop.is_empty() && dev_prop.is_empty())
	{
		TangoSys_OMemStream	tms;
		tms << endl <<"Property \'" << dev_prop.name;
		if (Tango::Util::instance()->_UseDb==true)
			tms << "\' is mandatory but not defined in database";
		else
			tms << "\' is mandatory but cannot be defined without database";
		string	status(get_status());
		status += tms.str();
		set_status(status);
		mandatoryNotDefined = true;
		/*----- PROTECTED REGION ID(SnmpClient::check_mandatory_property) ENABLED START -----*/
		cerr << tms.str() << " for " << device_name << endl;
		
		/*----- PROTECTED REGION END -----*/	//	SnmpClient::check_mandatory_property
	}
}


//--------------------------------------------------------
/**
 *	Method      : SnmpClient::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void SnmpClient::always_executed_hook()
{
	DEBUG_STREAM << "SnmpClient::always_executed_hook()  " << device_name << endl;
	if (mandatoryNotDefined)
	{
		string	status(get_status());
		Tango::Except::throw_exception(
					(const char *)"PROPERTY_NOT_SET",
					status.c_str(),
					(const char *)"SnmpClient::always_executed_hook()");
	}
	/*----- PROTECTED REGION ID(SnmpClient::always_executed_hook) ENABLED START -----*/
	
	//	code always executed before all requests
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : SnmpClient::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void SnmpClient::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "SnmpClient::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(SnmpClient::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : SnmpClient::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void SnmpClient::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(SnmpClient::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Method      : SnmpClient::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void SnmpClient::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(SnmpClient::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	SnmpClient::add_dynamic_commands
}

/*----- PROTECTED REGION ID(SnmpClient::namespace_ending) ENABLED START -----*/

//	Additional Methods


void SnmpClient::get(const string &oid, string &reply)
{	
	vector<string> vs_oids = {oid};
	vector<string> vs_replies(1);
	get(vs_oids, vs_replies);
	reply = vs_replies[0];
}
void SnmpClient::get(vector<string> &oids, vector<string> &replies)
{
	DEBUG_STREAM << "SnmpClient::get() - " << device_name << endl;
	
	if(!device_proxy)
		Tango::Except::throw_exception("device_proxy not initialized", "Snmp \"GET\" request can't be sent", "SnmpClient::get()");
	
	Tango::DeviceData ddin, ddout;
	Tango::DevVarLongStringArray *dvlsa = new Tango::DevVarLongStringArray();
	size_t oids_num = oids.size();
	dvlsa->lvalue.length(1);
	dvlsa->lvalue[0] = timeout;
	dvlsa->svalue.length(oids_num);
	for(size_t i = 0; i < oids_num; i++)
		dvlsa->svalue[i] = CORBA::string_dup(oids[i].c_str());
	ddin << dvlsa;
	ddout = device_proxy->command_inout("Get", ddin);
	const Tango::DevVarStringArray *dvsa;
	ddout >> dvsa;
	for(size_t i = 0; i < oids_num; i++)
	{
		replies[i] = (*dvsa)[i];
		
		DEBUG_STREAM << "SnmpClient::get() - oid = <"<< oids[i] << "> - returned value = <"<< replies[i] << ">" << endl;	
	}
}

void SnmpClient::set(const string &oid, const string &value, const string &expected_reply)
{
	vector<string> vs_oids = {oid};
	vector<string> vs_values = {value};
	vector<string> vs_expected_replies = {expected_reply};
	set(vs_oids, vs_values, vs_expected_replies);
}
void SnmpClient::set(vector<string> &oids, vector<string> &values, vector<string> &expected_replies)
{
	DEBUG_STREAM << "SnmpClient::set() - " << device_name << endl;
	
	if(!device_proxy)
		Tango::Except::throw_exception("device_proxy not initialized", "Snmp \"SET\" request can't be sent", "SnmpClient::set()");
	
	Tango::DeviceData ddin, ddout;
	Tango::DevVarLongStringArray *dvlsa = new Tango::DevVarLongStringArray();
	size_t oids_num = oids.size();
	dvlsa->lvalue.length(1);
	dvlsa->lvalue[0] = timeout;
	dvlsa->svalue.length(2 * oids_num);
	for (size_t i = 0; i < oids_num; i++ )
	{
		dvlsa->svalue[i * 2] = CORBA::string_dup(oids[i].c_str());
		dvlsa->svalue[i * 2 + 1] = CORBA::string_dup(values[i].c_str());
	}
	ddin << dvlsa;
	ddout = device_proxy->command_inout("Set", ddin);
	const Tango::DevVarStringArray *dvsa;
	ddout >> dvsa;
	string reply;
	string mismatch_info("");	 
	for (size_t i = 0; i < oids_num; i++)
	{
		reply = (*dvsa)[i]; 
		if (reply != expected_replies[i])
			mismatch_info +=  " - " + oids[i] + " (expected reply: " + expected_replies[i] + " but returned: " + reply + ")\n";
				
		DEBUG_STREAM << "SnmpClient::set() - oid = <"<< oids[i] << "> returned value = <"<< reply << ">" << endl;
	}
	if(!mismatch_info.empty())
			Tango::Except::throw_exception("",
										   "Mismatch between expected reply and actual reply for the following oids: \n" + mismatch_info,
										   "SnmpClient::set()");
}

/*----- PROTECTED REGION END -----*/	//	SnmpClient::namespace_ending
} //	namespace