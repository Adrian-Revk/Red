#ifndef CONTEXT_HPP
#define CONTEXT_HPP

#include "Singleton.hpp"
#include "EventManager.hpp"
#include "Clock.hpp"
#include "Renderer.hpp"

//#include "AntTweakBar\include\AntTweakBar.h"

#include <vector>

namespace red {


	/// Class initializing and maintaining a valid OpenGL Context associated with
	/// a GLFW Window. 
	class Context : public Singleton<Context> {
	friend class Singleton<Context>;

	public:
		Context();
		~Context();

		/// Initialize the OpenGL/Glew Context and the GLFW window using given params
		void Initialize( u32 pWidth, u32 pHeight, u32 pFSAALevel = 0, bool pFullscreen = false );

		bool IsInitialized() const { return mInit; }

		/// Return true if the GLFW window is currently opened
		bool IsOpened() const;

		/// Update the context. Call this every frame end
		void Update();

		// Window modification functions
			/// Modify the window title
			void SetTitle( const std::string &pTitle );

			/// Modify the window size
			void SetSize( u32 pWidth, u32 pHeight );

			/// Modify the window position
			void SetPosition( int pX, int pY );

			/// Set VSYNC On or Off
			void SetVSync( bool pVal );

		/// Show or Hide the cursor
		void ShowCursor( bool pVal );

		/// Returns the context renderer
		Renderer* GetRenderer() { return &mRenderer; }

		/// Return the time interval between 2 frames
		f32 GetFrameTime() const { return mTimeStep; }


	private:
		bool mInit;						///< Initialized flag for the context, one at a time
		glm::vec2 mWindowSize;			///< Window dimensions

		u32  mOpenMode;					///< Opening mode, GLFW_WINDOW or GLFW_FULLSCREEN
		u32 mFSAALevel;					///< FSAA Level
		std::vector<glm::vec2> mVModes;	///< Vector of all Video Modes available

		Clock	mClock;					///< Context main clock
		f32		mLastTime,				///< Last frame time
				mTimeStep;				///< Time step between 2 frames

		Renderer mRenderer;				///< OpenGL Renderer

		/// Check if a given resolution is available
		bool ResolutionAvailable( u32 pWidth, u32 pHeight );

		/// Destroy the current context
		void Destroy();

	};
}
#endif
