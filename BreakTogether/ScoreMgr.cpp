#include "pch.h"
#include "ScoreMgr.h"
#include <queue>

ScoreMgr::ScoreMgr() :m_iCurScore(0)
{

}

ScoreMgr::~ScoreMgr()
{
}

void ScoreMgr::PushNewScore(int _score)
{
	highScores.push_back(_score);
}

vector<int> ScoreMgr::GetHighScores()
{
	sort(highScores.rbegin(), highScores.rend());

	vector<int> vec;
	for (int i = 0; i < 10; i++)
	{
		if (i >= highScores.size()) { return vec; }
		vec.push_back(highScores[i]);
	}
	return vec;
}