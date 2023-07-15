#include "Buffer.h"
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

/* The VertexBuffer has to be bound before executing this method. */
void BufferLayout::set() const {
	uint32_t index = 0;
	for (auto& el : m_Elements) {
		glVertexAttribPointer(index, getComponentSize(el.Type), getOpenGLType(el.Type), el.Normalized, m_Stride, (const void*)el.Offset);
		index++;
	}
}

/* The VertexBuffer has to be bound before executing this method. */
void BufferLayout::enable() const {
	for (uint32_t index = 0; index < m_Elements.size(); index++)
		glEnableVertexAttribArray(index);
}

/* The VertexBuffer has to be bound before executing this method. */
void BufferLayout::disable() const {
	for (uint32_t index = 0; index < m_Elements.size(); index++)
		glDisableVertexAttribArray(index);
}


/** VertexBuffer methods **/

void VertexBuffer::bind() const {
	glBindVertexArray(m_Vao);
	m_layout.enable();
}

void VertexBuffer::unbind() const {
	m_layout.disable();
	glBindVertexArray(0);
}
