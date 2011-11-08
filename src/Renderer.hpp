#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Shader.hpp"
#include "Mesh.hpp"

#include <vector>

namespace red {
	
	void CheckGLErrorImpl( const std::string &pFile, u32 pLine );
	#define CheckGLError CheckGLErrorImpl( __FILE__, __LINE__ );

	class Renderer {
	public:
		Renderer();
		~Renderer();

		/// Returns a mesh created from raw data
		/// @param pPos			: Array of position elements of Mesh
		/// @param pPosSize		: size of this array
		/// @param pNorm		: Array of normal elements of Mesh
		/// @param pNormSize	: size of this array
		/// @param pIndices		: Array of index elements of Mesh
		/// @param pIndicesSize : size of this array
		Mesh* CreateMesh(	const glm::vec3* pPos, u32 pPosSize, 
							const glm::vec3* pNorm, u32 pNormSize,
							const u32* pIndices, u32 pIndicesSize );

        Mesh* LoadMesh( const std::string &pFileName );


		/// Returns a shader program created from direct Source string
		/// @param pVS : string containing the Vertex Shader src
		/// @param pFS : string containing the Fragment Shader src
		Shader* CreateShader( const std::string &pVS, const std::string &pFS );
		
		/// Returns a shader program created from shader files
		/// @param pVS : string containing the Vertex Shader filename
		/// @param pFS : string containing the Fragment Shader filename
		Shader* CreateShaderFromFile( const std::string &pVS, const std::string &pFS );

		/// Returns the current 3d projection matrix
		glm::mat4 GetProjectionMatrix() const { return m3DProjectionMatrix; }

	private:
		std::vector<Shader*>	mShaders;				///< List of created shaders
		std::vector<Mesh*>		mMeshes;				///< List of created meshes

		// Matrices
			glm::mat4			m3DProjectionMatrix;	///< Projection Matrix for 3d perspective
	};
}

#endif
