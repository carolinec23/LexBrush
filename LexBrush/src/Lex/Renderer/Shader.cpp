#include "lbpch.h"
#include "glad/glad.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

namespace LexBrush
{
	Shader::Shader(const std::string& vertexShader, const std::string& fragmentShader)
	{
		m_Shader = glCreateProgram();
		unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
		unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

		glAttachShader(m_Shader, vs);
		glAttachShader(m_Shader, fs);
		glLinkProgram(m_Shader);
		glValidateProgram(m_Shader);

		glDeleteShader(vs);
		glDeleteShader(fs);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_Shader);
	}

	void Shader::BindShader() const
	{
		glUseProgram(m_Shader);
	}

	void Shader::UnbindShader() const
	{
		glUseProgram(0);
	}

	ShaderProgramSource Shader::ParseShader(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1, VERTEX = 0, FRAGMENT = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line, '\r'))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
					type = ShaderType::VERTEX;
				else if (line.find("fragment") != std::string::npos)
					type = ShaderType::FRAGMENT;
				else
					std::cout << "Wrong type" << std::endl;
			}
			else
			{
				ss[(int)type] << line << '\n';
			}
		}

		return { ss[0].str(), ss[1].str() };
	}

	void Shader::SetUniform1i(const std::string& name, int value)
	{
		glUniform1i(GetUniformLocation(name), value);
	}

	void Shader::SetUniform4f(const char *name, float* value)
	{ 
		glUniform4f(GetUniformLocation(name), value[0], value[1], value[2], value[3]);
	}

	void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
	{
		glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
	}

	unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		//ERROR HANDLING:
		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE)
		{
			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);
			std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader." << std::endl;
			std::cout << message << std::endl;
			glDeleteShader(id);
		}
		//

		return id;
	}
	int Shader::GetUniformLocation(const std::string& name)
	{ 
		if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
			return m_UniformLocationCache[name];

		int location = glGetUniformLocation(m_Shader, name.c_str());
		if (location == -1)
			std::cout << "Warning: uniform " << name << " does not exist." << std::endl;

		m_UniformLocationCache[name] = location;
		return location;
	}
}
