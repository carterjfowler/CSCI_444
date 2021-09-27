/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab4
 *  File: noise2D.f.glsl
 *
 *  Description:
 *      Computes Perlin Noise
 *
 *  Author:
 *      Dr. Jeffrey Paone, Colorado School of Mines
 *
 *  Notes:
 *
 */

// we are using OpenGL 4.1 Core profile
#version 410 core
#define M_PI 3.1415926535897932384626433832795

// ***** FRAGMENT SHADER UNIFORMS *****
uniform PermutationTable {
    int permutations[512];
};
uniform Transform {
    mat4 mvpMtx;
    float time;
};

// ***** FRAGMENT SHADER INPUT *****
in vec2 point;

// ***** FRAGMENT SHADER OUTPUT *****
out vec4 fragColorOut;

// ***** FRAGMENT SHADER SUBROUTINES *****


// ***** FRAGMENT SHADER HELPER FUNCTIONS *****
float fade(float t) {
    return 6.0f * pow(t, 5) - 15.0f * pow(t, 4) + 10.0f * pow(t, 3);
}

float grad(int hash, float x, float y) {
    int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
    float u = h<8 ? x : y,                 // INTO GRADIENT DIRECTIONS.
        v = h<4 ? y : h==12||h==14 ? x : 0;
    return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

float noise(float x, float y) {
    int unitX = int(floor(x)) & 255,                  // FIND UNIT CUBE THAT
        unitY = int(floor(y)) & 255;                       // CONTAINS POINT.
    x -= floor(x);                                    // FIND RELATIVE X,Y
    y -= floor(y);                                    // OF POINT IN SQUARE.

    float u = fade(x),                                // COMPUTE FADE CURVES
        v = fade(y);                                  // FOR EACH OF X,Y.
    int A = permutations[unitX]+unitY , AA = permutations[A] ,
        AB = permutations[A+1] , B = permutations[unitX+1]+unitY ,       // HASH COORDINATES OF
        BA = permutations[B] , BB = permutations[B+1] ;          // THE SQUARE CORNERS,

    return mix( mix(grad(permutations[AA  ], x  , y  ),          // AND ADD BLENDED
        grad(permutations[BA  ], x-1, y  ), u),                  // RESULTS, FROM 4
        mix(grad(permutations[AB  ], x  , y-1),                  // CORNERS OF SQR.
        grad(permutations[BB  ], x-1, y-1), u), v);
}
// ***** FRAGMENT SHADER MAIN FUNCTION *****
void main() {
    float n = noise(point.x + cos(time + point.y), point.y + sin(time + point.x)) + 1;
    float nNorm = n / 2;
    float newN = (cos(nNorm * M_PI) + 1.0f) / 2.0f + 0.3f;
    vec3 sky = vec3(0.3, 0.3, 0.9);
    vec3 clouds = vec3(1.0, 1.0, 1.0);
    vec3 color = clamp(mix(sky, clouds, newN), 0.0f, 1.0f);
    // set the output color to the interpolated color
    fragColorOut = vec4(color, 1);

	// if viewing the backside of the fragment, 
	// reverse the colors as a visual cue
	if( !gl_FrontFacing ) {
		fragColorOut.rgb = fragColorOut.bgr;
	}
}