#include "EventManager.hpp"

namespace blue {
	EventManager& EvtManager = EventManager::Call();

	void GLFWCALL KeyPressedCallback( int pKey, int pValue ) {
		EvtManager.mCurrentState.mKeyboardState[pKey] = pValue;

		Event e;
		e.mType = pValue ? Event::KeyPressed : Event::KeyReleased;
		e.mKey = (Key)pKey;
		e.mChar = pKey;

		EvtManager.PropagateEvent( e );
	}

	void GLFWCALL CharPressedCallback( int pChar, int pValue ) {
		Event e;
		e.mType = Event::CharPressed;
		e.mChar = pChar;

		EvtManager.PropagateEvent( e );
	}

	void GLFWCALL MousePressedCallback( int pButton, int pValue ) {
		EvtManager.mCurrentState.mMouseState[pButton] = pValue;

		Event e;
		e.mType = pValue ? Event::MousePressed : Event::MouseReleased;
		e.mMouseButton = (MouseButton)pButton;

		EvtManager.PropagateEvent( e );
	}

	void GLFWCALL MouseWheelCallback( int pWheel ) {
		EvtManager.mCurrentState.mWheelState = pWheel;

		Event e;
		e.mType = Event::MouseWheelMoved;
		e.mWheel = pWheel - EvtManager.mPreviousState.mWheelState;
		
		EvtManager.PropagateEvent( e );
	}
		
	void GLFWCALL MouseMovedCallback( int pX, int pY ) {
		EvtManager.mCurrentState.mMousePos = glm::vec2( pX, pY );

		Event e;
		e.mType = Event::MouseMoved;
		e.mMousePos = glm::vec2( pX, pY );

		EvtManager.PropagateEvent( e );
	}
	

	void EventManager::AddListener( Listener& pListener ) {
		if( pListener.GetType() == Listener::MouseListener )
			mMouseListeners.push_back( dynamic_cast<MouseListener*>( &pListener ) );
		else
			mKeyListeners.push_back( dynamic_cast<KeyListener*>( &pListener ) );
	}

	void EventManager::PropagateEvent( const Event& pEvent ) {
		if( pEvent.mType == Event::KeyPressed || pEvent.mType == Event::KeyReleased || pEvent.mType == Event::CharPressed )
			for( u32 i = 0; i < mKeyListeners.size(); ++i )
				mKeyListeners[i]->OnEvent( pEvent );
		else
			for( u32 i = 0; i < mMouseListeners.size(); ++i )
				mMouseListeners[i]->OnEvent( pEvent );

	}

 
	void EventManager::Update() {
		// Set previous states to current states for incoming frame
		for( int i = 0; i < 5; ++i )
			mPreviousState.mMouseState[i] = mCurrentState.mMouseState[i];

		for( int i = 0; i < 330; ++i )
			mPreviousState.mKeyboardState[i] = mCurrentState.mKeyboardState[i];

		mPreviousState.mWheelState = mCurrentState.mWheelState;
		mPreviousState.mMousePos = mCurrentState.mMousePos;

	}

	bool EventManager::IsKeyDown( Key pB ) const {
		return mCurrentState.mKeyboardState[pB];
	}

	bool EventManager::IsKeyUp( Key pB ) const {
		return !mCurrentState.mKeyboardState[pB] && mPreviousState.mKeyboardState[pB];
	}

	bool EventManager::IsKeyHit( Key pB ) const {
		return mCurrentState.mKeyboardState[pB] && !mPreviousState.mKeyboardState[pB];
	}


	bool EventManager::IsMouseDown( MouseButton pB ) const {
		return mCurrentState.mMouseState[pB];
	}

	bool EventManager::IsMouseUp( MouseButton pB ) const {
		return !mCurrentState.mMouseState[pB] && mPreviousState.mMouseState[pB];
	}

	bool EventManager::IsMouseHit( MouseButton pB ) const {
		return mCurrentState.mMouseState[pB] && !mPreviousState.mMouseState[pB];
	}


	bool EventManager::IsWheelUp() const {
		return mCurrentState.mWheelState > mPreviousState.mWheelState;
	}

	bool EventManager::IsWheelDown() const {
		return mCurrentState.mWheelState < mPreviousState.mWheelState;
	}
}
