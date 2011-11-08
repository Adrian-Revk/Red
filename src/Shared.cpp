#include "Shared.hpp"
#include <iostream>

bool IsComment( std::string &pS, const std::string &pChar ) {
    while( ' ' == pS[0] || '\t' == pS[0] )
        pS.erase( 0, 1 );

    if( pS.substr( 0, pChar.length() ) == pChar )
        return true;
    return false;
}

std::vector<std::string> SplitString( const std::string &pS, const std::string &pTokens ) {
    std::vector<std::string> ret;
    
    size_t pos1 = 0, pos2 = pS.find_first_of( pTokens );

    while( std::string::npos != pos2 ) {
        ret.push_back( pS.substr( pos1, pos2 - pos1 ) );
        pos1 = pos2 + 1;
        pos2 = pS.find_first_of( pTokens, pos1 );
    }
    
    // add last substr
    ret.push_back( pS.substr( pos1, std::string::npos ) );

    return ret;
}
