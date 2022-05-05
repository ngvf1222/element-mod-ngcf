#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_B()
{
	Identifier = "DEFAULT_PT_B";
	Name = "B";
	Colour = PIXPACK(0x181818);
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

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = 100;

	HeatConduct = 251;
	Description = "Boron.";

	Properties = TYPE_SOLID | PROP_NEUTABSORB | PROP_HOT_GLOW;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 2349.00f;
	HighTemperatureTransition = PT_BL;

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
					parts[ID(neighborData)].ctype = PT_B;
					break;
				}
			}
		}
	}
	return 0;
}