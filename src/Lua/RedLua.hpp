#ifndef REDLUA_HPP
#define REDLUA_HPP


#include "LuaValue.hpp"
#include "Lunar.hpp"

namespace red {
	/// Lua function template
	/// Style :  int functionName(lua_State* L);
	typedef lua_CFunction LuaFunctionType;

	/// Wrapper class for Lua. Using the (slightly modified) LUNAR framework. 
	//
	//		HOW TO USE
	//
	//	INIT THE LUA MACHINE (only one needed) :
	//
	//		Lua myLua;
	//	
	//	REGISTER A C++ FUNC (to be called in a lua script) :
	//
	//		int myFunc( lua_State* L ) {
	//			int argCount = Lua::GetArgCount();
	//
	//			for( int i = 0; i < argCount: ++i )
	//				std::cout << "arg " << i << " : " 
	//					<< Lua::GetArgument<std::string>( L, i ) << std::endl;
	//
	//			Lua::SendValue( L, "Hello!" );
	//
	//			return 1;
	//		}
	//
	//		myLua.RegisterFunction( "funcName", myFunc );
	//
	//	The signature of a lua callable func is unique and must be a LuaFunctionType like
	//	int (*)( lua_State* ). When the function is registered, it became callable in a lua 
	//	script with the name specified ("funcName").
	//
	//	Lua::GetArgCount() is a static function returning the number of arguments specified 
	//	in the lua script when the function is called.
	//
	//	Lua::GetArgument<T>( L, i ) returns the i-th arguments sent by the function of the 
	//	lua script
	//
	//	Lua::SendValue( L, T val ) send a returning value for the function called in the 
	//	lua script.
	//
	//
	//	READ AND EXECUTE A LUA SCRIPT :
	//	
	//		myLua.LoadScript( "myscript.lua" )
	//
	//	This function reads and executes the given script and return true if no error occured, 
	//	false otherwise.
	//	Note that a C++ func must be registered BEFORE being able to be called by a lua script.
	//
	//
	//	GET A LUA SCRIPT GLOBAL VAR : 
	//
	//		std::string var = lua.GetGlobalVar( "var1" ).ToString();
	//
	//	GetGlobalVar reads a global lua gvar from the last read scripts and produce a LuaValue
	//	corresponding to the lua type read.
	//
	//
	//	CALL A LUA FUNC FROM C++ :
	//
	//		lua.CallFunction( "funcName", paramsTypes, params ... );
	//
	//	To call a lua func, you need its name as a string as the first parameter, and the 
	//	arguments it needs.
	//	The arguments are given as a list of arguments of CallFunction.
	//
	//	paramsTypes is a string corresponding to an array of characters representing the
	//	types of the following arguments. The characters are :
	//		
	//		d for a double
	//		s for a string
	//		b for a boolean
	//		i for an int
	//
	//		Example :
	//			
	//			lua.CallFunction( "funcName", "dsb", 4.5, "hello", true );
	//
	//
	//	CREATE A USABLE C++ CLASS FOR LUA :
	//
	//	To access a c++ class from Lua, you need to do some work. 
	//	1. 	The Constructor must have only one arg, a (lua_State*).
	//	2. 	Each function that can be called from lua must have the
	//	   	LuaFunctionType template : int (*)( lua_State* ).
	//	3.	Some static variables must be defined :
	//		
	//		- a const char[] representing the class name in Lua.
	//		- a Lunar<ClassName>::Method[] representing an array
	//		  of all the class' callable functions.
	//
	//		As static vars, they must be defined after the class
	//		declaration. Look at the Example to see how.
	//
	//	4.	Register the class to the Lua Machine with :
	//			
	//			myLua.Register<MyLuaClass>();
	//
	//
	//
	//		Example :
	//
	//			class MyLuaClass {
	//			public:
	//				MyLuaClass( lua_State* L ) { }
	//
	//				int SomeFunc( lua_State* L ) {
	//					// do Something
	//					return 1;
	//				}
	//
	//				static const char className[];
	//				static Lunar<MyLuaClass>::Method methods[];
	//			};
	//
	//			const char MyLuaClass::className[] = "MyClass";
	//			Lunar<MyLuaClass>::Method MyLuaClass::methods[] = {
	//				LUA_METHOD( MyLuaClass, SomeFunc ),
	//				{ 0 }
	//			};
	

