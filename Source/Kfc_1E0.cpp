#include "Kfc_1E0.hpp"
#include "Car_BC.hpp"
#include "Ped.hpp"
#include "PedGroup.hpp"
#include "Hamburger_500.hpp"

DEFINE_GLOBAL(Kfc_1E0*, gKfc_1E0_706280, 0x706280);

MATCH_FUNC(0x4beb00)
Kfc_30::Kfc_30()
{
    sub_5CBC00();
}

MATCH_FUNC(0x4beb10)
Kfc_30::~Kfc_30()
{
}

MATCH_FUNC(0x5cbc00)
void Kfc_30::sub_5CBC00()
{
    field_1A = 150;
    field_1E_is_used = 0;
    field_20_maybe_type = 0;
    field_24 = 0;
    field_0_car = 0;
    field_4_ped = 0;
    field_28 = 0;
    field_8_group = 0;
    field_2C = 0;
    field_1C = 0;
}

MATCH_FUNC(0x5cbc30)
void Kfc_30::sub_5CBC30()
{
    sub_5CBC00();
}

MATCH_FUNC(0x5cbc40)
void Kfc_30::sub_5CBC40(Ped* a2)
{
    field_8_group->RemovePed_4C9970(a2);
    field_4_ped = field_8_group->field_2C_ped_leader;
}

STUB_FUNC(0x5cbc60)
bool Kfc_30::sub_5CBC60()
{
    NOT_IMPLEMENTED;
    Ped* pPed = this->field_4_ped;
    if (pPed && pPed->field_278_ped_state_1 == ped_state_1::dead_9)
    {
        return false;
    }
    // TODO: Something strange going on here:
    // mov 0x28(%ecx),%ecx
    //this = (Kfc_30*)field_28;
    return true;
}

MATCH_FUNC(0x5cbc90)
char_type Kfc_30::sub_5CBC90()
{
    PedGroup* pGroup = this->field_8_group;
    if (!pGroup)
    {
        return 0;
    }

    u8 idx = 0;
    Ped* pPedAtIdx = pGroup->field_4_ped_list[idx];
    while (pPedAtIdx)
    {
        if (pPedAtIdx->field_278_ped_state_1 != ped_state_1::dead_9 && !pPedAtIdx->field_16C_car)
        {
            Ped* pKfcPed = this->field_4_ped;
            if (pKfcPed->field_16C_car)
            {
                sub_5CBC40(pKfcPed);
            }
            else
            {
                pGroup->PromoteMemberToLeader_4C9680(idx);
                Ped* pLeader = this->field_8_group->field_2C_ped_leader;
                this->field_4_ped = pLeader;
                pLeader->SetObjective(objectives_enum::no_obj_0, 9999);
                const s32 occupation = pPedAtIdx->field_240_occupation;
                pPedAtIdx->field_240_occupation = ped_ocupation_enum::dummy;
                pPedAtIdx->Kill_46F9D0();
                pPedAtIdx->field_240_occupation = occupation;
                pPedAtIdx->SetObjective(objectives_enum::objective_28, 9999);
            }
            return 1;
        }
        idx++;
        pPedAtIdx = pGroup->field_4_ped_list[idx];
    }
    return 0;
}

STUB_FUNC(0x5cbd50)
void Kfc_30::sub_5CBD50()
{
    NOT_IMPLEMENTED;
}

