in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 transform;
uniform mat4 texture_transform;

void main()
{
    gl_Position = projection * transform * vec4(vertex.xy, 0.0, 1.0);
    TexCoords = (texture_transform * vec4(vertex.zw, 0, 1)).xy;
}