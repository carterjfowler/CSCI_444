/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab6
 *  File: skybox.g.glsl
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

layout(points) in;
layout(triangle_strip, max_vertices=4) out;

// ***** GEOMETRY SHADER UNIFORMS *****
uniform vec3 eyePosition;
uniform vec3 lookAtPoint;
uniform vec3 upVector;

// ***** GEOMETRY SHADER INPUT *****

// ***** GEOMETRY SHADER OUTPUT *****
// TODO E texture coordinate varying output
out vec3 textureCoord;
// ***** GEOMETRY SHADER SUBROUTINES *****

void main() {

    // TODO G compute camera basis
    vec3 z = normalize(eyePosition - lookAtPoint);
    vec3 x = normalize(cross(z, upVector));
    vec3 y = normalize(cross(x, z));



//Bottom Right -Z – Y + X
    // TODO A Top Left
    gl_Position = vec4(-1.0f, 1.0f, -1.0f , 1.0f);
    textureCoord = vec3(-z + y - x);
    EmitVertex();

    // TODO B Bottom Left
    gl_Position = vec4(-1.0f, -1.0f, -1.0f , 1.0f);
    textureCoord = vec3(-z - y - x);
    EmitVertex();

    // TODO C Top Right
    gl_Position = vec4(1.0f, 1.0f, -1.0f , 1.0f);
    textureCoord = vec3(-z + y + x);
    EmitVertex();

    // TODO D Bottom Right
    gl_Position = vec4(1.0f, -1.0f, -1.0f , 1.0f);
    textureCoord = vec3(-z - y + x);
    EmitVertex();

    EndPrimitive();
}
