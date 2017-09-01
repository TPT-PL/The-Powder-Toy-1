#include "simulation/Elements.h"
//#TPT-Directive ElementClass Element_E183 PT_E183 183
Element_E183::Element_E183()
{
	Identifier = "DEFAULT_PT_E183";
	Name = "E183";
	Colour = PIXPACK(0x3636FF);
	MenuVisible = 1;
	MenuSection = SC_POWDERS;
	Enabled = 1;

	Advection = 0.7f;
	AirDrag = 0.02f * CFDS;
	AirLoss = 0.94f;
	Loss = 0.95f;
	Collision = 0.0f;
	Gravity = 0.2f;
	Diffusion = 0.00f;
	HotAir = 0.000f	* CFDS;
	Falldown = 1;

	Flammable = 0;
	Explosive = 0;
	Meltable = 0;
	Hardness = 2;

	Weight = 55;

	Temperature = R_TEMP+0.0f	+273.15f;
	HeatConduct = 70;
	Description = "Test element, turns to water in contact with dust.";

	Properties = TYPE_PART;

	LowPressure = IPL;
	LowPressureTransition = NT;
	HighPressure = IPH;
	HighPressureTransition = NT;
	LowTemperature = ITL;
	LowTemperatureTransition = NT;
	HighTemperature = ITH;
	HighTemperatureTransition = NT;

	Update = &Element_E183::update;
	Graphics = NULL
}

//#TPT-Directive ElementHeader Element_CLST static int update(UPDATE_FUNC_ARGS)
int Element_E183::update(UPDATE_FUNC_ARGS)
{
	int r, rx, ry;
	float cxy = 0;
	for (rx=-2; rx<3; rx++)
		for (ry=-2; ry<3; ry++)
			if (BOUNDS_CHECK && (rx || ry))
			{
				r = pmap[y+ry][x+rx];
				if (!r)
					continue;
				if ((r&0xFF)==PT_DUST)
				{
					if (!(rand()%1500))
					{
						sim->create_part(i, x, y, PT_WATR);
						sim->kill_part(r>>8);
					}
				}
			}
	return 0;
}


Element_E183::~Element_E183() {}
