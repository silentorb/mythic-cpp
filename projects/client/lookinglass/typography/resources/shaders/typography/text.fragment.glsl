in vec2 TexCoords;
out vec4 output_color;

uniform sampler2D text;
uniform vec4 color;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    output_color = color * sampled; // * 0 + vec4(0, 1, 0, 1);
//    output_color = vec4(0, 1, 0, 1); // * 0 + vec4(0, 1, 0, 1);
}