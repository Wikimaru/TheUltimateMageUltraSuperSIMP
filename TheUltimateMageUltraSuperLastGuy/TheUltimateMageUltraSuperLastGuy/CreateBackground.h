#pragma once
#include "Infected.h"
using namespace sf;
int createBackground(VertexArray& rVA, IntRect arena);

infected* createHorde(int numZombies, IntRect arena);