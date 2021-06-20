#pragma once
#define GLENGINE 1

#ifndef DEBUG
#define DEBUG 0
#endif 

#include <SFML/Graphics.hpp>

// variable language
#include <VL/VL>

// utilities
#include <due/DUE.h>

// game lib include
#define gameLibrary 1
#include "Math/Math.h"

#include "Graphics/Graphics.h"

#include "Collisions/Collisions.h"

#include "GUI/GUI.h"

#include "Network/Network.h"

#include "TextureManagement/TextureManagement.h"

// MADE USING SFML

#ifdef DEBUG
#include <Debug.h>
#else
#define gL_log(x)
#endif

