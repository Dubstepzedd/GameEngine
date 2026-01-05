#pragma once
#include "engine/gfx/geometry/Mesh.h"
#include <vector>
#include <glm/glm.hpp>  
#include <map>
#include <iostream>
#include <fstream>
#include "spdlog/spdlog.h"

enum class ObjElementType {
    POSITION,
    TEXCOORD,
    NORMAL, 
    FACE
};

struct ObjIndex {
    unsigned int posIndex;
    unsigned int uvIndex;
    unsigned int normIndex;
};

struct ObjFace {
    std::vector<ObjIndex> vertices;
};

struct RawModelData {
    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> texCoords;
    std::vector<glm::vec3> normals;

    // A list of actual polygonal faces
    std::vector<ObjFace> faces;
};

class MeshLoader {

    public:
	    MeshLoader() = delete;

        static RawModelData loadMesh(const std::string& path);
    private:
		// Helper functions for parsing
        static glm::vec3 parsePos(const std::string& data);
		static ObjFace parseFace(const std::string& data);
		static glm::vec2 parseTexCoord(const std::string& data);
		static glm::vec3 parseNormal(const std::string& data);

        static std::map<const std::string, ObjElementType> valueToType;
};