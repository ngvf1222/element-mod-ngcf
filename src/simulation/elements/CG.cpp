#include "simulation/ElementCommon.h"

void Element::Element_CG()
{
	Identifier = "DEFAULT_PT_CG";
	Name = "C-g";
	Colour = PIXPACK(0xA21A00);
	MenuVisible = 0;
	MenuSection = SC_ATOM;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.10f;
	Gravity = 0.00f;
	Diffusion = 3.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 5;
	Hardness = 1;

	Weight = 90;

	DefaultProperties.temp = R_TEMP + 4500.15f + 273.15f;
	HeatConduct = 251;
	Description = "Gas Carbon.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = 100.00f;
	HighPressureTransition = PT_C_L;
	LowTemperature = 3915.00f;
	LowTemperatureTransition = PT_C;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
}
