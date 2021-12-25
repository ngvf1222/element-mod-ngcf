#include "simulation/ElementCommon.h"

int Element_FIRE_update(UPDATE_FUNC_ARGS);
static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ANEU()
{
	Identifier = "DEFAULT_PT_ANEU";
	Name = "ANEU";
	Colour = PIXPACK(0xDF1F00);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = 0.99f;
	Gravity = 0.0f;
	Diffusion = 0.01f;
	HotAir = -0.002f * CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	DefaultProperties.temp = R_TEMP + 4.0f + 273.15f;
	HeatConduct = 60;
	Description = "Anti Neutron.";

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
	unsigned int pressureFactor = 3 + (int)sim->pv[y / CELL][x / CELL];
	for (rx = -2; rx <= 2; rx++)
		for (ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (!r) continue;
				rt = TYP(r);
				switch (rt) {
				case PT_NEUT:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);
					sim->kill_part(i);
					break;
				}
			}

	for (rx = -1; rx < 2; rx++)
		for (ry = -1; ry < 2; ry++)
			if (BOUNDS_CHECK)
			{
				r = pmap[y + ry][x + rx];
				switch (TYP(r))
				{
				case PT_DSTW:
					if (RNG::Ref().chance(3, 20))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_WATR);
				case PT_ICEI:
				case PT_SNOW:
					parts[i].vx *= 0.995f;
					parts[i].vy *= 0.995f;
					break;
				case PT_D:
					if (RNG::Ref().chance(1, 1))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_H2);
					break;
				case PT_T:
					if (RNG::Ref().chance(1, 100))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_D);
					break;
				case PT_NEUT:
					sim->create_part(i, x, y, PT_PHOT);
					sim->create_part(ID(r), x + rx, y + ry, PT_PHOT);
					sim->kill_part(i);
					break;
				case PT_DUST:
					if (RNG::Ref().chance(3, 200))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_GUNP);
					break;
				case PT_YEST:
					if (RNG::Ref().chance(3, 200))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_DYST);
					break;
				case PT_DYST:
					sim->part_change_type(ID(r), x + rx, y + ry, PT_YEST);
					break;
				case PT_GOO:
					if (RNG::Ref().chance(3, 200))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_PLEX);
					break;
				case PT_DESL:
					if (RNG::Ref().chance(3, 200))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_NITR);
					break;
				case PT_WOOD:
					if (RNG::Ref().chance(1, 2))
						if (RNG::Ref().chance(1, 20))
							sim->create_part(ID(r), x + rx, y + ry, PT_PLNT);
						else 
							continue;
					else
						if (RNG::Ref().chance(1, 20))
							sim->create_part(ID(r), x + rx, y + ry, PT_COAL);
					break;
				case PT_GAS:
					sim->create_part(ID(r), x + rx, y + ry, PT_RFRG);
					if (RNG::Ref().chance(3, 200))
						if (RNG::Ref().chance(1, 2))
							sim->part_change_type(ID(r), x + rx, y + ry, PT_DESL);
						else
							sim->part_change_type(ID(r), x + rx, y + ry, PT_OIL);
					break;
				case PT_SAWD:
					if (RNG::Ref().chance(1, 20))
						sim->create_part(ID(r), x + rx, y + ry, PT_BCOL);
					break;
				case PT_FWRK:
					if (RNG::Ref().chance(1, 20))
						sim->part_change_type(ID(r), x + rx, y + ry, PT_DUST);
					break;
				case PT_ISOZ:
					if (RNG::Ref().chance(1, 20))
						sim->create_part(ID(r), x + rx, y + ry, PT_ACID);
					break;
				case PT_TTAN:
					if (RNG::Ref().chance(1, 20))
					{
						sim->create_part(ID(r), x + rx, y + ry, PT_ANEU);
					}
					break;
				case PT_CAUS:
					sim->create_part(ID(r), x + rx, y + ry, PT_RFRG);
					break;
				default:
					break;
				}
			}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 120;
	*firer = 245;
	*fireg = 175;
	*fireb = 135;

	*pixel_mode |= FIRE_ADD;
	return 1;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	float r = RNG::Ref().between(128, 255) / 127.0f;
	float a = RNG::Ref().between(0, 359) * 3.14159f / 180.0f;
	sim->parts[i].life = RNG::Ref().between(480, 959);
	sim->parts[i].vx = r * cosf(a);
	sim->parts[i].vy = r * sinf(a);
}