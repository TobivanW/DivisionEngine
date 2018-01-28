#include "D3D9Renderer.h"
#include "D3D9Texture.h"
#include "D3D9Camera.h"
#include "LoggerPool.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_TEX1)

namespace Division
{
	D3D9Renderer::D3D9Renderer(LPDIRECT3DDEVICE9 direct3DDevice) :
		direct3DDevice_(direct3DDevice)
	{
	}



	D3D9Renderer::~D3D9Renderer()
	{
	}



	void D3D9Renderer::setup()
	{
		initializeGraphics();
		setupMatrices();

		direct3DDevice_->SetFVF(D3DFVF_CUSTOMVERTEX);
	}



	void D3D9Renderer::initializeGraphics()
	{
		//direct3DDevice_->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE); //Set cull type, currentlty none. Default Cull back faces with counterclockwise vertices.
		direct3DDevice_->SetRenderState(D3DRS_LIGHTING, FALSE); // Turn off Direct3D Lighting effects
		//direct3DDevice_->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}



	void D3D9Renderer::setupMatrices()
	{
		D3DXVECTOR3 viewPointStart(0.0f, 0.0f, 0.0f); //Vectors for building the viewMatrix
		D3DXVECTOR3 viewLookAt(5.0f, -1.0f, 0.0f);
		D3DXVECTOR3 upVector(0.0f, 1.0f, 0.0f);
		D3DXMATRIXA16 viewMatrix;
		D3DXMatrixLookAtLH(&viewMatrix, &viewPointStart, &viewLookAt, &upVector); //Builds a left-handed, look-at matrix.
		direct3DDevice_->SetTransform(D3DTS_VIEW, &viewMatrix); //Set the view matrix.

		D3DXMATRIXA16 projectionMatrix;
		D3DXMatrixPerspectiveFovLH(&projectionMatrix, D3DX_PI / 4, 1.0f, 0.4f, 100.0f); // Builds a left-handed perspective projection matrix based on a field of view.
		direct3DDevice_->SetTransform(D3DTS_PROJECTION, &projectionMatrix); //Set the perspective matrix.
	}



	void D3D9Renderer::setCameraMatrix(void* view) 
	{
		cameraView_ = static_cast<D3DXMATRIX*>(view); 
	}



	void D3D9Renderer::setWorldMatrix(Position* position)
	{
		D3DXMATRIX translationEntity;
		D3DXMATRIX rotationEntity;
		D3DXMATRIX worldEntity;
		
		// Translate and rotate the entity into the world.
		D3DXMatrixTranslation(&translationEntity, position->xPosition,  //Builds a matrix using the specified offsets.
							  position->yPosition, position->zPosition);
		D3DXMatrixRotationYawPitchRoll(&rotationEntity, position->yAngle, //Builds a matrix with a specified yaw, pitch, and roll.
									   position->xAngle, position->zAngle);
		// Translate then rotate, so the entity is rendered on the right spot.
		D3DXMatrixMultiply(&worldEntity, &translationEntity, &rotationEntity); //Determines the product of two matrices.

		direct3DDevice_->SetTransform(D3DTS_WORLD, &(worldEntity * (*cameraView_))); // Identifies the transformation matrix being set as the world transformation matrix. And sets it in the renderer.
	}



	void D3D9Renderer::setVertexBuffer(DivisionVertex* vertexBuffer, int verts)
	{
		// Create the vertex buffer.
		if (FAILED(direct3DDevice_->CreateVertexBuffer(verts * sizeof(DivisionVertex),
			0, D3DFVF_CUSTOMVERTEX,
			D3DPOOL_DEFAULT, &vertexBuffer_, NULL)))
		{
			;
		}

		// Fill the vertex buffer.
		VOID* pVertices;
		if (FAILED(vertexBuffer_->Lock(0, sizeof(DivisionVertex)* verts, (void**)&pVertices, 0))) //Locks a range of vertex data and obtains a pointer to the vertex buffer memory.
			;
		memcpy(pVertices, vertexBuffer, sizeof(DivisionVertex)* verts); // Copy vertexbuffer to locked memory space.
		vertexBuffer_->Unlock();//Unlocks vertex data.
		direct3DDevice_->SetStreamSource(0, vertexBuffer_, 0, sizeof(DivisionVertex)); //Binds a vertex buffer to a device data stream.
		vertexBuffer_->Release(); //Decrements the reference count for an interface on an object.
	}



	void D3D9Renderer::setIndexBuffer(void* indexBuffer, int indexes)
	{
		// Create the index buffer.
		if (FAILED(direct3DDevice_->CreateIndexBuffer(indexes * sizeof(DWORD),
			D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,
			D3DFMT_INDEX32,
			D3DPOOL_DEFAULT, &indexBuffer_, NULL)))
		{
			;
		}

		// Fill the index buffer.
		VOID* pData;
		if (FAILED(indexBuffer_->Lock(0, sizeof(DWORD)* indexes, (void**)&pData, 0)))
			;
		memcpy(pData, indexBuffer, sizeof(DWORD)* indexes); //Copy indexBuffer to locked memory space
		indexBuffer_->Unlock(); //Unlocks index data.
		direct3DDevice_->SetIndices(indexBuffer_); //Sets index data.
		indexBuffer_->Release(); //Decrements the reference count for an interface on an object.
	}



	void* D3D9Renderer::getDevice()
	{
		return direct3DDevice_;
	}



	void D3D9Renderer::increaseReferenceCount()
	{
		referenceCount_++;
	}



	void D3D9Renderer::decreaseReferenceCount()
	{
		referenceCount_--;
	}



	short D3D9Renderer::getReferenceCount()
	{
		return referenceCount_;
	}



	void D3D9Renderer::clear()
	{
		direct3DDevice_->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0xff, 0xff), 1.0f, 0); //Clears render target and depth buffer to yellow.
	}



	void D3D9Renderer::beginScene()
	{
		direct3DDevice_->BeginScene();
	}



	void D3D9Renderer::endScene()
	{
		direct3DDevice_->EndScene();
	}



	void D3D9Renderer::present(void* window)
	{
		HWND win = static_cast<HWND>(window);
		direct3DDevice_->Present(NULL, NULL, win, NULL); //Presents the contents of the next buffer in the sequence of win device.
	}



	void D3D9Renderer::setTexture(void* resource)
	{
		D3D9Texture* texture = static_cast<D3D9Texture*>(resource);
		direct3DDevice_->SetTexture(0, texture->getTextureData()); //Assigns a texture to a stage for a device.
		direct3DDevice_->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE); // Sets the state for stage to texture argument. Permissions are read-only.
		direct3DDevice_->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1); // Texture color blending operation to unmodified so original.
	}



	void D3D9Renderer::setHandle(void* handle)
	{
		windowHandle_ = static_cast<HWND>(handle);
	}
}