#pragma once
#include <glad/glad.h>
#include "engine/helpers/Core.h"
#include <string>
#include <vector>
#include <iostream>


enum class  ShaderDataType {
	FLOAT, FLOAT2, FLOAT3, MAT3, MAT4, INT, INT2, INT3, BOOL 
};

static unsigned int getTypeSize(ShaderDataType type) {
	switch (type)
	{
		case ShaderDataType::FLOAT:		return sizeof(float);
		case ShaderDataType::FLOAT2:	return sizeof(float) * 2;
		case ShaderDataType::FLOAT3:	return sizeof(float) * 3;
		case ShaderDataType::MAT3:		return 3 * 3 * sizeof(float); //9 floats in a MAT3.
		case ShaderDataType::MAT4:		return  4 * 4 * sizeof(float); //16 floats in a MAT4.
		case ShaderDataType::INT:		return sizeof(int);
		case ShaderDataType::INT2:		return sizeof(int) * 2;
		case ShaderDataType::INT3:		return sizeof(int) * 3;
		case ShaderDataType::BOOL:		return sizeof(bool);
	}

	ENGINE_ASSERT(false);

	return 0;
}

static unsigned int getComponentSize(ShaderDataType type) {
	switch (type)
	{
		case ShaderDataType::FLOAT:		return 1;
		case ShaderDataType::FLOAT2:	return 2;
		case ShaderDataType::FLOAT3:	return 3;
		case ShaderDataType::MAT3:		return 3 * 3;
		case ShaderDataType::MAT4:		return  4 * 4;
		case ShaderDataType::INT:		return 1;
		case ShaderDataType::INT2:		return 2;
		case ShaderDataType::INT3:		return 3;
		case ShaderDataType::BOOL:		return 1;
	}

	ENGINE_ASSERT(false);

	return 0;
}

static GLenum getOpenGLType(const ShaderDataType type) {
	switch (type)
	{
		case ShaderDataType::FLOAT:		return GL_FLOAT;
		case ShaderDataType::FLOAT2:	return GL_FLOAT;
		case ShaderDataType::FLOAT3:	return GL_FLOAT;
		case ShaderDataType::MAT3:		return GL_FLOAT;
		case ShaderDataType::MAT4:		return GL_FLOAT;
		case ShaderDataType::INT:		return GL_INT;
		case ShaderDataType::INT2:		return GL_INT;
		case ShaderDataType::INT3:		return GL_INT;
		case ShaderDataType::BOOL:		return GL_BOOL;
	}

	ENGINE_ASSERT(false);

	return 0;
}



struct BufferElement {
	std::string m_Name;
	size_t m_Size;
	ShaderDataType m_Type;
	uint32_t m_Offset;
	bool m_Normalized;

	BufferElement(ShaderDataType type, std::string name, bool normalized = false) : m_Name(name), m_Type(type), m_Size(getTypeSize(type)), m_Offset(0), m_Normalized(normalized) {}

};

class  BufferLayout {
public:
	BufferLayout() {}
	BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
		
		calculateOffsetAndStride();
	}
	
	bool isInitialized() const {
		return !m_Elements.empty();
	}
	void set() const;
	void enable() const;
	void disable() const;

private:
	void calculateOffsetAndStride();
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride = 0;

};

class  VertexBuffer {
public:

	VertexBuffer(std::initializer_list<float> vertexData) {
		glGenBuffers(1, &m_Vbo);
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.begin(), GL_STATIC_DRAW);
		unbind();
	}

	VertexBuffer(float data[], size_t count) {
		glGenBuffers(1, &m_Vbo);
		bind();
		glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
		unbind();
	}

	~VertexBuffer() {
		glDeleteBuffers(1, &m_Vbo);
	}

	void bind() const;
	void unbind() const;

private:
	uint32_t m_Vbo;
};

class  IndexBuffer {
public:
	IndexBuffer(std::initializer_list<unsigned int> indices) : m_Count(indices.size()) {
		glGenBuffers(1, &m_Ibo);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.begin(), GL_STATIC_DRAW);
		unbind();
	};
	
	IndexBuffer(unsigned int indices[], size_t count) : m_Count(count) {
		glGenBuffers(1, &m_Ibo);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		unbind();
	};

	~IndexBuffer() {
		glDeleteBuffers(1, &m_Ibo);
	}

	void bind() const;
	void unbind() const;

	size_t getCount() const {
		return m_Count;
	}

private:
	uint32_t m_Ibo;
	size_t m_Count;
};

class  VertexArray {
public:
	VertexArray() {
		glGenVertexArrays(1, &m_Vao);
	}

	~VertexArray() {
		// Only delete if we actually own a valid ID (not moved from)
		if (m_Vao != 0) {
			glDeleteVertexArrays(1, &m_Vao);
		}
	}

	VertexArray(const VertexArray&) = delete;
	VertexArray& operator=(const VertexArray&) = delete;

	//TODO Might want to add so we can have multiple VertexBuffers with corresponding layouts.
	void setBuffer(const std::shared_ptr<VertexBuffer> buffer, const BufferLayout& layout);
	void bind() const;
	void unbind() const;


private:
	uint32_t m_Vao = 0;
	std::shared_ptr<VertexBuffer> m_Vbo;
};