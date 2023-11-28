
#include "OpenGLShader.h"
#include "glad/glad.h"
#include "Log.h"
#include "glm/gtc/type_ptr.hpp"
#include <fstream>
#include "tracy/Tracy.hpp"

namespace Nova {
	// shader种类，目前只支持 VS/PS
	static GLenum ShaderTypeFromString(const std::string& type) {
		if (type == "vertex") {
			return GL_VERTEX_SHADER;
		}

		if (type == "fragment" || type == "pixel") {
			return GL_FRAGMENT_SHADER;
		}

		NOVA_ASSERT(false, "Unknown shader type!");
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filePath) {
		// 读取 glsl 源码
		std::string source = ReadFile(filePath);
		auto ShaderSources = PreProcess(source);
		Compile(ShaderSources);

		// 以文件名作为shader名字
		// Extract name from filepath
		auto lastSlash = filePath.find_last_of("/\\");
		lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
		auto lastDot = filePath.rfind('.');
		auto count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;
		m_Name = filePath.substr(lastSlash, count);

		LOG_INFO("Init Shader Success: {}", filePath);
	}

	OpenGLShader::OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc) {
		// Create an empty vertex shader handle
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// Send the vertex shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		//reference to https://www.khronos.org/opengl/wiki/Shader_Compilation#Example
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// Compile the vertex shader
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(vertexShader);

			LOG_INFO("{0}", infoLog.data());
			NOVA_ASSERT(false, std::string("Vertex shader compilation failure! ") + "\n" + "vertex :\n" + vertexSrc);
			return;
		}

		// Create an empty fragment shader handle
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// Send the fragment shader source code to GL
		// Note that std::string's .c_str is NULL character terminated.
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// Compile the fragment shader
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// We don't need the shader anymore.
			glDeleteShader(fragmentShader);
			// Either of them. Don't leak shaders.
			glDeleteShader(vertexShader);

			LOG_INFO("{0}", infoLog.data());
			NOVA_ASSERT(false, std::string("Fragment shader compilation failure!") + "\n" + "fragment :\n" + fragmentSrc);
			return;
		}

		// Vertex and fragment shaders are successfully compiled.
		// Now time to link them together into a program.
		// Get a program object.
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// Attach our shaders to our program
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// Link our program
		glLinkProgram(program);

		// Note the different functions here: glGetProgram* instead of glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// We don't need the program anymore.
			glDeleteProgram(program);
			// Don't leak shaders either.
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			LOG_INFO("{0}", infoLog.data());
			NOVA_ASSERT(false, "Shader link failure!");
			return;
		}

		// Always detach shaders after a successful link.
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	OpenGLShader::~OpenGLShader() {
		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filePath) {
		std::string result;
		std::ifstream in(filePath, std::ios::in | std::ios::binary);
		if (in) {
			// 移动到文件末尾
			in.seekg(0, std::ios::end);
			// tellg()当前索引，即获取文件的二进制长度，按照字节来计算偏移
			// string.resize()按照char为单位，也是字节
			result.resize(in.tellg());
			// 移动到文件开头
			in.seekg(0, std::ios::beg);
			// 读取文件内容到result
			// 注意! &result[0]获取的是真正放字符串内容的内存地址，和std::string的地址是不一样的
			in.read(&result[0], result.size());
			in.close();
		}
		else {
			LOG_ERROR("Could not open file '{0}'", filePath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		std::unordered_map<GLenum, std::string> shaderSource;

		const char* typeToken = "#type";
		size_t typeTokenLength = strlen(typeToken);
		// pos： 指向"#type"开头
		// eol：指向"vertex"末尾
		// begin：指向"vertex"开头
		// nextLinePos：指向"#version"开头
		size_t pos = source.find(typeToken, 0);
		while (pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);         //#type后面的换行
			NOVA_ASSERT(eol != std::string::npos, "Syntax error");  // 没有换行，则后面没有逻辑，语法错误
			size_t begin = pos + typeTokenLength + 1;               // glsl第一行代码 +1表示跳过一个空格
			std::string type = source.substr(begin, eol - begin);

			size_t nextLinePos = source.find_first_not_of("\r\n", eol);
			// 找到下一个"#type"
			pos = source.find(typeToken, nextLinePos);
			shaderSource[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - nextLinePos);
		}
		return shaderSource;

	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {

		GLuint program = glCreateProgram();
		NOVA_ASSERT(shaderSources.size() <= 2, "we only support 2 shaders for now");
		std::array<GLenum, 2> glShaderIDs;
		int glShaderIDIndex = 0;
		for (auto& kv : shaderSources) {
			GLenum type = kv.first;
			const std::string& source = kv.second;
			GLuint shader = glCreateShader(type);
			const GLchar* sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);
			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
			if (isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);
				glDeleteShader(shader);

				LOG_ERROR("{0}", infoLog.data());
				NOVA_ASSERT(false, "Shader compilation failure!");
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = shader;
		}

		m_RendererID = program;
		glLinkProgram(program);
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
			glDeleteProgram(program);
			for (auto id : glShaderIDs) {
				glDeleteShader(id);
			}
			LOG_ERROR("{0}", infoLog.data());
			NOVA_ASSERT(false, "Shader link failure!");
			return;
		}
		for (auto id : glShaderIDs) {
			glDetachShader(program, id);
		}
	}

	void OpenGLShader::Bind() const {
		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		glUseProgram(0);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}
		glUniform2f(location, value.x, value.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}
		glUniform3f(location, value.x, value.y, value.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3 value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 value) {
		ZoneScopedN("OpenGLShader_UploadUniformMat4");
		ZoneText(name.c_str(), sizeof(name));
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());

		if (location == -1) {
			LOG_ERROR("No uniform found: {}", name);
			return;
		}

		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
}