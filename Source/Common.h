#pragma once

#ifdef _WINDOWS

#include "targetver.h"

#define NOMINMAX

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <array>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <cstdint>
#include <map>
#include <functional>
#include <unordered_set>
#include <iterator>
#include <ctime>
#include <type_traits>
#include <cassert>
#include <utility>
#include <sstream>
#include <tuple>


#endif