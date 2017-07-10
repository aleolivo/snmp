/*----- PROTECTED REGION ID(Snmp.cpp) ENABLED START -----*/
static const char *RcsId = "$Id: Snmp.cpp,v 1.11 2016-04-18 14:04:35 alessio Exp $";
//=============================================================================
//
// file :        Snmp.cpp
//
// description : C++ source for the Snmp class and its commands.
//               The class is derived from Device. It represents the
//               CORBA servant object which will be accessed from the
//               network. All commands which can be executed on the
//               Snmp are implemented in this file.
//
// project :     
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
// $Author: alessio $
//
// $Revision: 1.11 $
// $Date: 2016-04-18 14:04:35 $
//
// $HeadURL:  $
//
//=============================================================================
//                This file is generated by POGO
//        (Program Obviously used to Generate tango Object)
//=============================================================================


#include <Snmp.h>
#include <SnmpClass.h>

/*----- PROTECTED REGION END -----*/	//	Snmp.cpp

/**
 *  Snmp class description:
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
//  Get           |  get
//  Set           |  set
//================================================================

//================================================================
//  Attributes managed is:
//================================================================
//================================================================

namespace Snmp_ns
{
/*----- PROTECTED REGION ID(Snmp::namespace_starting) ENABLED START -----*/

//	static initializations

/*----- PROTECTED REGION END -----*/	//	Snmp::namespace_starting

//--------------------------------------------------------
/**
 *	Method      : Snmp::Snmp()
 *	Description : Constructors for a Tango device
 *                implementing the classSnmp
 */
//--------------------------------------------------------
Snmp::Snmp(Tango::DeviceClass *cl, string &s)
 : TANGO_BASE_CLASS(cl, s.c_str())
{
	/*----- PROTECTED REGION ID(Snmp::constructor_1) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::constructor_1
}
//--------------------------------------------------------
Snmp::Snmp(Tango::DeviceClass *cl, const char *s)
 : TANGO_BASE_CLASS(cl, s)
{
	/*----- PROTECTED REGION ID(Snmp::constructor_2) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::constructor_2
}
//--------------------------------------------------------
Snmp::Snmp(Tango::DeviceClass *cl, const char *s, const char *d)
 : TANGO_BASE_CLASS(cl, s, d)
{
	/*----- PROTECTED REGION ID(Snmp::constructor_3) ENABLED START -----*/
	init_device();
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::constructor_3
}

//--------------------------------------------------------
/**
 *	Method      : Snmp::delete_device()
 *	Description : will be called at device destruction or at init command
 */
//--------------------------------------------------------
void Snmp::delete_device()
{
	DEBUG_STREAM << "Snmp::delete_device() " << device_name << endl;
	/*----- PROTECTED REGION ID(Snmp::delete_device) ENABLED START -----*/

	_delete_device();

	/*----- PROTECTED REGION END -----*/	//	Snmp::delete_device
}

//--------------------------------------------------------
/**
 *	Method      : Snmp::init_device()
 *	Description : will be called at device initialization.
 */
//--------------------------------------------------------
void Snmp::init_device()
{
	DEBUG_STREAM << "Snmp::init_device() create device " << device_name << endl;
	/*----- PROTECTED REGION ID(Snmp::init_device_before) ENABLED START -----*/

	session = NULL;	
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::init_device_before
	

	//	Get the device properties from database
	get_device_property();
	
	//	No longer if mandatory property not set. 
	if (mandatoryNotDefined)
		return;

	/*----- PROTECTED REGION ID(Snmp::init_device) ENABLED START -----*/
	
	reload_default_mibs();
	
	netsnmp_session ts;

	_init_device(ts);

	if (session == NULL)
	{
		string errmesg;
		get_error(&ts, errmesg);
		Tango::Except::throw_exception( "",
				errmesg,
				"Snmp::init_device()");
	}

	/*----- PROTECTED REGION END -----*/	//	Snmp::init_device
}

//--------------------------------------------------------
/**
 *	Method      : Snmp::get_device_property()
 *	Description : Read database to initialize property data members.
 */
