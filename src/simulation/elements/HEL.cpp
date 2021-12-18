#include "simulation/ElementCommon.h"
static int update(UPDATE_FUNC_ARGS);

void Element::Element_HEL()
{
	Identifier = "DEFAULT_PT_HEL";
	Name = "He-l";
	Colour = PIXPACK(0x2BE3CD);
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
	Meltable = 5;
	Hardness = 1;

	Weight = 90;

	DefaultProperties.temp = R_TEMP - 292.0f + 273.15f;
	HeatConduct = 251;
	Description = "Liquid Helium.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = 4.22f;
	HighTemperatureTransition = PT_HE;

	Update = &update;
}

static int update(UPDATE_FUNC_ARGS)
{
	if (parts[i].temp < 274.10 && sim->pv[y / CELL][x / CELL] > 25.0f)
		sim->create_part(i, x, y, PT_HES);
	return 0;

	int r, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y + ry][x + rx];
				if (TYP(r) != PT_HEL && TYP(r) != PT_NONE)
				{
					sim->create_part(-1, x+rx, y+ry, PT_DUST);
				}
				return 1;
			}
}