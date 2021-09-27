/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2019
 *
 *  Project: lab2
 *  File: colorPassThrough.f.glsl
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
uniform float time;

// ***** FRAGMENT SHADER INPUT *****
in vec3 color;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

// ***** FRAGMENT SHADER SUBROUTINES *****

// TODO A create subroutines
subroutine vec3 processColor(vec3);
subroutine uniform processColor colorProcessor;
subroutine(processColor)
vec3 grayScale(vec3 inputColor) {
	float gray = (inputColor.x + inputColor.y + inputColor.z) / 3;
	return vec3(gray, gray, gray);
}
subroutine(processColor)
vec3 passThrough(vec3 inputColor) {
	return inputColor;
}
subroutine(processColor)
vec3 timeFlow(vec3 inputColor) {
	return inputColor * vec3( (sin(time)+1.0)/2.0,
	(cos(time)+1.0)/2.0,
	(cos(time)+1.0)/4.0 + (sin(time)+1.0)/4.0
	);
}


void main() {
    // set the output color to the interpolated color
	// TODO B use subroutine
	fragColorOut = vec4( colorProcessor(color), 1 );
	
	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}
