#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include "Singleton.hpp"
#include "Shared.hpp"
#include "Listener.hpp"

namespace blue {
	
	/// Manage real time events from GLFW callbacks
	/// and distribute them to all registered listeners
	/// Possess also the input states.
	class EventManager : public Singleton<EventManager> {
	friend class Singleton<EventManager>;
	// GLFW callbacks friended for InputStates access
		friend void GLFWCALL KeyPressedCallback( int pKey, int pValue ); 
		friend void GLFWCALL CharPressedCallback( int pKey, int pValue ); 
		friend void GLFWCALL MousePressedCallback( int pKey, int pValue ); 
		friend void GLFWCALL MouseWheelCallback( int pWheel ); 
		friend void GLFWCALL MouseMovedCallback( int pX, int pY ); 

	public:
		// Input Query functions
			bool IsKeyDown( Key pB ) const;
			bool IsKeyUp( Key pB ) const;
			bool IsKeyHit( Key pB ) const;

			bool IsMouseDown( MouseButton pB ) const;
			bool IsMouseUp( MouseButton pB ) const;
			bool IsMouseHit( MouseButton pB ) const;

			bool IsWheelUp() const;
			bool IsWheelDown() const;

			u32	 GetMouseX() const { return mCurrentState.mMousePos.x; }
			u32	 GetMouseY() const { return mCurrentState.mMousePos.y; }

		/// Add a Listener to the container, allowing it to be informed
		void AddListener( Listener& pListener );

		/// Update the input states. Must be called one time per frame
		void Update();

	private:
		/// Useful structure containing the state of all inputs
		/// during one frame
		struct InputState {
			InputState() : mWheelState( 0 ), mCloseSignal( false ) {
				memset( mKeyboardState, false, 330 * sizeof( bool ) );
				memset( mMouseState, false, 5 * sizeof( bool ) );
			}

			bool mKeyboardState[330];	///< Keyboard keys
			bool mMouseState[5];		///< Mouse buttons
			int  mWheelState;			///< MouseWheel absolute pos
			bool mCloseSignal;			///< Window closing signal

			glm::vec2 mMousePos;		///< Mouse absolute pos
		};

		InputState mCurrentState;				///< Inputs of current frame
		InputState mPreviousState;				///< Inputs of preceding frame


		MouseListenerList mMouseListeners;		///< All current Mouse Listeners
		KeyListenerList mKeyListeners;			///< All current Key Listeners
		

		/// Used by the GLFW callback functions to distribute the recorded events
		/// to all Listeners appropriate listeners
		void PropagateEvent( const Event& pEvent );

	};

	// GLFW Callback functions
		void GLFWCALL KeyPressedCallback( int pKey, int pValue ); 
		void GLFWCALL CharPressedCallback( int pKey, int pValue ); 
		void GLFWCALL MousePressedCallback( int pKey, int pValue ); 
		void GLFWCALL MouseWheelCallback( int pWheel ); 
		void GLFWCALL MouseMovedCallback( int pX, int pY ); 
}
#endif
