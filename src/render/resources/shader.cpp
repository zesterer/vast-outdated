//----STANDARD----
#include "stdio.h"
#include "fstream"
#include "vector"

//----LIBRARY----
#include "glbinding/gl/gl.h"
#include "glbinding/Binding.h"

//----LOCAL----
#include "shader.h"
#include "common/io.h"

namespace Vast
{
	namespace Render
	{
		namespace Resources
		{
			void Shader::enable()
			{
				//IO::output("Enabled shader program");
				gl::glUseProgram(this->gl_id);
			}
			
			glid Shader::getGLID()
			{
				return this->gl_id;
			}

			void Shader::loadFromFiles(std::string vertex_file_path, std::string fragment_file_path)
			{printf("TESTING\n");
				// Read the Vertex Shader code from the file
				IO::output("Loading vertex shader code from '" + vertex_file_path + "'");
				std::string VertexShaderCode;
				std::ifstream VertexShaderStream(vertex_file_path.c_str(), std::ios::in);
				if(VertexShaderStream.is_open())
				{
					std::string Line = "";
					while(std::getline(VertexShaderStream, Line))
						VertexShaderCode += Line + "\n";
					VertexShaderStream.close();
				}
				else
				{
					IO::output("Vertex shader location '" + vertex_file_path + "' cannot be opened", IO::OutputType::Error);
					return;
				}

				// Read the Fragment Shader code from the file
				IO::output("Loading fragment shader code from '" + fragment_file_path + "'");
				std::string FragmentShaderCode;
				std::ifstream FragmentShaderStream(fragment_file_path.c_str(), std::ios::in);
				if(FragmentShaderStream.is_open())
				{
					std::string Line = "";
					while(std::getline(FragmentShaderStream, Line))
						FragmentShaderCode += Line + "\n";
					FragmentShaderStream.close();
				}
				else
				{
					IO::output("Fragment shader location '" + fragment_file_path + "' cannot be opened", IO::OutputType::Error);
					return;
				}
				
				this->loadFromStrings(VertexShaderCode, FragmentShaderCode);
			}

			void Shader::loadFromStrings(std::string vertex_shader_code, std::string fragment_shader_code)
			{
				// Create the shaders
				gl::GLuint VertexShaderID = gl::glCreateShader(gl::GL_VERTEX_SHADER);
				gl::GLuint FragmentShaderID = gl::glCreateShader(gl::GL_FRAGMENT_SHADER);

				gl::GLint Result = 0;//GL_FALSE;
				int InfoLogLength;

				// Compile Vertex Shader
				IO::output("Compiling vertex shader");
				char const * VertexSourcePointer = vertex_shader_code.c_str();
				gl::glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
				gl::glCompileShader(VertexShaderID);

				// Check Vertex Shader
				gl::glGetShaderiv(VertexShaderID, gl::GL_COMPILE_STATUS, &Result);
				gl::glGetShaderiv(VertexShaderID, gl::GL_INFO_LOG_LENGTH, &InfoLogLength);
				std::vector<char> VertexShaderErrorMessage(InfoLogLength);
				gl::glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
				std::fprintf(stdout, "%s", &VertexShaderErrorMessage[0]);

				// Compile Fragment Shader
				IO::output("Compiling fragment shader");
				char const * FragmentSourcePointer = fragment_shader_code.c_str();
				gl::glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
				gl::glCompileShader(FragmentShaderID);

				// Check Fragment Shader
				gl::glGetShaderiv(FragmentShaderID, gl::GL_COMPILE_STATUS, &Result);
				gl::glGetShaderiv(FragmentShaderID, gl::GL_INFO_LOG_LENGTH, &InfoLogLength);
				std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
				gl::glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
				std::fprintf(stdout, "%s", &FragmentShaderErrorMessage[0]);

				// Link the program
				IO::output("Linking shader program");
				gl::GLuint ProgramID = gl::glCreateProgram();
				gl::glAttachShader(ProgramID, VertexShaderID);
				gl::glAttachShader(ProgramID, FragmentShaderID);
				gl::glLinkProgram(ProgramID);

				// Check the program
				gl::glGetProgramiv(ProgramID, gl::GL_LINK_STATUS, &Result);
				gl::glGetProgramiv(ProgramID, gl::GL_INFO_LOG_LENGTH, &InfoLogLength);
				std::vector<char> ProgramErrorMessage(std::max(InfoLogLength, int(1)));
				gl::glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
				if (ProgramErrorMessage.size() > 1)
					std::fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);

				//Delete the individual shaders (they're now packaged as part of a shader 'program')
				gl::glDeleteShader(VertexShaderID);
				gl::glDeleteShader(FragmentShaderID);

				this->gl_id = ProgramID;
			}
		}
	}
}
