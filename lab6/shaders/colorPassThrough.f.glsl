/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab2
 *  File: colorPassThrough.f.glsl
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

// ***** FRAGMENT SHADER UNIFORMS *****
uniform float time;

// ***** FRAGMENT SHADER INPUT *****
in vec3 color;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

// ***** FRAGMENT SHADER SUBROUTINES *****


void main() {
    // set the output color to the interpolated color
    fragColorOut = vec4( color, 1.0f );
	
	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}
