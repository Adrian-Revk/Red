#ifndef SHARED
#define SHARED


	// Version
	#define RED_MAJOR 0
	#define RED_MINOR 0
	#define RED_PATCH 1

	// Platform
	#if defined(_WIN32) || defined(WIN32)
	#	define BLUE_WIN32
	#	define GLFWCALL __stdcall
	#	include <time.h>
	#else
	#	define BLUE_LINUX
	#	define GLFWCALL
	#	include <sys/time.h>
	#endif


	// Commonly used stuff
	#include <string>
	#include <cstring>

	// Math library
	#include "ext/glm/glm.hpp"

	// Engine Types
	#include "Types.hpp"

	// End Of Line
	#define eol "\n"

	/// Returns time in "HH:MM:SS" format
	inline std::string GetTime(){
		time_t tps = time( NULL );
		tm* temps = localtime( &tps );
		char ret[9];
		strftime( ret, 9, "%H:%M:%S", temps );
		return ret;
	}

	/// Returns date in "Day DD MMM YYYY" format
	inline std::string GetDate(){
		time_t tps = time( NULL );
		tm* temps = localtime( &tps );
		char ret[16];
		strftime( ret, 16, "%a %d %b %Y", temps );
		return ret;
	}
#endif
