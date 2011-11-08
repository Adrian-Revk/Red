#ifndef SHADER_HPP
#define SHADER_HPP

#include "Shared.hpp"

namespace red {
	class Shader {
	public:
		Shader() : mProgram( 0 ) {}
		~Shader();
		
		/// Create a Shader Program from a Vertex and a Fragment Shader
		/// @param pVS : raw text source of the Vertex Shader
		/// @param pFS : raw text source of the Fragment Shader
		void BuildProgram( const std::string &pVS, const std::string &pFS );

		/// Create a Shader Program from a Vertex, a Fragment Shader and a Geometry Shader
		/// @param pVS : raw text source of the Vertex Shader
		/// @param pFS : raw text source of the Fragment Shader
		/// @param pGS : raw text source of the Geometry Shader
		void BuildProgram( const std::string &pVS, const std::string &pFS, const std::string &pGS );

		/// Link the Shader Program to the OpenGL machine
		void Link();

		/// Bind a shader attrib location to a shader variable name
		void BindAttribLocation( const std::string &pVarName, u32 pLocation );

		/// Bind the Shader Program to the GL State
		void Bind() const;

		/// Unbind all Shader Programs from the GL State
		static void Unbind();

		/// Send a uniform Matrix4x4 to the shader.
		/// @param pVarName : Variable name in the shader src
		/// @param p... : Actual value to send to the shader
			
			// for a mat4
			void SendMatrix4( const std::string &pVarName, const glm::mat4 &pMatrix ) const;

			// for a vec3
			void SendVector3( const std::string &pVarName, const glm::vec3 &pVector ) const;

			// for unique value
			void SendFloat( const std::string &pVarName, f32 pValue ) const; 

		u32 mProgram;	///< Shader Program ID

	private:
		/// Create a GL Shader from raw text source
		/// @param pSrc : string containing the shader source
		/// @param pType : type de shader (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER)
		/// @return : the created shader GL ID
		u32 BuildShader( const std::string &pSrc, u32 pType ) const;
	};
}

#endif