#include "File.hpp"
#include "Context.hpp"
#include "Scene.hpp"
#include "Logger.hpp"
#include "Lua/RedLua.hpp"

#include "HandleManager.hpp"
#include "GL/glew.h"


#include "GL/SOIL.h"

/*
		TODO
	
    - textures
	- camera
    - frustum culling
    - scene hierarchy (octree)

*/

///////////////////////////////////////////////////////////////////////////////////////////////////////
//						TEST STUFF
///////////////////////////////////////////////////////////////////////////////////////////////////////

using namespace red;
int function1( lua_State *L ) {
	int argCount = Lua::GetArgCount( L );
	
	printf( "%d arguments dans func1\n", argCount );
	return 1;
}

class luaClass {
public:
	luaClass( lua_State* ) {}

	int testFunc( lua_State* ) {
		printf("luaClass::testFunc OK!\n" );
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






///////////////////////////////////////////////////////////////////////////////////////////////////////

int main ( int argc, char* argv[] ) {
	LogManager::Call().Init();
	Context::Call().Initialize( 800, 600 );


	Renderer* rend = Context::Call().GetRenderer();
	Scene scene( rend );



    Texture* t = rend->CreateTextureFromFile( "img_test.png" );
	Shader* s = rend->CreateShaderFromFile( "phong.vs", "phong.fs" );

	s->BindAttribLocation( "Position", 0 );
	s->BindAttribLocation( "Normal", 1 );
	s->Link();
	s->Bind();
	s->SendFloat( "SurfaceSmooth", 256.f );
	s->SendVector3( "SurfaceDiffuse", glm::vec3( 0.9f, 0.5f, 1 ) );
	s->SendVector3( "SurfaceSpecular", glm::vec3( 0.3f, 0.3f, 0.3f ) );


	//listtest t;
	//EventManager::Call().AddListener( t );

    Mesh* m = rend->CreateMeshFromFile( "sphere.obj" );
    glm::mat4 identity;
	u32 entity = scene.AddEntity( m, s, identity );

	Lua lua;
	lua.RegisterFunction( "function1", function1 );
	lua.RegisterClass<luaClass>();

	if( !lua.LoadScript("test.lua") ) {
		printf( "failed to load lua script\n" );
	} else {
		double hur = 4.5;
		printf( "%s\n", lua.CallFunction( "hur", "d", hur ).ToString().c_str() );
	}
	

	while( !EventManager::Call().IsKeyUp( Escape ) && Context::Call().IsOpened() ) {
		
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


		static float rotY, rotX;
		const glm::mat4 world = glm::rotate( glm::degrees( rotY += Context::Call().GetFrameTime() ), 0.0f, 1.0f, 0.0f )
						* glm::rotate( glm::degrees( rotX += Context::Call().GetFrameTime() ), 1.f, 0.f, 0.f );
		
		scene.SetEntityMatrix( entity, world );

		scene.Render();

		EventManager::Call().Update();
		Context::Call().Update();
	}


	EventManager::Kill();
	Context::Kill();
	LogManager::Kill();

#ifdef _WIN32
	system("PAUSE");
#endif

	return 0;
}
