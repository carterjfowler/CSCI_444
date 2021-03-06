/** @file ShaderProgram.hpp
 * @brief Class to work with OpenGL 3.0+ Shaders
 * @author Dr. Jeffrey Paone
 * @date Last Edit: 12 Oct 2020
 * @version 2.2.0
 *
 * @copyright MIT License Copyright (c) 2017 Dr. Jeffrey Paone
 *
 *	These functions, classes, and constants help minimize common
 *	code that needs to be written.
 */

#ifndef __CSCI441_SHADERPROGRAM_H__
#define __CSCI441_SHADERPROGRAM_H__

#include "ShaderUtils.hpp"

#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

/** @namespace CSCI441
  * @brief CSCI441 Helper Functions for OpenGL
	*/
namespace CSCI441 {

    /** @class ShaderProgram
        * @desc Handles registration and compilation of Shaders
        */
    class ShaderProgram {
    public:
        /** @desc Enables debug messages from Shader Program functions
          *
            * Enables debug messages from Shader Program functions.  Debug messages are on by default.
          */
        static void enableDebugMessages();
        /** @desc Disables debug messages from Shader Program functions
          *
            * Disables debug messages from Shader Program functions.  Debug messages are on by default.
          */
        static void disableDebugMessages();

        /** @desc Creates a Shader Program using a Vertex Shader and Fragment Shader
          *
            * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
            * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
          */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *fragmentShaderFilename );

