#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_N13()
{
	Identifier = "DEFAULT_PT_N13";
	Name = "N-13";
	Colour = PIXPACK(0x6494F4);
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
	Meltable = 0;
	Hardness = 0;

	Weight = 100;

	HeatConduct = 251;
	Description = "Nitrogen-13.";

	Properties = TYPE_GAS;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;

}

static int update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry, rt;
	for (rx = -2; rx < 3; rx++)
		for (ry = -2; ry < 3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y + ry][x + rx];
				if (!r)
					continue;
				rt = TYP(r);
				if (RNG::Ref().chance(1, 250))
				{
					sim->create_part(-1, x + 1, y, PT_NEUT);
					sim->create_part(-1, x - 1, y, PT_ENET);
					sim->part_change_type(i, x, y, PT_C13);
				}
			}
	return 0;
}