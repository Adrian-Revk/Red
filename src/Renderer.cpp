#include "Renderer.hpp"
#include "File.hpp"
#include "Logger.hpp"

#include "GL/glew.h"
#include "GL/SOIL.h"

#include <sstream>
#include <map>

namespace red {

	Renderer::Renderer() {
		m3DProjectionMatrix = glm::perspective( 60.f, 800.f/600.f, 0.1f, 50.f );
	}


	Renderer::~Renderer() {
		for(u32 i = 0; i < mShaders.size(); ++i)
			delete mShaders[i];
		
		for(u32 i = 0; i < mTextures.size(); ++i)
			delete mTextures[i];
		
		for(u32 i = 0; i < mMeshes.size(); ++i)
			delete mMeshes[i];
	}
	
	Mesh* Renderer::CreateMesh(	const glm::vec3* pPos, u32 pPosSize, 
								const glm::vec3* pNorm, u32 pNormSize,
								const u32* pIndices, u32 pIndicesSize ) {

		Mesh* m = new Mesh();

		m->Begin();
			m->AddIBO( pIndices, pIndicesSize );
			m->AddVBO( pPos, pPosSize, 0 );
			m->AddVBO( pNorm, pNormSize, 1 );
		m->End();

		mMeshes.push_back( m );

		return m;
	}

    Mesh* Renderer::CreateMeshFromFile( const std::string &pFileName ) {

        File objFile( pFileName, RWM_ReadOnly );

		if( !objFile.IsOpened() ) {
			DebugLog << "Renderer::LoadMesh : Cant open file " << pFileName << eol;
			return nullptr;
		}

        struct face {
            int pos;
            int tex;
            int norm;
        };

        std::vector<face> faces;                    // vector of faces of object in file
        std::vector<glm::vec3> positions, normals;  // vectors of first pass positions and normals retrieving
        std::vector<u32> indices;                   // vector of object indices
        f32 x,y,z;                                  // floats used to retrieve x, y and z components in file
        int pos, tex, norm;                         // ints used to retrieve pos, tex and norms indices from faces in file

        
        std::string line, word;
        while( !objFile.End() ) {
            line = objFile.GetLine();

            // process line if not a comment
            if( !IsComment( line, "#" ) ) {
                std::stringstream is ( line );
                is >> word;

                // vertex declaration
                if( "v" == word ) {
                    is >> word;
                    x = atof( word.c_str() );
                    is >> word;
                    y = atof( word.c_str() );
                    is >> word;
                    z = atof( word.c_str() );
                    positions.push_back( glm::vec3( x, y, z ) );
                }

                // normal declaration
                if( "vn" == word ) {
                    is >> word;
                    x = atof( word.c_str() );
                    is >> word;
                    y = atof( word.c_str() );
                    is >> word;
                    z = atof( word.c_str() );
                    normals.push_back( glm::vec3( x, y, z ) );
                }

                // face declaration
                if( "f" == word ) {

                    for( u32 u = 0; u < 3; ++u ) {
                        is >> word;
                        std::vector<std::string> svec = SplitString( word, "/" );
                        pos = atoi( svec[0].c_str() );
                        tex = atoi( svec[1].c_str() );
                        norm = atoi( svec[2].c_str() );
                        
                        int vertexFound = -1;
                        for( u32 v = 0; v < faces.size(); ++v )
                            if( norm == faces[v].norm && pos == faces[v].pos ) {
                                vertexFound = v;
                                break;
                            }

                        if( vertexFound >= 0 )
                            indices.push_back( vertexFound );
                        else {
                            face f = { pos, tex, norm };
                            faces.push_back( f );
                            indices.push_back( faces.size() - 1 );
                        }
                    }
                }
            }
        }

        // Creation of final vectors of pos, norm and texCoords 
        // after having retrieved the right indices from each faces
        std::vector<glm::vec3> finPos, finNorm;
        for( u32 u = 0; u < faces.size(); ++u) {
            finPos.push_back( positions[faces[u].pos - 1] );
            finNorm.push_back( normals[faces[u].norm - 1] );
        }


        // Mesh creation with VAO and retrieved data
        Mesh* ret = new Mesh();
        ret->Begin();
            ret->AddVBO( &finPos[0], finPos.size() * sizeof( glm::vec3 ), 0 );
            ret->AddVBO( &finNorm[0], finPos.size() * sizeof( glm::vec3 ), 1 );
            ret->AddIBO( &indices[0], indices.size() * sizeof( u32 ) );
        ret->End();

		mMeshes.push_back( ret );


        return ret;
    }

