#pragma once
#include "Object.h"
class Image;

class Bullet : public Object
{
	Vec2 m_vDir;
	Image* m_pImage;

public:
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}

	void Update() override;
	void Render(HDC _dc) override;
	void EnterCollision(Collider* _pOther) override;

	CLONE(Bullet);

	Bullet();
	~Bullet() override;
};
