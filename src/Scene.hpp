#ifndef SCENE_HPP
#define SCENE_HPP

#include "Renderer.hpp"
#include "HandleManager.hpp"

namespace red {
	/// During the rendering phase, the scene use a Data-oriented object storage to do its business
	/// Each 'object/entity' is stored in continuous space as a :
	///		- Mesh containing the actual OGL VAO to use				(in mMeshes)
	///		- Shader used to render the Mesh						(in mShaders)
	///		- World matrix used to translate and rotate the mesh	(in mWorldMatrices)
	///
	///	As such, an 'entity' is only a unique index integer, used to access the data in the parallel
	///	arrays.
	class Scene {
	public:
		Scene( Renderer* pRenderer );

		/// Add an entity to the current Scene. It will be rendered automatically
		/// every frames within the Render() function
		/// @param pMesh	: pointer to the Mesh to render
		/// @param pShader	: pointer to the Shader to use to render it
		/// @param pMatrix	: world matrix of the mesh
		/// @return			: the index in the scene arrays where the entity is added
		u32 AddEntity( Mesh* pMesh, Shader* pShader, const glm::mat4 &pMatrix );

		/// Render every 'entities' stored in the rendering arrays
		void Render();

		/// Used to change an entity's World Matrix from the outside
		void SetEntityMatrix( u32 pEntity, const glm::mat4 &pMatrix );

	private:
		// These arrays are parallels
		HandleManager<Mesh*>    	mMeshes;			///< Continuous array of Meshes that have to be rendered
		HandleManager<Shader*>		mShaders;			///< Continuous array of Shaders that are used to render the meshes
		HandleManager<glm::mat4>	mWorldMatrices;		///< Continuous array of World matrices that are used to move the meshes

		Renderer*					mRenderer;			///< Pointer to the Context's Renderer

		glm::mat4					m3DViewMatrix,		///< General View matrix of the scene
									m3DProjViewMatrix;	///< Product of the Renderer's projection matrix and the Scene View Matrix
	};
}

#endif
