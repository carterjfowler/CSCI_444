/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2019
 *
 *  Project: lab1
 *  File: colorPassThrough.v.glsl
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

// ***** UNIFORMS *****
uniform mat4 mvpMtx;

// ***** ATTRIBUTES *****
in vec3 vPos;     // vertex position
in vec3 vColor;

// ***** VERTEX SHADER OUTPUT *****
out vec3 vertColorOut;

void main() {
    // transform our vertex into clip space
    gl_Position = mvpMtx * vec4(vPos, 1);
    
    // pass the color through
    vertColorOut = vColor;
}
