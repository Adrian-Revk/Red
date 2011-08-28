#ifndef LISTENER_HPP
#define LISTENER_HPP

/********************************************************************
	created:	2011/01/17
	filename: 	E:\C++\Red\src\Graphics\Listener.hpp
	author:		Red
	
	purpose:	Abstract class for all Listeners
*********************************************************************/

#include "Event.hpp"

#include <vector>

namespace blue {
	
	/// Abstract class for all Input Listeners
	class Listener {
	public:
		
		/// Listener Type
		enum Type {
			MouseListener,
			KeyListener,
			KeyMouseListener
		};

		/// Callable function which send the received event in the right callback
		/// @param pEvent : Received Event
		virtual void OnEvent(const Event &pEvent) = 0;

		/// Returns the Listener Type
		Type GetType() const { return mType; }

	protected:
		Type mType;		///< Listener Type
	};



	/// Mouse callback specialised Listener
	class MouseListener : public Listener {
	public:
		MouseListener() {
			mType = Listener::MouseListener;	
		}

		/// Callable function which send the received event in the right callback
		/// @param pEvent : Received Event
		virtual void OnEvent(const Event &pEvent) {
			switch(pEvent.mType){
			case Event::MouseMoved:
				OnMouseMoved( pEvent );
				break;
			case Event::MousePressed:
				OnMousePressed( pEvent );
				break;
			case Event::MouseReleased:
				OnMouseReleased( pEvent );
				break;
			case Event::MouseWheelMoved:
				OnMouseWheelMoved( pEvent );
				break;
			default:
				break;
			}
		}

	protected:
		// Overloadable functions for an inherited class
		virtual void OnMouseMoved( const Event &pEvent ) {}
		virtual void OnMousePressed( const Event &pEvent ) {}
		virtual void OnMouseReleased( const Event &pEvent ) {}
		virtual void OnMouseWheelMoved( const Event &pEvent ) {}
	};

	typedef std::vector<MouseListener*> MouseListenerList;
	


	/// Keyboard callback specialised Listener
	class KeyListener : public Listener {
	public:
		KeyListener() {
			mType = Listener::KeyListener;	
		}

		/// Callable function which send the received event in the right callback
		/// @param pEvent : Received Event
		virtual void OnEvent(const Event &pEvent){
			switch(pEvent.mType){
			case Event::KeyPressed:
				OnKeyPressed( pEvent );
				break;
			case Event::KeyReleased:
				OnKeyReleased( pEvent );
				break;
			case Event::CharPressed:
				OnCharPressed( pEvent );
				break;
			default:
				break;
			}
		}

	protected:
		// Overloadable functions for an inherited class
		virtual void OnKeyPressed( const Event& pEvent ) {}
		virtual void OnKeyReleased( const Event& pEvent ) {}
		virtual void OnCharPressed( const Event& pEvent ) {}
	};

	typedef std::vector<KeyListener*> KeyListenerList;

/*
	class KeyMouseListener : public Listener {
	public:
		KeyMouseListener() {
			mType = Listener::KeyMouseListener;
		}

		virtual void OnEvent( const Event& pEvent ) {
			switch( pEvent.mType ) {
			case Event::KeyPressed:
				OnKeyPressed( pEvent );
				break;
			case Event::KeyReleased:
				OnKeyReleased( pEvent );
				break;
			case Event::CharPressed:
				OnCharPressed( pEvent );
				break;
			case Event::MouseMoved:
				OnMouseMoved( pEvent );
				break;
			case Event::MousePressed:
				OnMousePressed( pEvent );
				break;
			case Event::MouseReleased:
				OnMouseReleased( pEvent );
				break;
			case Event::MouseWheelMoved:
				OnMouseWheelMoved( pEvent );
				break;
			default:
				break;
			}
		}

	protected:
		// Overloadable functions for an inherited class
		virtual void OnKeyPressed( const Event& pEvent ) {}
		virtual void OnKeyReleased( const Event& pEvent ) {}
		virtual void OnCharPressed( const Event& pEvent ) {}
		virtual void OnMouseMoved( const Event &pEvent ) {}
		virtual void OnMousePressed( const Event &pEvent ) {}
		virtual void OnMouseReleased( const Event &pEvent ) {}
		virtual void OnMouseWheelMoved( const Event &pEvent ) {}
	};
	*/
}
#endif // LISTENER_HPP
