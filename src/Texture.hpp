#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include "Shared.hpp"

namespace red {
    class Texture {
        friend class Renderer;
    public:
        Texture();
        ~Texture();

        /// Returns the (w,h) size of the texture
        //glm::vec2 GetSize() const { return mSize; }

        /// Binds the texture to the given unit
        /// @param pUnit : Unit of the binding (ex : 0 for GL_TEXURE0)
        void Bind( int pUnit ) const;

        /// Unbind all textures at the given unit on the given target
        /// @param pUnit   : Unit of the binding (ex : 0 for GL_TEXURE0)
        /// @param pTarget : Target of the binding (ex : GL_TEXTURE_2D)
        static void Unbind( int pUnit, u32 pTarget );

    private:
        u32     mTexture;           ///< GL ID of this texture
        u32     mTarget;            ///< Target of the texture (GL_TEXTURE_2D, ... )

        static int CurrentUnit;     ///< Current OpenGL Texture Unit (0,1,2 ..)
        static u32 CurrentTexture;  ///< Currently binded texture ID
    };
} 
#endif

