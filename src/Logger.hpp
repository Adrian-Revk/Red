#ifndef LOGGER_HPP
#define LOGGER_HPP

/********************************************************************
	created:	2011/02/13
	filename: 	E:\C++\RedEngine\src\Engine\Debug\Logger.hpp
	author:		Red
	
	purpose:	Logger classes, permit engine-wide logging
*********************************************************************/

#include "Singleton.hpp"
#include "Shared.hpp"

#include <map>
#include <fstream>
#include <sstream>

namespace blue {
	/// Default Base Log name
	const std::string defaultBaseLog = "Engine.log";

	/// Default Error Log name
	const std::string defaultErrorLog = "Error.log";

	class Log;

	/// Logger Interface Class allowing the creation of a Log type Output with different implementation means
	class LogManager : public Singleton<LogManager>{
		friend class Singleton<LogManager>;
	public:
		LogManager();
		~LogManager();

		/// Initialize Basic Loggers
		void Init();

		/// Add a new log
		/// @param pLogname : name of log
		/// @param pLog : pointer to the log
		void AddLog(const std::string &pLogname, Log* pLog);

		/// Change the currently used log
		void SetLogger(Log* Log);

		/// Returns a Log With a Name
		//Logger& Log(const char* pLogname);

		/// Returns Base Log
		Log& Base();

		/// Returns Error Log
		Log& Error();

		/// Returns Debug Log
		Log& Debug();

		/// Returns true if the LogManager has been initialized
		bool UseLogs() const { return mUseLoggers; }

		/// Returns the currently used Log
		Log& GetCurrentLog() { return *mCurrInstance; }


	protected:
		bool mUseLoggers;							///< True in Debug Mode when logs are used

	private:
		Log* mCurrInstance;							///< Currently used Log
		std::map<std::string, Log*> mInstanceStack;	///< Logs
	};
	

	/// Ease of Use
	#define BaseLog	 LogManager::Call().Base()
	#define ErrorLog LogManager::Call().Error()
	#define DebugLog LogManager::Call().Debug()





	/// Interface class for any Log
	/// Must be inherited
	class Log {
	public:
		virtual ~Log(){}

		/// Send a message in the log
		template<class T> Log& operator << (const T& ToLog){
			if(LogManager::Call().UseLogs()){
				std::ostringstream oss;
				oss << ToLog;
				Write(oss.str());
			}
			return LogManager::Call().GetCurrentLog();
		}

	protected:
		/// Abstract Method used to write in the current Log
		virtual void Write(const std::string &pMsg) = 0;
	};



	/// Implementation with a File on drive
	class FileLogger : public Log {
	public:
		/// Create the log at the specified path
		/// @param pFilename : Path and filename of the log
		FileLogger(const std::string &pFilename);

	private:
		/// Destroy the log
		~FileLogger();

		/// Overload the Logger Write function
		virtual void Write(const std::string &pMsg);

		std::ofstream mFile;		/// Log File
	};

	/// Debug implementation of a log
	class DebugLogger : public Log {
		/// Overload the Logger Write function
		virtual void Write( const std::string &pMsg );
	};
}
#endif
