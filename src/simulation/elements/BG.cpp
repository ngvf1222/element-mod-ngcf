#include "simulation/ElementCommon.h"

void Element::Element_BG()
{
	Identifier = "DEFAULT_PT_BG";
	Name = "B-g";
	Colour = PIXPACK(0xD92E00);
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
	Description = "Gas Boron.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 4200.00f;
	LowTemperatureTransition = PT_BG;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
}
