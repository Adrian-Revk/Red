#include <sstream>
#include "File.hpp"


namespace red {
	File::File() : mFileName( "" ) {
	}

	File::File( const std::string &pFilename, ReadWriteMode pRwm, FilePos pFp ) {
		Open( pFilename, pRwm, pFp );
	}

	File::~File() {
		Close();
	}

	void File::Open( const std::string &pFilename, ReadWriteMode pRwm, FilePos pFp ) {
		std::ios_base::openmode mode;
		switch( pRwm ){
			case RWM_Write: 
				mode = std::fstream::in | std::fstream::out | std::fstream::trunc; break;
			case RWM_Open : 
				mode = std::fstream::in | std::fstream::out; break;
			case RWM_ReadOnly : 
				mode = std::fstream::in; break;
		}

		if( pFp == FP_Bottom )
				mode |= std::fstream::ate; 

		mFileName = pFilename;
		mFile.open( pFilename.c_str(), mode );
	}

	void File::Close() {
		if( IsOpened() )
			mFile.close();
	}

	void File::Flush() {
		if( IsOpened() )
			mFile.flush();
	}

	bool File::IsOpened() const {
		return mFile.is_open();
	}

	bool File::Exists( const std::string &pFilename ) {
		std::ifstream readFile( pFilename.c_str(), std::ios::in );
		readFile.close();
		return !readFile.fail();
	}

	std::string File::Filename() const {
		return mFileName;
	}

	bool File::End() const {
		return mFile.eof();
	}

	std::string File::GetLine(){
		std::string line;
		getline( mFile, line );
		return line;
	}

    std::string File::Content() const {
		if( mFile ){
			std::stringstream buffer;
			buffer << mFile.rdbuf();
			std::string ret( buffer.str() );
			ret.push_back( '\0' );
			return ret;
		} else {
			printf( "Tried to read an inexistant file : %s\n", mFileName.c_str() );	
			return "<unknown>";
		}
    }
/*

    void File::GoTo(FilePos pos){
        if(mFile.is_open())
            switch(pos){
                case BEG: mFile.seekg(0, ios::beg); break;
                case END: mFile.seekg(0, ios::end); break;
                case NEXT: JumpLine(); break;
                default:break;
            }
    }

    s

    string File::GetUntil(string s, char c){
        size_t pos = s.find_first_of(c);
        if(pos >= 10000){
            pos = 0;
            ErrLog << "File : in " << s << ", " << c << " is not present!" << eol;
        }
        return s.substr(0,pos);
    }
*/
}
