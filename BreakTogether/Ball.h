#pragma once
#include "BWindow.h"
#include "define.h"
#include "Object.h"
#include "Vec2.h"
class Image;

class Ball : public Object
{
	Vec2 m_vDir;
	Image* m_pImage;
	bool m_bounce = false;


	enum class BounceDir
	{
		X,
		Y
	};

public:
	void SetDir(Vec2 _vDir)
	{
		m_vDir = _vDir;
		m_vDir.Normalize();
	}

	void Update() override;
	void Render(HDC _dc) override;
	void EnterCollision(Collider* _pOther) override;

	CLONE(Ball);

	Ball();
	~Ball() override;

private:
	void Bounce(BounceDir bounce_dir);
};
