#include "ScreenScene.h"
#include "Shader.h"
#include "ScreenShader.h"
#include "Drawable.h"

namespace GK
{
	void ScreenScene::preRender()
	{
		GLRUN(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLRUN(glClear(GL_COLOR_BUFFER_BIT));
		GLRUN(glDisable(GL_DEPTH_TEST));
		GLRUN(glDisable(GL_BLEND));
	}

	ScreenScene::ScreenScene()
		: Scene(0, 0)
	{
		screenShader = std::shared_ptr<ScreenShader>(new ScreenShader());
		screenShader->compile();

		std::vector<Vertex> vertices = {
			Vertex({ -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f }),
			Vertex({ -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f }),
			Vertex({ 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f }),

			Vertex({ -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f }),
			Vertex({ 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f }),
			Vertex({ 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f })
		};
		auto instance = std::shared_ptr<DrawableInstance>(new DrawableInstance(screenShader, std::shared_ptr<Material>()));
		screenRect = std::shared_ptr<Drawable>(new Drawable(vertices, { instance }));
		this->getDrawables()->push_back(screenRect);
	}
	ScreenScene::~ScreenScene()
	{
	}
}