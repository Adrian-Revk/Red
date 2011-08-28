#ifndef FILE_HPP
#define FILE_HPP


#include "Shared.hpp"
#include <fstream>

namespace blue {
	/// Read/Write file opening mode
	enum ReadWriteMode{
		RWM_Write,				///< Read/Write, make a new file or overwrite an existant one
		RWM_Open,				///< Read/Write, does not overwrite, file must exist
		RWM_ReadOnly ,			///< Read Only mode, file must exist
	};

	/// Opening cursor position in file
	enum FilePos{
		FP_Top,									
		FP_Bottom
	};


	/// Class used for any file handling
	class File{
	public:
		/// Ctor, default, do nothing
		File();

		/// Ctor, open the given file in given mode
		/// @param pFilename : name of the file
		/// @param pFp		: file cursor position
		/// @param pRwm      : opening mode
		File( const std::string &pFilename, ReadWriteMode pRwm = RWM_Open, FilePos pFp = FP_Top );

		virtual ~File();

		/// Open a file (in buffer)
		/// @param pFilename : name of the file
		/// @param pFp		: file cursor position
		/// @param pRwm      : opening mode
		void Open( const std::string &pFilename, ReadWriteMode pRwm = RWM_Open, FilePos pFp = FP_Top );

		/// Close the opened file (buffer)
		void Close();

		/// Flush the buffer in the file
		void Flush();

		/// Returns the content of opened file in one string
		std::string Read() const;

		/// Returns true if a file is opened
		bool IsOpened() const;

		/// Returns the name of opened file
		std::string Filename() const;

		/// Returns true if EoF is reached
		bool End() const;

		/// Returns the current line in the opened file(and increments cursor afterwards)
		std::string GetLine();

		/// Stream Op for in file writing
		template<class T> File& operator<< ( T &pMsg );


		/// Static Methods
			/// Check if a file exists on drive
			/// @param pFilename : path to the file
			static bool Exists( const std::string &pFilename );

	protected:
		std::fstream mFile;			///< File buffer
		std::string mFileName;		///< File name (with path)
	};

	template<class T>
	inline File& File::operator<< ( T &pMsg ){
		if( IsOpened() )
			mFile << pMsg;
		return *this;
	}
}
#endif
