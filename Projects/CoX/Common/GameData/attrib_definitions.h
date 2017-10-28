#pragma once
#include <vector>
#include <QtCore/QString>

struct Parse_AttribDesc
{
    QString Name;
    QString DisplayName;
    QString IconName;
};
struct AttribNames_Data
{
    std::vector<Parse_AttribDesc> m_Damage;
    std::vector<Parse_AttribDesc> m_Defense;
    std::vector<Parse_AttribDesc> m_Boost;
    std::vector<Parse_AttribDesc> m_Group;
};

struct Parse_CharAttrib
{
    float m_DamageType00;
    float m_DamageType01;
    float m_DamageType02;
    float m_DamageType03;
    float m_DamageType04;
    float m_DamageType05;
    float m_DamageType06;
    float m_DamageType07;
    float m_DamageType08;
    float m_DamageType09;
    float m_DamageType10;
    float m_DamageType11;
    float m_DamageType12;
    float m_DamageType13;
    float m_DamageType14;
    float m_DamageType15;
    float m_DamageType16;
    float m_DamageType17;
    float m_DamageType18;
    float m_DamageType19;
    float m_DamageType20;
    float m_DamageType21;
    float m_DamageType22;
    float m_DamageType23;
    float m_HitPoints;
    float m_Endurance;
    float m_ToHit;
    float m_DefenseType00;
    float m_DefenseType01;
    float m_DefenseType02;
    float m_DefenseType03;
    float m_DefenseType04;
    float m_DefenseType05;
    float m_DefenseType06;
    float m_DefenseType07;
    float m_DefenseType08;
    float m_DefenseType09;
    float m_DefenseType10;
    float m_DefenseType11;
    float m_DefenseType12;
    float m_DefenseType13;
    float m_DefenseType14;
    float m_DefenseType15;
    float m_DefenseType16;
    float m_DefenseType17;
    float m_DefenseType18;
    float m_DefenseType19;
    float m_DefenseType20;
    float m_DefenseType21;
    float m_DefenseType22;
    float m_DefenseType23;
    float m_Defense;
    float m_Evade;
    float m_SpeedRunning;
    float m_SpeedFlying;
    float m_SpeedSwimming;
    float m_SpeedJumping;
    float m_JumpHeight;
    float m_MovementControl;
    float m_MovementFriction;
    float m_Stealth;
    float m_StealthRadius;
    float m_PerceptionRadius;
    float m_Regeneration;
    float m_Recovery;
    float m_ThreatLevel;
    float m_Taunt;
    float m_Confused;
    float m_Afraid;
    float m_Held;
    float m_Immobilized;
    float m_Stunned;
    float m_Sleep;
    float m_Fly;
    float m_Jumppack;
    float m_Teleport;
    float m_Untouchable;
    float m_Intangible;
    float m_OnlyAffectsSelf;
    float m_Knockup;
    float m_Knockback;
    float m_Repel;
    float m_Accuracy;
    float m_Radius;
    float m_Arc;
    float m_Range;
    float m_TimeToActivate;
    float m_RechargeTime;
    float m_InterruptTime;
    float m_EnduranceDiscount;
    float *begin() { return &m_DamageType00; }
    float *end() { return (&m_EnduranceDiscount)+1; }
    const float *begin() const { return &m_DamageType00; }
    const float *end() const { return (&m_EnduranceDiscount)+1; }
};
struct Parse_CharAttribMax
{
    std::vector<float> m_DamageType00;
    std::vector<float> m_DamageType01;
    std::vector<float> m_DamageType02;
    std::vector<float> m_DamageType03;
    std::vector<float> m_DamageType04;
    std::vector<float> m_DamageType05;
    std::vector<float> m_DamageType06;
    std::vector<float> m_DamageType07;
    std::vector<float> m_DamageType08;
    std::vector<float> m_DamageType09;
    std::vector<float> m_DamageType10;
    std::vector<float> m_DamageType11;
    std::vector<float> m_DamageType12;
    std::vector<float> m_DamageType13;
    std::vector<float> m_DamageType14;
    std::vector<float> m_DamageType15;
    std::vector<float> m_DamageType16;
    std::vector<float> m_DamageType17;
    std::vector<float> m_DamageType18;
    std::vector<float> m_DamageType19;
    std::vector<float> m_DamageType20;
    std::vector<float> m_DamageType21;
    std::vector<float> m_DamageType22;
    std::vector<float> m_DamageType23;
    std::vector<float> m_HitPoints;
    std::vector<float> m_Endurance;
    std::vector<float> m_ToHit;
    std::vector<float> m_DefenseType00;
    std::vector<float> m_DefenseType01;
    std::vector<float> m_DefenseType02;
    std::vector<float> m_DefenseType03;
    std::vector<float> m_DefenseType04;
    std::vector<float> m_DefenseType05;
    std::vector<float> m_DefenseType06;
    std::vector<float> m_DefenseType07;
    std::vector<float> m_DefenseType08;
    std::vector<float> m_DefenseType09;
    std::vector<float> m_DefenseType10;
    std::vector<float> m_DefenseType11;
    std::vector<float> m_DefenseType12;
    std::vector<float> m_DefenseType13;
    std::vector<float> m_DefenseType14;
    std::vector<float> m_DefenseType15;
    std::vector<float> m_DefenseType16;
    std::vector<float> m_DefenseType17;
    std::vector<float> m_DefenseType18;
    std::vector<float> m_DefenseType19;
    std::vector<float> m_DefenseType20;
    std::vector<float> m_DefenseType21;
    std::vector<float> m_DefenseType22;
    std::vector<float> m_DefenseType23;
    std::vector<float> m_Defense;
    std::vector<float> m_Evade;
    std::vector<float> m_SpeedRunning;
    std::vector<float> m_SpeedFlying;
    std::vector<float> m_SpeedSwimming;
    std::vector<float> m_SpeedJumping;
    std::vector<float> m_JumpHeight;
    std::vector<float> m_MovementControl;
    std::vector<float> m_MovementFriction;
    std::vector<float> m_Stealth;
    std::vector<float> m_StealthRadius;
    std::vector<float> m_PerceptionRadius;
    std::vector<float> m_Regeneration;
    std::vector<float> m_Recovery;
    std::vector<float> m_ThreatLevel;
    std::vector<float> m_Taunt;
    std::vector<float> m_Confused;
    std::vector<float> m_Afraid;
    std::vector<float> m_Held;
    std::vector<float> m_Immobilized;
    std::vector<float> m_Stunned;
    std::vector<float> m_Sleep;
    std::vector<float> m_Fly;
    std::vector<float> m_Jumppack;
    std::vector<float> m_Teleport;
    std::vector<float> m_Untouchable;
    std::vector<float> m_Intangible;
    std::vector<float> m_OnlyAffectsSelf;
    std::vector<float> m_Knockup;
    std::vector<float> m_Knockback;
    std::vector<float> m_Repel;
    std::vector<float> m_Accuracy;
    std::vector<float> m_Radius;
    std::vector<float> m_Arc;
    std::vector<float> m_Range;
    std::vector<float> m_TimeToActivate;
    std::vector<float> m_RechargeTime;
    std::vector<float> m_InterruptTime;
    std::vector<float> m_EnduranceDiscount;
};
