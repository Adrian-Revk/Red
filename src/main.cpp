#include "File.hpp"
#include "Context.hpp"
#include "Clock.hpp"
#include "Logger.hpp"
#include "Lua/RedLua.hpp"

#include "HandleManager.hpp"


using namespace blue;
int function1( lua_State *L ) {
	int argCount = Lua::GetArgCount( L );
	
	printf( "%d arguments dans func1\n", argCount );
	return 1;
}

class luaClass {
public:
	luaClass( lua_State* ) {}

	int testFunc( lua_State* ) {
		printf("oyeabertet\n" );
		return 1;
	}

	static const char className[];
	static Lunar<luaClass>::Method methods[];
};

const char luaClass::className[] = "luaClass";
Lunar<luaClass>::Method luaClass::methods[] = {
	LUA_METHOD( luaClass, testFunc ),
	{ 0 }
};

class listtest : public MouseListener {
public:
	virtual void OnMouseMoved( const Event& pEvent ) {
		printf( "%f %f\n", pEvent.mMousePos.x, pEvent.mMousePos.y );
	}

	virtual void OnMouseWheelMoved( const Event& pEvent ) {
		printf( "wheel: %d\n", pEvent.mWheel );
	}
};

int main ( int argc, char* argv[] ) {
	LogManager::Call().Init();
	Context::Call().Initialize( 800, 600 );

	listtest t;
	EventManager::Call().AddListener( t );

	Lua lua;
	lua.RegisterFunction( "function1", function1 );
	lua.RegisterClass<luaClass>();

	if( !lua.LoadScript("test.lua") ) {
		printf( "failed to load lua script\n" );
	} else {
		double hur = 4.5;
		printf( "%s\n", lua.CallFunction( "hur", "d", hur ).ToString().c_str() );
	}
	
	bool run = true;
	while(run) {
		run = !EventManager::Call().IsKeyUp( Escape ); 
		
		if( EventManager::Call().IsWheelUp() )
			DebugLog << "wheelup" << eol;
		if( EventManager::Call().IsWheelDown() )
			DebugLog << "wheeldown" << eol;

		EventManager::Call().Update();
		Context::Call().Update();
	}
	EventManager::Kill();
	Context::Kill();
	LogManager::Kill();


	return 0;
}
