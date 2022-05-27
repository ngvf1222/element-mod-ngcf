#include "simulation/ElementCommon.h"
static int update(UPDATE_FUNC_ARGS);
void Element::Element_Al26()
{
	Identifier = "DEFAULT_PT_Al26";
	Name = "Al26";
	Colour = PIXPACK(0xE1E1E1);
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
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Aluminum-26.";

	Properties = TYPE_SOLID;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

}
static int update(UPDATE_FUNC_ARGS)
{
	if (RNG::Ref().between(1, 720000) == 1 && RNG::Ref().between(1, 365) == 1 && RNG::Ref().between(1, 24) == 1 && RNG::Ref().between(1, 60) == 1 && RNG::Ref().between(1, 60) == 1 && RNG::Ref().between(1, 60) == 1)
	{
		sim->part_change_type(i, x, y, PT_Mg26);
		sim->create_part(-1, x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1), PT_PRON);//¹èÅ¸ºØ±«
		sim->create_part(-1, x + RNG::Ref().between(-1, 1), y + RNG::Ref().between(-1, 1), PT_ENET);
	}
}