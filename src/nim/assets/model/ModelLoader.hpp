#ifndef MODELLOADER_HPP
#define MODELLOADER_HPP

#include <assimp/scene.h>

#include <nim/assets/model/Model.hpp>
#include <nim/engine/core/file/Path.hpp>

class ModelLoader {
public:
	static Model loadModel(const Path& path);
	static void uploadModel(Model& model);
	static Model uploadModel(const aiScene& scene);
	static Model getTestObject();
};

#endif /* MODELLOADER_HPP */