WIP_FUNC(0x5cc1c0)
void Kfc_30::sub_5CC1C0()
{
    WIP_IMPLEMENTED;

    PedGroup* pGroup = this->field_8_group;
    bool b1 = 0;
    bool b2 = 1;
    bool b3 = 1;

    if (pGroup)
    {
        if (pGroup->field_34_count == 0)
        {
            pGroup->ClearGroupData_4C8E90();
            this->field_8_group = 0;
        }
    }

    Ped* pPed;
    Ped* pPed_;
    PedGroup* pGroup_1;
    Ped* pPedListIter;
    s32 i;
    s32 i_;
    PedGroup* pGroup_2;
    Ped* pPed_1;
    Ped* pPed_2;
    Ped* pPedListIter_1;

    if (this->field_24 == 1)
    {
        Car_BC* pCar = this->field_0_car;
        if (this->field_0_car && pCar->field_88 != 5 && !pCar->IsMaxDamage_40F890())
        {
            if (pCar->field_76_last_seen_timer <= this->field_1A)
            {
            LABEL_14:
                pPed = this->field_4_ped;
                if (pPed)
                {
                    if (pPed->field_168_game_object)
                    {
                        if (pPed->field_20e < this->field_1A)
                        {
                            b2 = 0;
                        }
                    }
                    else if (pPed->field_278_ped_state_1 == ped_state_1::dead_9)
                    {
                        this->field_4_ped = 0;
                    }
                }

                pPed_ = this->field_4_ped;
                if (pPed_)
                {
                    if (pPed_->field_168_game_object)
                    {
                        b2 = 0;
                    }
                }

                pGroup_1 = this->field_8_group;
                if (pGroup_1)
                {
                    pPedListIter = pGroup_1->field_4_ped_list[0];
                    for (i = 0; pPedListIter; pPedListIter = pGroup_1->field_4_ped_list[i])
                    {
                        if (pPedListIter->field_168_game_object)
                        {
                            if (pPedListIter->field_20e < this->field_1A)
                            {
                                b2 = 0;
                            }
                        }
                        else
                        {
                            b3 = 0;
                        }
                        ++i;
                    }
                }

                if (b1)
                {
                    if (field_0_car)
                    {
                        if (field_0_car->field_60)
                        {
                            gHamburger_500_678E30->Cancel_474CC0(field_0_car->field_60); // something to do with car route
                            field_0_car->field_60 = 0;
                        }
                    }
                    field_0_car = 0;

                    if (b2)
                    {
                        pPed_1 = this->field_4_ped;
                        if (pPed_1)
                        {
                            pPed_1->set_occupation_403970(ped_ocupation_enum::dummy);
                            pPed_2 = this->field_4_ped;
                            pPed_2->ClearGroupAndGroupIdx_403A30();
                            field_4_ped->Deallocate_45EB60();
                        }
                        pGroup_2 = this->field_8_group;
                        i_ = 0;
                        if (pGroup_2)
                        {
                            for (pPedListIter_1 = pGroup_2->field_4_ped_list[0]; pPedListIter_1;
                                 pPedListIter_1 = this->field_8_group->field_4_ped_list[i_])
                            {
                                pPedListIter_1->set_occupation_403970(ped_ocupation_enum::dummy);
                                pPedListIter_1->ClearGroupAndGroupIdx_403A30();
                                pPedListIter_1->Deallocate_45EB60();
                                ++i_;
                            }
                            field_8_group->ClearGroupData_4C8E90();
                        }
                        this->field_8_group = 0;
                        this->field_2C = 1;
                    }
                    else if (b3)
                    {
                        if (this->field_4_ped->field_168_game_object)
                        {
                            this->field_24 = 0;
                        }
                    }
                }
                return;
            }
            else
            {
                pCar->sub_421470();
            }
        }
        b1 = 1;
        goto LABEL_14;
    }

    Ped* pPed_3 = this->field_4_ped;
    if (pPed_3)
    {
        if (pPed_3->field_20e < this->field_1A)
        {
            b2 = 0;
        }
    }

    PedGroup* pGroup_3 = this->field_8_group;
    if (pGroup_3)
    {
        Ped* pPedListIter_2 = pGroup_3->field_4_ped_list[0];
        for (s32 i__ = 0; pPedListIter_2; pPedListIter_2 = pGroup_3->field_4_ped_list[i__])
        {
            if (pPedListIter_2->field_20e < this->field_1A)
            {
                b2 = 0;
            }
            ++i__;
        }
    }

    if (b2)
    {
        if (pPed_3)
        {
            pPed_3->ClearGroupAndGroupIdx_403A30();
            field_4_ped->Deallocate_45EB60();
        }

        PedGroup* pGroup_4 = this->field_8_group;
        s32 i___ = 0;
        if (pGroup_4)
        {
            for (Ped* pPedListIter_3 = pGroup_4->field_4_ped_list[0]; pPedListIter_3;
                 pPedListIter_3 = this->field_8_group->field_4_ped_list[i___])
            {
                pPedListIter_3->ClearGroupAndGroupIdx_403A30();
                pPedListIter_3->Deallocate_45EB60();
                ++i___;
            }
            field_8_group->ClearGroupData_4C8E90();
        }
        this->field_2C = 1;
    }
}

