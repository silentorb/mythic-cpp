in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection;
uniform vec2 position;
uniform vec2 scale;

void main()
{
    gl_Position = projection * vec4(vertex.xy * scale + position, 0.0, 1.0);
    TexCoords = vertex.zw;
}