#ifndef MODEL_HPP
#define MODEL_HPP

#include <nim/engine/components/Mesh.hpp>
#include <nim/assets/material/Material.hpp>
#include <vector>


class Model {
public:
	std::vector<Mesh> meshes;
	std::vector<Material> materials;

	void addMesh(const Mesh& mesh);
	void addMaterial(const Material& material);
};


#endif /* MODEL_HPP */
