#include "simulation/ElementCommon.h"

static int update(UPDATE_FUNC_ARGS);
static int graphics(GRAPHICS_FUNC_ARGS);
static void create(ELEMENT_CREATE_FUNC_ARGS);

void Element::Element_ZBOS()
{
	Identifier = "DEFAULT_PT_ZBOS";
	Name = "ZBOS";
	Colour = PIXPACK(0x2222DD);
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
	Description = "Z Boson.";

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
	int r, rx, ry;
	for (rx = -2; rx <= 2; rx++)
		for (ry = -2; ry <= 2; ry++)
			if (BOUNDS_CHECK) {
				r = pmap[y + ry][x + rx];
				if (!r)
					r = sim->photons[y + ry][x + rx];
				if (parts[i].life == 1)
				{
					if (RNG::Ref().chance(55, 100))
					{
						if (RNG::Ref().chance(30, 55))
						{
							if (RNG::Ref().chance(10, 30))
							{
								if (RNG::Ref().chance(2, 3))
								{
									if (RNG::Ref().chance(1, 2))
									{
										sim->create_part(-1, x + 1, y + 1, PT_ELEC);
										sim->create_part(-1, x + rx, y + ry, PT_PRON);
									}
									else
									{
										sim->create_part(-1, x + 1, y + 1, PT_MUON);
										sim->create_part(-1, x + rx, y + ry, PT_AMON);
									}
								}
								else
								{
									sim->create_part(-1, x + 1, y + 1, PT_TAON);
									sim->create_part(-1, x + rx, y + ry, PT_ATON);
								}
							}
							else
							{
								if (RNG::Ref().chance(2, 3))
								{
									if (RNG::Ref().chance(1, 2))
									{
										sim->create_part(-1, x + 1, y + 1, PT_ENET);
										sim->create_part(-1, x + rx, y + ry, PT_AENT);
									}
									else
									{
										sim->create_part(-1, x + 1, y + 1, PT_MNET);
										sim->create_part(-1, x + rx, y + ry, PT_AMNT);
									}
								}
								else
								{
									sim->create_part(-1, x + 1, y + 1, PT_TNET);
									sim->create_part(-1, x + rx, y + ry, PT_ATNT);
								}
							}
						}
						else
						{
							if (RNG::Ref().chance(1, 2))
							{
								sim->create_part(-1, x + 1, y + 1, PT_UPQK);
								sim->create_part(-1, x + rx, y + ry, PT_AUPQ);
							}
							else
							{
								sim->create_part(-1, x + 1, y + 1, PT_CHQK);
								sim->create_part(-1, x + rx, y + ry, PT_ACHQ);
							}
						}
					}
					else
					{
						if (RNG::Ref().chance(2, 3))
						{
							if (RNG::Ref().chance(1, 2))
							{
								sim->create_part(-1, x + 1, y + 1, PT_DNQK);
								sim->create_part(-1, x + rx, y + ry, PT_ADNQ);
							}
							else
							{
								sim->create_part(-1, x + 1, y + 1, PT_STQK);
								sim->create_part(-1, x + rx, y + ry, PT_ASTQ);
							}
						}
						else
						{
							sim->create_part(-1, x + 1, y + 1, PT_BTQK);
							sim->create_part(-1, x + rx, y + ry, PT_ABTQ);
						}
					}
					sim->kill_part(i);
				}
			}
	return 0;
}

static int graphics(GRAPHICS_FUNC_ARGS)
{
	*firea = 255;
	*firer = 200;
	*fireg = 200;
	*fireb = 10;

	*pixel_mode |= FIRE_ADD;
	return 0;
}

static void create(ELEMENT_CREATE_FUNC_ARGS)
{
	float a = RNG::Ref().between(0, 359) * 3.14159f / 180.0f;
	sim->parts[i].life = 300;
	sim->parts[i].vx = 2.0f * cosf(a);
	sim->parts[i].vy = 2.0f * sinf(a);
}