        /** @desc Creates a Shader Program using a Vertex Shader and Fragment Shader
          *
            * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
            * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
         * @param const bool isSeparable - if program is separable
          */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSpearable);

        /** @desc Creates a Shader Program using a Vertex Shader, Tesselation Shader, Geometry Shader, and Fragment Shader
              *
              * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
              * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
              * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
              * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
              * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
              */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename );

        /** @desc Creates a Shader Program using a Vertex Shader, Tesselation Shader, Geometry Shader, and Fragment Shader
              *
              * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
              * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
              * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
              * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
              * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
         * @param const bool isSeparable - if program is separable
              */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSeparable );

        /** @desc Creates a Shader Program using a Vertex Shader, Tesselation Shader, and Fragment Shader
             *
             * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
             * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
             * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
             * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
             */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *fragmentShaderFilename );

        /** @desc Creates a Shader Program using a Vertex Shader, Tesselation Shader, and Fragment Shader
             *
             * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
             * @param const char* tesselationControlShaderFilename - name of the file corresponding to the tesselation control shader
             * @param const char* tesselationEvaluationShaderFilename - name of the file corresponding to the tesselation evaluation shader
             * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
             * @param const bool isSeparable - if program is separable
             */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *tesselationControlShaderFilename,
                       const char *tesselationEvaluationShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSeparable);

        /** @desc Creates a Shader Program using a Vertex Shader, Geometry Shader, and Fragment Shader
          *
            * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
            * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
            * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
            */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename );

        /** @desc Creates a Shader Program using a Vertex Shader, Geometry Shader, and Fragment Shader
          *
            * @param const char* vertexShaderFilename - name of the file corresponding to the vertex shader
            * @param const char* geometryShaderFilename - name of the file corresponding to the geometry shader
            * @param const char* fragmentShaderFilename - name of the file corresponding to the fragment shader
             * @param const bool isSeparable - if program is separable
            */
        ShaderProgram( const char *vertexShaderFilename,
                       const char *geometryShaderFilename,
                       const char *fragmentShaderFilename,
                       const bool isSeparable );

        /** @desc Creates a Shader Program using any combination of shaders.  Intended to be used to create separable programs
         * but can be used as an alternative to the above overloaded constructors to explicitly state which shaders are present.
         *
         * @param const char **shaderFilenames - an array of filenames corresponding to all the shaders.  size must be equal to
         * the sum of true shaders present, with two for the tessellation shader
         *
         * @param const bool vertexPresent - if vertex shader is present
         * @param const bool tessellationPresent - if tessellation shader is present
         * @param const bool geometryPresent - if geometry shader is present
         * @param const bool fragmentPresent - if fragment shader is present
         * @param const bool isSeparable - if program is seperable
         */
        ShaderProgram( const char **shaderFilenames,
                       const bool vertexPresent, const bool tessellationPresent, const bool geometryPresent, const bool fragmentPresent,
                       const bool isSeparable );

        /** @desc Clean up memory associated with the Shader Program
             */
        ~ShaderProgram();

        /** @desc Returns the location of the given uniform in this shader program
          * @note Prints an error message to standard error stream if the uniform is not found
            * @param const char* uniformName - name of the uniform to get the location for
          * @return GLint - location of the given uniform in this shader program
          */
        GLint getUniformLocation( const char *uniformName );

        /** @desc Returns the index of the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to get the index for
          * @return GLint - index of the given uniform block in this shader program
          */
        GLint getUniformBlockIndex( const char *uniformBlockName );
        /** @desc Returns the size of the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to get the size for
          * @return GLint - size of the given uniform block in this shader program
          */
        GLint getUniformBlockSize( const char *uniformBlockName );
        /** @desc Returns an allocated buffer for the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to allocate a buffer for
          * @return GLubyte* - allocated buffer for the given uniform block in this shader program
          */
        GLubyte* getUniformBlockBuffer( const char *uniformBlockName );
        /** @desc Returns an array of offsets into the buffer for the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to return offsets for
          * @return GLint* - array of offsets for the given uniform block in this shader program
          */
        GLint* getUniformBlockOffsets( const char *uniformBlockName );
        /** @desc Returns an array of offsets into the buffer for the given uniform block and names in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to return offsets for
            * @param const char* names[] - names of the uniform block components to get offsets for
          * @return GLint* - array of offsets for the given uniform block in this shader program
          */
        GLint* getUniformBlockOffsets( const char *uniformBlockName, const char *names[] );
        /** @desc Set the binding point for the given uniform block in this shader program
          * @note Prints an error message to standard error stream if the uniform block is not found
            * @param const char* uniformBlockName - name of the uniform block to bind
            * @param GLuint binding               - binding point for this uniform block
          */
        void setUniformBlockBinding( const char *uniformBlockName, GLuint binding );

        /** @desc Returns the location of the given attribute in this shader program
          * @note Prints an error message to standard error stream if the attribute is not found
            * @param const char* attributeName - name of the attribute to get the location for
          * @return GLint - location of the given attribute in this shader program
          */
        GLint getAttributeLocation( const char *attributeName );

        /** @desc Returns the index of the given subroutine for a shader stage in this shader program
          * @note Prints an error message to standard error stream if the subroutine is not found
            * @param GLenum shaderStage         - stage of the shader program to get the subroutine for.
            *   Allowable values: GL_VERTEX_SHADER, GL_TESS_CONTROL_SHADER, GL_TESS_EVALUATION_SHADER, GL_GEOMETRY_SHADER, GL_FRAGMENT_SHADER
            * @param const char* subroutineName - name of the subroutine to get the location for
          * @return GLuint - index of the given subroutine for the shader stage in this shader program
          */
        GLuint getSubroutineIndex( GLenum shaderStage, const char *subroutineName );

        /** @desc Returns the number of active uniforms in this shader program
          * @return GLuint - number of active uniforms in this shader program
          */
        GLuint getNumUniforms();
        /** @desc Returns the number of active uniform blocks in this shader program
          * @return GLuint - number of active uniform blocks in this shader program
          */
        GLuint getNumUniformBlocks();
        /** @desc Returns the number of active attributes in this shader program
          * @return GLuint - number of active attributes in this shader program
          */
        GLuint getNumAttributes();

        /** @desc Returns the handle for this shader program
          * @return GLuint - handle for this shader program
          */
        GLuint getShaderProgramHandle();

        /** @desc Sets the Shader Program to be active
          */
        void useProgram();
    private:
        ShaderProgram();

        static bool sDEBUG;

        GLuint _vertexShaderHandle;
        GLuint _tesselationControlShaderHandle;
        GLuint _tesselationEvaluationShaderHandle;
        GLuint _geometryShaderHandle;
        GLuint _fragmentShaderHandle;

        GLuint _shaderProgramHandle;

        bool registerShaderProgram( const char *vertexShaderFilename,
                                    const char *tesselationControlShaderFilename,
                                    const char *tesselationEvaluationShaderFilename,
                                    const char *geometryShaderFilename,
                                    const char *fragmentShaderFilename,
                                    const bool isSeparable );

        GLint* getUniformBlockOffsets( GLint uniformBlockIndex );
        GLint* getUniformBlockOffsets( GLint uniformBlockIndex, const char *names[] );
    };

}

