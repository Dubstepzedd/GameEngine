#shader vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 oColor;
void main() {
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	oColor = aColor;
}


#shader fragment
#version 460 core
out vec4 FragColor;
in vec3 oColor;
void main() {
	FragColor = vec4(oColor.x, oColor.y, oColor.z, 1.0);
}


