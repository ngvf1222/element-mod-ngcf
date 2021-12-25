#include "simulation/ElementCommon.h"

void Element::Element_LIL()
{
	Identifier = "DEFAULT_PT_LIL";
	Name = "Li-l";
	Colour = PIXPACK(0xA79CAF);
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

	DefaultProperties.temp = R_TEMP + 480.0f + 273.15f;
	HeatConduct = 30;
	Description = "Liquid Lithium.";

	Properties = TYPE_LIQUID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 453.69f;
	LowTemperatureTransition = PT_LITH;
	HighTemperature = 1615.00f;
	HighTemperatureTransition = PT_LIG;
}
