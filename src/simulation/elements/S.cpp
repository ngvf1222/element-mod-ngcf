#include "simulation/ElementCommon.h"
static int update(UPDATE_FUNC_ARGS);
void Element::Element_S()
{
	Identifier = "DEFAULT_PT_S";
	Name = "S";
	Colour = PIXPACK(0xFFB600);
	MenuVisible = 1;
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

	Flammable = 1;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Sulfur.";

	Properties = TYPE_SOLID;

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
	Particle& self = parts[i];

	for (int rx = -2; rx <= 2; ++rx)
	{
		for (int ry = -2; ry <= 2; ++ry)
		{
			if (BOUNDS_CHECK && (rx || ry))
			{
				int neighborData = pmap[y + ry][x + rx];
				switch (TYP(neighborData))
				{
				case PT_FIRE:
					parts[ID(neighborData)].ctype = PT_S;
					if (RNG::Ref().between(1, 1000) == 1) {
						sim->part_change_type(i, x, y, PT_FIRE);
						parts[i].ctype = PT_S;
					}
					break;
				}
			}
		}
	}
	return 0;
}