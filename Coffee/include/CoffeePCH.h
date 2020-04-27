#pragma once

#include <algorithm>
#include <array>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <glm/glm.hpp>

#include "Coffee/Core/Logging.h"
#include "Coffee/Debug/Instrumentation.h"

#if CF_PLATFORM_WINDOWS
#include <Windows.h>
#endif