//--------------------------------------------------------
void Snmp::get_device_property()
{
	/*----- PROTECTED REGION ID(Snmp::get_device_property_before) ENABLED START -----*/
	
	//	Initialize property data members
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::get_device_property_before

	mandatoryNotDefined = false;

	//	Read device properties from database.
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("Version"));
	dev_prop.push_back(Tango::DbDatum("Hostname"));
	dev_prop.push_back(Tango::DbDatum("Community"));
	dev_prop.push_back(Tango::DbDatum("Username"));
	dev_prop.push_back(Tango::DbDatum("Passphrase"));

	//	is there at least one property to be read ?
	if (dev_prop.size()>0)
	{
		//	Call database and extract values
		if (Tango::Util::instance()->_UseDb==true)
			get_db_device()->get_property(dev_prop);
	
		//	get instance on SnmpClass to get class property
		Tango::DbDatum	def_prop, cl_prop;
		SnmpClass	*ds_class =
			(static_cast<SnmpClass *>(get_device_class()));
		int	i = -1;

		//	Try to initialize Version from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  version;
		else {
			//	Try to initialize Version from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  version;
		}
		//	And try to extract Version value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  version;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

		//	Try to initialize Hostname from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  hostname;
		else {
			//	Try to initialize Hostname from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  hostname;
		}
		//	And try to extract Hostname value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  hostname;
		//	Property StartDsPath is mandatory, check if has been defined in database.
		check_mandatory_property(cl_prop, dev_prop[i]);

		//	Try to initialize Community from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  community;
		else {
			//	Try to initialize Community from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  community;
		}
		//	And try to extract Community value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  community;

		//	Try to initialize Username from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  username;
		else {
			//	Try to initialize Username from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  username;
		}
		//	And try to extract Username value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  username;

		//	Try to initialize Passphrase from class property
		cl_prop = ds_class->get_class_property(dev_prop[++i].name);
		if (cl_prop.is_empty()==false)	cl_prop  >>  passphrase;
		else {
			//	Try to initialize Passphrase from default device value
			def_prop = ds_class->get_default_device_property(dev_prop[i].name);
			if (def_prop.is_empty()==false)	def_prop  >>  passphrase;
		}
		//	And try to extract Passphrase value from database
		if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  passphrase;

	}

	/*----- PROTECTED REGION ID(Snmp::get_device_property_after) ENABLED START -----*/

	if (version != 1 && version != 2 && version != 3)
	{
		mandatoryNotDefined = true;
		set_state(Tango::FAULT);
		set_status("SNMP version must be choosen between 1, 2 or 3.");
	}

	if ((version == 1 || version == 2) && community.size() == 0)
	{
		mandatoryNotDefined = true;
		set_state(Tango::FAULT);
		set_status("Community property is mandatory with SNMP version 1 and 2.");
	}

	if (version == 3 && (username.size() == 0 || passphrase.size() == 0))
	{
		mandatoryNotDefined = true;
		set_state(Tango::FAULT);
		set_status("Username and Passphrase properties are mandatory with SNMP version 3.");
	}
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::get_device_property_after
}
//--------------------------------------------------------
/**
 *	Method      : Snmp::check_mandatory_property()
 *	Description : For mandatory properties check if defined in database.
 */
//--------------------------------------------------------
void Snmp::check_mandatory_property(Tango::DbDatum &class_prop, Tango::DbDatum &dev_prop)
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
		/*----- PROTECTED REGION ID(Snmp::check_mandatory_property) ENABLED START -----*/
		cerr << tms.str() << " for " << device_name << endl;
		
		/*----- PROTECTED REGION END -----*/	//	Snmp::check_mandatory_property
	}
}


//--------------------------------------------------------
/**
 *	Method      : Snmp::always_executed_hook()
 *	Description : method always executed before any command is executed
 */
//--------------------------------------------------------
void Snmp::always_executed_hook()
{
	DEBUG_STREAM << "Snmp::always_executed_hook()  " << device_name << endl;
	if (mandatoryNotDefined)
	{
		string	status(get_status());
		Tango::Except::throw_exception(
					(const char *)"PROPERTY_NOT_SET",
					status.c_str(),
					(const char *)"Snmp::always_executed_hook()");
	}
	/*----- PROTECTED REGION ID(Snmp::always_executed_hook) ENABLED START -----*/
	
	if (Tango::Util::instance()->is_svr_shutting_down() == false
			&& Tango::Util::instance()->is_device_restarting(device_name) == false
			&& Tango::Util::instance()->is_svr_starting() == false) {
		if (! session) {
			netsnmp_session ts;
			_init_device(ts);
		}
	}
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::always_executed_hook
}

