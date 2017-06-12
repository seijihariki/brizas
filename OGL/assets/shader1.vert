#version 330

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 texture_coords;
layout(location = 2) in vec3 normal_vector;

out vec2 tex_coords;
out vec4 frag_position;
out vec3 frag_normal;

uniform mat4 MT;
uniform mat4 MVP;

void main() {
    tex_coords = texture_coords;
    frag_position = MT * vec4(vertexPosition_modelspace, 1);
    frag_normal = normalize(MT * vec4(normal_vector, 0)).xyz;
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1);
}
