#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ATON()
{
	Identifier = "DEFAULT_PT_ATON";
	Name = "ATON";
	Colour = PIXPACK(0x113333);
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
	Description = "Anti Tauon.";

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
				if (RNG::Ref().chance(1, 5))
				{
					parts[i].vx *= 1.05f;
					parts[i].vy *= 1.05f;
				}
				if (parts[i].life == 1)
				{
					if (RNG::Ref().chance(7, 20))
						if (RNG::Ref().chance(1, 2))
						{
							sim->create_part(-1, x, y, PT_PRON);
							sim->create_part(-1, x, y, PT_ENET);
							sim->create_part(-1, x, y, PT_ATNT);
						}
						else
						{
							sim->create_part(-1, x, y, PT_AMON);
							sim->create_part(-1, x, y, PT_MNET);
							sim->create_part(-1, x, y, PT_ATNT);
						}
					else
					{
						sim->create_part(-1, x, y, PT_PION);
						sim->create_part(-1, x, y, PT_ATNT);
					}
				}
				switch (rt) {
				case PT_TAON:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);;
					break;
				}
			}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 70;
	*firer = *colr;
	*fireg = *colg;
	*fireb = *colb;

	*pixel_mode |= FIRE_ADD;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	float a = RNG::Ref().between(0, 359) * 3.14159f / 180.0f;
	sim->parts[i].life = 200;
	sim->parts[i].vx = 0.1f * cosf(a);
	sim->parts[i].vy = 0.1f * sinf(a);
}
