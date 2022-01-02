#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_CHQK()
{
	Identifier = "DEFAULT_PT_CHQK";
	Name = "CHQK";
	Colour = PIXPACK(0x00FF00);
	MenuVisible = 1;
	MenuSection = SC_PARTICLE;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 1;

	Weight = -1;

	HeatConduct = 61;
	Description = "Charm Quark.";

	Properties = TYPE_ENERGY | PROP_LIFE_DEC | PROP_LIFE_KILL_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &update;
	Graphics = &graphics;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	int r, rt, rx, ry;
	for (rx = -2; rx <= 2; rx++)
		for (ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				rt = TYP(r);
				if (RNG::Ref().chance(1, 1000))
				{
					if (RNG::Ref().chance(1, 20))
						sim->create_part(-1, x + rx, y + ry, PT_DNQK);
					else
						sim->create_part(-1, x + rx, y + ry, PT_STQK);
					sim->kill_part(i);
				}
				switch (rt) {
				case PT_ACHQ:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);
					break;
				}
			}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 50;
	*firer = 50;
	*fireg = 250;
	*fireb = 50;

	*pixel_mode |= FIRE_BLEND;
	return 1;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	float a = RNG::Ref().between(0, 359) * 3.14159f / 180.0f;
	sim->parts[i].life = 250 + RNG::Ref().between(0, 199);
	sim->parts[i].tmp = RNG::Ref().between(1, 2);
	sim->parts[i].vx = 2.0f * cosf(a);
	sim->parts[i].vy = 2.0f * sinf(a);
}