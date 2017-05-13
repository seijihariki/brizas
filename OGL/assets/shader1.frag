#version 330
out vec3 color;

in vec4 frag_position;
in vec3 frag_normal;

uniform vec3 camera_pos;
uniform vec3 lights[10];
uniform vec3 colors[10];

void main(){
    vec3 ambient = vec3(.1, .1, .1);

    color = ambient;

    for (int i = 0; i < 10; i++)
    {
        color += colors[i] * dot(normalize(lights[i] - frag_position.xyz), normalize(frag_normal))/length(lights[i] - frag_position.xyz);
        vec3 reflection = reflect(normalize(frag_position.xyz - lights[i]), frag_normal);
        float cosine = dot(normalize(camera_pos - frag_position.xyz), reflection);
        float final_int = pow(cosine, 10);
        final_int = clamp(final_int, 0.0, 1.0);
        color += colors[i]*final_int;
    }
    //color = surface_cam;
    color = clamp(color, 0.0, 1.0);
}
