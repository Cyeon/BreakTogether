#pragma once
#include "pch.h"
#include "define.h"

class SkillMgr
{
public:
	SINGLE(SkillMgr);

	std::vector<Action> OnSkillBoom;
	std::vector<Action> OnSkillSpawn;
	std::vector<Action> OnSkillRun;

	std::vector<std::function<void(Vec2Int)>> OnBlockBreak;

	RECT m_rUIRect{ 0,600,150,700 };
	TCHAR skillCoolTimeChar[255];

	float skillCoolTimeBoom = 0;
	float skillCoolTimeSpawn = 0;
	float skillCoolTimeRun = 0;

	void SkillBoom()
	{
		if (skillCoolTimeBoom > 0) return;
		skillCoolTimeBoom = 5;
		for (auto& action : OnSkillBoom)
			action();
	}

	void SkillSpawn()
	{
		if (skillCoolTimeSpawn > 0) return;
		skillCoolTimeSpawn = 5;
		for (auto& action : OnSkillSpawn)
			action();
	}

	void SkillRun()
	{
		if (skillCoolTimeRun > 0) return;
		skillCoolTimeRun = 5;
		for (auto& action : OnSkillRun)
			action();
	}

	void BreakBlock(Vec2Int position)
	{
		for (auto& action : OnBlockBreak)
			action(position);
	}

	void Update(float dt)
	{
		skillCoolTimeBoom = max(0, skillCoolTimeBoom - dt);
		skillCoolTimeSpawn = max(0, skillCoolTimeSpawn - dt);
		skillCoolTimeRun = max(0, skillCoolTimeRun - dt);
	}

	void Clear()
	{
		OnSkillBoom.clear();
		OnSkillSpawn.clear();
		OnSkillRun.clear();

		OnBlockBreak.clear();
	}

	void Render(HDC _dc)
	{
		swprintf(skillCoolTimeChar, sizeof(TCHAR) * 255, L"½ºÅ³ ÄðÅ¸ÀÓ\n\n Æø¡Ú¹ß: %d\n¹° »Ñ¸®±â: %d\n ´Þ¸®±â :%d", (int)skillCoolTimeBoom, (int)skillCoolTimeSpawn, (int)skillCoolTimeRun);
		DrawText(_dc, skillCoolTimeChar, -1, &m_rUIRect, DT_LEFT);
	}

};
