/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab3
 *  File: bezierPatch.f.glsl
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

// ***** FRAGMENT SHADER UNIFORMS *****


// ***** FRAGMENT SHADER INPUT *****
// TODO L - receive the patch point
in vec3 color;
// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

// ***** FRAGMENT SHADER SUBROUTINES *****


// ***** FRAGMENT SHADER HELPER FUNCTIONS *****


// ***** FRAGMENT SHADER MAIN FUNCTION *****
void main() {
	// TODO M - set the color to the patch point
	fragColorOut = vec4( color, 1 );

	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}
