#pragma once


#include "engine/gfx/Buffer.h"
#include "engine/gfx/Shader.h"
#include "engine/events/Event.h"
#include "engine/core/Window.h"

class  Renderer {

public:

    static Renderer& getInstance()
    {
        static Renderer instance;

        return instance;
    }
    Renderer(const Renderer&) = delete;
    void operator=(const Renderer&) = delete;

	void draw(const VertexArray& vArr, const IndexBuffer& iBuff);
	void clear();
    void onEvent(Event& event);
	void bindShader(Shader* shader);
	void unbindShader();
    Shader* getBoundShader() { return m_Shader; }

private:
    Renderer() {}
    Shader* m_Shader = nullptr;

};