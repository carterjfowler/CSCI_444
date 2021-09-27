/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab2
 *  File: colorPassThrough.v.glsl
 *
 *  Description:
 *      Lab6
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
uniform float time;

// ***** VERTEX SHADER INPUT *****
layout(location=0) in vec3 vPos;     // vertex position
layout(location=1) in vec3 vColor;   // vertex color

// ***** VERTEX SHADER OUTPUT *****
out vec3 color;

// ***** VERTEX SHADER SUBROUTINES *****

void main() {
    // transform our vertex into clip space
    gl_Position = mvpMtx * vec4( vPos, 1.0f );
    
    // pass the color through
    color = vColor;
}
