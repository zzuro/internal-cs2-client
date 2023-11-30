#pragma once
#include "../../src/math/types/vector.h"
#include <limits>

enum ECommandButtons : int
{
	IN_ATTACK = (1 << 0),
	IN_JUMP = (1 << 1),
	IN_DUCK = (1 << 2),
	IN_FORWARD = (1 << 3),
	IN_BACK = (1 << 4),
	IN_USE = (1 << 5),
	IN_CANCEL = (1 << 6),
	IN_LEFT = (1 << 7),
	IN_RIGHT = (1 << 8),
	IN_MOVELEFT = (1 << 9),
	IN_MOVERIGHT = (1 << 10),
	IN_SECOND_ATTACK = (1 << 11),
	IN_RUN = (1 << 12),
	IN_RELOAD = (1 << 13),
	IN_LEFT_ALT = (1 << 14),
	IN_RIGHT_ALT = (1 << 15),
	IN_SCORE = (1 << 16),
	IN_SPEED = (1 << 17),
	IN_WALK = (1 << 18),
	IN_ZOOM = (1 << 19),
	IN_FIRST_WEAPON = (1 << 20),
	IN_SECOND_WEAPON = (1 << 21),
	IN_BULLRUSH = (1 << 22),
	IN_FIRST_GRENADE = (1 << 23),
	IN_SECOND_GRENADE = (1 << 24),
	IN_MIDDLE_ATTACK = (1 << 25),
	IN_USE_OR_RELOAD = (1 << 26)
};

struct BasePB {
    void *vftable;
    uint32_t has_bits;
    uint64_t cached_size;
};



template< typename T >
struct RepeatedPtrField {
    struct Rep {
        int allocated_size;
        T *elements[ ( (std::numeric_limits<int>::max)() - 2 * sizeof( int ) ) /
                     sizeof( void * ) ];
    };
 
    void *arena;
    int current_size;
    int total_size;
    Rep *rep;
};
 
struct CMsgVector : BasePB {
    float x;
    float y;
    float z;
};
 
struct CMsgQAngle : BasePB {
    float x;
    float y;
    float z;
};
 
struct CInButtonStatePB : BasePB {
    uint64_t buttonstate1;
    uint64_t buttonstate2;
    uint64_t buttonstate3;
};
 
struct CSubtickMoveStep : BasePB {
    uint64_t button;
    bool pressed;
    float when;
};
 
struct CBaseUserCmdPB : BasePB {
    RepeatedPtrField< CSubtickMoveStep > subtick_moves;
    void *move_crc;// this is a string ptr, should prob of made it that but I DON'T CARE
    CInButtonStatePB *buttons_pb;
    CMsgQAngle *viewangles;
    int32_t command_number;
    int32_t tick_count;
    float forwardmove;
    float leftmove;
    float upmove;
    int32_t impulse;
    int32_t weaponselect;
    int32_t random_seed;
    int32_t mousedx;
    int32_t mousedy;
    bool hasbeenpredicted;
    uint32_t consumed_server_angle_changes;
    int32_t cmd_flags;
    uint32_t pawn_entity_handle;
};
 
struct CSGOInterpolationInfoPB : BasePB {
    float frac;
    int32_t src_tick;
    int32_t dst_tick;
};
 
struct CSGOInputHistoryEntryPB : BasePB {
    CMsgQAngle *view_angles;
    CMsgVector *shoot_position;
    CMsgVector *target_head_pos_check;
    CMsgVector *target_abs_pos_check;
    CMsgQAngle *target_abs_ang_check;
    CSGOInterpolationInfoPB *cl_interp;
    CSGOInterpolationInfoPB *sv_interp0;
    CSGOInterpolationInfoPB *sv_interp1;
    CSGOInterpolationInfoPB *player_interp;
    int32_t render_tick_count;
    float render_tick_fraction;
    int32_t player_tick_count;
    float player_tick_fraction;
    int32_t frame_number;
    int32_t target_ent_index;
};
 
struct CSGOUserCmdPB {
    uint32_t has_bits;
    uint64_t cached_size;
    RepeatedPtrField< CSGOInputHistoryEntryPB > input_history;
    CBaseUserCmdPB *base;
    int weapon_decision;
    int32_t weapon_decision_weapon;
    int32_t attack3_start_history_index;
    int32_t attack1_start_history_index;
    int32_t attack2_start_history_index;
};
 
// not protobufs
struct CInButtonState {
    void *vftable;
    uint64_t buttonstate1;
    uint64_t buttonstate2;
    uint64_t buttonstate3;
};
 
struct CUserCmd {
    void *vftable;
    CSGOUserCmdPB cmd;
    CInButtonState button_states;
    char pad[48];
};