	class Lua{
	public:
		Lua();
		~Lua();

		/// Returns implicitly the lua_State pointer
		operator lua_State*() { return mState; }

		/// Load a given script on the stack
		/// @param pName : Script FileName
		/// @return : True if the script has been successfully loaded
		bool LoadScript( const std::string &pName );

		/// Register a Lua callable C++ Function
		/// @param pName : Function name callable in the lua script
		/// @param pFunction : Function definition
		void RegisterFunction( const std::string &pName, LuaFunctionType pFunction );
		
		/// Register a Lua usable C++ Class
		/// @param T : The template parameter is the name of the class to register.
		template<class T>
		void RegisterClass() { Lunar<T>::Register( mState ); }

		/// Check if the sended lua status int caused an error
		/// @param pStatus : status to check
		/// @return : True if an error occured
		bool CheckError( int pStatus );

		/// Collect Lua scripts garbage.
		void CollectGarbage();
	
		/// Call a Lua function from the C++ code
		/// @param pFuncName  : Name of the Lua script function to call
		/// @param pSignature : Signature of the different types of arguments sent.
		//						Must be a string of chars 'b'(boolean), 's'(string), 'i'(int),
		//						'd'(double). Ex : "bsbi".
		/// @param ...		  : Variables to send as arguments to the la func, must be in the
		//						same order as their types in pSignature.
		//						Ex : true, "hello", false, 4
		//	@return			  : A LuaValue with the return value of the script. Can be NIL
		LuaValue CallFunction( const std::string &pFuncName, const std::string pSignature, ... );

		/// Retrieve a Global Var from the last read Lua Script
		/// @param pVariable : Variable name to retrieve
		/// @return			 : A LuaValue with the value of the gvar. NIL if doesn't exist.
		LuaValue GetGlobalVar( const std::string &pVariable );

		// Static functions used in defined functions
			/// Returns the argument number from a function
			static int GetArgCount( lua_State* pState );
			
			/// Returns the n-th argument from a function
			template<class T>
			static T GetArgument( lua_State* pState, int pPos );

			/// Send a return value to the script
			template<class T>
			static void SendValue( lua_State* pState, T pValue );



	private:
		lua_State* mState;		///< Lua State used for the whole program
	};




	template<>
	inline void Lua::SendValue( lua_State* pState, const char* pValue ) {
		lua_pushstring( pState, pValue );
	}

	template<>
	inline void Lua::SendValue( lua_State* pState, int pValue ) {
		lua_pushinteger( pState, pValue );
	}

	template<>
	inline void Lua::SendValue( lua_State* pState, f32 pValue ) {
		lua_pushnumber( pState, (f64)pValue );
	}

	template<>
	inline void Lua::SendValue( lua_State* pState, bool pValue ) {
		lua_pushboolean( pState, pValue );
	}



	template<>
	inline std::string Lua::GetArgument( lua_State* pState, int pPos ) {
		if( pPos > Lua::GetArgCount(pState) - 1 ) {
			printf( "Error in Lua::GetArgument() : %d is not a valid position\n", pPos );
			return "<unknown>";
		}

		return lua_tostring( pState, pPos + 1 );
	}

	template<>
	inline int Lua::GetArgument( lua_State* pState, int pPos ) {
		if( pPos > Lua::GetArgCount(pState) - 1 ) {
			printf( "Error in Lua::GetArgument() : %d is not a valid position\n", pPos );
			return -1;
		}

		return lua_tointeger( pState, pPos + 1 );
	}

	template<>
	inline f32 Lua::GetArgument( lua_State* pState, int pPos ){
		if( pPos > Lua::GetArgCount(pState) - 1 ) {
			printf( "Error in Lua::GetArgument() : %d is not a valid position\n", pPos );
			return -1.f;
		}

		return (f32)lua_tonumber( pState, pPos + 1 );
	}

	template<>
	inline bool Lua::GetArgument( lua_State* pState, int pPos ){
		if( pPos > Lua::GetArgCount(pState) - 1 ) {
			printf( "Error in Lua::GetArgument() : %d is not a valid position\n", pPos );
			return false;
		}

		return lua_toboolean( pState, pPos + 1 ) > 0;
	}

}

#endif // LUA_HPP
