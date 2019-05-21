#pragma once
//Camera의 base
//기본적인 함수만 정의해두고 세부적 처리 내용은 자식들에게 맡길 것

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	void Initiailze();
	void Frame();
	void Clear();

protected:
	D3DXVECTOR3 position;
	D3DXVECTOR3 oPosition;
	D3DXVECTOR3 lookAt;
};