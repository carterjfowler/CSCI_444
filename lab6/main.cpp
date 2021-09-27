/*
 *  CSCI 444, Advanced Computer Graphics, Spring 2021
 *
 *  Project: lab6
 *  File: main.cpp
 *
 *  Description:
 *      Starter code for rendering environment mapping
 *
 *  Author:
 *      Dr. Jeffrey Paone, Colorado School of Mines
 *  
 *  Notes:
 *
 */

//**********************************************************************************************************************

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdlib>
#include <cstdio>

#include <CSCI441/modelLoader.hpp>
#include <CSCI441/OpenGLUtils.hpp>
#include <CSCI441/ShaderProgram.hpp>
#include <CSCI441/UniformBufferObject.hpp>

//**********************************************************************************************************************
// Structure definitions

// a container to group all vertex attributes together
struct Vertex {
    glm::vec3 position;                         // vertex position
    glm::vec3 color;                            // vertex color
    glm::vec3 normal;                           // vertex normal
};

//**********************************************************************************************************************
// Global Parameters

// fix our window to a specific size
const GLint WINDOW_WIDTH = 640, WINDOW_HEIGHT = 640;

// keep track of our mouse information
GLboolean isShiftDown;                          // if the control key was pressed when the mouse was pressed
GLboolean isLeftMouseDown;                      // if the mouse left button is currently pressed
glm::vec2 mousePosition;                        // current mouse vPos

// keep track of all our camera information
struct CameraParameters {
    glm::vec3 cameraAngles;                     // cameraAngles --> x = theta, y = phi, z = radius
    glm::vec3 camDir;                           // direction to the camera
    glm::vec3 eyePoint;                         // camera vPos
    glm::vec3 lookAtPoint;                      // location of our object of interest
    glm::vec3 upVector;                         // the upVector of our camera
} arcballCam;

// all drawing information
const GLuint NUM_VAOS = 2;
const struct VAOIDs {
    const GLuint CUBE = 0;                      // draws a unit cube centered at the origin
    const GLuint SKYBOX = 1;                    // draws a single point at the origin that gets expanded to fill the screen
} VAOS;
GLuint vaods[NUM_VAOS];                         // an array of our VAO descriptors
GLuint vbods[NUM_VAOS];                         // an array of our VBO descriptors
GLuint ibods[NUM_VAOS];                         // an array of our IBO descriptors
GLuint iboCounts[NUM_VAOS];                     // an array of the IBO sizes

CSCI441::ModelLoader *peashooter = nullptr;

// Skybox Shader Program Information
CSCI441::ShaderProgram *skyboxShaderProgram = nullptr;
struct SkyboxUniformLocations {
    GLint eyePosition;
    GLint lookAtPoint;
    GLint upVector;
} skyboxUniformLocations;
struct SkyboxAttribLocations {
    GLint vPos;
} skyboxAttribLocations;
GLuint cubeMapTextureHandle;

// Pass-Through Color Shader Program Information
CSCI441::ShaderProgram *colorShaderProgram = nullptr;
struct ColorUniformLocations {
    GLint mvpMtx;
} colorUniformLocations;
struct ColorAttribLocations {
    GLint vPos;
    GLint vColor;
} colorAttribLocations;

// Reflection Shader Program Information
CSCI441::ShaderProgram *reflectShaderProgram = nullptr;
struct ReflectUniformLocations {
    GLint mvpMtx;
    GLint modelMatrix;
    GLint normalMatrix;
    GLint eyePosition;
} reflectUniformLocations;
struct ReflectAttribLocations {
    GLint vPos;
    GLint vNormal;
} reflectAttribLocations;

bool useReflectionShader = false;
bool drawCube = true;

//**********************************************************************************************************************
// Helper Funcs

