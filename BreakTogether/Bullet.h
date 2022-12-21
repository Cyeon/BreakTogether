#pragma once
#include "Object.h"
class Image;
class Bullet :
    public Object
{
private:
    //    float m_fDir; // �Ѿ� ����(��, �Ʒ�)
    float m_fTheta; // �Ѿ� ����(��, �Ʒ�)
    Vec2  m_vDir;
    Image* m_pImage;

public:
    Bullet();
    ~Bullet();
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
public:
    CLONE(Bullet);

    void SetDir(float _fTheta)
    {
        m_fTheta = _fTheta;
    }
    void SetDir(Vec2 _vDir)
    {
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
};