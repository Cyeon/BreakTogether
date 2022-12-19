#pragma once
class Object;
class Animation;
class Image;

class Animator
{
private:
	Object* m_pOwner; // animation 소유 오브젝트
	map<wstring, Animation*> m_mapAni; // 모든 animation
	Animation* m_pCurAni; // 현재 재생중인 animation
	bool m_bRepeat;
public:
	Animator();
	~Animator();
	friend class Object;
public:
	Object* GetObj() { return m_pOwner; }
public:
	void CreateAnimation(wstring _strName, Image* _pImage, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, UINT _iFrameCount,
		float _fDuration, Vec2 _vAniSize, bool bIsCyan = false);
	Animation* FindAnimation(wstring _strName);
	void Play(wstring _strName, bool _bRepeat);
	void Stop();
	void Update();
	void Render(HDC _dc);
};