MATCH_FUNC(0x5cc480)
bool Kfc_30::Service_5CC480()
{
    if (field_18 > 0)
    {
        this->field_18--;
        return 0;
    }

    if (field_18 > -80)
    {
        this->field_18--;
    }

    switch (this->field_28)
    {
        case 5:
            sub_5CC1C0();
            return 0;

        case 6:
            sub_5CBD50();
            return 0;

        case 3:
            // fall through to default below
            break;

        default:
            return 0;
    }

    switch (this->field_20_maybe_type)
    {
        case 1:
            if (gCar_6C_677930->CanAllocateOfType_446930(4))
            {
                this->field_0_car = gCar_6C_677930->SpawnCarAtRoadDirection_444CF0(car_model_enum::MEDICAR,
                                                                                   this->field_C_x,
                                                                                   this->field_10_y,
                                                                                   this->field_14_z);
            }
            else
            {
                this->field_0_car = 0;
            }

            if (this->field_0_car)
            {
                this->field_2C = 1;
                field_0_car->IncrementCarStats_443D70(4);
            }
            break;

        case 3:
            if (gCar_6C_677930->CanAllocateOfType_446930(6))
            {
                this->field_0_car = gCar_6C_677930->SpawnCarAtRoadDirection_444CF0(car_model_enum::COPCAR,
                                                                                   this->field_C_x,
                                                                                   this->field_10_y,
                                                                                   this->field_14_z);
            }
            else
            {
                this->field_0_car = 0;
            }
            if (this->field_0_car)
            {
                this->field_2C = 1;
                field_0_car->IncrementCarStats_443D70(6);
            }
            break;

        case 5:
            if (gCar_6C_677930->CanAllocateOfType_446930(6))
            {
                this->field_0_car = gCar_6C_677930->SpawnCarAtRoadDirection_444CF0(car_model_enum::SWATVAN,
                                                                                   this->field_C_x,
                                                                                   this->field_10_y,
                                                                                   this->field_14_z);
            }
            else
            {
                this->field_0_car = 0;
            }

            if (this->field_0_car)
            {
                this->field_2C = 1;
                field_0_car->IncrementCarStats_443D70(6);
            }
            break;

        default:
            this->field_0_car = 0;
            break;
    }

    return 0;
}

MATCH_FUNC(0x4beb20)
Kfc_1E0::~Kfc_1E0()
{
}

MATCH_FUNC(0x5cbb70)
void Kfc_1E0::init_5CBB70()
{
}

MATCH_FUNC(0x5cbb80)
Kfc_30* Kfc_1E0::New_5CBB80()
{
    for (u8 i = 0; i < GTA2_COUNTOF(field_0); i++)
    {
        if (!field_0[i].field_1E_is_used)
        {
            return &field_0[i];
        }
    }
    return 0;
}

MATCH_FUNC(0x5cbbd0)
void Kfc_1E0::sub_5CBBD0()
{
    for (s32 i = 0; i < 10; i++)
    {
        if (field_0[i].field_1E_is_used)
        {
            if (field_0[i].Service_5CC480())
            {
                field_0[i].field_1E_is_used = 0;
            }
        }
    }
}