    Texture* Renderer::CreateTextureFromFile( const std::string &pFileName ) {
        Texture* t = new Texture();

        GLuint tex = SOIL_load_OGL_texture( pFileName.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT );

        t->mTexture = tex;

        mTextures.push_back( t );
        return t;
    }


	Shader* Renderer::CreateShader( const std::string &pVS, const std::string &pFS ) {
		Shader* s = new Shader();
		s->BuildProgram( pVS, pFS );

		mShaders.push_back( s );

		return mShaders[mShaders.size() - 1];
	}
	
	Shader* Renderer::CreateShaderFromFile( const std::string &pVS, const std::string &pFS ) {
		File vs( pVS, RWM_ReadOnly );
		if( !vs.IsOpened() ) {
			DebugLog << "Error cant open file " << pVS << eol;
			return nullptr;
		}

		File fs( pFS, RWM_ReadOnly );
		if( !fs.IsOpened() ) {
			DebugLog << "Error : Can't open file " << pFS << eol;
			return nullptr;
		}

		Shader* s = new Shader();
		s->BuildProgram( vs.Content(), fs.Content() );

		mShaders.push_back( s );

		return mShaders[mShaders.size() - 1];
	}

	void CheckGLErrorImpl( const std::string &pFile, u32 pLine ) {
#ifdef _DEBUG
		GLenum error = glGetError();

		if (error != GL_NO_ERROR)
		{
			std::string errorStr = "Unknown error.";
			std::string description  = "No description.";

			switch (error)
			{
				case GL_INVALID_ENUM :
				{
					errorStr = "GL_INVALID_ENUM";
					description = "An unacceptable value has been specified for an enumerated argument.";
					break;
				}

				case GL_INVALID_VALUE :
				{
					errorStr = "GL_INVALID_VALUE";
					description = "A numeric argument is out of range.";
					break;
				}

				case GL_INVALID_OPERATION :
				{
					errorStr = "GL_INVALID_OPERATION";
					description = "The specified operation is not allowed in the current state.";
					break;
				}

				case GL_STACK_OVERFLOW :
				{
					errorStr = "GL_STACK_OVERFLOW";
					description = "This command would cause a stack overflow.";
					break;
				}

				case GL_STACK_UNDERFLOW :
				{
					errorStr = "GL_STACK_UNDERFLOW";
					description = "This command would cause a stack underflow.";
					break;
				}

				case GL_OUT_OF_MEMORY :
				{
					errorStr = "GL_OUT_OF_MEMORY";
					description = "There is not enough memory left to execute the command.";
					break;
				}

				case GL_INVALID_FRAMEBUFFER_OPERATION :
				{
					errorStr = "GL_INVALID_FRAMEBUFFER_OPERATION_EXT";
					description = "The object bound to FRAMEBUFFER_BINDING is not \"framebuffer complete\".";
					break;
				}
			}

			ErrorLog << "OpenGL Error (" << /*StringUtils::GetFileNameWithoutPath(pFile) */ pFile
					 << " [" << pLine << "]) :" << eol
					 << "-- Error       : " << errorStr << eol 
					 << "-- Description : " << description << eol;
			DebugLog << "OpenGL Error happened! Check Error Log." << eol;
		}
#endif
	}
}
