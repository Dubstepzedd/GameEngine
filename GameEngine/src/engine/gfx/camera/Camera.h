#pragma once


#include <glm/glm.hpp>
#include "engine/gfx/Shader.h"

class  Camera {

public:
	Camera(const glm::vec3 pos) : m_Pos(pos), m_View(glm::mat4(1.0f)), m_Proj(glm::mat4(1.0f)) {};

	virtual void updateProj(const Shader& shader) = 0;
	virtual void updateView(const Shader& shader) = 0;

	glm::vec3 getPos() const {
		return m_Pos;
	}

	void setPos(const glm::vec3& pos) {
		m_Pos = pos;
	}

protected:
	glm::vec3 m_Pos;
	glm::mat4 m_Proj; 
	glm::mat4 m_View; 
	std::string m_ProjName = "uProj";
	std::string m_ViewName = "uView";
};