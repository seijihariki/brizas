#version 330
out vec3 color;

in vec4 frag_position;
in vec3 frag_normal;

void main(){
    vec3 ambient = vec3(.02, .02, .02);

    vec3 point_light_1 = vec3(5, 0, 5);
    vec3 light_color_1 = vec3(1, 0, 0);

    vec3 point_light_2 = vec3(0, -5, -5);
    vec3 light_color_2 = vec3(0, 0, 1);

    vec3 point_light_3 = vec3(0, -5, 5);
    vec3 light_color_3 = vec3(0, 1, 0);

    float I1 = dot(normalize(point_light_1 - frag_position.xyz), normalize(frag_normal));
    float I2 = dot(normalize(point_light_2 - frag_position.xyz), normalize(frag_normal));
    float I3 = dot(normalize(point_light_3 - frag_position.xyz), normalize(frag_normal));

    color =  ambient + light_color_1 * I1 + light_color_2 * I2 + light_color_3 * I3;
}
