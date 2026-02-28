#pragma once
#include "engine/gfx/geometry/Mesh.h"
#include "engine/io/geometry/MeshLoader.h"
#include "engine/gfx/geometry/Buffer.h"


class MeshFactory {
	private:
		MeshFactory() = delete;
		static void addVertexData(std::vector<float>& vertexData, std::vector<unsigned int>& indicesData, const RawModelData& data, const ObjFace& face, unsigned int& index, unsigned int vertexIndex);
	public:
		static std::shared_ptr<Mesh> createMesh(const RawModelData& data, const std::shared_ptr<Material> material);
		
};