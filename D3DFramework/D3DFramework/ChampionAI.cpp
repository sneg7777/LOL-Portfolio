﻿#include "stdafx.h"
#include "ChampionAI.h"
#include "MiniScorePanel.h"
#include "Champion.h"

ChampionAI::ChampionAI(GameObject* owner)
    :IComponent(owner)
{
    unit = (Unit*)owner;
}

ChampionAI::ChampionAI(const ChampionAI& rhs)
    :IComponent(rhs)
{
}

ChampionAI::~ChampionAI()
{
}

void ChampionAI::Update()
{
    if (unit->IsDead())
    {
        deadFlag = true;
        return;
    }
    if (deadFlag)
    {
        deadFlag = false;
        nextPoint = Vector3(-3.49f, 67.72f, 3.92f);
        wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
    }

    int minute = 0;
    int second = 0;
    MiniScorePanel::GetInstance()->GetTime(&minute, &second);

    if (minute < 1) return;
    if (minute == 1 && second == 5)
    {
        startFlag = true;
        nextPoint = Vector3(-3.49f, 67.72f, 3.92f);
        wayPoint.push_back(Vector3(36.59f, 68.05f, 42.96f));
        return;
    }

    if (startFlag == false) return;

    float dt = Time::DeltaTime();

    if (unit->GetAttackTarget() == nullptr)
    {
        unit->SetAttackTarget(unit->GetLastAttacker());

        if (unit->GetAttackTarget() == nullptr)
        {
            unit->SetAttackTarget(unit->GetNearestEnemy(unit->transform->position, 3.5f));
            unit->SetNextSkill(unit->skillList[(int)SkillIndex::Attack]);
        }
    }

    if (unit->GetAttackTarget() != nullptr) // 타겟이 있을 때
    {
        if (unit->GetAttackTarget()->IsDead())
        {
            unit->SetAttackTarget(nullptr);
            return;
        }
    }
    else //  타겟이 없을 때
    {
        Vector3 to = nextPoint - unit->transform->position;
        float dist = to.Length();
        if (dist < 3.0f)
        {
            if (wayPoint.empty() == false)
            {
                nextPoint = wayPoint.front();
                wayPoint.pop_front();
            }
        }

        moveTick += dt;
        if (moveTick > moveDelay)
        {
            moveTick = 0.f;
            unit->SetAttackTarget(nullptr);
            unit->agent->SetStoppingDistance(1.f);
            //unit->SetDestination(nextPoint);
            unit->agent->SetDestination(nextPoint, true);
        }
    }
    


}

IComponent* ChampionAI::Clone()
{
    return new ChampionAI(*this);
}