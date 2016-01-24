in vec2 TexCoords;
out vec4 output_color;

uniform sampler2D text;

void main()
{
    output_color = texture(text, TexCoords);
}