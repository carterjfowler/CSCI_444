/** @file ShaderUtils3.hpp
 * @brief Helper functions to work with OpenGL Shaders
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 09 Jun 2020
 * @version 2.0
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 *
 *	@warning NOTE: This header file depends upon GLEW
 */

#ifndef __CSCI441_SHADEREUTILS_H__
#define __CSCI441_SHADEREUTILS_H__

#include <GL/glew.h>

#include <stdio.h>
#include <string.h>

#include <fstream>
#include <string>

////////////////////////////////////////////////////////////////////////////////

namespace CSCI441_INTERNAL {
	namespace ShaderUtils {
		static bool sDEBUG = true;

		void enableDebugMessages();
		void disableDebugMessages();

		const char* GL_type_to_string( GLenum type );
		const char* GL_shader_type_to_string( GLenum type );
		const char* GL_primitive_type_to_string( GLenum type );

		void readTextFromFile( const char* filename, char* &output );
		GLuint compileShader( const char *filename, GLenum shaderType );

		void printLog( GLuint handle );
		GLboolean printSubroutineInfo( GLuint handle, GLenum shaderStage, GLboolean printHeader );
		void printShaderProgramInfo( GLuint handle );
        void printShaderProgramInfo( GLuint handle, GLboolean hasVertexShader, GLboolean hasTessControlShader, GLboolean hasTessEvalShader, GLboolean hasGeometryShader, GLboolean hasFragmentShader, GLboolean useLastNewLine );
	}
}

////////////////////////////////////////////////////////////////////////////////

inline void CSCI441_INTERNAL::ShaderUtils::enableDebugMessages() {
	sDEBUG = true;
}

inline void CSCI441_INTERNAL::ShaderUtils::disableDebugMessages() {
	sDEBUG = false;
}

