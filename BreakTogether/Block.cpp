#include "pch.h"
#include "Block.h"
#include "Collider.h"
#include"Image.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "SkillMgr.h"
#include "ScoreMgr.h"

Block::Block(int& objectCount, Vec2Int position) :m_iHp(1), objectCount(objectCount)
{
	objectCount++;
	isdead = false;
	m_pImage = ResMgr::GetInst()->ImgLoad(L"BasicBlockImg", L"Image\\BasicBlock.bmp");
	m_pImage->SetScale(Vec2(4.f, 4.f));
	CreateCollider();
	GetCollider()->SetScale(Vec2(64.f, 64.f));

	this->position.x = position.x;
	this->position.y = position.y;

	SkillMgr::GetInst()->OnSkillBoom.emplace_back([&]
		{
			this->isExplosionNow = true;
		});

	SkillMgr::GetInst()->OnBlockBreak.emplace_back([&](Vec2Int pos)
		{
			if (!this->isExplosionNow) return;
			this->isExplosionNow = false;

			const Vec2Int tempPos = this->position;
			const float distX = abs(pos.x - this->position.x);
			const float distY = abs(pos.y - this->position.y);

			if ((distX + distY) <= 2.0f)
				DestroyBlock();
		});
}

Block::~Block()
{
	objectCount--;
}

void Block::Update()
{
}

void Block::Render(HDC _dc)
{
	m_pImage->Render(_dc, GetPos(), Vec2(0.f, 0.f));
	Component_Render(_dc);
}

void Block::EnterCollision(Collider* _pOther) {
	Object* pOtherObj = _pOther->GetObj();
	wstring wStr = pOtherObj->GetName();
	if (wStr == L"BALL") {
		SetDamage(1);
		if (m_iHp <= 0)
			DestroyBlock();
	}
}

void Block::DestroyBlock()
{
	if (isdead) return;
	ScoreMgr::GetInst()->ScoreUp(10);
	isdead = true;
	DeleteObject(this);

	if (!this->isExplosionNow) return;
	this->isExplosionNow = false;
	SkillMgr::GetInst()->BreakBlock(position);
}