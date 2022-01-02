#include "simulation/ElementCommon.h"

static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_WPBS()
{
	Identifier = "DEFAULT_PT_WPBS";
	Name = "WPBS";
	Colour = PIXPACK(0xDD2222);
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
	Description = "W+ Boson.";

	Properties = TYPE_ENERGY|PROP_LIFE_DEC|PROP_LIFE_KILL_DEC;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Graphics = &graphics;
	Create = &create;
}


static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 255;
	*firer = 10;
	*fireg = 200;
	*fireb = 200;

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
