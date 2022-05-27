#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ALPA()
{
	Identifier = "DEFAULT_PT_ALPA";
	Name = "ALPA";
	Colour = PIXPACK(0x602060);
	MenuVisible = 1;
	MenuSection = SC_PARTICLE;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = -0.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	HeatConduct = 251;
	Description = "Alpha Particle.";

	Properties = TYPE_ENERGY|PROP_LIFE_DEC|PROP_LIFE_KILL_DEC;

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
				if (!r) continue;
				rt = TYP(r);
				if (TYP(r) != PT_ALPA && TYP(r) != PT_NONE)
				{
					parts[i].vx *= 0.95f;
					parts[i].vy *= 0.95f;
				}
				switch (rt) {
				case PT_AALP:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);
					break;
				case PT_ANHE:
					sim->part_change_type(ID(r), x, y, PT_PRON);
					sim->kill_part(i);
					break;
				case PT_BE:
					if ((-2 < rx && rx < 2) && (-2 < ry && ry < 2) && TYP(pmap[y - 1][x - 1]) != PT_C && TYP(pmap[y - 1][x + 1]) != PT_C && TYP(pmap[y + 1][x - 1]) != PT_C && TYP(pmap[y + 1][x + 1]) != PT_C && TYP(pmap[y][x - 1]) != PT_C && TYP(pmap[y][x + 1]) != PT_C && TYP(pmap[y - 1][x]) != PT_C && TYP(pmap[y + 1][x]) != PT_C) {
						sim->create_part(-3, x + rx, y + ry, PT_C);
						sim->create_part(-3, x, y, PT_NEUT);
					}
				case PT_N:
					if ((-2 < rx && rx < 2) && (-2 < ry && ry < 2)) {
						sim->create_part(-3, x + rx, y + ry, PT_F);
						sim->kill_part(i);
					}
				case PT_F:
					if ((-2 < rx && rx < 2) && (-2 < ry && ry < 2)) {
						sim->create_part(-3, x + rx, y + ry, PT_Na);
						sim->kill_part(i);
					}
				case PT_Na:
					if ((-2 < rx && rx < 2) && (-2 < ry && ry < 2)){
						sim->create_part(-3, x + rx, y + ry, PT_Al26);
						sim->kill_part(i);
					}
				}
			}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 30;
	*firer = *colr;
	*fireg = *colg;
	*fireb = *colb;

	*pixel_mode |= FIRE_ADD;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	float a = RNG::Ref().between(0, 359) * 3.14159f / 180.0f;
	sim->parts[i].life = 300;
	sim->parts[i].vx = 1.5f * cosf(a);
	sim->parts[i].vy = 1.5f * sinf(a);
}
