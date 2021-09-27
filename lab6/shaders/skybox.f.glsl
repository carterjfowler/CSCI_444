/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab6
 *  File: skybox.f.glsl
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

// ***** FRAGMENT SHADER UNIFORMS *****
uniform samplerCube cubeMap;

// ***** FRAGMENT SHADER INPUT *****
// TODO F texture coordinate varying input
in vec3 textureCoord;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

// ***** FRAGMENT SHADER SUBROUTINES *****


void main() {
	// TODO H look up texel from cubeMap
//    fragColorOut = vec4( gl_FragCoord.xy/640.0f, 0.0f, 1.0f );
	fragColorOut = texture(cubeMap, textureCoord);

	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}