////////////////////////////////////////////////////////////////////////////////

inline bool CSCI441::ShaderProgram::sDEBUG = true;

inline void CSCI441::ShaderProgram::enableDebugMessages() {
    sDEBUG = true;
}
inline void CSCI441::ShaderProgram::disableDebugMessages() {
    sDEBUG = false;
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *fragmentShaderFilename ) {
    registerShaderProgram( vertexShaderFilename, "", "", "", fragmentShaderFilename, false );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *fragmentShaderFilename, bool isSeparable ) {
    registerShaderProgram( vertexShaderFilename, "", "", "", fragmentShaderFilename, isSeparable );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename ) {
    registerShaderProgram( vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename, geometryShaderFilename, fragmentShaderFilename, false );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    registerShaderProgram( vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename, geometryShaderFilename, fragmentShaderFilename, isSeparable );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *fragmentShaderFilename ) {
    registerShaderProgram( vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename, "", fragmentShaderFilename, false );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    registerShaderProgram( vertexShaderFilename, tesselationControlShaderFilename, tesselationEvaluationShaderFilename, "", fragmentShaderFilename, isSeparable );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename ) {
    registerShaderProgram( vertexShaderFilename, "", "", geometryShaderFilename, fragmentShaderFilename, false );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char *vertexShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, bool isSeparable  ) {
    registerShaderProgram( vertexShaderFilename, "", "", geometryShaderFilename, fragmentShaderFilename, isSeparable );
}

inline CSCI441::ShaderProgram::ShaderProgram( const char **shaderFilenames,
                                       const bool vertexPresent, const bool tessellationPresent, const bool geometryPresent, const bool fragmentPresent,
                                       const bool isSeparable ) {
    if( vertexPresent && !tessellationPresent && !geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( shaderFilenames[0], "", "", "", "", isSeparable );
        }
    } else if( vertexPresent && tessellationPresent && !geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], "", "", isSeparable );
        }
    } else if( vertexPresent && tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], shaderFilenames[3], "", isSeparable );
        }
    } else if( vertexPresent && tessellationPresent && geometryPresent && fragmentPresent ) {
        registerShaderProgram( shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], shaderFilenames[3], shaderFilenames[4], isSeparable );
    } else if( vertexPresent && tessellationPresent && !geometryPresent && fragmentPresent ) {
        registerShaderProgram( shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], "", shaderFilenames[3], isSeparable );
    } else if( vertexPresent && !tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Fragment Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( shaderFilenames[0], "", "", shaderFilenames[1], "", isSeparable );
        }
    } else if( vertexPresent && !tessellationPresent && geometryPresent && fragmentPresent ) {
        registerShaderProgram( shaderFilenames[0], "", "", shaderFilenames[1], shaderFilenames[2], isSeparable );
    } else if( vertexPresent && !tessellationPresent && !geometryPresent && fragmentPresent ) {
        registerShaderProgram( shaderFilenames[0], "", "", "", shaderFilenames[1], isSeparable );
    } else if( !vertexPresent && tessellationPresent && !geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex & Fragment Shaders not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", shaderFilenames[0], shaderFilenames[1], "", "", isSeparable );
        }
    } else if( !vertexPresent && tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex & Fragment Shaders not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], "", isSeparable );
        }
    } else if( !vertexPresent && tessellationPresent && geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", shaderFilenames[0], shaderFilenames[1], shaderFilenames[2], shaderFilenames[3], isSeparable );
        }
    } else if( !vertexPresent && tessellationPresent && !geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", shaderFilenames[0], shaderFilenames[1], "", shaderFilenames[2], isSeparable );
        }
    } else if( !vertexPresent && !tessellationPresent && geometryPresent && !fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex & Fragment Shaders not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", "", "", shaderFilenames[0], "", isSeparable );
        }
    } else if( !vertexPresent && !tessellationPresent && geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", "", "", shaderFilenames[0], shaderFilenames[1], isSeparable );
        }
    } else if( !vertexPresent && !tessellationPresent && !geometryPresent && fragmentPresent ) {
        if( !isSeparable ) {
            fprintf(stderr, "[ERROR]: Vertex Shader not present.  Program must be separable.\n");
        } else {
            registerShaderProgram( "", "", "", "", shaderFilenames[0], isSeparable );
        }
    } else if( !vertexPresent && !tessellationPresent && !geometryPresent && !fragmentPresent ) {
        fprintf(stderr, "[ERROR]: At least one shader must be present.\n");
    } else {
        fprintf(stderr, "[ERROR]: Unknown state.\n");
    }
}

