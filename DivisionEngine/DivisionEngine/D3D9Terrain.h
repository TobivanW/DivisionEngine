#ifndef DIVISION_TERRAIN_H
#define DIVISION_TERRAIN_H

#include "D3D9Mesh.h"
#include "Renderer.h"
#include "Resource.h"
#include "Entity.h"

namespace Division
{
	/**
	    A terrain object to render and create terrain.
	*/
	class D3D9Terrain : public Entity
	{
	public:
		D3D9Terrain(ResourceManager*, DivisionVertex vertices[], int, int);
		~D3D9Terrain();
		void render(Renderer* renderer);
		/**
		   Generates indices based on the vertices.
		*/
		int generateIndices(int** ppIndices, int verticesAlongWidth, int verticesAlongLength);
		void setTexture(std::string textureFile);
	private:
		Resource* texture_ = NULL; // texture
		DivisionVertex* vertices_;
		int vertexCount_ = 0;
		int* indices_ = NULL;
		DWORD indexCount_ = 0;
		LPDIRECT3DDEVICE9 direct3Ddevice_ = NULL; // device
		LPDIRECT3DVERTEXBUFFER9 vertexBuffer_ = NULL; // buffer
		LPDIRECT3DINDEXBUFFER9 indexBuffer_ = NULL; // Buffer to hold indices
	};
}

#endif