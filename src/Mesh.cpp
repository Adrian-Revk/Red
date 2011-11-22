#include "Mesh.hpp"
#include "Logger.hpp"
#include "GL/glew.h"

namespace red {
	Mesh::~Mesh() {
		glDeleteVertexArrays( 1, &mVao );
		glDeleteBuffers( 3, mVbo );
	}
	
	void Mesh::Begin() {
		if( mVao ) {
			glDeleteVertexArrays( 1, &mVao );
			glDeleteBuffers( 3, mVbo );
			mVao = 0;
		}

		glGenVertexArrays( 1, &mVao );
		glBindVertexArray( mVao );
	}

	void Mesh::End() {
		glBindVertexArray( 0 );
	}

	void Mesh::AddVBO( const glm::vec3* pData, u32 pDataSize, u32 pVAOPos ) {
		if( mVbo[pVAOPos] ) {
			ErrorLog << "Error in Mesh::AddVBO : VAO Position " << pVAOPos << " is already taken." << eol;
			return;
		}

		glGenBuffers( 1, &mVbo[pVAOPos] );
	
		glBindBuffer( GL_ARRAY_BUFFER, mVbo[pVAOPos] );
		glBufferData( GL_ARRAY_BUFFER, pDataSize, pData, GL_STATIC_DRAW );

		glVertexAttribPointer( pVAOPos, 3, GL_FLOAT, GL_FALSE, 0, 0 );
		glEnableVertexAttribArray( pVAOPos );
	}
	
	void Mesh::AddIBO( const u32* pData, u32 pDataSize) {
		glGenBuffers( 1, &mVbo[2] );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mVbo[2] );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, pDataSize, pData, GL_STATIC_DRAW );

		mIndexCount = pDataSize / sizeof( u32 );
	}

	void Mesh::Bind() const {
		glBindVertexArray( mVao );
	}

	void Mesh::Unbind() {
		glBindVertexArray( 0 );
	}
}
