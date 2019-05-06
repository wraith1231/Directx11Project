#ifndef __COMMON_H__
#define __COMMON_H__
#include "stdafx.h"

namespace Common
{
	template<typename T> class Singleton
	{
	public:
		static T* Get()
		{
			return m_cSingleton;
		}

		static void Set(T* val)
		{
			if (val == NULL)
				return;

			m_cSingleton = val;
		}

		static void Destroy()
		{
			delete m_cSingleton;
			m_cSingleton = NULL;
		}

	private:
		static T* m_cSingleton;
	};

	template <typename T> T* Singleton<T>::m_cSingleton = NULL;
}

struct Vertex
{
	Vertex()
		: Pos(0, 0, 0) {}

	D3DXVECTOR3 Pos;
};

struct VertexColor
{
	VertexColor()
	: Pos(0, 0, 0), Color(0, 0, 0, 1) { }

	D3DXVECTOR3 Pos;
	D3DXCOLOR Color;
};

struct VertexColorNormal
{
	VertexColorNormal()
		: Pos(0, 0, 0), Color(0, 0, 0, 1), Normal(0, 1, 0) {}

	D3DXVECTOR3 Pos;
	D3DXCOLOR Color;
	D3DXVECTOR3 Normal;
};

struct VertexTexture
{
	VertexTexture()
		: Pos(0, 0, 0), Uv(0, 0) {}

	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Uv;
};

struct VertexTextureNormal
{
	VertexTextureNormal()
		: Pos(0, 0, 0), Uv(0, 0), Normal(0, 1, 0) {}

	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Uv;
	D3DXVECTOR3 Normal;
};

struct VertexColorTextureNormal
{
	VertexColorTextureNormal()
		: Pos(0, 0, 0), Color(0, 0, 0, 1), Uv(0, 0), Normal(0, 1, 0) {}

	D3DXVECTOR3 Pos;
	D3DXCOLOR Color;
	D3DXVECTOR2 Uv;
	D3DXVECTOR3 Normal;
};

struct VertexTextureNormalBlend
{
	VertexTextureNormalBlend()
		: Pos(0, 0, 0), Uv(0, 0), Normal(0, 1, 0), BlendIndices(0, 0, 0, 0), BlendWeights(0, 0, 0, 0)
	{}

	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Uv;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 BlendIndices;
	D3DXVECTOR4 BlendWeights;
};

struct VertexTextureNormalTangent
{
	VertexTextureNormalTangent()
		: Pos(0, 0, 0), Uv(0, 0), Normal(0, 1, 0), Tangent(0, 1, 0)
	{}

	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Uv;
	D3DXVECTOR3 Normal;
	D3DXVECTOR3 Tangent;
};

struct VertexTextureTwoColor
{
	VertexTextureTwoColor()
		: Pos(0, 0, 0), Uv(0, 0), Color(0, 0, 0, 1), Color2(0, 0, 0, 1)
	{}

	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Uv;
	D3DXCOLOR Color;
	D3DXCOLOR Color2;
};

struct VertexTextureNormalColor
{
	VertexTextureNormalColor()
		: Pos(0, 0, 0), Uv(0, 0), Normal(0, 0, 0), Color(0, 0, 0, 1)
	{}

	D3DXVECTOR3 Pos;
	D3DXVECTOR2 Uv;
	D3DXVECTOR3 Normal;
	D3DXCOLOR Color;
};

#endif // !__COMMON_H__
