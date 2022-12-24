#include "pch.h"
#include "ItemMgr.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Player.h"

ItemMgr::ItemMgr() :m_bIsPlaying(false), m_iItemAmountArr{},checkDAbleTime(0.f), m_wstrItemAmount(L"")
{
}

ItemMgr::~ItemMgr()
{
}

void ItemMgr::Update()
{
	swprintf(itemAmount, sizeof(TCHAR) * 255, L"남은 아이템의 수\n\nBall Size Up : %d\nHp Up : %d\n무적 :%d", m_iItemAmountArr[0], m_iItemAmountArr[1], m_iItemAmountArr[2]);

}
void ItemMgr::Render(HDC _dc)
{
	RECT rt = RECT(0, 700, 150, 800);
	DrawText(_dc, itemAmount, -1, &rt, DT_LEFT );
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
	m_iItemAmountArr[0]--;
	BallSizeUp();
}

void ItemMgr::HpHeal(Player* _player)
{
	if (m_iItemAmountArr[1] <= 0) { return; }
	m_iItemAmountArr[1]--;
	int hp = _player->GetHp();
	_player->SetHp(hp + 1);
}

void ItemMgr::DamageAble(Player* _player)
{
	if (m_iItemAmountArr[2] <= 0) { return; }
	m_iItemAmountArr[2]--;
	checkDAbleTime = TimeMgr::GetInst()->GetPlayTime();
	_player->SetDamageAlbe(false);
}