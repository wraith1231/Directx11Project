#pragma once
//모델, 오브젝트 등등의 Base가 될 클래스
//가급적 추상함수들로 구성할 것
//Render는 각 Frame 계산에서 Culling 후에 RenderManager에 넘겨주는걸 기본으로
//model 명만 가지고 계세오

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