#pragma once
//Camera�� base
//�⺻���� �Լ��� �����صΰ� ������ ó�� ������ �ڽĵ鿡�� �ñ� ��

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