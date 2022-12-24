#pragma once
class ScoreMgr
{
private:
	int m_iCurScore;
	vector<int> highScores;
	TCHAR m_tcScoreText[255];
public:
	SINGLE(ScoreMgr);
	ScoreMgr();
	~ScoreMgr();

	void Render(HDC _dc);

	int GetCurrentScore() { return m_iCurScore; }
	void ScoreUp(int _score) { m_iCurScore += _score; }
	void ScoreReset() { m_iCurScore = 0; }

	void SaveData();
	void LoadData();

	void PushNewScore(int _score);
	vector<int> GetHighScores();
};