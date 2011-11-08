#include "RedLua.hpp"

namespace red {
	Lua::Lua() : mState(lua_open()){
		luaL_openlibs(mState);
	}

	Lua::~Lua(){
		lua_close(mState);
	}

	bool Lua::LoadScript( const std::string &pName ){
		int script = luaL_dofile(mState, pName.c_str());

		// Check errors if one arise
		return !CheckError(script);
	}

	void Lua::RegisterFunction(const std::string &pName, LuaFunctionType pFunction){
		lua_register(mState, pName.c_str(), pFunction);
	}

	bool Lua::CheckError(int pStatus){
		if(pStatus != 0){
			if(pStatus == LUA_ERRFILE)
				printf( "-- Lua File Error : %s\n", lua_tostring( mState, -1 ) );
			else if(pStatus == LUA_ERRSYNTAX)
				printf( "-- Lua Syntax Error : %s\n", lua_tostring( mState, -1 ) );
			else
				printf( "-- Lua Error : %s\n", lua_tostring( mState, -1 ) );
			lua_pop(mState, 1);
		}

		return pStatus != 0;
	}

	int Lua::GetArgCount(lua_State* pState){
		return lua_gettop(pState);
	}

	LuaValue Lua::GetGlobalVar( const std::string &pVariable ){
		lua_getglobal(mState, pVariable.c_str());

		// Find the type
		if(lua_isboolean(mState, -1))
			return LuaValue(lua_toboolean(mState, -1));
		else if(lua_isnumber(mState, -1))
			return LuaValue(lua_tonumber(mState, -1));
		else if(lua_isstring(mState, -1))
			return LuaValue(lua_tostring(mState, -1));
		
		return LuaValue();
	}

	LuaValue Lua::CallFunction( const std::string &pFuncName, const std::string pSignature, ... ){
		va_list vl;
		int nargs = 0;

		// Retrieve arguments/return
		va_start(vl, pSignature);

		// Retrieve function
		lua_getglobal(mState, pFuncName.c_str());

		// Push arguments 
		for(u32 i = 0; i < pSignature.size(); ++i){
			switch(pSignature[i]){
			case 'd':
				lua_pushnumber(mState, va_arg(vl, f64));
				++nargs;
				break;
			case 'i':
				lua_pushinteger(mState, va_arg(vl, int));
				++nargs;
				break;
			case 'b':
				lua_pushboolean(mState, va_arg(vl, int));
				++nargs;
				break;
			case 's':
				lua_pushstring(mState, va_arg(vl, char*));
				++nargs;
				break;
			default:
				printf( "Lua::CallFunction() : %c is not a valid argument option.\n", pSignature[i] );
			}
		}
		va_end(vl);


		int ret = lua_pcall(mState, nargs, LUA_MULTRET, 0);
		if(CheckError(ret))
			return LuaValue();

		// Get return param
		LuaValue retVal;
		switch(lua_type(mState, lua_gettop(mState))){
		case LUA_TBOOLEAN: 
			retVal = LuaValue(lua_toboolean(mState, lua_gettop(mState)));
			lua_pop(mState, 1);
			break;
		case LUA_TNUMBER: 
			retVal = LuaValue(lua_tonumber(mState, lua_gettop(mState)));
			lua_pop(mState, 1);
			break;
		case LUA_TSTRING: 
			retVal = LuaValue(lua_tostring(mState, lua_gettop(mState)));
			lua_pop(mState, 1);
			break;
		default			: break;
		}

		return retVal;
	}

	void Lua::CollectGarbage(){
		//lua_set setgcthreshold(mState, 0);
		lua_gc(mState, LUA_GCCOLLECT, 0);
	}


}