inline bool CSCI441::ShaderProgram::registerShaderProgram( const char *vertexShaderFilename, const char *tesselationControlShaderFilename, const char *tesselationEvaluationShaderFilename, const char *geometryShaderFilename, const char *fragmentShaderFilename, const bool isSeparable ) {
    GLint major, minor;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);

    if( sDEBUG ) printf( "\n[INFO]: /--------------------------------------------------------\\\n");

    /* compile each one of our shaders */
    if( strcmp( vertexShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Vertex Shader: %39s |\n", vertexShaderFilename );
        _vertexShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader( vertexShaderFilename, GL_VERTEX_SHADER );
    } else {
        _vertexShaderHandle = 0;
    }

    if( strcmp( tesselationControlShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Tess Control Shader: %33s |\n", tesselationControlShaderFilename );
        if( major < 4 ) {
            printf( "[ERROR]:|   TESSELATION SHADER NOT SUPPORTED!!  UPGRADE TO v4.0+ |\n" );
            _tesselationControlShaderHandle = 0;
        } else {
            _tesselationControlShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader( tesselationControlShaderFilename, GL_TESS_CONTROL_SHADER );
        }
    } else {
        _tesselationControlShaderHandle = 0;
    }

    if( strcmp( tesselationEvaluationShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Tess Evaluation Shader: %30s |\n", tesselationEvaluationShaderFilename );
        if( major < 4 ) {
            printf( "[ERROR]:|   TESSELATION SHADER NOT SUPPORTED!!  UPGRADE TO v4.0+ |\n" );
            _tesselationEvaluationShaderHandle = 0;
        } else {
            _tesselationEvaluationShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader( tesselationEvaluationShaderFilename, GL_TESS_EVALUATION_SHADER );
        }
    } else {
        _tesselationEvaluationShaderHandle = 0;
    }

    if( strcmp( geometryShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Geometry Shader: %37s |\n", geometryShaderFilename );
        if( major < 3 || (major == 3 && minor < 2) ) {
            printf( "[ERROR]:|   GEOMETRY SHADER NOT SUPPORTED!!!    UPGRADE TO v3.2+ |\n" );
            _geometryShaderHandle = 0;
        } else {
            _geometryShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader( geometryShaderFilename, GL_GEOMETRY_SHADER );
        }
    } else {
        _geometryShaderHandle = 0;
    }

    if( strcmp( fragmentShaderFilename, "" ) != 0 ) {
        if( sDEBUG ) printf( "[INFO]: | Fragment Shader: %37s |\n", fragmentShaderFilename );
        _fragmentShaderHandle = CSCI441_INTERNAL::ShaderUtils::compileShader( fragmentShaderFilename, GL_FRAGMENT_SHADER );
    } else {
        _fragmentShaderHandle = 0;
    }
    /* get a handle to a shader program */
    _shaderProgramHandle = glCreateProgram();

    /* if program is separable, make it so */
    if( isSeparable ) {
        glProgramParameteri( _shaderProgramHandle, GL_PROGRAM_SEPARABLE, GL_TRUE );
    }

    /* attach the vertex and fragment shaders to the shader program */
    if( _vertexShaderHandle != 0 ) {
        glAttachShader( _shaderProgramHandle, _vertexShaderHandle );
    }
    if( _tesselationControlShaderHandle != 0 ) {
        glAttachShader( _shaderProgramHandle, _tesselationControlShaderHandle );
    }
    if( _tesselationEvaluationShaderHandle != 0 ) {
        glAttachShader( _shaderProgramHandle, _tesselationEvaluationShaderHandle );
    }
    if( _geometryShaderHandle != 0 ) {
        glAttachShader( _shaderProgramHandle, _geometryShaderHandle );
    }
    if( _fragmentShaderHandle != 0 ) {
        glAttachShader( _shaderProgramHandle, _fragmentShaderHandle );
    }

    /* link all the programs together on the GPU */
    glLinkProgram( _shaderProgramHandle );

    if( sDEBUG ) printf( "[INFO]: | Shader Program: %41s", "|\n" );

    /* check the program log */
    CSCI441_INTERNAL::ShaderUtils::printLog( _shaderProgramHandle );

    /* detach & delete the vertex and fragment shaders to the shader program */
    if( _vertexShaderHandle != 0 ) {
        glDetachShader( _shaderProgramHandle, _vertexShaderHandle );
        glDeleteShader( _vertexShaderHandle );
    }
    if( _tesselationControlShaderHandle != 0 ) {
        glDetachShader( _shaderProgramHandle, _tesselationControlShaderHandle );
        glDeleteShader( _tesselationControlShaderHandle );
    }
    if( _tesselationEvaluationShaderHandle != 0 ) {
        glDetachShader( _shaderProgramHandle, _tesselationEvaluationShaderHandle );
        glDeleteShader( _tesselationEvaluationShaderHandle );
    }
    if( _geometryShaderHandle != 0 ) {
        glDetachShader( _shaderProgramHandle, _geometryShaderHandle );
        glDeleteShader( _geometryShaderHandle );
    }
    if( _fragmentShaderHandle != 0 ) {
        glDetachShader( _shaderProgramHandle, _fragmentShaderHandle );
        glDeleteShader( _fragmentShaderHandle );
    }


    GLint separable = GL_FALSE;
    glGetProgramiv( _shaderProgramHandle, GL_PROGRAM_SEPARABLE, &separable );

    if( sDEBUG ) printf( "[INFO]: | Program Separable: %35s |\n", (separable ? "Yes" : "No"));

    /* print shader info for uniforms & attributes */
    CSCI441_INTERNAL::ShaderUtils::printShaderProgramInfo( _shaderProgramHandle );

    /* return handle */
    return _shaderProgramHandle != 0;
}

inline GLint CSCI441::ShaderProgram::getUniformLocation( const char *uniformName ) {
    GLint uniformLoc = glGetUniformLocation( _shaderProgramHandle, uniformName );
    if( uniformLoc == -1 )
        fprintf( stderr, "[ERROR]: Could not find uniform %s\n", uniformName );
    return uniformLoc;
}

inline GLint CSCI441::ShaderProgram::getUniformBlockIndex( const char *uniformBlockName ) {
    GLint uniformBlockLoc = glGetUniformBlockIndex( _shaderProgramHandle, uniformBlockName );
    if( uniformBlockLoc == -1 )
        fprintf( stderr, "[ERROR]: Could not find uniform block %s\n", uniformBlockName );
    return uniformBlockLoc;
}

inline GLint CSCI441::ShaderProgram::getUniformBlockSize( const char *uniformBlockName ) {
    GLint blockSize;
    glGetActiveUniformBlockiv( _shaderProgramHandle, getUniformBlockIndex(uniformBlockName), GL_UNIFORM_BLOCK_DATA_SIZE, &blockSize );
    return blockSize;
}

inline GLubyte* CSCI441::ShaderProgram::getUniformBlockBuffer( const char *uniformBlockName ) {
    GLubyte *blockBuffer;

    GLint blockSize = getUniformBlockSize( uniformBlockName );

    blockBuffer = (GLubyte*)malloc(blockSize);

    return blockBuffer;
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( const char *uniformBlockName ) {
    return getUniformBlockOffsets( getUniformBlockIndex(uniformBlockName) );
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( const char *uniformBlockName, const char *names[] ) {
    return getUniformBlockOffsets( getUniformBlockIndex(uniformBlockName), names );
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( GLint uniformBlockIndex ) {
    GLint numUniforms;
    glGetActiveUniformBlockiv( _shaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms );

    GLuint *indices = (GLuint*)malloc(numUniforms*sizeof(GLuint));
    glGetActiveUniformBlockiv( _shaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES, (GLint*)indices);

    GLint *offsets = (GLint*)malloc(numUniforms*sizeof(GLint));
    glGetActiveUniformsiv( _shaderProgramHandle, numUniforms, indices, GL_UNIFORM_OFFSET, offsets );
    return offsets;
}

inline GLint* CSCI441::ShaderProgram::getUniformBlockOffsets( GLint uniformBlockIndex, const char *names[] ) {
    GLint numUniforms;
    glGetActiveUniformBlockiv( _shaderProgramHandle, uniformBlockIndex, GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS, &numUniforms );

    GLuint *indices = (GLuint*)malloc(numUniforms*sizeof(GLuint));
    glGetUniformIndices( _shaderProgramHandle, numUniforms, names, indices );

    GLint *offsets = (GLint*)malloc(numUniforms*sizeof(GLint));
    glGetActiveUniformsiv( _shaderProgramHandle, numUniforms, indices, GL_UNIFORM_OFFSET, offsets );
    return offsets;
}

inline void CSCI441::ShaderProgram::setUniformBlockBinding( const char *uniformBlockName, GLuint binding ) {
    glUniformBlockBinding( _shaderProgramHandle, getUniformBlockIndex(uniformBlockName), binding );
}

inline GLint CSCI441::ShaderProgram::getAttributeLocation( const char *attributeName ) {
    GLint attributeLoc = glGetAttribLocation( _shaderProgramHandle, attributeName );
    if( attributeLoc == -1 )
        fprintf( stderr, "[ERROR]: Could not find attribute %s\n", attributeName );
    return attributeLoc;
}

inline GLuint CSCI441::ShaderProgram::getSubroutineIndex( GLenum shaderStage, const char *subroutineName ) {
    GLuint subroutineIndex = glGetSubroutineIndex( _shaderProgramHandle, shaderStage, subroutineName );
    if( subroutineIndex == GL_INVALID_INDEX )
        fprintf( stderr, "[ERROR]: Could not find subroutine %s for %s\n", subroutineName, CSCI441_INTERNAL::ShaderUtils::GL_shader_type_to_string(shaderStage) );
    return subroutineIndex;
}

inline GLuint CSCI441::ShaderProgram::getNumUniforms() {
    int numUniform = 0;
    glGetProgramiv( _shaderProgramHandle, GL_ACTIVE_UNIFORMS, &numUniform );
    return numUniform;
}

inline GLuint CSCI441::ShaderProgram::getNumUniformBlocks() {
    int numUniformBlocks = 0;
    glGetProgramiv( _shaderProgramHandle, GL_ACTIVE_UNIFORM_BLOCKS, &numUniformBlocks );
    return numUniformBlocks;
}

inline GLuint CSCI441::ShaderProgram::getNumAttributes() {
    int numAttr = 0;
    glGetProgramiv( _shaderProgramHandle, GL_ACTIVE_ATTRIBUTES, &numAttr );
    return numAttr;
}

inline GLuint CSCI441::ShaderProgram::getShaderProgramHandle() {
    return _shaderProgramHandle;
}

inline void CSCI441::ShaderProgram::useProgram() {
    glUseProgram( _shaderProgramHandle );
}

inline CSCI441::ShaderProgram::ShaderProgram() {}

inline CSCI441::ShaderProgram::~ShaderProgram() {
    glDeleteProgram( _shaderProgramHandle );
}

#endif //__CSCI441_SHADERPROGRAM_H__
