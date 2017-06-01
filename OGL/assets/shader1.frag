#version 330
out vec3 color;

in vec2 tex_coords;
in vec4 frag_position;
in vec3 frag_normal;

uniform vec3 camera_pos;
uniform vec3 lights[10];
uniform vec3 colors[10];
uniform float intens[10];

uniform sampler2D text;
uniform sampler2D bump;

void main(){
    vec3 ambient = vec3(.1, .1, .1);

    color = ambient;
    color += texture(text, tex_coords).xyz;
    color -= ambient*5;

    vec3 normal = frag_normal;

    for (int i = 0; i < 10; i++)
    {
        color += intens[i] * colors[i] *
                (dot(normalize(lights[i] - frag_position.xyz), normalize(normal))
                /length(lights[i] - frag_position.xyz));
        vec3 reflection = reflect(normalize(frag_position.xyz - lights[i]), normal);
        float cosine = dot(normalize(camera_pos - frag_position.xyz), reflection);
        float final_int = pow(cosine, 10);
        final_int = clamp(final_int, 0.0, 1.0);
        color += intens[i] * colors[i]*final_int/distance(frag_position.xyz, lights[i]);
        color += clamp(colors[i] * pow(dot(normalize(frag_position.xyz - camera_pos), normalize(lights[i] - camera_pos)), 10000.0), 0.0, 1.0);
    }
    //color = surface_cam;
    //color = texture(bump, tex_coords).xyz;
    //color = vec3(tex_coords, 0);
    //color = ambient * texture(text, tex_coords).xyz;
    color = clamp(color, 0.0, 1.0);
}
