#pragma once
#include <spdlog/spdlog.h>
#define ENGINE_ASSERT(x) if (!x) { spdlog::error("ENGINE_ASSERT triggered"); __debugbreak(); }
