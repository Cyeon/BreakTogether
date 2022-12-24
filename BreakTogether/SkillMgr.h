#pragma once
#include "pch.h"
#include "define.h"

class SkillMgr
{
public:
	SINGLE(SkillMgr);

	std::vector<Action> OnSkill0;
	std::vector<Action> OnSkill1;
	std::vector<Action> OnSkill2;

	std::vector<std::function<void(Vec2Int)>> OnBlockBreak;

	RECT m_rUIRect{ 0,600,150,700 };
	TCHAR skillCoolTimeChar[255];

	float skillCoolTime0 = 0;
	float skillCoolTime1 = 0;
	float skillCoolTime2 = 0;

	void Skill0()
	{
		if (skillCoolTime0 > 0) return;
		skillCoolTime0 = 5;
		for (auto& action : OnSkill0)
			action();
	}

	void Skill1()
	{
		if (skillCoolTime1 > 0) return;
		skillCoolTime1 = 5;
		for (auto& action : OnSkill1)
			action();
	}

	void Skill2()
	{
		if (skillCoolTime2 > 0) return;
		skillCoolTime2 = 5;
		for (auto& action : OnSkill2)
			action();
	}

	void BreakBlock(Vec2Int position)
	{
		for (auto& action : OnBlockBreak)
			action(position);
	}

	void Update(float dt)
	{
		skillCoolTime0 = max(0, skillCoolTime0 - dt);
		skillCoolTime1 = max(0, skillCoolTime1 - dt);
		skillCoolTime2 = max(0, skillCoolTime2 - dt);
	}

	void Clear()
	{
		OnSkill0.clear();
		OnSkill1.clear();
		OnSkill2.clear();

		OnBlockBreak.clear();
	}

	void Render(HDC _dc)
	{
		swprintf(skillCoolTimeChar, sizeof(TCHAR) * 255, L"½ºÅ³ ÄðÅ¸ÀÓ\n\n Æø¡Ú¹ß: %d\n¹° »Ñ¸®±â: %d\n ´Þ¸®±â :%d", (int)skillCoolTime0, (int)skillCoolTime1, (int)skillCoolTime2);
		DrawText(_dc, skillCoolTimeChar, -1, &m_rUIRect, DT_LEFT);
	}

};
