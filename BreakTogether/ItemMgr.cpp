#include "pch.h"
#include "ItemMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Player.h"

ItemMgr::ItemMgr() :m_bIsPlaying(false), m_iItemAmountArr{},checkDAbleTime(0.f)
{
}

ItemMgr::~ItemMgr()
{
}

void ItemMgr::Init()
{
	ResetItem();
}

void ItemMgr::Update()
{
}

void ItemMgr::ResetItem()
{
	for (int i = 0; i < 3; i++)
	{
		m_iItemAmountArr[i] = MAX_ITEM_COUNT;
	}
}

void ItemMgr::SizeUpBall()
{
	if (m_iItemAmountArr[0] <= 0) { return; }
	BallSizeUp();
}

void ItemMgr::HpHeal(Player* _player)
{
	if (m_iItemAmountArr[1] <= 0) { return; }
	int hp = _player->GetHp();
	_player->SetHp(hp + 1);
}

void ItemMgr::DamageAble(Player* _player)
{
	if (m_iItemAmountArr[2] <= 0) { return; }
	checkDAbleTime = TimeMgr::GetInst()->GetPlayTime();
	_player->SetDamageAlbe(false);
}