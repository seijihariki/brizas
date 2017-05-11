#version 330
out vec3 color;

in vec4 frag_position;
in vec3 frag_normal;

uniform vec3 lights[10];
uniform vec3 colors[10];

void main(){
    vec3 ambient = vec3(.1, .1, .1);

    color = ambient;

    for (int i = 0; i < 10; i++)
        color += colors[i] * dot(normalize(lights[i] - frag_position.xyz), normalize(frag_normal));
}
