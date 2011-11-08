#ifndef AABB_HPP
#define AABB_HPP

#include "Shared.hpp"
#include "glm/gtc/quaternion.hpp"

namespace red {
	struct Vertex;

	/// Axis-Aligned Bounding Box Class
	class AABB{
		/// For BSphere computation
		friend class BSphere;
	public:
		/// Ctor from already known bounding box
		AABB( glm::vec3 pOrigin, glm::vec3 pEnd );

		/// Initialize the AABB from a vertices array
		/// @param pVertices : vertice array
		/// @param pSize : element number in above array
		void Init( glm::vec3* pVertices, u32 pSize);

		/// Sets the AABB origin position
		void SetOrigin( const glm::vec3 &pOrigin ) { mOrigin = pOrigin; }

		/// Sets the AABB end position
		void SetEnd( const glm::vec3 &pEnd ) { mEnd = pEnd; }

		/// Scales the AABB with factors depending on axis
		void Scale( const glm::vec3 &pScaleFactor );

		/// Moves the AABB with a Vector
		void Translate( const glm::vec3 &pTrans );

		/// Rotate the AABB with a Quaternion
		void Rotate( const glm::quat &pOrient );

		/// Returns the 8 positions of the AABB
		void GetVertices( glm::vec3 pTab[8] ) const;
		
	protected:
		glm::vec3 mOrigin;
		glm::vec3 mEnd;
	};




	/// Bounding Sphere
	class BSphere {
	public:
		/// Ctor from an Origin point and a Radius
		BSphere( glm::vec3 pOrigin, f32 mRadius = 1.f );

		/// Initialize the BSphere from a vertices array
		/// @param pVertices : vertices array
		/// @param pSize : element number in above array
		void Init( Vertex* pVertices, u32 pSize );

		/// Initialize the BSphere from an AABB
		void Init( const AABB &pAABB );

		/// Sets the BSphere radius
		void SetRadius( f32 pValue ) { mRadius = pValue; }

		/// Sets the BSphere Origin point
		void SetOrigin( const glm::vec3 &pOrigin ) { mOrigin = pOrigin; }

		/// Moves the BSphere with a Vector3
		void Translate( const glm::vec3 &pTrans ) { mOrigin += pTrans; }

		/// Scales the BSPhere
		void Scale( f32 pScaleFactor ) { mRadius *= pScaleFactor; }

		/// Returns the BSphere radius
		f32 GetRadius() const { return mRadius; }

		/// Returns the BSphere origin point
		const glm::vec3& GetOrigin() const { return mOrigin; }

	private:
		f32 mRadius;
		glm::vec3 mOrigin;
	};
}
#endif
