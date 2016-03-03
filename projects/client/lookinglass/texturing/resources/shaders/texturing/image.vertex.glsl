in vec4 vertex;
out vec2 TexCoords;

uniform mat4 projection;
uniform mat4 transform;

void main()
{
    vec4 temp = transform * vec4(vertex.xy, 0.0, 1.0);
    gl_Position = vec4(temp.x / 500 - 1, (1000 - temp.y) / 500 - 1, 0.0, 1);
 //    gl_Position = projection * transform * vec4(vertex.xy, 0.0, 1.0);
   TexCoords = vertex.zw;
}