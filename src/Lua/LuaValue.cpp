#include "LuaValue.hpp"

#include <sstream>

namespace red {
	LuaValue::LuaValue() : mDataType( LUA_TNIL ) {
	}

	LuaValue::LuaValue( bool b ) : mDataType( LUA_TBOOLEAN ) {
		mBool = b;
	}

	LuaValue::LuaValue( f32 f ) : mDataType( LUA_TNUMBER ) {
		lua_Number lNum = static_cast<lua_Number>( f );
		mNumber = lNum;
	}

	LuaValue::LuaValue( f64 f ) : mDataType( LUA_TNUMBER ) {
		lua_Number lNum = static_cast<lua_Number>( f );
		mNumber = lNum;
	}

	LuaValue::LuaValue( int s ) : mDataType( LUA_TNUMBER ) {
		lua_Number lNum = static_cast<lua_Number>( s );
		mNumber = lNum;
	}

	LuaValue::LuaValue( const std::string &pString ) : mDataType( LUA_TSTRING ) {
		mString = pString;
	}

	LuaValue::LuaValue( const char* pStr ) : mDataType( LUA_TSTRING ) {
		mString = pStr;
	}

	std::string LuaValue::GetTypeName() const {
		switch( mDataType ) {
		case LUA_TNIL:
			return "nil";
		case LUA_TNUMBER:
			return "number";
		case LUA_TBOOLEAN:
			return "bool";
		case LUA_TSTRING:
			return "string";
		default:
			return "";
		}
	}

	bool LuaValue::ToBool() const {
		if( mDataType == LUA_TBOOLEAN )
			return mBool;
		else {
			printf( "LuaValue : tried to convert a %s to a bool.", GetTypeName().c_str() );
			return false;
		}
	}

	std::string LuaValue::ToString() const{
		if( mDataType == LUA_TSTRING )
			return mString;
		else if( mDataType == LUA_TNUMBER ) {
			return "";
		} else if( mDataType == LUA_TNIL )
			return "null";
		else if( mDataType == LUA_TBOOLEAN )
			return mBool ? "true" : "false";
		else {
			printf( "LuaValue : tried to convert a %s to a string.", GetTypeName().c_str() );
			return "<unknown>";
		}
	}

	int LuaValue::ToInt() const{
		if( mDataType == LUA_TNUMBER )
			return (int)mNumber;
		else if( mDataType == LUA_TSTRING ) {
			int ret;
			std::istringstream iss( mString );
			if( iss >> ret )
				return ret;
		}

		printf( "LuaValue : tried to convert a %s to a int.", GetTypeName().c_str() );
		return -1;
	}

	f32 LuaValue::ToFloat() const{
		if( mDataType == LUA_TNUMBER )
			return (f32)mNumber;
		else if( mDataType == LUA_TSTRING ) {
			f32 ret;
			std::istringstream iss( mString );
			if( iss >> ret )
				return ret;
		}

		printf( "LuaValue : tried to convert a %s to a float.", GetTypeName().c_str() );
		return -1.f;
	}

}
