#include "Mesh.h"

void Mesh::bind() const
{
	m_VertexArray->bind();
	m_IndexBuffer->bind();
}

void Mesh::unbind() const
{
	m_VertexArray->unbind();
	m_IndexBuffer->unbind();
}