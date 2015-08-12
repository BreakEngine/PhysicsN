#pragma once

#include <Windows.h>

#undef min
#undef max

#include <cstring> // strlen, memcpy, etc.
#include <cstdlib> // exit
#include <cfloat>  // FLT_MAX
#include <vector>
#include <chrono>

#include "glut.h"
#include "IEMath.h"
#include "Clock.h"
#include "Body.h"
#include "rigidBody.h"
#include "Collision.h"
#include "Manifold.h"
#include "World.h"