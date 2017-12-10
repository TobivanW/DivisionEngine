#ifndef DIVISION_MESHLOADER_H
#define DIVISION_MESHLOADER_H

#include <d3d9.h>
#include <d3dx9.h>
#include <string>

#include "D3D9Mesh.h"
#include "ResourceLoader.h"

namespace Division
{
	class MeshLoader : public ResourceLoader
	{
	public:
		MeshLoader();
		~MeshLoader();
		static DivisionMesh* getResource(std::string, void*);
	};
}

#endif // !DIVISION_MESHLOADER_H