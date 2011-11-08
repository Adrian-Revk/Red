#ifndef MESH_HPP
#define MESH_HPP

#include "Shared.hpp"

namespace red {
	/// Example of creation of a Mesh :
	///		const glm::vec3 pos[] = {	glm::vec3( -0.5f, 0, 0.5f ), ..., ..., ... };
	///		const glm::vec3 norm[] = {	glm::vec3( 0, 1, 0 ), ..., ..., ... };
	///		const u32 indices[] = { 0, 1, 2, , ..., ... };
	///
	///		Mesh m;
	///
	///		m.Begin();
	///			m.AddIBO( indices, sizeof( indices ) );
	///			m.AddVBO( pos, sizeof( pos ), 0 );
	///			m.AddVBO( norm, sizeof( norm ), 1 );
	///		m.End();
	///
	///
	///	This must be done like that. Position and Indices are a minimum. Normals and other
	/// are dependant of the shader.
	class Mesh {
	public:
		Mesh() : mVao( 0 ) {
			memset( mVbo, 0, sizeof( mVbo ) );
		}

		~Mesh();

		/// Function used to create the VAO and bind it.
		/// Call it before adding any VBO or IBO
		void Begin();

		/// Function used to end the VAO creation
		/// Call it after any VBO or IBO addition
		void End();
		
		/// Add a VBO to the current VAO
		/// @param pData		: array of vec3 data to store in VBO
		/// @param pDataSize	: size of this array
		/// @param pVAOPos		: position in VAO Attrib Array
		void AddVBO( const glm::vec3* pData, u32 pDataSize, u32 pVAOPos );

		/// Add an IBO to the current VAO
		/// @param pData		: array of u32 indices to store in IBO
		/// @param pDataSize	: size of this array
		void AddIBO( const u32* pData, u32 pDataSize );


		/// Bind the Mesh VAO to the GL State
		void Bind() const;
		
		/// Unbind all VAO from the GL State
		static void Unbind();

		/// Returns the number of indices in the mesh
		u32 GetIndexCount() const { return mIndexCount; }

	private:
		u32		mVao;			///< GL ID du VAO
		u32		mVbo[3];		///< GL ID des VBO ( 0=Position, 1=Normal, 2=Indices )
			
		u32		mIndexCount;	///< Number of indices of the mesh
	};
}
#endif