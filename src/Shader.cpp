#include "Shader.hpp"
#include "Logger.hpp"
#include "Renderer.hpp"
#include "GL/glew.h"

#include <vector>

namespace red {
	Shader::~Shader() {
		glDeleteProgram( mProgram );
	}
	
	void Shader::BuildProgram( const std::string &pVS, const std::string &pFS ) {
		bool error = false;

		mProgram = glCreateProgram();

		if( !pVS.empty() && !pFS.empty() ) {
			GLuint shader = BuildShader( pVS, GL_VERTEX_SHADER );
			if( !shader )
				error = true;
			else {
				glAttachShader( mProgram, shader );
				glDeleteShader( shader );

				shader = BuildShader( pFS, GL_FRAGMENT_SHADER );
				if( !shader )
					error = true;
				else {
					glAttachShader( mProgram, shader );
					glDeleteShader( shader );
				}
			}
		} else
			error = true;

		if ( error ) {
			glDeleteProgram( mProgram );
			ErrorLog << "Failed to build Shader Program" << eol << eol;
		}
	}

	void Shader::BuildProgram( const std::string &pVS, const std::string &pFS, const std::string &pGS ) {

	}
	
	void Shader::Link() {
		glLinkProgram( mProgram );

		GLint status;
		glGetProgramiv( mProgram, GL_LINK_STATUS, &status );

		if( !status ) {
			GLint len;
			glGetProgramiv( mProgram, GL_INFO_LOG_LENGTH, &len );

			std::vector<GLchar> log(len);
			glGetProgramInfoLog( mProgram, static_cast<GLsizei>(log.size()), NULL, &log[0] );

			ErrorLog	<< "OpenGL Error :" << eol 
						<< "---------------------------------------------------" << eol
						<< &log[0] << eol
						<< "---------------------------------------------------" << eol;
			DebugLog	<< "OpenGL Error : Failed to link ShaderProgram. Check the ErrorLog!" << eol;
		}
	}
	
	void Shader::BindAttribLocation( const std::string &pVarName, u32 pLocation ) {
		glBindAttribLocation( mProgram, pLocation, pVarName.c_str() );
	}

	void Shader::Bind() const{
		glUseProgram(mProgram);
	}

	void Shader::Unbind() {
		glUseProgram(0);
	}

	u32 Shader::BuildShader( const std::string &pSrc, u32 pType ) const {
		u32 shader = glCreateShader( pType );

		const GLchar* src = pSrc.c_str();

		glShaderSource( shader, 1, &src, NULL );
		glCompileShader( shader );

		GLint status;
		glGetShaderiv( shader, GL_COMPILE_STATUS, &status );

		if( !status ) {
			GLint len;
			glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

			std::vector<GLchar> log(len);
			glGetShaderInfoLog( shader, static_cast<GLsizei>(log.size()), NULL, &log[0] );

			ErrorLog	<< "OpenGL Error :" << eol 
						<< "---------------------------------------------------" << eol
						<< &log[0] << eol
						<< "---------------------------------------------------" << eol;
			DebugLog	<< "OpenGL Error : Failed to compile Shader. Check the ErrorLog!" << eol;

			glDeleteShader( shader );
			shader = 0;
		}

		return shader;
	}
	
	void Shader::SendMatrix4( const std::string &pVarName, const glm::mat4 &pMatrix ) const {
		glUniformMatrix4fv( glGetUniformLocation( mProgram, pVarName.c_str() ), 1, GL_FALSE, glm::value_ptr( pMatrix ) );
		CheckGLError
	}

	void Shader::SendVector3( const std::string &pVarName, const glm::vec3 &pVector ) const {
		glUniform3fv( glGetUniformLocation( mProgram, pVarName.c_str() ), 1, glm::value_ptr( pVector ) );
		CheckGLError
	}
	
	void Shader::SendFloat( const std::string &pVarName, f32 pValue ) const {
		glUniform1f( glGetUniformLocation( mProgram, pVarName.c_str() ), pValue );
		CheckGLError
	}
}