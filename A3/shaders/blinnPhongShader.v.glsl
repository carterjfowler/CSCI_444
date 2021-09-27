#version 410 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 vPosition;
out vec3 vNormal;

layout(std140) uniform VertInfo {
    mat4 ModelViewMatrix;
    mat3 NormalMatrix;
    mat4 ProjectionMatrix;
    mat4 MVP;
} vert;

void main() {
    vNormal = normalize(vert.NormalMatrix * VertexNormal);
    vPosition = ( vert.ModelViewMatrix * vec4(VertexPosition, 1.0)).xyz;
    gl_Position = vert.MVP * vec4(VertexPosition,1.0);
}
