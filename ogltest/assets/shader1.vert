#version 330

layout(location = 1) in vec3 vertexPosition_modelspace;

uniform mat4 MT;
uniform mat4 MVP;

void main() {
    gl_Position = vec4(vertexPosition_modelspace, 1);
}
