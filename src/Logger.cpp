#include "Logger.hpp"

namespace red {
///			Logger Interface			///
	LogManager::LogManager() : mUseLoggers( false ), mCurrInstance(0) {
	}

	LogManager::~LogManager() {
		std::map<std::string, Log*>::iterator it;
		for( it = LogManager::Call().mInstanceStack.begin(); it != LogManager::Call().mInstanceStack.end(); ++it ) {
			delete (*it).second;
			(*it).second = NULL;
		}
		LogManager::Call().mCurrInstance = 0;
	}

	void LogManager::Init() {
		AddLog( "BasicLog", new FileLogger( defaultBaseLog ) );
		AddLog( "ErrorLog", new FileLogger( defaultErrorLog ) );
		AddLog( "DebugLog", new DebugLogger() );
		mUseLoggers = true;
	}

	void LogManager::AddLog( const std::string &pLogname, Log *pLog ) {
		if( pLog )
			mInstanceStack[pLogname] = pLog;
	}

	Log & LogManager::Base() {
		SetLogger( mInstanceStack["BasicLog"] );
		return *mCurrInstance;
	}

	Log & LogManager::Error() {
		SetLogger( mInstanceStack["ErrorLog"] );
		return *mCurrInstance;
	}

	Log & LogManager::Debug() {
		SetLogger( mInstanceStack["DebugLog"] );
		return *mCurrInstance;
	}

	void LogManager::SetLogger( Log* pLog ){
		mCurrInstance = pLog;
	}


///			FileLog Implementation		///
	FileLogger::FileLogger( const std::string &pFilename ) : mFile( pFilename.c_str() ) {
		if( !mFile )
			printf( "Error while opening %s.\n", pFilename.c_str() );
		else {
			mFile << "\t   ===============================================" << eol;
			mFile << "\t   ||\t\t  :: Engine Log ::\t\t||" << eol;
			mFile << "\t   ||\t    <" << GetDate() << ", " << GetTime() << ">   \t||" << eol;
			mFile << "\t   ===============================================" << eol;
		}

	}

	FileLogger::~FileLogger() {
		mFile << "\t   ===============================================" << eol;
		mFile << "\t   ||\t\t   :: Log End ::\t\t||" << eol;
		mFile << "\t   ===============================================" << eol;
		mFile.close();
	}

	void FileLogger::Write( const std::string &pMsg ) {
		if( mFile.is_open() ){
			mFile <<  pMsg;
			if( pMsg == eol )
				mFile.flush();
		}
	}

	void DebugLogger::Write( const std::string &pMsg ) {
		printf( "%s", pMsg.c_str() );
	}
}
