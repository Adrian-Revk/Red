#ifndef LUAVALUE_HPP
#define LUAVALUE_HPP

#include "Shared.hpp"
#include "Lua/lua.hpp"

namespace blue {

	/// Union of all possible Lua Value Type, plus functions for easeofuse
	class LuaValue {
	public:
		/// Constructor for a nil value
		LuaValue();

		/// Constructor for a bool value
		LuaValue( bool b );

		/// Constructor for a float value
		LuaValue( f32 f );

		/// Constructor for a double value
		LuaValue( f64 f );

		/// Constructor for a int value
		LuaValue( int s );

		/// Constructor for a string value
		LuaValue( const std::string &pString );

		/// Constructor for a const char* value
		LuaValue( const char* pStr );

		/// Returns the LuaValue Type in string form
		std::string GetTypeName() const;

		// Getters in different type form
			f32			ToFloat()	const;
			int			ToInt()		const;
			std::string ToString()	const;
			bool		ToBool()	const;

	private:
		/// Lua defined type
		int mDataType;

		/// All possible types
		lua_Number	mNumber;	
		bool		mBool;
		std::string	mString;
	};
}

#endif // LUAVALUE_HPP
