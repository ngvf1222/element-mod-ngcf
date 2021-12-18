#include "simulation/ElementCommon.h"

void Element::Element_HES()
{
	Identifier = "DEFAULT_PT_HES";
	Name = "He-s";
	Colour = PIXPACK(0x1CD4BE);
	MenuVisible = 0;
	MenuSection = SC_ATOM;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.90f;
	Loss = 0.00f;
	Collision = 0.0f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 5;
	Hardness = 1;

	Weight = 90;

	DefaultProperties.temp = R_TEMP - 295.15f + 273.15f;
	HeatConduct = 251;
	Description = "Solid Helium.";

	Properties = TYPE_SOLID|PROP_CONDUCTS|PROP_LIFE_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 0.95f;
	HighTemperatureTransition = PT_HEL;
}
