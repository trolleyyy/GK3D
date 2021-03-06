#ifndef _GK_SCENELOADER
#define _GK_SCENELOADER

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include <functional>

#include "Common.h"
#include "Face3D.h"

namespace GK
{
	struct Vertex;
	struct Material;
	class Drawable;
	class Image;
	struct ModelData;

	class DrawableInstance;
	class PointLightInstance;
	class SpotLightInstance;
	class SurfaceInstance;
	class ShaderProgram;
	class SkyBox;
	typedef std::vector<std::shared_ptr<PointLightInstance> > PointLightsArray;
	typedef std::vector<std::shared_ptr<SpotLightInstance> > SpotLightsArray;
	typedef std::vector<std::shared_ptr<Drawable> > DrawablesArray;

	class GK3DSceneLoader
	{
	public:
		GK3DSceneLoader();
		~GK3DSceneLoader();

		void load();
		std::shared_ptr<PointLightsArray> getPointLights();
		std::shared_ptr<SpotLightsArray> getSpotLights();
		std::shared_ptr<DrawablesArray> getDrawables();
		glm::vec3 getCameraPosition();
		glm::vec3 getCameraFront();
		std::shared_ptr<PointLightInstance> getDamagedLamp();
		std::shared_ptr<SurfaceInstance> getSurface();
		std::shared_ptr<Drawable> getSkyBox();
		std::shared_ptr<DrawableInstance> getPlaneRect();
	private:
		std::shared_ptr<PointLightsArray> pointLights;
		std::shared_ptr<SpotLightsArray> spotLights;
		std::shared_ptr<DrawablesArray> drawables;
		std::shared_ptr<SurfaceInstance> surface;
		glm::vec3 cameraPosition;
		glm::vec3 cameraFront;

		void loadShaders();
		std::map<int, std::shared_ptr<ShaderProgram> > shaders;

		void loadModelsData();
		std::map<int, std::shared_ptr<ModelData>> modelsData;

		void loadSkybox();
		std::map<Face3D, std::shared_ptr<Image> > faces;
		std::shared_ptr<SkyBox> skyBoxInstance;
		std::shared_ptr<Drawable> skyBox;
		std::shared_ptr<DrawableInstance> planeRect;

		void createInstances();
		void createCubes();
		void createBenches();
		void createLamps();
		void createFirs();
		void createFlashLight();

		void createSkybox();
		void createSphere();

		void createGenericModel(int modelType, size_t count, glm::vec3 scale, glm::vec3* positions, glm::vec3* angles, std::shared_ptr<Material> defaultMaterial, int shader = 0,
			std::function<void(int, std::shared_ptr<DrawableInstance>)> createdInstanceCallback = nullptr);
		void createLampCallback(int modelType, std::shared_ptr<DrawableInstance> pointLight);
		std::map<int, std::vector<std::shared_ptr<DrawableInstance> > > instances;

		void buildPlaneRect();
		void buildSurface();
		void buildScene();
	};
}

#endif