#version 410 core

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 vPosition;
out vec3 vNormal;
out mat4 ModelViewMatrix_Frag;
out mat3 NormalMatrix_Frag;

uniform VertInfo {
    mat4 ModelViewMatrix, ProjectionMartrix, MVP;
    mat3 NormalMatrix;
} vert;

void main() {
    vNormal = normalize(vert.NormalMatrix * VertexNormal);
    vPosition = ( vert.ModelViewMatrix * vec4(VertexPosition, 1.0)).xyz;
    ModelViewMatrix_Frag = vert.ModelViewMatrix;
    NormalMatrix_Frag = vert.NormalMatrix;
    gl_Position = vert.MVP * vec4(VertexPosition,1.0);
}
