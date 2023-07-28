#include "engine/gfx/Buffer.h"
#include "GL/glew.h"

/** BufferLayout methods **/
void BufferLayout::calculateOffsetAndStride() {

	uint32_t offset = 0;
	m_Stride = 0;

	for (auto& el : m_Elements) {
		el.Offset = offset;
		offset += el.Size;
		m_Stride += el.Size;
	}
}

void BufferLayout::set() const {
	uint32_t index = 0;
	for (auto& el : m_Elements) {
		glVertexAttribPointer(index, getComponentSize(el.Type), getOpenGLType(el.Type), el.Normalized, m_Stride, (const void*)el.Offset);
		index++;
	}
}

void BufferLayout::enable() const {
	for (uint32_t index = 0; index < m_Elements.size(); index++)
		glEnableVertexAttribArray(index);
}

void BufferLayout::disable() const {
	for (uint32_t index = 0; index < m_Elements.size(); index++)
		glDisableVertexAttribArray(index);
}


/** VertexBuffer methods **/

void VertexBuffer::bind() const {
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
}

void VertexBuffer::unbind() const {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


/** VertexArray methods **/

void VertexArray::setBuffer(const VertexBuffer& buffer, const BufferLayout& layout) {
	bind();
	buffer.bind();
	layout.enable();
	layout.set();
	buffer.unbind();
	unbind();

}

void VertexArray::bind() const {
	glBindVertexArray(m_Vao);
}

void VertexArray::unbind() const {
	glBindVertexArray(0);
}

/** IndexBuffer methods **/

void IndexBuffer::bind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ibo);
}

void IndexBuffer::unbind() const {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
