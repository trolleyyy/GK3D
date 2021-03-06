#ifndef _GK_SURFACEINSTANCE
#define _GK_SURFACEINSTANCE

#include "Drawable.h"

class SurfaceShader;

namespace GK
{
	class SurfaceInstance : public DrawableInstance
	{
	private:
		Texture terrainTexes[2];
		int currentTerrainTex;
		Texture marksTexture;
		bool marksTexUsed;
		glm::vec2 texScale;
		glm::vec2 texOffset;
	public:
		SurfaceInstance(std::shared_ptr<ShaderProgram> shaderProgram,
			Texture firstTerrainTexture,
			Texture secondTerrainTexture,
			Texture marksTexture,
			glm::vec2 texScale,
			glm::vec2 texOffset,
			std::shared_ptr<Material> material,
			glm::vec3 position = glm::vec3(0, 0, 0),
			glm::vec3 scale = glm::vec3(1, 1, 1),
			GLfloat angleX = 0, GLfloat angleY = 0, GLfloat angleZ = 0);

		void toggleTerrainTex();
		void toggleMarksTex();
		void changeTexScale(float modifier);
		void moveTex(glm::vec2 offset);
		friend class SurfaceShader;
	};
}

#endif