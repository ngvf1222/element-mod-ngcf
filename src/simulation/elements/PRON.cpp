#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_PRON()
{
	Identifier = "DEFAULT_PT_PRON";
	Name = "PRON";
	Colour = PIXPACK(0x1E8FFF);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
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

	DefaultProperties.temp = R_TEMP + 200.0f + 273.15f;
	HeatConduct = 251;
	Description = "Positron.";

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
	int r, rt, rx, ry, nb, rrx, rry;
	for (rx = -2; rx <= 2; rx++)
		for (ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (!r)
					continue;
				rt = TYP(r);
				switch (rt)
				{
				case PT_GLAS:
					for (rrx = -1; rrx <= 1; rrx++)
						for (rry = -1; rry <= 1; rry++)
							if (x + rx + rrx >= 0 && y + ry + rry >= 0 && x + rx + rrx < XRES && y + ry + rry < YRES) {
								nb = sim->create_part(-1, x + rx + rrx, y + ry + rry, PT_EMBR);
								if (nb != -1) {
									parts[nb].tmp = 0;
									parts[nb].life = 50;
									parts[nb].temp = parts[i].temp * 0.8f;
									parts[nb].vx = float(RNG::Ref().between(-10, 10));
									parts[nb].vy = float(RNG::Ref().between(-10, 10));
								}
							}
					sim->kill_part(i);
					return 1;
				case PT_LCRY:
					parts[ID(r)].tmp2 = 0;
					break;
				case PT_H2:
					sim->part_change_type(ID(r), x + rx, y + ry, PT_PROT);
					sim->kill_part(i);
					break;
				case PT_HE:
					sim->part_change_type(ID(r), x + rx, y + ry, PT_ALPA);
					sim->kill_part(i);
					break;
				case PT_ELEC:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);
					sim->kill_part(i);
					break;
				case PT_DEUT:
					if (parts[ID(r)].life < 6000)
						parts[ID(r)].life -= 1;
					parts[ID(r)].temp = 0;
					sim->kill_part(i);
					return 1;
				case PT_EXOT:
					parts[ID(r)].tmp2 -= 5;
					parts[ID(r)].life = 1000;
					break;
				case PT_SPRK:
					parts[ID(r)].life = 0;
					break;
				case PT_NONE: //seems to speed up ELEC even if it isn't used
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
	sim->parts[i].life = 680;
	sim->parts[i].vx = 2.0f * cosf(a);
	sim->parts[i].vy = 2.0f * sinf(a);
}
