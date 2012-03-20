#include "WPILib.h"
#include "ParadoxTipper.h"
#include "math.h"

ParadoxTipper::ParadoxTipper (UINT32 solo, UINT32 soli, UINT32 asonar)
{
	BridgeOUT		= new Solenoid(solo);
	BridgeIN		= new Solenoid(soli);
	Sonar			= new AnalogChannel(asonar);
	
	
	float inches	= Sonar->GetVoltage()/0.009766; 
	//myRoutine= ToTip;
}
void ParadoxTipper::Tip(bool go)
{
	/*switch (myRoutine)
	{
		default:
			break;
		case ToTip:
			break;
	}*/
}
void ParadoxTipper::Manual(bool manualtip)
{
	if (manualtip==true)
	{
		BridgeOUT->Set(0);
		BridgeIN->Set(1);
	}
	else
	{
		BridgeOUT->Set(1);
		BridgeIN->Set(0);
	}
}