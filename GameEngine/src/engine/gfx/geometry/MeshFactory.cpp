#include "engine/gfx/geometry/MeshFactory.h"
#include <unordered_map>

void MeshFactory::addVertexData(std::vector<float>& vertexData, std::vector<unsigned int>& indicesData, const RawModelData& data, const ObjFace& face, unsigned int& index, unsigned int vertexIndex) {
	const ObjIndex& obj = face.vertices[vertexIndex];

	glm::vec3 p = data.positions[obj.posIndex];
	vertexData.push_back(p.x);
	vertexData.push_back(p.y);
	vertexData.push_back(p.z);

	if (obj.normIndex == OBJ_INVALID_INDEX) {
		spdlog::warn("Missing normal for vertex at position index {}", obj.posIndex);
		vertexData.push_back(1.0f);
		vertexData.push_back(1.0f);
		vertexData.push_back(1.0f);
	}
	else {
		glm::vec3 pNorm = data.normals[obj.normIndex];
		vertexData.push_back(pNorm.x);
		vertexData.push_back(pNorm.y);
		vertexData.push_back(pNorm.z);
	}

	indicesData.push_back(index++);
}

std::shared_ptr<Mesh> MeshFactory::createMesh(const RawModelData& data, const std::shared_ptr<Material> material) {

	// TODO: This is not memory efficient, so make it (dont repeat vertices inte vertex data - use a s)

	std::unordered_map<glm::vec3, unsigned int>;
	std::vector<float> vertexData;
	std::vector<unsigned int> indicesData;

	// Populate vertex data and indices
	unsigned int index = 0;
	for (const ObjFace& face : data.faces) {
		const size_t vertexCount = face.vertices.size();
		if (vertexCount < 3) {
			spdlog::warn("Face with less than 3 vertices found, skipping.");
			continue; // Skip malformed
		}

		// We need to triangulate the face if it has more than 3 vertices.
		for (size_t i = 1; i < vertexCount - 1; i++) {
			MeshFactory::addVertexData(vertexData, indicesData, data, face, index, 0);
			MeshFactory::addVertexData(vertexData, indicesData, data, face, index, i);
			MeshFactory::addVertexData(vertexData, indicesData, data, face, index, i+1);
		}
	}
	
	// Add the data to the buffers and arrays.
	std::shared_ptr<VertexBuffer> buffer = std::make_shared<VertexBuffer>(vertexData.data(), vertexData.size());
	std::shared_ptr<VertexArray> vertexArr = std::make_shared<VertexArray>();
	vertexArr->setBuffer(buffer, material->getLayout());
	std::shared_ptr<IndexBuffer> indexBuff = std::make_shared<IndexBuffer>(indicesData.data(), indicesData.size());

	return std::make_shared<Mesh>(
		vertexArr,
		indexBuff,
		material
	);

}