#ifndef SHARED
#define SHARED


	// Version
	#define RED_MAJOR 0
	#define RED_MINOR 0
	#define RED_PATCH 10

	// Platform
	#if defined(_WIN32) || defined(WIN32)
	#	define RED_WIN32
	#	include <time.h>
	#else
	#	define RED_LINUX
	#	include <sys/time.h>
	#endif


	// Commonly used stuff
	#include <string>
	#include <cstring>
    #include <vector>

	// Math library
	#include "glm/glm.hpp"
	#include "glm/gtc/matrix_transform.hpp"
	#include "glm/gtc/type_ptr.hpp"
	#include "glm/gtx/transform.hpp"
	#include "glm/gtx/transform2.hpp"

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

    /// Returns whether a string is a comment or not
    bool IsComment( std::string &pS, const std::string &pChar = "//" ); 

    /// Returns an array of strings splitted from an original string
    std::vector<std::string> SplitString( const std::string &pS, const std::string &pTokens );
        
#endif
