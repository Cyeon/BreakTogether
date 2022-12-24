#pragma once
#define MAX_ITEM_COUNT 3
class Player;
class ItemMgr
{
public:
	SINGLE(ItemMgr);
	ItemMgr();
	~ItemMgr();
private:
	bool m_bIsPlaying;
	int m_iItemAmountArr[3];
	float checkDAbleTime;
	wstring m_wstrItemAmount;
	TCHAR itemAmount[255];
public:
	void Update();
	void Render(HDC _dc);
	void ResetItem();

	void SizeUpBall();
	void HpHeal(Player* player);
	void DamageAble(Player* player);
	
	float GetDAbleTime(){ return checkDAbleTime; }
};