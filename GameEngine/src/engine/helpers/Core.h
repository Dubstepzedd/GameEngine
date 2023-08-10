#pragma once

#define ENGINE_ASSERT(x) if (!x) { __debugbreak(); }
