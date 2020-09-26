#pragma once
#include <iostream>
#include <unordered_map>
#include "glm/glm.hpp"

namespace LexBrush
{
	struct ShaderProgramSource
	{
		std::string VertexSource;
		std::string FragmentSource;
	};

	class Shader
	{
	public:
		Shader(const std::string& vertexShader, const std::string& fragmentShader);
		~Shader();
		void BindShader() const;
		void UnbindShader() const;
		static ShaderProgramSource ParseShader(const std::string& filepath);
		void SetUniform1i(const std::string& name, int value);
		void SetUniform4f(const char* name,float* value);
		void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

	private:
		unsigned int CompileShader(unsigned int type, const std::string& source);
		int GetUniformLocation(const std::string& name);

	private:
		unsigned int m_Shader;
		std::unordered_map<std::string, int> m_UniformLocationCache;
	};

}