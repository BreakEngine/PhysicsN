#include <Windows.h>

#undef min
#undef max

#include <cstring> // strlen, memcpy, etc.
#include <cstdlib> // exit
#include <cfloat>  // FLT_MAX
#include <vector>
#include <chrono>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <gl\glfw3.h>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;


#include "IEMath.h"
#include "Clock.h"
#include "Body2D.h"
#include "IShape.h"
#include "Polygon.h"
#include "Circle.h"

#include "Manifold.h"
#include "Collision.h"
#include "PhysicsN.h"
