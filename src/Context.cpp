#include "Context.hpp"

#include "GL/glew.h"
#include "GL/glfw.h"

#include <cstdio>

namespace blue {
	void WindowResizeCallback( int pWidth, int pHeight ) {
		Context::Call().SetSize( pWidth, pHeight );
	}


	Context::Context() {
		mInit = false;
		mOpenMode = GLFW_WINDOW;
		mFSAALevel = 0;
	}

	Context::~Context() {
		if ( mInit ) 
			Destroy();
	}

	void Context::Destroy() {
		mInit = false;
		glfwTerminate();
	}

	bool Context::IsOpened() const {
		return ! glfwGetWindowParam( GLFW_OPENED ) == 0;
	}

	bool Context::ResolutionAvailable( u32 pWidth, u32 pHeight ) {
		if( mInit )
			for( u32 i = 0; i < mVModes.size(); ++i ) 
				if( pWidth == mVModes[i].x && pHeight == mVModes[i].y )
					return true;
		
		return false;
	}

	void Context::Initialize ( u32 pWidth, u32 pHeight, u32 pFSAALevel, bool pFullscreen ) {
		if ( mInit ) 
			Destroy();

		int init = glfwInit();

		if ( init ) {
			if ( pFullscreen )
				mOpenMode = GLFW_FULLSCREEN;
			else
				mOpenMode = GLFW_WINDOW;


			// Check all available video modes and store them
			GLFWvidmode modes[64];
			int nVModes = glfwGetVideoModes( modes, 64 );
				
			for( int i = 0; i < nVModes; ++i ) 
				mVModes.push_back( glm::vec2( modes[i].Width, modes[i].Height ) );


			// OpenGL Version
			glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
			glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );

			
			// FSAA
			if( pFSAALevel != 2 || pFSAALevel != 4 || pFSAALevel != 8 )
				pFSAALevel = 0;

			glfwOpenWindowHint( GLFW_FSAA_SAMPLES, pFSAALevel );

			// Check if wanted resolution is available. Default it otherwise.
			if( !ResolutionAvailable( pWidth, pHeight ) ) {
				pWidth = 640;
				pHeight = 480;
			}
			
			// Open the GLFW Window
			init = glfwOpenWindow( pWidth, pHeight,
									8, 8, 8, 8,
									24, 8, mOpenMode );

			if ( init ) {
				// GLFW key pressed callback
				glfwSetKeyCallback( KeyPressedCallback );
			
				// GLFW character callback
				glfwSetCharCallback( CharPressedCallback );
			
				// GLFW window resizing callback
				glfwSetWindowSizeCallback( WindowResizeCallback );

				// GLFW mouse pressed callback
				glfwSetMouseButtonCallback( MousePressedCallback );

				// GLFW mouse wheel callback
				glfwSetMouseWheelCallback( MouseWheelCallback );

				// GLFW mouse pos callback
				glfwSetMousePosCallback( MouseMovedCallback );

				
				// Enable Key Repeat
				glfwEnable( GLFW_KEY_REPEAT );

				// If window is okay, initialize GLEW
				GLenum glewerr = glewInit();
					
				if ( GLEW_OK == glewerr )
					printf( "GLEW %s\n", glewGetString(GLEW_VERSION) );
				else {
					printf( "GLEW Error : %s\n", glewGetErrorString(glewerr) );
					Destroy();
				}

				mInit = true;		
			} else {
				printf( "GLFW Error: Can't open window!\n" );
				Destroy();
			}
		} else
			printf( "GLFW Error: initialization failed!\n" );
	}

	void Context::Update() {
		glfwSwapBuffers();
	}

	void Context::SetVSync( bool pVal ) {
		glfwSwapInterval( (int)pVal );
	}

	void Context::SetTitle( const std::string &pTitle ) {
		glfwSetWindowTitle( pTitle.c_str() );
	}

	void Context::SetSize( u32 pWidth, u32 pHeight ) {
		glfwSetWindowSize( pWidth, pHeight );
		mWindowSize = glm::vec2( pWidth, pHeight );
	}

	void Context::SetPosition( int pX, int pY ) {
		glfwSetWindowPos( pX, pY );
	}

	void Context::ShowCursor( bool pVal ) {
		if( pVal )
			glfwEnable( GLFW_MOUSE_CURSOR );
		else
			glfwDisable( GLFW_MOUSE_CURSOR );
	}


}
