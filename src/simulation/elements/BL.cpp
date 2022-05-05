#include "simulation/ElementCommon.h"

void Element::Element_BL()
{
	Identifier = "DEFAULT_PT_BL";
	Name = "B-l";
	Colour = PIXPACK(0xB92700);
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
	Description = "Liquid Boron.";

	Properties = TYPE_LIQUID | PROP_NEUTABSORB;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = 2349.00f;
	LowTemperatureTransition = PT_B;
	HighTemperature = 4200.00f;
	HighTemperatureTransition = PT_BG;
}