// /////////////////////////////////////////////////////////////////////////////
/// \desc
/// This function updates the camera's vPos in cartesian coordinates based
///  on its vPos in spherical coordinates. Should be called every time
///  cameraAngles is updated.
///
// /////////////////////////////////////////////////////////////////////////////
void updateCameraDirection() {
    // ensure the camera does not flip upside down at either pole
    if( arcballCam.cameraAngles.y < 0 )     arcballCam.cameraAngles.y = 0.0f + 0.001f;
    if( arcballCam.cameraAngles.y >= M_PI ) arcballCam.cameraAngles.y = M_PI - 0.001f;

    // do not let our camera get too close or too far away
    if( arcballCam.cameraAngles.z <= 2.0f )  arcballCam.cameraAngles.z = 2.0f;
    if( arcballCam.cameraAngles.z >= 35.0f ) arcballCam.cameraAngles.z = 35.0f;

    // update the new direction to the camera
    arcballCam.camDir.x =  sinf( arcballCam.cameraAngles.x ) * sinf( arcballCam.cameraAngles.y );
    arcballCam.camDir.y = -cosf( arcballCam.cameraAngles.y );
    arcballCam.camDir.z = -cosf( arcballCam.cameraAngles.x ) * sinf( arcballCam.cameraAngles.y );

    // normalize this direction
    arcballCam.camDir = glm::normalize(arcballCam.camDir);

    // update the eye point
    arcballCam.eyePoint = arcballCam.lookAtPoint + arcballCam.camDir * arcballCam.cameraAngles.z;
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
/// Loads a texture into CPU memory and transfers it to the corresponding
///     cube map face on the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void loadCubeMapFaceTexture(const GLint CUBE_MAP_FACE, const char* FILENAME) {
    int imageWidth, imageHeight, imageChannels;
    unsigned char *data = stbi_load( FILENAME, &imageWidth, &imageHeight, &imageChannels, 0);

    if( data ) {
        const GLint STORAGE_TYPE = (imageChannels == 4 ? GL_RGBA : GL_RGB);
        glTexImage2D(CUBE_MAP_FACE, 0, STORAGE_TYPE, imageWidth, imageHeight, 0, STORAGE_TYPE, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        fprintf( stderr, "[ERROR]: Could not load texture map \"%s\"\n", FILENAME );
    }
}

//**********************************************************************************************************************
// GLFW Event Callbacks

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///		We will register this function as GLFW's error callback.
///	When an error within GLFW occurs, GLFW will tell us by calling
///	this function.  We can then print this info to the terminal to
///	alert the user.
///
// /////////////////////////////////////////////////////////////////////////////
static void error_callback(int error, const char* description) {
	fprintf(stderr, "[ERROR]: (%d) %s\n", error, description);
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///		We will register this function as GLFW's keypress callback.
///	Responds to key presses and key releases
///
// /////////////////////////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_ESCAPE:
            case GLFW_KEY_Q:
                glfwSetWindowShouldClose(window, GLFW_TRUE);
                break;

            case GLFW_KEY_C:
                drawCube = !drawCube;
                break;

            case GLFW_KEY_R:
                useReflectionShader = !useReflectionShader;
                break;

            default:
                break;
        }
    }
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///		We will register this function as GLFW's mouse button callback.
///	Responds to mouse button presses and mouse button releases.  Keeps track if
///	the control key was pressed when a left mouse click occurs to allow
///	zooming of our arcball camera.
///
// /////////////////////////////////////////////////////////////////////////////
static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if( button == GLFW_MOUSE_BUTTON_LEFT ) {
        if( action == GLFW_PRESS ) {
            isLeftMouseDown = GL_TRUE;
            isShiftDown = (mods & GLFW_MOD_SHIFT);
        } else {
            isLeftMouseDown = GL_FALSE;
            isShiftDown = GL_FALSE;
            mousePosition = glm::vec2(-9999.0f, -9999.0f);
        }
    }
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///		We will register this function as GLFW's cursor movement callback.
///	Responds to mouse movement.  When active motion is used with the left
///	mouse button an arcball camera model is followed.
///
// /////////////////////////////////////////////////////////////////////////////
static void cursor_callback( GLFWwindow* window, double xPos, double yPos ) {
    // make sure movement is in bounds of the window
    // glfw captures mouse movement on entire screen
    if( xPos > 0 && xPos < WINDOW_WIDTH ) {
        if( yPos > 0 && yPos < WINDOW_HEIGHT ) {
            // active motion
            if( isLeftMouseDown ) {
                if( (mousePosition.x - -9999.0f) > 0.001f ) {
                    if( !isShiftDown ) {
                        // if shift is not held down, update our camera angles theta & phi
                        arcballCam.cameraAngles.x += (xPos - mousePosition.x) * 0.005f;
                        arcballCam.cameraAngles.y += (mousePosition.y - yPos) * 0.005f;
                    } else {
                        // otherwise shift was held down, update our camera radius
                        double totChgSq = (xPos - mousePosition.x) + (yPos - mousePosition.y);
                        arcballCam.cameraAngles.z += totChgSq*0.01f;
                    }
                    // recompute our camera direction
                    updateCameraDirection();
                }
                // update the last mouse vPos
                mousePosition = glm::vec2(xPos, yPos);
            }
            // passive motion
            else {

            }
        }
    }
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///		We will register this function as GLFW's scroll wheel callback.
///	Responds to movement of the scroll where.  Allows zooming of the arcball
///	camera.
///
// /////////////////////////////////////////////////////////////////////////////
static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset ) {
    double totChgSq = yOffset;
    arcballCam.cameraAngles.z += totChgSq*0.2f;
    updateCameraDirection();
}

