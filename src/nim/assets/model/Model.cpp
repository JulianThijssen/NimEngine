#include "Model.hpp"

void Model::addMesh(const Mesh& mesh) {
	meshes.push_back(mesh);
}

void Model::addMaterial(const Material& material) {
	materials.push_back(material);
}
