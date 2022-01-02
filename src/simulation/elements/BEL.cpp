#include "simulation/ElementCommon.h"

void Element::Element_BEL()
{
	Identifier = "DEFAULT_PT_BEL";
	Name = "Be-l";
	Colour = PIXPACK(0x8AA5FF);
	MenuVisible = 0;
	MenuSection = SC_ATOM;
	Enabled = 1;

	Advection = 0.6f;
	AirDrag = 0.01f * CFDS;
	AirLoss = 0.98f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.1f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 2;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 20;

	Weight = 30;

	DefaultProperties.temp = R_TEMP + 3000.0f + 273.15f;
	HeatConduct = 251;
	Description = "Liquid Beryllium.";

	Properties = TYPE_LIQUID | PROP_DEADLY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 1560.00f;
	LowTemperatureTransition = PT_BE;
	HighTemperature = 2742.00f;
	HighTemperatureTransition = PT_BEG;
}
