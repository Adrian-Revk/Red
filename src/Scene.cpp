#include "Scene.hpp"
#include "GL/glew.h"

namespace red {
	Scene::Scene( Renderer* pRenderer ) : mRenderer( pRenderer ) {
		m3DViewMatrix = glm::lookAt( glm::vec3( 4.f, 4.f, 4.f ), glm::vec3( 0.f,0.f,0.f ), glm::vec3( 0.f,1.f,0.f ));

		m3DProjViewMatrix = mRenderer->GetProjectionMatrix() * m3DViewMatrix;

        //mWorldMatrices.ManageMemory( true );
	}

	u32 Scene::AddEntity( Mesh* pMesh, Shader* pShader, const glm::mat4 &pMatrix ) {
        u32 Handle = mMeshes.AddEntry( pMesh );
        u32 hS = mShaders.AddEntry( pShader );
        u32 hM = mWorldMatrices.AddEntry( pMatrix );

        if( Handle != hS || Handle != hM || hS != hM )
            DebugLog << "Scene Error : Stored Mesh/Shader/Matrices in HandleManagers arent parallels!!!!" << eol;

		//mMeshes.push_back( pMesh );
		//mShaders.push_back( pShader );
		//mWorldMatrices.push_back( pMatrix );

		//return mMeshes.size() - 1;
        return Handle;
	}

	void Scene::Render() {
		for( u32 i = 0; i < mMeshes.Size(); ++i ) {
            if( !mMeshes.GetEntry(i).mUsed )
                continue;

			if( i && mShaders[i] != mShaders[i-1] )
					mShaders[i]->Bind();
			
			mShaders[i]->SendMatrix4( "WorldMatrix", mWorldMatrices[i] );
			mShaders[i]->SendMatrix4( "MVPMatrix", m3DProjViewMatrix * mWorldMatrices[i] );

			mMeshes[i]->Bind();
			glDrawElements(GL_TRIANGLES, mMeshes[i]->GetIndexCount(), GL_UNSIGNED_INT, 0);
		}
	}

	void Scene::SetEntityMatrix( u32 pEntity, const glm::mat4 &pMatrix ) {
		if( pEntity < mWorldMatrices.Size() )
			mWorldMatrices.Set( pEntity, pMatrix );
	}
}
