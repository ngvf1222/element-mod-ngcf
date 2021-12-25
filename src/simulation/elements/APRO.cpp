#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_APRO()
{
	Identifier = "DEFAULT_PT_APRO";
	Name = "APRO";
	Colour = PIXPACK(0x66FFFF);
	MenuVisible = 1;
	MenuSection = SC_NUCLEAR;
	Enabled = 1;

	Advection = 0.0f;
	AirDrag = 0.00f * CFDS;
	AirLoss = 1.00f;
	Loss = 1.00f;
	Collision = 0.99f;
	Gravity = 0.0f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 0;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 0;

	Weight = -1;

	HeatConduct = 61;
	Description = "Anti Proton.";

	Properties = TYPE_ENERGY;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	DefaultProperties.life = 75;

	Update = &update;
	Graphics = &graphics;
	Create = &create;
}

static int update(UPDATE_FUNC_ARGS)
{
	sim->pv[y / CELL][x / CELL] -= .003f;
	int under = pmap[y][x];
	int utype = TYP(under);
	int uID = ID(under);
	switch (utype)
	{
	case PT_PROT:
		sim->create_part(i, x, y, PT_PHOT);
		sim->create_part(ID(utype), x + 1, y + 1, PT_PHOT);
		sim->kill_part(i);
		break;
	case PT_HE3:
		parts[uID].type = PT_LITH;
		sim->kill_part(i);
		break;
	case PT_LCRY:
		//Powered LCRY reaction: PROT->PHOT
		if (parts[uID].life > 5 && RNG::Ref().chance(1, 10))
		{
			sim->part_change_type(i, x, y, PT_PHOT);
			parts[i].life *= 2;
			parts[i].ctype = 0x3FFFFFFF;
		}
		break;
	case PT_WIFI:
		float change;
		if (parts[i].temp > 173.15f) change = -1000.0f;
		else if (parts[i].temp > 273.15f) change = -100.0f;
		else if (parts[i].temp < 473.15f) change = 1000.0f;
		else if (parts[i].temp > 373.15f) change = 100.0f;
		else change = 0.0f;
		parts[uID].temp = restrict_flt(parts[uID].temp + change, MIN_TEMP, MAX_TEMP);
		break;
	case PT_NONE:
		//slowly kill if it's not inside an element
		if (parts[i].life)
		{
			if (!--parts[i].life)
				sim->kill_part(i);
		}
		break;
	default:
		if ((sim->elements[utype].Properties & PROP_CONDUCTS) && (utype != PT_NBLE || parts[i].temp < 2273.15))
		{
			sim->create_part(-1, x, y, PT_SPRK);
			sim->kill_part(i);
			return 1;
		}
		break;
	}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 7;
	*firer = 5;
	*fireg = 85;
	*fireb = 85;

	*pixel_mode |= FIRE_BLEND;
	return 1;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	float a = RNG::Ref().between(0, 35) * 0.17453f;
	sim->parts[i].life = 680;
	sim->parts[i].vx = 2.0f * cosf(a);
	sim->parts[i].vy = 2.0f * sinf(a);
}
