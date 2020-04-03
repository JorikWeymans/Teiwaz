#pragma once
#include "SDXLLibrary.h"
#include <DirectXMath.h>
struct ID3D11DeviceContext;
struct ID3D11Device;

struct SDXLContext
{
	ID3D11DeviceContext* pContext;
	ID3D11Device* pDevice;
};

struct VertexPosCol
{
	VertexPosCol() : VertexPosCol({ 0.f,0.f,0.f }, {0.0f,0.0f,0.0f,0.0f}) {};
	VertexPosCol(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT4 col) :
		Position(pos), Color(col) {}

	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT4 Color;
};
namespace SDXL
{
	struct SDXLVec2
	{
		float x, y;
	};
	struct Vector3
	{
		float x, y, z;
	};
	struct SDXLVec4
	{
		float x, y, z, w;
	};
	
	SDXLLibrary_API struct SDXLRect
	{
		float x, y;
		float width, height;
	};
	
	SDXLLibrary_API enum class SDXL_EventType : UINT
	{
		SDX_NONE = 0b0000'0000,
		SDXL_QUIT = 0b1000'0000,


	};
	
	struct SDXL_EVENT
	{
		SDXL_EventType type = SDXL_EventType::SDX_NONE;
	};
	
}

