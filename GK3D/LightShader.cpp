#include "Common.h"
#include "LightShader.h"
#include "Scene.h"
#include "Camera.h"
#include <cmath>

namespace GK
{
	LightFragmentShader::LightFragmentShader()
		: Shader(Shader::FromFile("light_fragment_shader.glsl"), ShaderType::FragmentShader) {}
	LightFragmentShader::~LightFragmentShader() {}

	LightShader::LightShader()
		: ShaderProgram(std::shared_ptr<ObjectVertexShader>(new ObjectVertexShader()),
		std::shared_ptr<LightFragmentShader>(new LightFragmentShader()))
	{
	}

	LightShader::~LightShader() {}

	void LightShader::beforeLink()
	{
		glBindAttribLocation(getProgramId(), 0, "position");
	}

	void LightShader::prepareForRender(std::shared_ptr<DrawableInstance> drawableInstance, std::shared_ptr<Scene> scene)
	{
		std::shared_ptr<Camera> camera = scene->getCamera();

		// projection
		glm::mat4 projection;
		projection = glm::perspective(camera->getZoom(),
			((float)camera->getScreenWidth()) / camera->getScreenHeight(), 0.1f, 100.0f);
		glUniformMatrix4fv(getUniformLocation("view"), 1, GL_FALSE,
			glm::value_ptr(camera->getViewMatrix()));
		glUniformMatrix4fv(getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 model;
		model = glm::translate(model, drawableInstance->position);
		model = glm::rotate(model, glm::radians(drawableInstance->angleX), glm::vec3(1.0f, 0, 0));
		model = glm::rotate(model, glm::radians(drawableInstance->angleY), glm::vec3(0, 1.0f, 0));
		model = glm::rotate(model, glm::radians(drawableInstance->angleZ), glm::vec3(0, 0, 1.0f));
		model = glm::scale(model, drawableInstance->scale);
		glUniformMatrix4fv(getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(model));

		glm::vec3 intensity = drawableInstance->material->ambient + drawableInstance->material->diffuse;
		GLfloat maxval = fmax(fmax(intensity.r, intensity.g), intensity.b);
		if (maxval > 0)
			intensity /= maxval;
		glUniform3f(getUniformLocation("intensity"), intensity.r, intensity.g, intensity.b);
		glUniform3f(getUniformLocation("viewPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);
	}
}