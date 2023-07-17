#pragma once
#include "GL/glew.h"
#include <string>
#include <vector>
#include <iostream>


enum class ShaderType {
	FLOAT, FLOAT2, FLOAT3, MAT3, MAT4, INT, INT2, INT3, BOOL 
};

static unsigned int getTypeSize(ShaderType type) {
	switch (type)
	{
		case ShaderType::FLOAT:		return sizeof(float);
		case ShaderType::FLOAT2:	return sizeof(float) * 2;
		case ShaderType::FLOAT3:	return sizeof(float) * 3;
		case ShaderType::MAT3:		return 3 * 3 * sizeof(float); //9 floats in a MAT3.
		case ShaderType::MAT4:		return  4 * 4 * sizeof(float); //16 floats in a MAT4.
		case ShaderType::INT:		return sizeof(int);
		case ShaderType::INT2:		return sizeof(int) * 2;
		case ShaderType::INT3:		return sizeof(int) * 3;
		case ShaderType::BOOL:		return sizeof(bool);
	}

	//Assert here.

	return 0;
}

static unsigned int getComponentSize(ShaderType type) {
	switch (type)
	{
		case ShaderType::FLOAT:		return 1;
		case ShaderType::FLOAT2:	return 2;
		case ShaderType::FLOAT3:	return 3;
		case ShaderType::MAT3:		return 3 * 3;
		case ShaderType::MAT4:		return  4 * 4;
		case ShaderType::INT:		return 1;
		case ShaderType::INT2:		return 2;
		case ShaderType::INT3:		return 3;
		case ShaderType::BOOL:		return 1;
	}

	//Assert here

	return 0;
}

static GLenum getOpenGLType(const ShaderType type) {
	switch (type)
	{
		case ShaderType::FLOAT:		return GL_FLOAT;
		case ShaderType::FLOAT2:	return GL_FLOAT;
		case ShaderType::FLOAT3:	return GL_FLOAT;
		case ShaderType::MAT3:		return GL_FLOAT;
		case ShaderType::MAT4:		return GL_FLOAT;
		case ShaderType::INT:		return GL_INT;
		case ShaderType::INT2:		return GL_INT;
		case ShaderType::INT3:		return GL_INT;
		case ShaderType::BOOL:		return GL_BOOL;
	}
}



struct BufferElement {
	std::string Name;
	uint32_t Size;
	ShaderType Type;
	uint32_t Offset;
	bool Normalized;

	BufferElement(ShaderType type, std::string name, bool normalized = false) : Name(name), Type(type), Size(getTypeSize(type)), Offset(0), Normalized(normalized) {}

};

class BufferLayout {
public:
	BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
		
		calculateOffsetAndStride();
	}
	
	void set() const;
	void enable() const;
	void disable() const;

private:
	void calculateOffsetAndStride();
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride;

};

class VertexBuffer {
public:
	//TODO Fix this. Restructure this.

	//Has to know the amount of vertices it has. Create a better creation architecture.
	VertexBuffer(std::initializer_list<float> vertexData) {
		glGenBuffers(1, &m_Vbo);
		bind();
		glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.begin(), GL_STATIC_DRAW);
		unbind();
	}

	VertexBuffer(float data[], uint32_t sizeBytes) {
		glGenBuffers(1, &m_Vbo);
		bind();
		glBufferData(GL_ARRAY_BUFFER, sizeBytes, data, GL_STATIC_DRAW);
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

class IndexBuffer {
public:
	IndexBuffer(std::initializer_list<unsigned int> indices) : m_Count(indices.size()) {
		glGenBuffers(1, &m_Ibo);
		bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.begin(), GL_STATIC_DRAW);
		unbind();
	};
	~IndexBuffer() {
		glDeleteBuffers(1, &m_Ibo);
	}

	void bind() const;
	void unbind() const;

	uint32_t getCount() const {
		return m_Count;
	}

private:
	uint32_t m_Ibo;
	uint32_t m_Count;
};

class VertexArray {
public:
	VertexArray() {
		glGenVertexArrays(1, &m_Vao);
	}
	~VertexArray() {
		glDeleteVertexArrays(1, &m_Vao);
	}

	//TODO Might want to add so we can have multiple VertexBuffers with corresponding layouts.
	void setBuffer(const VertexBuffer& buffer, const BufferLayout& layout);
	void bind() const;
	void unbind() const;


private:
	uint32_t m_Vao;
};