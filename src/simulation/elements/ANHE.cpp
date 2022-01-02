#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);

void Element::Element_ANHE()
{
	Identifier = "DEFAULT_PT_ANHE";
	Name = "ANHE";
	Colour = PIXPACK(0xD20E25);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 2.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 0.99f;
	Loss = 0.30f;
	Collision = -0.10f;
	Gravity = 0.00f;
	Diffusion = 3.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = 1;

	HeatConduct = 251;
	Description = "Anti Helium.";

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
	int r, rt, rx, ry;
	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (!r) continue;
				rt = TYP(r);
				switch (rt) {
				case PT_HE:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);
					break;
				}
			}
	return 0;
}