//**********************************************************************************************************************
// Setup Funcs

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///		Used to setup everything GLFW related.  This includes the OpenGL context
///	and our window.
///
// /////////////////////////////////////////////////////////////////////////////
GLFWwindow* setupGLFW() {
    // set what function to use when registering errors
    // this is the ONLY GLFW function that can be called BEFORE GLFW is initialized
    // all other GLFW calls must be performed after GLFW has been initialized
    glfwSetErrorCallback(error_callback);

    // initialize GLFW
    if (!glfwInit()) {
        fprintf( stderr, "[ERROR]: Could not initialize GLFW\n" );
        exit(EXIT_FAILURE);
    } else {
        fprintf( stdout, "[INFO]: GLFW initialized\n" );
    }

    glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );						// request forward compatible OpenGL context
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );	        // request OpenGL Core Profile context
    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );		                // request OpenGL 4.X context
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 1 );		                // request OpenGL X.1 context
    glfwWindowHint( GLFW_DOUBLEBUFFER, GLFW_TRUE );                             // request double buffering
    glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );                               // do not allow the window to be resized

    // create a window for a given size, with a given title
    GLFWwindow *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Lab6: Environment Mapping", nullptr, nullptr );
    if( !window ) {						                                        // if the window could not be created, NULL is returned
        fprintf( stderr, "[ERROR]: GLFW Window could not be created\n" );
        glfwTerminate();
        exit( EXIT_FAILURE );
    } else {
        fprintf( stdout, "[INFO]: GLFW Window created\n" );
    }

    glfwMakeContextCurrent(	window );	                                        // make the created window the current window
    glfwSwapInterval( 1 );				                                // update our screen after at least 1 screen refresh

    glfwSetKeyCallback(         window, key_callback		  );            	// set our keyboard callback function
    glfwSetMouseButtonCallback( window, mouse_button_callback );	            // set our mouse button callback function
    glfwSetCursorPosCallback(	window, cursor_callback  	  );	            // set our cursor vPos callback function
    glfwSetScrollCallback(		window, scroll_callback		  );	            // set our scroll wheel callback function

    return window;										                        // return the window that was created
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Used to setup everything OpenGL related.
///
// /////////////////////////////////////////////////////////////////////////////
void setupOpenGL() {
    glEnable( GL_DEPTH_TEST );					                    // enable depth testing
    glDepthFunc( GL_LESS );							                // use less than depth test

    glFrontFace( GL_CCW );                                          // front faces are counter clockwise

    glEnable( GL_BLEND );									        // enable blending
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );	        // use one minus blending equation

    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );	// clear the frame buffer to black

    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);                         // interpolate across cube map seams
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Used to initialize GLEW
///
// /////////////////////////////////////////////////////////////////////////////
void setupGLEW() {
    glewExperimental = GL_TRUE;
    GLenum glewResult = glewInit();                                 // initialize GLEW

    // check for an error
    if( glewResult != GLEW_OK ) {
        fprintf( stderr, "[ERROR]: Error initializing GLEW\n");
        fprintf( stderr, "[ERROR]: %s\n", glewGetErrorString(glewResult) );
        exit(EXIT_FAILURE);
    } else {
        fprintf( stdout, "\n[INFO]: GLEW initialized\n" );
        fprintf( stdout, "[INFO]: Using GLEW %s\n", glewGetString(GLEW_VERSION) );
    }
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Registers our Shader Programs and query locations
///          of uniform/attribute inputs
///
// /////////////////////////////////////////////////////////////////////////////
void setupShaders() {
    // Skybox Shading Program
    skyboxShaderProgram                = new CSCI441::ShaderProgram( "shaders/skybox.v.glsl", "shaders/skybox.g.glsl", "shaders/skybox.f.glsl" );
    // query all of our uniform locations
    skyboxUniformLocations.eyePosition      = skyboxShaderProgram->getUniformLocation("eyePosition");
    skyboxUniformLocations.lookAtPoint      = skyboxShaderProgram->getUniformLocation("lookAtPoint");
    skyboxUniformLocations.upVector         = skyboxShaderProgram->getUniformLocation("upVector");
    // query all of our attribute locations
    skyboxAttribLocations.vPos              = skyboxShaderProgram->getAttributeLocation("vPos");
    // set static uniforms
    skyboxShaderProgram->setProgramUniform("cubeMap", 0);

    // Pass-Through Color Shading Program
    colorShaderProgram        		   = new CSCI441::ShaderProgram( "shaders/colorPassThrough.v.glsl", "shaders/colorPassThrough.f.glsl" );
    // query all of our uniform locations
    colorUniformLocations.mvpMtx            = colorShaderProgram->getUniformLocation( "mvpMtx" );
    // query all of our attribute locations
    colorAttribLocations.vPos               = colorShaderProgram->getAttributeLocation( "vPos" );
    colorAttribLocations.vColor             = colorShaderProgram->getAttributeLocation( "vColor" );

    // Reflection Environment Mapping Program
    reflectShaderProgram               = new CSCI441::ShaderProgram( "shaders/reflect.v.glsl", "shaders/reflect.f.glsl" );
    // query all of our uniform locations
    reflectUniformLocations.mvpMtx          = reflectShaderProgram->getUniformLocation("mvpMtx");
    reflectUniformLocations.modelMatrix     = reflectShaderProgram->getUniformLocation("modelMatrix");
    reflectUniformLocations.normalMatrix    = reflectShaderProgram->getUniformLocation("normalMatrix");
    reflectUniformLocations.eyePosition     = reflectShaderProgram->getUniformLocation("eyePosition");
    // query all of our attribute locations
    reflectAttribLocations.vPos             = reflectShaderProgram->getAttributeLocation("vPos");
    reflectAttribLocations.vNormal          = reflectShaderProgram->getAttributeLocation("vNormal");
    // set static uniforms
    reflectShaderProgram->setProgramUniform("cubeMap", 0);
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Create our Vertex Array Objects and Vertex Buffer Objects on the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void setupVAOs() {
    // generate our vertex array object descriptors
    glGenVertexArrays( NUM_VAOS, vaods );
    // generate our vertex buffer object descriptors
    glGenBuffers( NUM_VAOS, vbods );
    // generate our index buffer object descriptors
    glGenBuffers( NUM_VAOS, ibods );

    //------------ BEGIN cube VAO ------------

    // specify our Cube Vertex information
    const unsigned int NUM_CUBE_VERTICES = 8;
    const Vertex CUBE_VERTICES[NUM_CUBE_VERTICES] = {
            {glm::vec3( -0.5f, -0.5f, -0.5f ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( -1.0f, -1.0f, -1.0f) },
            {glm::vec3(  0.5f, -0.5f, -0.5f ), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(  1.0f, -1.0f, -1.0f) },
            {glm::vec3(  0.5f,  0.5f, -0.5f ), glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(  1.0f,  1.0f, -1.0f) },
            {glm::vec3( -0.5f,  0.5f, -0.5f ), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3( -1.0f,  1.0f, -1.0f) },
            {glm::vec3( -0.5f, -0.5f,  0.5f ), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3( -1.0f, -1.0f,  1.0f) },
            {glm::vec3(  0.5f, -0.5f,  0.5f ), glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(  1.0f, -1.0f,  1.0f) },
            {glm::vec3(  0.5f,  0.5f,  0.5f ), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(  1.0f,  1.0f,  1.0f) },
            {glm::vec3( -0.5f,  0.5f,  0.5f ), glm::vec3(0.0f, 1.0f, 1.0f), glm::vec3( -1.0f,  1.0f,  1.0f) }
    };
    // specify our Cube Index Ordering
    const unsigned int NUM_CUBE_INDICES = 36;
    const GLushort CUBE_INDICES[NUM_CUBE_INDICES] = {
            0, 2, 1,    0, 3, 2,
            1, 2, 5,    5, 2, 6,
            2, 7, 6,    3, 7, 2,
            0, 1, 4,    1, 5, 4,
            4, 5, 6,    4, 6, 7,
            0, 4, 3,    4, 7, 3
    };
    iboCounts[VAOS.CUBE] = NUM_CUBE_INDICES;

    // bind our Cube VAO
    glBindVertexArray( vaods[VAOS.CUBE] );

    // bind the VBO for our Cube Array Buffer
    glBindBuffer( GL_ARRAY_BUFFER, vbods[VAOS.CUBE] );
    // send the data to the GPU
    glBufferData( GL_ARRAY_BUFFER, NUM_CUBE_VERTICES * sizeof(Vertex), CUBE_VERTICES, GL_STATIC_DRAW );

    // bind the VBO for our Cube Element Array Buffer
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibods[VAOS.CUBE] );
    // send the data to the GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, NUM_CUBE_INDICES * sizeof(GLushort), CUBE_INDICES, GL_STATIC_DRAW );

    // enable our vPos attribute
    glEnableVertexAttribArray(colorAttribLocations.vPos );
    // map the vPos attribute to data within our buffer
    glVertexAttribPointer(colorAttribLocations.vPos, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr );

    // enable our vColor attribute
    glEnableVertexAttribArray(colorAttribLocations.vColor );
    // map the vColor attribute to data within our buffer
    glVertexAttribPointer(colorAttribLocations.vColor, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)*1) );

    // enable our vNormal attribute
    glEnableVertexAttribArray(reflectAttribLocations.vNormal );
    // map the vNormal attribute to data within our buffer
    glVertexAttribPointer(reflectAttribLocations.vNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(glm::vec3)*2) );

    //------------  END  cube VAO ------------

    //------------ BEGIN skybox VAO ------------
    glm::vec3 skyboxPoint = glm::vec3(0.0, 0.0, 0.0);

    // bind skybox VAO
    glBindVertexArray( vaods[VAOS.SKYBOX] );

    // bind the VBO for our skybox
    glBindBuffer( GL_ARRAY_BUFFER, vbods[VAOS.SKYBOX] );
    // send the data to the GPU
    glBufferData( GL_ARRAY_BUFFER, sizeof(skyboxPoint), &skyboxPoint[0], GL_STATIC_DRAW );

    // enable our position attribute
    glEnableVertexAttribArray(skyboxAttribLocations.vPos );
    // map the position attribute to data within our buffer
    glVertexAttribPointer(skyboxAttribLocations.vPos, 3, GL_FLOAT, GL_FALSE, 0, nullptr );
    //------------  END  skybox VAO ------------
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Create our buffers on the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void setupBuffers() {
	setupVAOs();                // create the VAOs, VBOs, and IBOs for the objects to draw

	peashooter = new CSCI441::ModelLoader("assets/models/peashooter.obj");
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Create our textures on the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void setupTextures() {
    // TODO #1 generate and bind the cube map
    glGenTextures(1, &cubeMapTextureHandle);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureHandle);

    // TODO #2 load each cube map face
    loadCubeMapFaceTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_X, "assets/textures/colosseum/posx.jpg");
    loadCubeMapFaceTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, "assets/textures/colosseum/negx.jpg");
    loadCubeMapFaceTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, "assets/textures/colosseum/posy.jpg");
    loadCubeMapFaceTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, "assets/textures/colosseum/negy.jpg");
    loadCubeMapFaceTexture(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, "assets/textures/colosseum/posz.jpg");
    loadCubeMapFaceTexture(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, "assets/textures/colosseum/negz.jpg");

    // TODO #3 set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Initialize all of our scene information here
