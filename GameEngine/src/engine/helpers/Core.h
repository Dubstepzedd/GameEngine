#pragma once
#include <functional>

#define ENGINE_ASSERT(x) if (!x) { __debugbreak(); }
//Bind a function with one argument/parameter.
#define ENGINE_FN_BIND_1(fn) std::bind(&fn, this, std::placeholders::_1)