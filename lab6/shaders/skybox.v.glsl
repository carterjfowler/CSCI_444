/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab6
 *  File: skybox.v.glsl
 *
 *  Description:
 *      Lab6
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

// ***** VERTEX SHADER INPUT *****
layout(location=0) in vec3 vPos;     // vertex position

// ***** VERTEX SHADER OUTPUT *****

// ***** VERTEX SHADER SUBROUTINES *****

void main() {
    // pass our point through
    gl_Position = vec4( vPos, 1.0f );
}