///
// /////////////////////////////////////////////////////////////////////////////
void setupScene() {
    // set up mouse info
    isLeftMouseDown = GL_FALSE;
    isShiftDown = GL_FALSE;
    mousePosition = glm::vec2( -9999.0f, -9999.0f );

    // set up camera info
    arcballCam.cameraAngles   = glm::vec3( 1.82f, 2.01f, 15.0f );
    arcballCam.camDir         = glm::vec3( -1.0f, -1.0f, -1.0f );
    arcballCam.lookAtPoint    = glm::vec3( 0.0f, 0.0f, 0.0f) ;
    arcballCam.upVector       = glm::vec3( 0.0f,  1.0f,  0.0f );
    updateCameraDirection();
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Create our OpenGL context,
///          load all information to the GPU,
///          initialize scene information
///
// /////////////////////////////////////////////////////////////////////////////
GLFWwindow* initialize() {
    // GLFW sets up our OpenGL context so must be done first
    GLFWwindow* window = setupGLFW();	                // initialize all of the GLFW specific information related to OpenGL and our window
    setupGLEW();										// initialize all of the GLEW specific information
    setupOpenGL();										// initialize all of the OpenGL specific information

    CSCI441::OpenGLUtils::printOpenGLInfo();            // print our OpenGL information

    setupShaders();                                     // load all of our shader programs onto the GPU and get shader input locations
    setupBuffers();										// load all our VAOs and VBOs onto the GPU
    setupTextures();                                    // load all our textures onto the GPU
    setupScene();                                       // initialize all of our scene information

    fprintf( stdout, "\n[INFO]: Setup complete\n" );

    return window;
}

//**********************************************************************************************************************
// Cleanup Functions

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Delete shaders off of the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void cleanupShaders() {
    fprintf( stdout, "[INFO]: ...deleting shaders.\n" );

    delete skyboxShaderProgram;
    delete colorShaderProgram;
    delete reflectShaderProgram;
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Delete VAOs and VBOs, IBOs, UBOs, ACBOs, SSBOs off of the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void cleanupBuffers() {
    fprintf( stdout, "[INFO]: ...deleting IBOs....\n" );
    glDeleteBuffers( NUM_VAOS, ibods );

    fprintf( stdout, "[INFO]: ...deleting VBOs....\n" );
    glDeleteBuffers( NUM_VAOS, vbods );

    fprintf( stdout, "[INFO]: ...deleting VAOs....\n" );
    glDeleteVertexArrays( NUM_VAOS, vaods );

    delete peashooter;
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Delete Textures off of the GPU
///
// /////////////////////////////////////////////////////////////////////////////
void cleanupTextures() {
    fprintf( stdout, "[INFO]: ...deleting textures\n" );

}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Delete scene info off of the CPU
///
// /////////////////////////////////////////////////////////////////////////////
void cleanupScene() {
    fprintf( stdout, "[INFO]: ...deleting scene...\n" );

}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Free all memory on the CPU/GPU and close our OpenGL context
///
// /////////////////////////////////////////////////////////////////////////////
void shutdown(GLFWwindow* window) {
    fprintf( stdout, "\n[INFO]: Shutting down.......\n" );
    fprintf( stdout, "[INFO]: ...closing window...\n" );
    glfwDestroyWindow( window );                        // close our window
    cleanupShaders();                                   // delete shaders from GPU
    cleanupBuffers();                                   // delete VAOs/VBOs from GPU
    cleanupTextures();                                  // delete textures from GPU
    cleanupScene();                                     // delete scene info from CPU
    fprintf( stdout, "[INFO]: ...closing GLFW.....\n" );
    glfwTerminate();						            // shut down GLFW to clean up our context
    fprintf( stdout, "[INFO]: ..shut down complete!\n" );
}

//**********************************************************************************************************************
// Rendering / Drawing Functions - this is where the magic happens!

// /////////////////////////////////////////////////////////////////////////////
/// \desc
/// Handles the drawing of everything to our buffer.  Needs the view and
///     projection matrices to apply as part of the ModelViewProjection matrix.
///
// /////////////////////////////////////////////////////////////////////////////
void renderScene( const glm::mat4 VIEW_MTX, const glm::mat4 PROJ_MTX ) {
    // ------ BEGIN draw Skybox ------
    // create our Model, View, Projection matrices
    glm::mat4 modelMtx;
    modelMtx = glm::mat4(1.0f);

    // precompute the ModelView matrix
    glm::mat4 mvMtx = VIEW_MTX * modelMtx;
    // precompute the ModelViewProjection matrix
    glm::mat4 mvpMtx = PROJ_MTX * mvMtx;

    glDisable(GL_DEPTH_TEST);
    skyboxShaderProgram->useProgram();
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeMapTextureHandle);
    glUniform3fv(skyboxUniformLocations.eyePosition, 1, &arcballCam.eyePoint[0] );
    glUniform3fv(skyboxUniformLocations.lookAtPoint, 1, &arcballCam.lookAtPoint[0] );
    glUniform3fv(skyboxUniformLocations.upVector, 1, &arcballCam.upVector[0] );

    glBindVertexArray( vaods[VAOS.SKYBOX] );
    glDrawArrays( GL_POINTS, 0, 1 );
    glEnable(GL_DEPTH_TEST);
    // ------  END  draw Skybox ------

    // ------ BEGIN draw object ------
    GLdouble time = glfwGetTime();
    // apply a rotation based on time to our Model matrix
    modelMtx = glm::rotate(modelMtx, (GLfloat) time, glm::vec3(sin(time), cos(time), sin(time) - cos(time)));
    // scale the cube up
    modelMtx = glm::scale(modelMtx, glm::vec3(5, 5, 5));

    // update our ModelView matrix
    mvMtx = VIEW_MTX * modelMtx;
    // update our ModelViewProjection matrix
    mvpMtx = PROJ_MTX * mvMtx;

    if( !useReflectionShader ) {
        // use our color Program
        colorShaderProgram->useProgram();
        // update our dynamic uniform values
        glUniformMatrix4fv( colorUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );
    } else {
        // use our reflection Program
        reflectShaderProgram->useProgram();

        // update our dynamic uniform values
        glUniform3fv( reflectUniformLocations.eyePosition, 1, &arcballCam.eyePoint[0] );
        glUniformMatrix4fv( reflectUniformLocations.mvpMtx, 1, GL_FALSE, &mvpMtx[0][0] );
        glUniformMatrix4fv( reflectUniformLocations.modelMatrix, 1, GL_FALSE, &modelMtx[0][0] );
        glm::mat3 normalMtx = glm::transpose( glm::inverse(glm::mat3( modelMtx) ) );
        glUniformMatrix3fv( reflectUniformLocations.normalMatrix, 1, GL_FALSE, &normalMtx[0][0] );
    }

    if(drawCube) {
        // bind our Cube VAO
        glBindVertexArray( vaods[VAOS.CUBE] );
        // draw our cube!
        glDrawElements( GL_TRIANGLES, iboCounts[VAOS.CUBE], GL_UNSIGNED_SHORT, nullptr );
    } else {
        // draw our peashooter
        peashooter->draw( reflectAttribLocations.vPos, reflectAttribLocations.vNormal, colorAttribLocations.vColor );
    }
    // ------  END   draw object ------
}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Update all of our scene objects - perform animation here
///
// /////////////////////////////////////////////////////////////////////////////
void updateScene() {

}

// /////////////////////////////////////////////////////////////////////////////
/// \desc
///      Runs our draw loop and renders/updates our scene
/// \param window - window to render the scene to
// /////////////////////////////////////////////////////////////////////////////
void run(GLFWwindow* window) {
    // NOTE: we are doing the Viewport and Projection calculations prior to the loop since we are not
    // allowing our window to be resized so these values will never change throughout the life of our
    // program.  If we allowed the window to be resized, then we would need to create a window resize
    // callback and update these values only on change.

    // Get the size of our framebuffer.  Ideally this should be the same dimensions as our window, but
    // when using a Retina display the actual window can be larger than the requested window.  Therefore
    // query what the actual size of the window we are rendering to is.
    GLint windowWidth, windowHeight;
    glfwGetFramebufferSize( window, &windowWidth, &windowHeight );

    // update the viewport - tell OpenGL we want to render to the whole window
    glViewport( 0, 0, windowWidth, windowHeight );

    // compute our projection matrix
    const glm::mat4 PROJ_MTX = glm::perspective( 45.0f, windowWidth / (GLfloat) windowHeight, 0.001f, 100.0f );

    //  This is our draw loop - all rendering is done here.  We use a loop to keep the window open
    //	until the user decides to close the window and quit the program.  Without a loop, the
    //	window will display once and then the program exits.
    while( !glfwWindowShouldClose(window) ) {	        // check if the window was instructed to be closed
        // clear the prior contents of our buffer
        glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

        // compute our view matrix based on our current camera setup
        glm::mat4 vMtx = glm::lookAt( arcballCam.eyePoint, arcballCam.lookAtPoint, arcballCam.upVector );

        renderScene( vMtx, PROJ_MTX );                  // render our scene

        glfwSwapBuffers(window);                        // flush the OpenGL commands and make sure they get rendered!
        glfwPollEvents();				                // check for any events and signal to redraw screen

        updateScene();                                  // update the objects in our scene
    }
}

//**********************************************************************************************************************

// program entry point
int main() {
    GLFWwindow *window = initialize();                  // create OpenGL context and setup EVERYTHING for our program
    run(window);                                        // enter our draw loop and run our program
    shutdown(window);                                   // free up all the memory used and close OpenGL context
    return EXIT_SUCCESS;				                // exit our program successfully!
}
