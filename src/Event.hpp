#ifndef EVENT_HPP
#define EVENT_HPP

#include "Keys.hpp"

namespace blue {

	/// Event object binding a Type of Event to the value
	/// changed by the event.
	/// This is used primalarly by the GLFW Callback funcs
	/// to distribute the event recorded to all Listeners
	class Event {
	public:
		/// Type of the event
		enum Type {
			MouseMoved,
			MousePressed,
			MouseReleased,
			MouseWheelMoved,
			KeyPressed,
			KeyReleased,
			CharPressed
		} mType;
							
		glm::vec2 mMousePos;		///< In case of MouseMoved
		MouseButton mMouseButton;	///< In case of MousePressed/Released
		int mWheel;					///< In case of MouseWheelMoved
		Key mKey;					///< In case of KeyPressed/Released
		char mChar;					///< In case of CharPressed/KeyPressed/Released
	};


}
#endif