//--------------------------------------------------------
/**
 *	Method      : Snmp::read_attr_hardware()
 *	Description : Hardware acquisition for attributes
 */
//--------------------------------------------------------
void Snmp::read_attr_hardware(TANGO_UNUSED(vector<long> &attr_list))
{
	DEBUG_STREAM << "Snmp::read_attr_hardware(vector<long> &attr_list) entering... " << endl;
	/*----- PROTECTED REGION ID(Snmp::read_attr_hardware) ENABLED START -----*/
	
	//	Add your own code
	(void)attr_list;
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::read_attr_hardware
}


//--------------------------------------------------------
/**
 *	Method      : Snmp::add_dynamic_attributes()
 *	Description : Create the dynamic attributes if any
 *                for specified device.
 */
//--------------------------------------------------------
void Snmp::add_dynamic_attributes()
{
	/*----- PROTECTED REGION ID(Snmp::add_dynamic_attributes) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic attributes if any
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::add_dynamic_attributes
}

//--------------------------------------------------------
/**
 *	Command Get related method
 *	Description: 
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevVarStringArray *Snmp::get(const Tango::DevVarLongStringArray *argin)
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "Snmp::Get()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Snmp::get) ENABLED START -----*/
	
	size_t items = argin->svalue.length();

	if (argin->lvalue.length() != 1 || items == 0)
		Tango::Except::throw_exception( "",
				"Invalid input: It requires one only long value "
				"and one or more string values",
				"Snmp::get()");

	session->timeout = argin->lvalue[0] * 1000;
	netsnmp_pdu *pdu = snmp_pdu_create(SNMP_MSG_GET);

	for (size_t i=0; i<items; ++i)
	{
		oid anOID[MAX_OID_LEN];
		size_t anOID_len = MAX_OID_LEN;	
		DEBUG_STREAM << "Snmp::Get() "
			<< "Parsing " << string(argin->svalue[i]) << endl;
		if (! read_objid(argin->svalue[i], anOID, &anOID_len))
		{
			snmp_free_pdu(pdu);
			throw_exception("Parsing error");
		}
		snmp_add_null_var(pdu, anOID, anOID_len);
	}

	netsnmp_pdu *response;
	switch (snmp_synch_response(session, pdu, &response))
	{
		case STAT_SUCCESS:
			break;
		case STAT_ERROR:
			snmp_free_pdu(response);
			throw_exception("Error");
			break;
		case STAT_TIMEOUT:
			snmp_free_pdu(response);
			throw_exception("Timeout");
			break;
		default:
			assert(false);
	}
	
	if (! response) {
		assert(false);
		throw_exception("SNMP bug");
	}

	switch (response->errstat)
	{
		case SNMP_ERR_NOERROR:
			break;
		case SNMP_ERR_NOTWRITABLE:
			snmp_free_pdu(response);
			throw_exception("SNMP object isn't writeable");
			break;
		case SNMP_ERR_TOOBIG:
		case SNMP_ERR_NOSUCHNAME:
		case SNMP_ERR_BADVALUE:
		case SNMP_ERR_READONLY:
		case SNMP_ERR_GENERR:
		case SNMP_ERR_NOACCESS:
		case SNMP_ERR_WRONGTYPE:
		case SNMP_ERR_WRONGLENGTH:
		case SNMP_ERR_WRONGENCODING:
		case SNMP_ERR_WRONGVALUE:
		case SNMP_ERR_NOCREATION:
		case SNMP_ERR_INCONSISTENTVALUE:
		case SNMP_ERR_RESOURCEUNAVAILABLE:
		case SNMP_ERR_COMMITFAILED:
		case SNMP_ERR_UNDOFAILED:
		case SNMP_ERR_AUTHORIZATIONERROR:
		case SNMP_ERR_INCONSISTENTNAME:
			ERROR_STREAM << "SNMP protocol data unit Error: " << response->errstat << endl;
			snmp_free_pdu(response);
			throw_exception("Error");
			break;
		default:
			assert(false);
	}

	argout = new Tango::DevVarStringArray();
	argout->length(items);
	int i = 0;
	for(variable_list *vars = response->variables; vars;
			vars = vars->next_variable)
	{
		char buff[1024];
		int cp = snprint_value(buff, sizeof(buff), vars->name,
				vars->name_length, vars);

		if (cp == -1)
		{
			delete argout;
			snmp_free_pdu(response);
			throw_exception("Buffer overflow");
		}

		DEBUG_STREAM << "Snmp::get() "
			<< "Received " << string(buff) << endl;
		(*argout)[i++] = CORBA::string_dup(buff);
	}

	snmp_free_pdu(response);

	set_state(Tango::ON);
	set_status("The device is in ON state.");
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::get
	return argout;
}
//--------------------------------------------------------
/**
 *	Command Set related method
 *	Description: 
 *
 *	@param argin 
 *	@returns 
 */
