#include "simulation/ElementCommon.h"

void Element::Element_Cl()
{
	Identifier = "DEFAULT_PT_Cl";
	Name = "Cl";
	Colour = PIXPACK(0xFFD56D);
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
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Chlorine.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

}