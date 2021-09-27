/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab4
 *  File: noise2D.v.glsl
 *
 *  Description:
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
uniform Transform {
    mat4 mvpMtx;
    float time;
};

// ***** VERTEX SHADER INPUT *****
in vec3 vPos;     // vertex position

// ***** VERTEX SHADER OUTPUT *****
out vec2 point;

// ***** VERTEX SHADER SUBROUTINES *****


// ***** VERTEX SHADER HELPER FUNCTIONS *****


// ***** VERTEX SHADER MAIN FUNCTION *****
void main() {
    // transform our vertex into clip space
    point = vec2(vPos.x + cos(time), vPos.z + sin(time));
    gl_Position = mvpMtx * vec4( vPos, 1);
}
