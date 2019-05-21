#pragma once
//��, ������Ʈ ����� Base�� �� Ŭ����
//������ �߻��Լ���� ������ ��
//Render�� �� Frame ��꿡�� Culling �Ŀ� RenderManager�� �Ѱ��ִ°� �⺻����
//model �� ������ �輼��

class Object
{
public:
	Object();
	~Object();

	void Initialize();
	void Frame();
	void Clear();

protected:
	D3DXVECTOR3 position;
	D3DXVECTOR3 oPosition;
	D3DXVECTOR3 direction;

};