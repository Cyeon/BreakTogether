#include "pch.h"
#include "EventMgr.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "SoundMgr.h"
#include "Ball.h"
#include "Collider.h"

EventMgr::EventMgr()
{
}

EventMgr::~EventMgr()
{
}

void EventMgr::Update()
{
	// 이전 프레임에서 등록해둔 dead object 들을 삭제한다.
	for (size_t i = 0; i < m_vecDead.size(); i++)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();

	// ==== event 처리 ====

	for (size_t i = 0; i < m_vecEvent.size(); i++)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void EventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
		// lParam: Object Address
		// wParam: Group Type
		{
			auto pNewObj = (Object*)_eve.lParam;
 			auto eType = static_cast<GROUP_TYPE>(_eve.wParam);
			SceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
		}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
		{
			// lParam: Object Address
			// Object를 Dead 상태로 변경하고 삭제예정 오브젝트들을 모아둔다.
			auto pDeadObj = (Object*)_eve.lParam;
			pDeadObj->SetDead();
			m_vecDead.push_back(pDeadObj);
		}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
		{
			// lParam: Next Scene Type
			SoundMgr::GetInst()->StopAll();
			SceneMgr::GetInst()->ChangeScene(static_cast<SCENE_TYPE>(_eve.lParam));
		}
		break;
	case EVENT_TYPE::BALL_SIZEUP:
		{   
			vector<Object*> vec=SceneMgr::GetInst()->GetCurScene()->GetGroupObject(GROUP_TYPE::BALL);
			for (int i = 0; i < vec.size(); i++)
			{
				Ball* ball = static_cast<Ball*>(vec[i]);
				ball->SetSize((ball->GetSize()) * 2);
				ball->GetCollider()->SetScale(ball->GetCollider()->GetScale() * 2);
			}
	}
		break;
	}
}
