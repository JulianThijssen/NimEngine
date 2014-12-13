#include "ModelLoader.hpp"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <GL/glew.h>

#include <nim/engine/core/diag/Log.hpp>
#include <nim/engine/core/errors/AssetLoaderException.hpp>
#include <iostream>
#include <cstdio>

Model ModelLoader::loadModel(const Path& path) {
	Assimp::Importer importer;

	unsigned int flags = aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_SortByPType | aiProcess_GenUVCoords;
	const aiScene* scene = importer.ReadFile(path.str(), flags);

	if(!scene) {
		std::cout << importer.GetErrorString() << std::endl;
		//throw AssetLoaderException;
	}

	Model model = uploadModel(*scene);
	return model;
}

void ModelLoader::uploadModel(Model& model) {
	for(auto& mesh: model.meshes) {
		std::vector<float> vertexBuffer;
		std::vector<float> texCoordBuffer;
		std::vector<float> normalBuffer;
		std::vector<float> tangentBuffer;
		vertexBuffer.reserve(mesh.faces.size() * 9);
		texCoordBuffer.reserve(mesh.faces.size() * 6);
		normalBuffer.reserve(mesh.faces.size() * 9);
		tangentBuffer.reserve(mesh.faces.size() * 9);

		for(unsigned int i = 0; i < mesh.faces.size(); i++) {
			for(int j = 0; j < 3; j++) {
				const Face& face = mesh.faces[i];

				// Store the vertices in the buffer
				const Vector3f& vertex = mesh.vertices[face.vi[j]];
				vertexBuffer.push_back(vertex.x);
				vertexBuffer.push_back(vertex.y);
				vertexBuffer.push_back(vertex.z);

				// Store the texture coordinates in the buffer
				const Vector2f& texCoord = mesh.texCoords[face.vi[j]];
				texCoordBuffer.push_back(texCoord.x);
				texCoordBuffer.push_back(texCoord.y);

				// Store the normals in the buffer
				const Vector3f& normal = mesh.normals[face.vi[j]];
				normalBuffer.push_back(normal.x);
				normalBuffer.push_back(normal.y);
				normalBuffer.push_back(normal.z);

				// Store the tangents in the buffer
				const Vector3f& tangent = mesh.tangents[face.vi[j]];
				tangentBuffer.push_back(tangent.x);
				tangentBuffer.push_back(tangent.y);
				tangentBuffer.push_back(tangent.z);
			}
		}

		// Generate vertex array object
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Upload the vertices
		GLuint vertexVBO;
		glGenBuffers(1, &vertexVBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.vertices.size() * 3, vertexBuffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(0);

		// Upload the texture coordinates
		GLuint texCoordVBO;
		glGenBuffers(1, &texCoordVBO);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.texCoords.size() * 2, texCoordBuffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(1);

		// Upload the normals
		GLuint normalVBO;
		glGenBuffers(1, &normalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.normals.size() * 3, normalBuffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(2);

		// Upload the tangents
		GLuint tangentVBO;
		glGenBuffers(1, &tangentVBO);
		glBindBuffer(GL_ARRAY_BUFFER, tangentVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.tangents.size() * 3, tangentBuffer.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);
		glEnableVertexAttribArray(3);

		//Unbind the buffers
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		//Store relevant data in the new mesh
		mesh.handle = vao;
		mesh.numFaces = mesh.faces.size();
	}
}

Model ModelLoader::uploadModel(const aiScene& scene) {
	Model model;

	for(unsigned int i = 0; i < scene.mNumMeshes; i++) {
		aiMesh* aiMesh = scene.mMeshes[i];
		Mesh mesh;

		// Store face indices in an array
		//FIXME allocate on heap / vector
		unsigned int faceArray[aiMesh->mNumFaces * 3];

		for (unsigned int j = 0; j < aiMesh->mNumFaces; j++) {
			const aiFace* face = &aiMesh->mFaces[i];
			faceArray[j * 3 + 0] = face->mIndices[0];
			faceArray[j * 3 + 1] = face->mIndices[1];
			faceArray[j * 3 + 2] = face->mIndices[2];
		}

		// Generate vertex array object
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// Store faces in a buffer
		GLuint faceVBO;
		glGenBuffers(1, &faceVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, faceVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * aiMesh->mNumFaces * 3, faceArray, GL_STATIC_DRAW);

		// Store vertices in a buffer
		if (aiMesh->HasPositions()) {
			GLuint vertexVBO;
			glGenBuffers(1, &vertexVBO);
			glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * aiMesh->mNumVertices * 3, aiMesh->mVertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
			glEnableVertexAttribArray(0);
		}

		// Store texture coordinates in a buffer
		if (aiMesh->HasTextureCoords(0)) {
			GLuint texCoordVBO;
			glGenBuffers(1, &texCoordVBO);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * aiMesh->mNumVertices * 2, aiMesh->mTextureCoords[0], GL_STATIC_DRAW);
			glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);
			glEnableVertexAttribArray(1);
		}

		// Store normals in a buffer
		if (aiMesh->HasNormals()) {
			GLuint normalVBO;
			glGenBuffers(1, &normalVBO);
			glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * aiMesh->mNumVertices * 3, aiMesh->mNormals, GL_STATIC_DRAW);
			glVertexAttribPointer(2, 3, GL_FLOAT, 0, 0, 0);
			glEnableVertexAttribArray(2);
		}

		// Store tangents in a buffer
		if (aiMesh->HasTangentsAndBitangents()) {
			GLuint tangentVBO;
			glGenBuffers(1, &tangentVBO);
			glBindBuffer(GL_ARRAY_BUFFER, tangentVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * aiMesh->mNumVertices * 3, aiMesh->mTangents, GL_STATIC_DRAW);
			glVertexAttribPointer(3, 3, GL_FLOAT, 0, 0, 0);
			glEnableVertexAttribArray(3);
		}

		// Unbind the buffers
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Store relevant data in the new mesh
		mesh.handle = vao;
		mesh.numFaces = aiMesh->mNumFaces;

		model.addMesh(mesh);
	}

	return model;
}

Model ModelLoader::getTestObject() {
	Model model;
	Mesh mesh;
	mesh.vertices = {Vector3f(-1, -1, 0), Vector3f(1, 1, 0), Vector3f(-1, 1, 0)};
	Face face;
	face.vi[0] = 0;
	face.vi[1] = 1;
	face.vi[2] = 2;
	mesh.faces.push_back(face);

	float vertexBuffer[mesh.faces.size() * 9];

	for(unsigned int i = 0; i < mesh.faces.size(); i++) {
		for(int j = 0; j < 3; j++) {
			const Face& face = mesh.faces[i];
			unsigned int index = i * 9 + j * 3;

			// Store the vertices in the buffer
			const Vector3f& vertex = mesh.vertices[face.vi[j]];
			vertexBuffer[index + 0] = vertex.x;
			vertexBuffer[index + 1] = vertex.y;
			vertexBuffer[index + 2] = vertex.z;
		}
	}

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Upload the vertices
	GLuint vertexVBO;
	glGenBuffers(1, &vertexVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh.vertices.size() * 3, vertexBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	mesh.handle = vao;
	mesh.numFaces = 1;

	model.meshes.push_back(mesh);

	return model;
}
