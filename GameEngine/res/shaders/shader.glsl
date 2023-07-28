#shader vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
uniform mat4 uProj;
uniform mat4 uView;
out vec4 o_Color;

void main() {
	gl_Position = uProj * uView * vec4(aPos, 1.0f);
	o_Color = vec4(aColor,1.0);
}


#shader fragment
#version 460 core
out vec4 FragColor;
in vec4 o_Color;
void main() {
	FragColor = o_Color;
}


