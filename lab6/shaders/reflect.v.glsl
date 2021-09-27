/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab2
 *  File: reflect.v.glsl
 *
 *  Description:
 *      Lab1
 *
 *      Pass Through Shader to apply color
 *
 *  Author:
 *      Dr. Jeffrey Paone, Colorado School of Mines
 *
 *  Notes:
 *
 */

// we are using OpenGL 4.1 Core profile
#version 410 core

// ***** VERTEX SHADER UNIFORMS *****
uniform mat4 mvpMtx;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;

// ***** VERTEX SHADER INPUT *****
layout(location=0) in vec3 vPos;      // vertex position in object space
layout(location=2) in vec3 vNormal;   // vertex normal in object space

// ***** VERTEX SHADER OUTPUT *****
out vec3 worldPos;
out vec3 worldNorm;

// ***** VERTEX SHADER SUBROUTINES *****

void main() {
    // transform our vertex into clip space
    gl_Position = mvpMtx * vec4( vPos, 1.0f );
    
    // TODO I pass the position & normal through
    worldPos = (vec4(vPos, 1) * modelMatrix).xyz;
    worldNorm = vNormal * normalMatrix;
}