//--------------------------------------------------------
Tango::DevVarStringArray *Snmp::set(const Tango::DevVarLongStringArray *argin)
{
	Tango::DevVarStringArray *argout;
	DEBUG_STREAM << "Snmp::Set()  - " << device_name << endl;
	/*----- PROTECTED REGION ID(Snmp::set) ENABLED START -----*/
	
	size_t items = argin->svalue.length();
	if (argin->lvalue.length() != 1 || items == 0 || items % 2 != 0)
		Tango::Except::throw_exception( "",
				"Invalid input: It requires one only long value "
				"and one or more pair of string (composed by oid and value)",
				"Snmp::set()");

	session->timeout = argin->lvalue[0] * 1000;
	netsnmp_pdu *pdu = snmp_pdu_create(SNMP_MSG_SET);

	for (size_t i=0; i<items; i+=2)
	{
		oid anOID[MAX_OID_LEN];
		size_t anOID_len = MAX_OID_LEN;	
		DEBUG_STREAM << "Snmp::Set() "
			<< "Parsing " << string(argin->svalue[i]) << endl;
		if (! read_objid(argin->svalue[i], anOID, &anOID_len))
		{
			snmp_free_pdu(pdu);
			throw_exception( "Parsing error");
		}
		if (snmp_add_var(pdu, anOID, anOID_len, '=', argin->svalue[i+1]))
			throw_exception();
	}

	netsnmp_pdu *response;
	switch (snmp_synch_response(session, pdu, &response))
	{
		case STAT_SUCCESS:
			break;
		case STAT_ERROR:
			snmp_free_pdu(response);
			throw_exception("Error");
			break;
		case STAT_TIMEOUT:
			snmp_free_pdu(response);
			throw_exception("Timeout");
			break;
		default:
			assert(false);
	}
	
	if (! response) {
		assert(false);
		throw_exception("SNMP bug");
	}

	switch (response->errstat)
	{
		case SNMP_ERR_NOERROR:
			break;
		case SNMP_ERR_NOTWRITABLE:
			snmp_free_pdu(response);
			throw_exception("SNMP object isn't writeable");
			break;
		case SNMP_ERR_TOOBIG:
		case SNMP_ERR_NOSUCHNAME:
		case SNMP_ERR_BADVALUE:
		case SNMP_ERR_READONLY:
		case SNMP_ERR_GENERR:
		case SNMP_ERR_NOACCESS:
		case SNMP_ERR_WRONGTYPE:
		case SNMP_ERR_WRONGLENGTH:
		case SNMP_ERR_WRONGENCODING:
		case SNMP_ERR_WRONGVALUE:
		case SNMP_ERR_NOCREATION:
		case SNMP_ERR_INCONSISTENTVALUE:
		case SNMP_ERR_RESOURCEUNAVAILABLE:
		case SNMP_ERR_COMMITFAILED:
		case SNMP_ERR_UNDOFAILED:
		case SNMP_ERR_AUTHORIZATIONERROR:
		case SNMP_ERR_INCONSISTENTNAME:
			ERROR_STREAM << "SNMP protocol data unit Error: " << response->errstat << endl;
			snmp_free_pdu(response);
			throw_exception("Error");
			break;
		default:
			assert(false);
	}

	argout = new Tango::DevVarStringArray();
	argout->length(items);
	int i = 0;
	for(variable_list *vars = response->variables; vars;
			vars = vars->next_variable)
	{
		char buff[1024];
		int cp = snprint_value(buff, sizeof(buff), vars->name,
				vars->name_length, vars);
				
		if (cp == -1)
		{
			delete argout;
			snmp_free_pdu(response);
			throw_exception("Buffer overflow");
		}

		DEBUG_STREAM << "Snmp::set() "
			<< "Received " << string(buff) << endl;
		(*argout)[i++] = CORBA::string_dup(buff);		
	}

	snmp_free_pdu(response);

	set_state(Tango::ON);
	set_status("The device is in ON state.");
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::set
	return argout;
}
//--------------------------------------------------------
/**
 *	Method      : Snmp::add_dynamic_commands()
 *	Description : Create the dynamic commands if any
 *                for specified device.
 */
