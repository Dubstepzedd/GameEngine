#shader vertex
#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 uModel; 
uniform mat4 uView;
uniform mat4 uProj;

out vec3 v_Normal;  
out vec3 v_FragPos;  

void main() {
    gl_Position = uProj * uView * uModel * vec4(aPos, 1.0f);
    v_FragPos = vec3(uModel * vec4(aPos, 1.0));
    v_Normal = mat3(transpose(inverse(uModel))) * aNormal;
}

#shader fragment
#version 460 core

out vec4 FragColor;

in vec3 v_Normal;
in vec3 v_FragPos;

void main() {
    vec3 norm = v_Normal;
    if (length(norm) > 0.0) {
        norm = normalize(norm) * 0.5 + 0.5;
    } else {
        norm = vec3(1, 0, 0); // Safe fallback
    }
    FragColor = vec4(norm, 1.0);
}