/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab2
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

// ***** FRAGMENT SHADER UNIFORMS *****
uniform samplerCube cubeMap;
uniform vec3 eyePosition;

// ***** FRAGMENT SHADER INPUT *****
in vec3 worldPos;
in vec3 worldNorm;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

// ***** FRAGMENT SHADER SUBROUTINES *****


void main() {
    // TODO J compute incident ray & reflected ray
	vec3 incidentRay = normalize(worldPos - eyePosition);
	vec3 reflectedRay = reflect(incidentRay, normalize(worldNorm));

    // TODO K do texture lookup
//    fragColorOut = vec4( 0.0f, 1.0f, 0.0f, 1.0f );
	fragColorOut = texture(cubeMap, reflectedRay);

	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}