//--------------------------------------------------------
void Snmp::add_dynamic_commands()
{
	/*----- PROTECTED REGION ID(Snmp::add_dynamic_commands) ENABLED START -----*/
	
	//	Add your own code to create and add dynamic commands if any
	
	/*----- PROTECTED REGION END -----*/	//	Snmp::add_dynamic_commands
}

/*----- PROTECTED REGION ID(Snmp::namespace_ending) ENABLED START -----*/

void Snmp::reload_default_mibs()
{
	shutdown_mib();
	init_mib();
}

void Snmp::get_error(netsnmp_session *sess, string &ret)
{
	stringstream mesg;
	int pcliberr, psnmperr;
	char *pperrstring;
	snmp_error(sess, &pcliberr, &psnmperr, &pperrstring);
	mesg << string(pperrstring) << " (" << pcliberr << " "
		<< psnmperr << ")" << flush;
	free(pperrstring);
	ret = mesg.str();
}

void Snmp::throw_exception(const string &prepend)
{
	string errmesg;
	get_error(session, errmesg);
	set_state(Tango::FAULT);
	set_status(prepend + " " + errmesg);
	_delete_device();
	Tango::Except::throw_exception( "",
			prepend + " " + errmesg,
			"Snmp::throw_exception()");
}

void Snmp::_delete_device()
{
	if (session)
	{
		if (! snmp_close(session))
		{
			ERROR_STREAM << "Snmp::_delete_device() "
				<< "Error closing SNMP" << endl;
		}
		SOCK_CLEANUP;
	}
	session = NULL;	
}

void Snmp::_init_device(netsnmp_session &ts)
{
	snmp_sess_init(&ts);

	switch(version)
	{
		case 1:
			ts.peername = (char*)hostname.c_str();
			ts.version = SNMP_VERSION_1;
			ts.community = (u_char*)(community.c_str());
			ts.community_len = community.size() ;
			break;
		case 2:
			ts.peername = (char*)hostname.c_str();
			ts.version = SNMP_VERSION_2c;
			ts.community = (u_char*)(community.c_str());
			ts.community_len = community.size() ;
			break;
		case 3:
			ts.peername = (char*)hostname.c_str();
			ts.version = SNMP_VERSION_3;
			ts.securityName = (char*)username.c_str();
			ts.securityNameLen = username.size();
			ts.securityLevel = SNMP_SEC_LEVEL_AUTHNOPRIV;
			ts.securityAuthProto = usmHMACMD5AuthProtocol;
			ts.securityAuthProtoLen =
				sizeof(usmHMACMD5AuthProtocol)/sizeof(oid);
			ts.securityAuthKeyLen = USM_AUTH_KU_LEN;

			if (generate_Ku(ts.securityAuthProto,
						ts.securityAuthProtoLen,
						(u_char*)passphrase.c_str(),
						passphrase.size(),
						ts.securityAuthKey,
						&ts.securityAuthKeyLen)
					!= SNMPERR_SUCCESS)
				Tango::Except::throw_exception( "",
						"Error generating Ku from "
						"authentication pass phrase",
						"Snmp::init_device()");
			break;
	}

	SOCK_STARTUP;

	ts.retries = 0;
	
	netsnmp_ds_set_int(NETSNMP_DS_LIBRARY_ID, 
					   NETSNMP_DS_LIB_OID_OUTPUT_FORMAT,
					   NETSNMP_OID_OUTPUT_NUMERIC);
	
	session = snmp_open(&ts);
	
	if (session == NULL)
	{
		SOCK_CLEANUP;
	}
}

/*----- PROTECTED REGION END -----*/	//	Snmp::namespace_ending
} //	namespace
