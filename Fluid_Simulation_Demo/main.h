// Fluid_Simulation_Demo.h : Include file for standard system include files,
// or project specific include files.

#pragma once

// TODO: Reference additional headers your program requires here.

struct Position {
	float x, y, z;
};

struct Particle {
	Position current, last;

	float d = 1;
	float v = 0;

	Particle(Position p) {
		current = last = p;
	}
};