// readTextFromFile() //////////////////////////////////////////////////////////////
//
//  Reads in a text file as a single string. Used to aid in shader loading.
//
////////////////////////////////////////////////////////////////////////////////
inline void CSCI441_INTERNAL::ShaderUtils::readTextFromFile(const char *filename, char* &output){
    std::string buf = std::string("");
    std::string line;

    std::ifstream in(filename);
    if( !in.is_open() ) {
    	fprintf( stderr, "[ERROR]: Could not open file %s\n", filename );
    	return;
    }
    while( std::getline(in, line) ) {
        buf += line + "\n";
    }
    output = new char[buf.length()+1];
    strncpy(output, buf.c_str(), buf.length());
    output[buf.length()] = '\0';

    in.close();
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_type_to_string(GLenum type) {
  switch(type) {
    case GL_BOOL: return "bool";
    case GL_INT: return "int";
    case GL_FLOAT: return "float";
    case GL_FLOAT_VEC2: return "vec2";
    case GL_FLOAT_VEC3: return "vec3";
    case GL_FLOAT_VEC4: return "vec4";
    case GL_FLOAT_MAT2: return "mat2";
    case GL_FLOAT_MAT3: return "mat3";
    case GL_FLOAT_MAT4: return "mat4";
    case GL_SAMPLER_2D: return "sampler2D";
    case GL_SAMPLER_3D: return "sampler3D";
    case GL_SAMPLER_CUBE: return "samplerCube";
    case GL_SAMPLER_2D_SHADOW: return "sampler2DShadow";
    default: break;
  }
  return "other";
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(GLenum type) {
  switch(type) {
    case GL_VERTEX_SHADER: return "Vertex Shader";
    case GL_TESS_CONTROL_SHADER: return "Tess Ctrl Shader";
    case GL_TESS_EVALUATION_SHADER: return "Tess Eval Shader";
    case GL_GEOMETRY_SHADER: return "Geometry Shader";
    case GL_FRAGMENT_SHADER: return "Fragment Shader";
    default: break;
  }
  return "other";
}

inline const char* CSCI441_INTERNAL::ShaderUtils::GL_primitive_type_to_string(GLenum type) {
    switch(type) {
        case GL_POINTS: return "Points";
        case GL_LINES: return "Lines";
        case GL_LINE_STRIP: return "Line Strip";
        case GL_LINE_LOOP: return "Line Loop";
        case GL_LINES_ADJACENCY: return "Line Adjacency";
        case GL_TRIANGLES: return "Triangles";
        case GL_TRIANGLE_STRIP: return "Triangle Strip";
        case GL_TRIANGLES_ADJACENCY: return "Triangle Adjacency";
        case GL_PATCHES: return "Patches";
        default: break;
    }
    return "other";
}

// printLog() //////////////////////////////////////////////////////////////////
//
//  Check for errors from compiling or linking a vertex/fragment/shader program
//      Prints to terminal
//
////////////////////////////////////////////////////////////////////////////////
inline void CSCI441_INTERNAL::ShaderUtils::printLog( GLuint handle ) {
	int status;
    int infologLength = 0;
    int maxLength;
    bool isShader;

    /* check if the handle is to a vertex/fragment shader */
    if( glIsShader( handle ) ) {
        glGetShaderiv(  handle, GL_INFO_LOG_LENGTH, &maxLength );

        isShader = true;
    }
    /* check if the handle is to a shader program */
    else {
        glGetProgramiv( handle, GL_INFO_LOG_LENGTH, &maxLength );

        isShader = false;
    }

    /* create a buffer of designated length */
    char infoLog[maxLength];

    if( isShader ) {
    	glGetShaderiv( handle, GL_COMPILE_STATUS, &status );
    	if( sDEBUG ) printf( "[INFO]: |   Shader  Handle %2d: Compile%-26s |\n", handle, (status == 1 ? "d Successfully" : "r Error") );

        /* get the info log for the vertex/fragment shader */
        glGetShaderInfoLog(  handle, maxLength, &infologLength, infoLog );

        if( infologLength > 0 ) {
			/* print info to terminal */
        	if( sDEBUG ) printf( "[INFO]: |   %s Handle %d: %s\n", (isShader ? "Shader" : "Program"), handle, infoLog );
        }
    } else {
    	glGetProgramiv( handle, GL_LINK_STATUS, &status );
    	if( sDEBUG ) printf("[INFO]: |   Program Handle %2d: Linke%-28s |\n", handle, (status == 1 ? "d Successfully" : "r Error") );

        /* get the info log for the shader program */
        glGetProgramInfoLog( handle, maxLength, &infologLength, infoLog );

        if( infologLength > 0 ) {
			/* print info to terminal */
        	if( sDEBUG ) printf( "[INFO]: |   %s Handle %d: %s\n", (isShader ? "Shader" : "Program"), handle, infoLog );
        }
    }
}

inline GLboolean CSCI441_INTERNAL::ShaderUtils::printSubroutineInfo( GLuint handle, GLenum shaderStage, GLboolean printHeader ) {
	int params, params2;
	int *params3 = NULL;

	glGetProgramStageiv(handle, shaderStage, GL_ACTIVE_SUBROUTINE_UNIFORMS, &params);
	if( params > 0 ) {
        if( printHeader ) printf( "[INFO]: >--------------------------------------------------------<\n");
        printf("[INFO]: | GL_ACTIVE_SUBROUTINE_UNIFORMS (%-15s): %5i |\n", CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(shaderStage), params);
        for(int i = 0; i < params; i++ ) {
            char name[256];
            int max_length = 256;
            int actual_length = 0;

            glGetActiveSubroutineUniformName( handle, shaderStage, i, max_length, &actual_length, name );
            glGetActiveSubroutineUniformiv( handle, shaderStage, i, GL_NUM_COMPATIBLE_SUBROUTINES, &params2 );
            params3 = (int*)malloc(sizeof(int) * params2);
            glGetActiveSubroutineUniformiv( handle, shaderStage, i, GL_COMPATIBLE_SUBROUTINES, params3 );
            GLint loc = glGetSubroutineUniformLocation( handle, shaderStage, name );

            printf("[INFO]: |   %i) name: %-15s #subRoutines: %-5i loc: %2i |\n", i, name, params2, loc );

            for(int j = 0; j < params2; j++ ) {
                GLint idx = params3[j];

                char name2[64];
                int max_length2 = 64;
                int actual_length2 = 0;
                glGetActiveSubroutineName( handle, shaderStage, idx, max_length2, &actual_length2, name2 );

                printf("[INFO]: |     %i) subroutine: %-25s index: %2i |\n", j, name2, idx );
            }

            free(params3);
        }
	}
	return (params > 0);
}

inline void CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( GLuint handle ) {
    fprintf(stderr, "[WARN]: CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo(GLuint) is deprecated.  Replace with printShaderProgramInfo(GLuint, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean, GLboolean)");
    printShaderProgramInfo(handle, false, false, false, false, false, true);
}

inline void CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( GLuint handle, GLboolean hasVertexShader, GLboolean hasTessControlShader, GLboolean hasTessEvalShader, GLboolean hasGeometryShader, GLboolean hasFragmentShader, GLboolean useLastNewLine = true ) {
	int params;

    GLuint shaders[6];
    int max_count = 6;
    int actual_count;
    glGetAttachedShaders( handle, max_count, &actual_count, shaders );
    if(actual_count > 0) {
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
        if( sDEBUG ) printf("[INFO]: | GL_ATTACHED_SHADERS: %33i |\n", actual_count);
        for(int i = 0; i < actual_count; i++ ) {
            GLint shaderType;
            glGetShaderiv( shaders[i], GL_SHADER_TYPE, &shaderType );
            if( sDEBUG ) printf("[INFO]: |   %i) %-38s Handle: %2i |\n", i, GL_shader_type_to_string(shaderType), shaders[i]);
        }

    }

    if(hasVertexShader) {
        glGetProgramiv( handle, GL_ACTIVE_ATTRIBUTES, &params );
        if( params > 0 ) {
            if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
            if( sDEBUG ) printf( "[INFO]: | GL_ACTIVE_ATTRIBUTES: %32i |\n", params );
            for( int i = 0; i < params; i++ ) {
                char name[64];
                int max_length = 64;
                int actual_length = 0;
                int size = 0;
                GLenum type;
                glGetActiveAttrib( handle, i, max_length, &actual_length, &size, &type, name );
                if( size > 1 ) {
                    for( int j = 0; j < size; j++ ) {
                        char long_name[64];
                        sprintf( long_name, "%s[%i]", name, j );
                        int location = glGetAttribLocation( handle, long_name );
                        if( sDEBUG ) printf( "[INFO]: |   %i) type: %-15s name: %-13s loc: %2i |\n", i, GL_type_to_string( type ), long_name, location );
                    }
                } else {
                    int location = glGetAttribLocation( handle, name );
                    if( sDEBUG ) printf( "[INFO]: |   %i) type: %-15s name: %-13s loc: %2i |\n",i, GL_type_to_string( type ), name, location );
                }
            }
        }
    }

    glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &params);
    if( params > 0 ) {
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n" );
        if( sDEBUG ) printf("[INFO]: | GL_ACTIVE_UNIFORMS: %34i |\n", params);
        for(int i = 0; i < params; i++) {
            char name[64];
            int max_length = 64;
            int actual_length = 0;
            int size = 0;
            GLenum type;
            glGetActiveUniform( handle, i, max_length, &actual_length, &size, &type, name );
            if(size > 1) {
                for(int j = 0; j < size; j++) {
                    char long_name[64];
                    sprintf(long_name, "%s[%i]", name, j);
                    int location = glGetUniformLocation(handle, long_name);
                    if( sDEBUG ) printf("[INFO]: |  %2i) type: %-15s name: %-13s loc: %2i |\n",
                            i, GL_type_to_string(type), long_name, location);
                }
            } else {
                int location = glGetUniformLocation(handle, name);
                if( sDEBUG ) printf("[INFO]: |  %2i) type: %-15s name: %-13s loc: %2i |\n",
                        i, GL_type_to_string(type), name, location);
            }
        }
    }

    int vsCount, tcsCount, tesCount, gsCount, fsCount;
    vsCount = tcsCount = tesCount = gsCount = fsCount = 0;

    glGetProgramiv(handle, GL_ACTIVE_UNIFORM_BLOCKS, &params);
    if( params > 0 ) {
        if( sDEBUG ) printf( "[INFO]: >--------------------------------------------------------<\n");
        if( sDEBUG ) printf("[INFO]: | GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS: %20d |\n", params);
        for(int i = 0; i < params; i++ ) {
            int params2;
            glGetActiveUniformBlockiv(handle, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &params2 );

            int actualLen;
            glGetActiveUniformBlockiv(handle, i, GL_UNIFORM_BLOCK_NAME_LENGTH, &actualLen);
            char *name = (char *)malloc(sizeof(char) * actualLen);
            glGetActiveUniformBlockName(handle, i, actualLen, NULL, name);

            GLuint *indices = (GLuint*)malloc(params2*sizeof(GLuint));
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)indices);

            GLint *offsets = (GLint*)malloc(params2*sizeof(GLint));
            glGetActiveUniformsiv(handle, params2, indices, GL_UNIFORM_OFFSET, offsets);

            if( sDEBUG ) printf("[INFO]: | %d) %-34s   # Uniforms: %2d |\n", i, name, params2);

            GLint vs, tcs, tes, gs, fs;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER, &vs);			if( vs ) vsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_CONTROL_SHADER, &tcs);	if( tcs) tcsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_TESS_EVALUATION_SHADER, &tes);	if( tes) tesCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER, &gs);			if( gs ) gsCount++;
            glGetActiveUniformBlockiv( handle, i, GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER, &fs);			if( fs ) fsCount++;
            if( sDEBUG ) printf("[INFO]: |   Used in: %-4s %-8s %-8s %-3s %-4s   Shader(s) |\n", (vs ? "Vert" : ""), (tcs ? "TessCtrl" : ""), (tes ? "TessEval" : ""), (gs ? "Geo" : ""), (fs ? "Frag" : ""));

            int maxUniLength;
            glGetProgramiv(handle, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniLength);
            char *name2 = (char *)malloc(sizeof(char) * maxUniLength);
            for(int j = 0; j < params2; j++) {
                GLenum type;
                int uniSize;
                glGetActiveUniform(handle, indices[j], maxUniLength, &actualLen, &uniSize, &type, name2);

                if( sDEBUG ) printf("[INFO]: |  %2d) type: %-5s name: %-10s index: %2d offset: %2d |\n", j, GL_type_to_string(type), name2, indices[j], offsets[j]);
            }
        }

        if( vsCount + tcsCount + tesCount + gsCount + vsCount > 0 ) {
            if( sDEBUG ) printf( "[INFO]: | Shader Uniform Block Counts                            |\n");
            if( hasVertexShader ) {
                GLint maxVertexUniformBlocks = 0;
                glGetIntegerv( GL_MAX_VERTEX_UNIFORM_BLOCKS, &maxVertexUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Vertex   Shader Uniform Blocks: %16d/%2d  |\n", vsCount, maxVertexUniformBlocks );
            }
            if( hasTessControlShader ) {
                GLint maxTessControlUniformBlocks = 0;
                glGetIntegerv( GL_MAX_TESS_CONTROL_UNIFORM_BLOCKS, &maxTessControlUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Tess Ctrl Shader Uniform Blocks: %15d/%2d  |\n", tcsCount, maxTessControlUniformBlocks );
            }
            if( hasTessEvalShader ) {
                GLint maxTessEvalUniformBlocks = 0;
                glGetIntegerv( GL_MAX_TESS_EVALUATION_UNIFORM_BLOCKS, &maxTessEvalUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Tess Eval Shader Uniform Blocks: %15d/%2d  |\n", tesCount, maxTessEvalUniformBlocks );
            }
            if( hasGeometryShader ) {
                GLint maxGeometryUniformBlocks = 0;
                glGetIntegerv( GL_MAX_GEOMETRY_UNIFORM_BLOCKS, &maxGeometryUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Geometry Shader Uniform Blocks: %16d/%2d  |\n", gsCount, maxGeometryUniformBlocks );
            }
            if( hasFragmentShader ) {
                GLint maxFragmentUniformBlocks = 0;
                glGetIntegerv( GL_MAX_FRAGMENT_UNIFORM_BLOCKS, &maxFragmentUniformBlocks );

                if( sDEBUG ) printf( "[INFO]: |   Fragment Shader Uniform Blocks: %16d/%2d  |\n", fsCount, maxFragmentUniformBlocks );
            }
        }
    }

    if( sDEBUG ) {
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);

        if(hasGeometryShader) {
            if( major > 3 || (major >= 3 && minor >= 2)  ) {
                GLint verticesOut, inputType, outputType;
                glGetProgramiv(handle, GL_GEOMETRY_VERTICES_OUT, &verticesOut);
                glGetProgramiv(handle, GL_GEOMETRY_INPUT_TYPE,   &inputType);
                glGetProgramiv(handle, GL_GEOMETRY_OUTPUT_TYPE,  &outputType);

                printf( "[INFO]: >--------------------------------------------------------<\n");
                printf( "[INFO]: | GEOMETRY SHADER PRIMITIVE I/O                          |\n");
                printf( "[INFO]: |   Input Type: %40s |\n", GL_primitive_type_to_string(inputType) );
                printf( "[INFO]: |   Output Type: %39s |\n", GL_primitive_type_to_string(outputType) );
                printf( "[INFO]: |   Max Vertices Out: %34d |\n", verticesOut );
            }
        }

        if( major >= 4 ) {
            GLboolean printHeader = GL_TRUE;
            if( hasVertexShader   )     printHeader = printSubroutineInfo( handle, GL_VERTEX_SHADER, printHeader );
			if( hasTessControlShader)   printHeader = printSubroutineInfo( handle, GL_TESS_CONTROL_SHADER, printHeader );
			if( hasTessEvalShader)      printHeader = printSubroutineInfo( handle, GL_TESS_EVALUATION_SHADER, printHeader );
			if( hasGeometryShader )     printHeader = printSubroutineInfo( handle, GL_GEOMETRY_SHADER, printHeader );
			if( hasFragmentShader )     printHeader = printSubroutineInfo( handle, GL_FRAGMENT_SHADER, printHeader );
		}

		if(useLastNewLine) printf( "[INFO]: \\--------------------------------------------------------/\n\n");
	}
}

// compileShader() ///////////////////////////////////////////////////////////////
//
//  Compile a given shader program
//
////////////////////////////////////////////////////////////////////////////////
inline GLuint CSCI441_INTERNAL::ShaderUtils::compileShader( const char *filename, GLenum shaderType ) {
	GLuint shaderHandle = 0;
	char *shaderString;

    /* create a handle to our shader */
	shaderHandle = glCreateShader( shaderType );

    /* read in each text file and store the contents in a string */
    readTextFromFile( filename, shaderString );

    /* send the contents of each program to the GPU */
    glShaderSource( shaderHandle, 1, (const char**)&shaderString, NULL );

    /* we are good programmers so free up the memory used by each buffer */
    delete [] shaderString;

    /* compile each shader on the GPU */
    glCompileShader( shaderHandle );

    /* check the shader log */
    printLog( shaderHandle );

    /* return the handle of our shader */
    return shaderHandle;
}

#endif // __CSCI441_SHADEREUTILS_H__
