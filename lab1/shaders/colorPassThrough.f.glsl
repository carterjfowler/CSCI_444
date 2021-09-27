/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2019
 *
 *  Project: lab1
 *  File: colorPassThrough.f.glsl
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


// ***** FRAGMENT SHADER INPUT *****
in vec3 vertColorOut;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

void main() {
    // set the output color to the interpolated color
    fragColorOut = vec4(vertColorOut, 1);
	
	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}
