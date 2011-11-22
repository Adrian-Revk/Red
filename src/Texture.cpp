#include "Texture.hpp"
#include "GL/glew.h"

namespace red {
    int Texture::CurrentUnit = GL_TEXTURE0;
    u32 Texture::CurrentTexture = 0;

    Texture::Texture() : mTexture( 0 ), mTarget( GL_TEXTURE_2D ) {
    }

    Texture::~Texture() {
        glDeleteTextures( 1, &mTexture );
    }

    void Texture::Bind( int pUnit ) const {
        // Check which Texture ID is currently bind to the unit, to avoid unnecessary binds
        if( CurrentTexture != mTexture ) {
            CurrentTexture = mTexture;

            // Check which texture unit is active and change it if necessary
            if( ( pUnit + GL_TEXTURE0 ) != CurrentUnit ) {
                CurrentUnit = pUnit + GL_TEXTURE0;
                glActiveTexture( CurrentUnit );
            }   

            glBindTexture( mTarget, mTexture );
        }
    }

    void Texture::Unbind( int pUnit, u32 pTarget ) {
        // Check which texture unit is active and change it if necessary
        if( ( pUnit + GL_TEXTURE0 ) != CurrentUnit ) {
            CurrentUnit = pUnit + GL_TEXTURE0;
            glActiveTexture( CurrentUnit );
        }

        glBindTexture( pTarget, 0 );
    }
} 
