#include "AABB.hpp"

namespace blue {
	AABB::AABB( glm::vec3 pOrigin, glm::vec3 pEnd ) : mOrigin( pOrigin ), mEnd( pEnd ){
	}

	void AABB::Init( glm::vec3* pVertices, u32 pSize ) {
		for( u32 i = 0; i < pSize; ++i ) {
			mOrigin.x = glm::min( pVertices[i].x, mOrigin.x );
			mOrigin.y = glm::min( pVertices[i].y, mOrigin.y );
			mOrigin.z = glm::min( pVertices[i].z, mOrigin.z );

			mEnd.x = glm::max( pVertices[i].x, mEnd.x );
			mEnd.y = glm::max( pVertices[i].y, mEnd.y );
			mEnd.z = glm::max( pVertices[i].z, mEnd.z );
		}
	}

	void AABB::Scale( const glm::vec3 &pScaleFactor ) {
		mOrigin.x *= pScaleFactor.x;
		mOrigin.y *= pScaleFactor.y;
		mOrigin.z *= pScaleFactor.z;
		mEnd.x *= pScaleFactor.x;
		mEnd.y *= pScaleFactor.y;
		mEnd.z *= pScaleFactor.z;
	}

	void AABB::Translate( const glm::vec3 &pTrans ) {
		mOrigin += pTrans;
		mEnd += pTrans;
	}

	void AABB::GetVertices( glm::vec3 pTab[8] ) const {
		pTab[0] = mOrigin;
		pTab[1] = glm::vec3( mEnd.x, mOrigin.y, mOrigin.z );
		pTab[2] = glm::vec3( mOrigin.x, mEnd.y, mOrigin.z );
		pTab[3] = glm::vec3( mOrigin.x, mOrigin.y, mEnd.z );
		pTab[4] = glm::vec3( mOrigin.x, mEnd.y, mEnd.z );
		pTab[5] = glm::vec3( mEnd.x, mOrigin.y, mEnd.z );
		pTab[6] = glm::vec3( mEnd.x, mEnd.y, mOrigin.z );
		pTab[7] = mEnd;
	} 

	void BSphere::Init( const AABB &pAABB ) {
		mOrigin.x = ( pAABB.mOrigin.x + pAABB.mEnd.x ) / 2;
		mOrigin.y = ( pAABB.mOrigin.y + pAABB.mEnd.y ) / 2;
		mOrigin.z = ( pAABB.mOrigin.z + pAABB.mEnd.z ) / 2;

		mRadius = (f32)(( pAABB.mEnd - pAABB.mOrigin ).length());
	}
}
