#pragma once
#include <string>
#include <vector>

enum class ShaderType {
	FLOAT, FLOAT2, FLOAT3, MAT3, MAT4, INT, INT2, INT3, BOOL 
};

static unsigned int getTypeSize(ShaderType type) {
	switch (type)
	{
		case ShaderType::FLOAT:		return sizeof(float);
		case ShaderType::FLOAT2:	return sizeof(float) * 2;
		case ShaderType::FLOAT3:	return sizeof(float) * 3;
		case ShaderType::MAT3:		return 3 * 3 * sizeof(float);
		case ShaderType::MAT4:		return  4 * 4 * sizeof(float);
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

struct BufferElement {
	std::string Name;
	uint32_t Size;
	ShaderType Type;
	uint32_t Offset;


	BufferElement(ShaderType Type, std::string Name) : Name(Name), Type(Type), Size(getTypeSize(Type)), Offset(0) {}

};

class BufferLayout {
public:
	BufferLayout(const std::initializer_list<BufferElement>& elements) : m_Elements(elements) {
		
		CalculateOffsetAndStride();
	}

	void initialize();
	void enable();
	void disable();
private:
	std::vector<BufferElement> m_Elements;
	uint32_t m_Stride;

	void CalculateOffsetAndStride() {

		uint32_t offset = 0;
		m_Stride = 0;

		for (auto& el : m_Elements) {
			el.Offset = offset;
			offset += el.Size;
			m_Stride += el.Size;
		}
	}
};

class VertexBuffer {
public:
	VertexBuffer();
	void setLayout(BufferLayout layout);
	void bind();
	void unbind();

private:
	uint32_t m_Vbo, m_Vao;
	//uint32_t m_Size, m_AttributeSize;
};

class IndexBuffer {
public:
	IndexBuffer(std::initializer_list<unsigned int> indices) : m_Indices(indices) {};
	void bind();
	void unbind();
private:
	std::vector<unsigned int> m_Indices;
};