#include "simulation/ElementCommon.h"

void Element::Element_C_L()
{
	Identifier = "DEFAULT_PT_C_L";
	Name = "C-l";
	Colour = PIXPACK(0x751300);
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

	DefaultProperties.temp = R_TEMP + 2500.0f + 273.15f;
	HeatConduct = 30;
	Description = "Liquid Carbon.";

	Properties = TYPE_LIQUID | PROP_NEUTABSORB;

	LowPressure = 100.00f;
	LowPressureTransition = PT_CG;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 3823.00f;
	LowTemperatureTransition = PT_C;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;
}
