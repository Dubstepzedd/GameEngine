#pragma once
#include "engine/gfx/geometry/Mesh.h"
#include "engine/gfx/geometry/Buffer.h"
#include "engine/gfx/Shader.h"
#include "engine/events/Event.h"
#include "engine/core/Window.h"
#include "engine/gfx/material/Material.h"

class  Renderer {

public:

    static Renderer& getInstance()
    {
        static Renderer instance;
        return instance;
    }

    Renderer(const Renderer&) = delete;
    void operator=(const Renderer&) = delete;

	void draw(const Mesh& mesh, const glm::mat4& view, const glm::mat4& proj, AssetManager& manager);
	void clear();
    void onEvent(Event& event);

private:
    Renderer() {}

};