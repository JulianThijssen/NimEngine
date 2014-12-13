#ifndef MESH_HPP
#define MESH_HPP

#include <nim/assets/model/Face.hpp>
#include <nim/engine/components/Component.hpp>
#include <nim/engine/core/math/Vector3f.hpp>
#include <nim/engine/core/math/Vector2f.hpp>
#include <vector>
#include <string>

class Mesh : public Component {
public:
	std::string name;
	std::vector<Vector3f> vertices;
	std::vector<Vector2f> texCoords;
	std::vector<Vector3f> normals;
	std::vector<Vector3f> tangents;
	std::vector<Face> faces;

	unsigned int handle;
	unsigned int numFaces;
};

#endif /* MESH_HPP */
