#include "pch.h"
#include "ScoreMgr.h"
#include "json.h"

#include <fstream>
#include <queue>
#include <sstream>

#include "PathMgr.h"

ScoreMgr::~ScoreMgr()
{
}

void ScoreMgr::PushNewScore(int _score)
{
	highScores.push_back(_score);
	SaveData();
}

ScoreMgr::ScoreMgr() :m_iCurScore(0)
{
	LoadData();
}

void ScoreMgr::SaveData()
{
	Json::Value root;
	Json::StreamWriterBuilder builder;

	for (int i = 0; i < highScores.size(); i++)
	{
		root["highScores"][i] = highScores[i];
	}

	wstring path = PathMgr::GetInst()->GetRsrcPath();
	path += L"highScores.save";
	std::ofstream ofs(path);
	std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
	writer->write(root, &ofs);
	ofs.close();
}

void ScoreMgr::LoadData()
{
	Json::Value root;
	Json::CharReaderBuilder builder;

	wstring path = PathMgr::GetInst()->GetRsrcPath();
	path += L"highScores.save";
	std::ifstream ifs(path);
	std::string errs;

	if (Json::parseFromStream(builder, ifs, &root, &errs))
	{
		for (int i = 0; i < root["highScores"].size(); i++)
		{
			highScores.push_back(root["highScores"][i].asInt());
		}
	}

	ifs.close();
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