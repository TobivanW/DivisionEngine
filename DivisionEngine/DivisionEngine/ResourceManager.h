#ifndef DIVISION_RESOURCEMANAGER_H
#define DIVISION_RESOURCEMANAGER_H

#include <map>
#include <d3dx9.h>

#include "DivisionMesh.h"

namespace Division
{
	class ResourceManager
	{
	public:
		ResourceManager();
		ResourceManager(LPDIRECT3DDEVICE9);
		~ResourceManager();
		Resource* getTexture(std::string);
		DivisionMesh* getMesh(std::string);
		void removeTexture(std::string);
		void removeMesh(std::string);
	private:
		Resource* addNewTexture(std::string);
		DivisionMesh* addNewMesh(std::string);
		std::map<std::string, Resource*> textures_;
		std::map<std::string, Resource*> meshes_;
		LPDIRECT3DDEVICE9 direct3Ddevice_;
	};
}
#endif
