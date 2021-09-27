/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab3
 *  File: bezierPatch.v.glsl
 *
 *  Description:
 *      Renders a patch based off of control points
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
in vec3 vPos;     // vertex position

// ***** VERTEX SHADER OUTPUT *****


// ***** VERTEX SHADER SUBROUTINES *****


// ***** VERTEX SHADER HELPER FUNCTIONS *****


// ***** VERTEX SHADER MAIN FUNCTION *****
void main() {
    // transform our vertex into clip space
    gl_Position = vec4( vPos, 1);
}
