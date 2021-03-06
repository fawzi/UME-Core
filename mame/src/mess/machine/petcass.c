/**********************************************************************

    Commodore PET/VIC-20/C64/Plus-4 Datassette Port emulation

    Copyright MESS Team.
    Visit http://mamedev.org for licensing and usage restrictions.

**********************************************************************/

#include "machine/petcass.h"



//**************************************************************************
//  GLOBAL VARIABLES
//**************************************************************************

const device_type PET_DATASSETTE_PORT = &device_creator<pet_datassette_port_device>;



//**************************************************************************
//  CARD INTERFACE
//**************************************************************************

//-------------------------------------------------
//  device_pet_datassette_port_interface - constructor
//-------------------------------------------------

device_pet_datassette_port_interface::device_pet_datassette_port_interface(const machine_config &mconfig, device_t &device)
	: device_slot_card_interface(mconfig,device)
{
	m_slot = dynamic_cast<pet_datassette_port_device *>(device.owner());
}


//-------------------------------------------------
//  ~device_pet_datassette_port_interface - destructor
//-------------------------------------------------

device_pet_datassette_port_interface::~device_pet_datassette_port_interface()
{
}



//**************************************************************************
//  LIVE DEVICE
//**************************************************************************

//-------------------------------------------------
//  pet_datassette_port_device - constructor
//-------------------------------------------------

pet_datassette_port_device::pet_datassette_port_device(const machine_config &mconfig, const char *tag, device_t *owner, UINT32 clock) :
	device_t(mconfig, PET_DATASSETTE_PORT, "Datassette Port", tag, owner, clock),
	device_slot_interface(mconfig, *this),
	m_read_handler(*this)
{
}


//-------------------------------------------------
//  pet_datassette_port_device - destructor
//-------------------------------------------------

pet_datassette_port_device::~pet_datassette_port_device()
{
}


//-------------------------------------------------
//  device_start - device-specific startup
//-------------------------------------------------

void pet_datassette_port_device::device_start()
{
	m_cart = dynamic_cast<device_pet_datassette_port_interface *>(get_card_device());

	// resolve callbacks
	m_read_handler.resolve_safe();
}


READ_LINE_MEMBER( pet_datassette_port_device::read ) { int state = 1; if (m_cart != NULL) state = m_cart->datassette_read(); return state; }
WRITE_LINE_MEMBER( pet_datassette_port_device::write ) { if (m_cart != NULL) m_cart->datassette_write(state); }
READ_LINE_MEMBER( pet_datassette_port_device::sense_r ) { int state = 1; if (m_cart != NULL) state = m_cart->datassette_sense(); return state; }
WRITE_LINE_MEMBER( pet_datassette_port_device::motor_w ) { if (m_cart != NULL) m_cart->datassette_motor(state); }

WRITE_LINE_MEMBER( pet_datassette_port_device::read_w ) { m_read_handler(state); }
