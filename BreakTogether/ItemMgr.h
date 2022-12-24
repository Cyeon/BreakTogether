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
public:
	void Init();
	void Update();

	void ResetItem();

	void SizeUpBall();
	void HpHeal(Player* player);
	void DamageAble(Player* player);
	
	float GetDAbleTime(){ return checkDAbleTime; }
};