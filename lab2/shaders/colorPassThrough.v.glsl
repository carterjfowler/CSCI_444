/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab2
 *  File: colorPassThrough.v.glsl
 *
 *  Description:
 *      Lab2
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

// ***** UNIFORMS *****
uniform mat4 mvpMtx;    // precomputed MVP Matrix
uniform float time;     // current time within our program

// ***** ATTRIBUTES *****
in vec3 vPos;           // vertex position
in vec3 vColor;         // vertex color

// ***** VERTEX SHADER OUTPUT *****
out vec3 color;         // color to apply to this vertex

// ***** VERTEX SHADER SUBROUTINES *****

// TODO C create subroutines
subroutine vec3 processVertex(vec3);
subroutine uniform processVertex vertexProcessor;
subroutine(processVertex)
vec3 passThrough(vec3 inputVertex) {
    return inputVertex;
}
subroutine(processVertex)
vec3 timeFlow(vec3 inputVertex) {
    return inputVertex + vec3( cos(inputVertex.x + time), sin(inputVertex.z + time), 0 );
}
subroutine(processVertex)
vec3 custom(vec3 inputVertex) {
    return inputVertex + vec3( 0, 0, sin(inputVertex.z + time) );
}

void main() {
    // transform our vertex into clip space
    // TODO D use subroutine
//    gl_Position = mvpMtx * vec4(vPos, 1);
    gl_Position = mvpMtx * vec4( vertexProcessor(vPos), 1 );
    
    // pass the color through
    color = vColor;
}
