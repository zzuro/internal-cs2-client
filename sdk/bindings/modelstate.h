#pragma once
#include <intsafe.h>
#include "../../src/math/types/vector.h"
#include "../../src/math/types/quaternion.h"
#include <vector>
#include <list>

enum BONEINDEX : DWORD
{
    HEAD = 6,
    NECK = 5,
    UPPER_SPINE = 4,
    LOWER_SPINE = 2,
    PELVIS = 0,
    LEFT_UPPER_ARM = 8,
    LEFT_LOWER_ARM = 9,
    RIGHT_UPPER_ARM = 13,
    RIGHT_LOWER_ARM = 14,
    LEFT_HAND = 10,
    RIGHT_HAND = 15,
    LEFT_ANKLE = 24,
    RIGHT_ANKLE = 27,
    LEFT_UPPER_LEG = 22,
    LEFT_LOWER_LEG = 23,
    RIGHT_UPPER_LEG = 25,
    RIGHT_LOWER_LEG = 26,
};

namespace BoneJointList
{

    inline std::list<DWORD> Trunk = {HEAD, NECK, LOWER_SPINE, PELVIS};

    inline std::list<DWORD> LeftArm = {NECK, LEFT_UPPER_ARM, LEFT_LOWER_ARM, LEFT_HAND};

    inline std::list<DWORD> RightArm = {NECK, RIGHT_UPPER_ARM, RIGHT_LOWER_ARM, RIGHT_HAND};

    inline std::list<DWORD> LeftLeg = {PELVIS, LEFT_UPPER_LEG, LEFT_LOWER_LEG, LEFT_ANKLE};

    inline std::list<DWORD> RightLeg = {PELVIS, RIGHT_UPPER_LEG, RIGHT_LOWER_LEG, RIGHT_ANKLE};

    inline std::vector<std::list<DWORD>> List = {Trunk, LeftArm, RightArm, LeftLeg, RightLeg};
}

struct CBoneData
{
    Vector Location;
    float Scale;
    Quaternion Rotation;
};

class CModelState
{
public:
    unsigned char pad[0x80]; // 0x0 - 0xA0
    CBoneData *m_boneArray;
};
