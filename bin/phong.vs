#version 150

uniform mat4 MVPMatrix;
uniform mat4 WorldMatrix;

in vec4 Position;
in vec3 Normal;

out vec3 WorldPos;
out vec3 WorldNormal;
out vec3 normal;


void main() {
    gl_Position = MVPMatrix * Position;
    WorldPos = vec3(WorldMatrix * Position);
    WorldNormal = mat3(WorldMatrix) * Normal;
    normal = Normal;
}
