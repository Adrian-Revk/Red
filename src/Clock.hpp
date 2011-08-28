#ifndef CLOCK_HPP
#define CLOCK_HPP


#include "Shared.hpp"

namespace blue {
	/// Returns system time, depending on platform
    /// @return the UTC time, seconds only
	f64 GetSystemTime();

	/// Make the current thread sleep
	/// @param pTime : sleep time in seconds
	void Sleep(f32 pTime);


	/// Small Pausable Timer class
	class Clock{
	public:
		/// Ctor, zeroed clock
		Clock();

		/// Reset the clock to zero
		void Reset();

		/// Pause the clock
		void Pause();

		/// Resume the clock if it has been paused
		void Resume();

		/// Returns time elapsed since last Reset
		f32 GetElapsedTime();

	private:
		f64 mLastFrameTime;	///< Global seconds elapsed the previons frame
		f64 mClockTime;		///< Seconds since last clock reset
		f64 mTempTime;		///< Variable used in mClockTime calculation

		bool mPaused;		///< True if the clock is paused
	};
}
#endif
