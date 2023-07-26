#pragma once
#ifndef SKILL_SPURT_H
#define SKILL_SPURT_H

#include "Skill.h"

class Skill_Spurt :public Skill {
public:
    Skill_Spurt();
    ~Skill_Spurt();

    void Update(float elapsedTime);
};

#endif