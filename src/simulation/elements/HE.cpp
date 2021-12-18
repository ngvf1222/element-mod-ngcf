#include "simulation/ElementCommon.h"

void Element::Element_HE()
{
	Identifier = "DEFAULT_PT_HE";
	Name = "He";
	Colour = PIXPACK(0x2DF1DA);
	MenuVisible = 1;
	MenuSection = SC_ATOM;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.10f;
	Gravity = 0.00f;
	Diffusion = 3.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	HeatConduct = 251;
	Description = "Helium.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 4.22f;
	LowTemperatureTransition = PT_HEL;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
}