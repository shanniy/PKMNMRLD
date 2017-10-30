
// Includes
#include "global.h"
#include "main.h"
#include "region_map.h"
#include "menu.h"
#include "palette.h"
#include "bg.h"

// Static type declarations

struct UnkStruct_0203A148 {
    u8 filler_000[0xa74];
};

enum
{
    INPUT_EVENT_NONE,
    INPUT_EVENT_DPAD,
    INPUT_EVENT_2,
    INPUT_EVENT_3,
    INPUT_EVENT_A_BUTTON,
    INPUT_EVENT_B_BUTTON,
};


// Static RAM declarations

EWRAM_DATA struct RegionMap *gUnknown_0203A144 = NULL;
EWRAM_DATA struct UnkStruct_0203A148 *gUnknown_0203A148 = NULL;

// Static ROM declarations

u8 sub_81230C4(void);
u8 sub_8123254(void);
void sub_81236C4(s32 a0, s32 a1, s32 a2, s32 a3, u16 a4, u16 a5, u16 a6);
void sub_81237B4(void);
void sub_81238AC(void);
u8 get_flagnr_blue_points(u16 mapSecId);
u16 sub_8123EB4(u16 mapSecId);
void sub_8123FB0(void);
u8 _swiopen(void);

// .rodata

extern const u8 gUnknown_0859F77C[];
extern const u8 gUnknown_085A04E0[];
extern const u16 gUnknown_0859F73C[];
extern const u8 gUnknown_0859F60C[];
extern const u8 gUnknown_0859F650[];

// .text

void sub_8122CDC(struct RegionMap *regionMap, u8 argument)
{
    sub_8122CF8(regionMap, NULL, argument);
    while (sub_8122DB0());
}

void sub_8122CF8(struct RegionMap *regionMap, struct UnkStruct_8122CF8 *arg1, u8 arg2)
{
    gUnknown_0203A144 = regionMap;
    gUnknown_0203A144->unk_079 = 0;
    gUnknown_0203A144->unk_078 = arg2;
    gUnknown_0203A144->inputCallback = arg2 == TRUE ? sub_8123254 : sub_81230C4;
    if (arg1 != NULL)
    {
        gUnknown_0203A144->unk_080 = arg1->unk_0_0;
        gUnknown_0203A144->unk_081 = arg1->unk_0_2;
        gUnknown_0203A144->unk_082 = arg1->unk_0_4;
        gUnknown_0203A144->unk_083 = TRUE;
    }
    else
    {
        gUnknown_0203A144->unk_080 = 2;
        gUnknown_0203A144->unk_081 = 2;
        gUnknown_0203A144->unk_082 = 28;
        gUnknown_0203A144->unk_083 = FALSE;
    }
}

void sub_8122D88(struct RegionMap *regionMap)
{
    gUnknown_0203A144 = regionMap;
    sub_81238AC();
    gUnknown_0203A144->unk_074 = gUnknown_0203A144->unk_054;
    gUnknown_0203A144->unk_076 = gUnknown_0203A144->unk_056;
}

bool8 sub_8122DB0(void)
{
    switch (gUnknown_0203A144->unk_079)
    {
        case 0:
            if (gUnknown_0203A144->unk_083)
            {
                decompress_and_copy_tile_data_to_vram(gUnknown_0203A144->unk_080, gUnknown_0859F77C, 0, 0, 0);
            }
            else
            {
                LZ77UnCompVram(gUnknown_0859F77C, (u16 *)BG_SCREEN_ADDR(16));
            }
            break;
        case 1:
            if (gUnknown_0203A144->unk_083)
            {
                if (!free_temp_tile_data_buffers_if_possible())
                {
                    decompress_and_copy_tile_data_to_vram(gUnknown_0203A144->unk_080, gUnknown_085A04E0, 0, 0, 1);
                }
            }
            else
            {
                LZ77UnCompVram(gUnknown_085A04E0, (u16 *)BG_SCREEN_ADDR(28));
            }
            break;
        case 2:
            if (!free_temp_tile_data_buffers_if_possible())
            {
                LoadPalette(gUnknown_0859F73C, 0x70, 0x60);
            }
            break;
        case 3:
            LZ77UnCompWram(gUnknown_0859F60C, gUnknown_0203A144->unk_184);
            break;
        case 4:
            LZ77UnCompWram(gUnknown_0859F650, gUnknown_0203A144->unk_284);
            break;
        case 5:
            sub_81238AC();
            gUnknown_0203A144->unk_074 = gUnknown_0203A144->unk_054;
            gUnknown_0203A144->unk_076 = gUnknown_0203A144->unk_056;
            gUnknown_0203A144->mapSecId = sub_8123EB4(gUnknown_0203A144->mapSecId);
            gUnknown_0203A144->unk_002 = get_flagnr_blue_points(gUnknown_0203A144->mapSecId);
            GetMapName(gUnknown_0203A144->mapSecName, gUnknown_0203A144->mapSecId, 16);
            break;
        case 6:
            if (gUnknown_0203A144->unk_078 == 0)
            {
                sub_81236C4(0, 0, 0, 0, 0x100, 0x100, 0);
            }
            else
            {
                gUnknown_0203A144->unk_05c = gUnknown_0203A144->unk_054 * 8 - 0x34;
                gUnknown_0203A144->unk_05e = gUnknown_0203A144->unk_056 * 8 - 0x44;
                gUnknown_0203A144->unk_064 = gUnknown_0203A144->unk_054;
                gUnknown_0203A144->unk_066 = gUnknown_0203A144->unk_056;
                sub_81236C4(gUnknown_0203A144->unk_05c, gUnknown_0203A144->unk_05e, 0x38, 0x48, 0x80, 0x80, 0);
            }
            break;
        case 7:
            sub_8123FB0();
            sub_81237B4();
            gUnknown_0203A144->unk_01c = NULL;
            gUnknown_0203A144->unk_020 = NULL;
            gUnknown_0203A144->unk_07a = 0;
            gUnknown_0203A144->unk_07e = 0;
            if (gUnknown_0203A144->unk_083)
            {
                SetBgAttribute(gUnknown_0203A144->unk_080, BG_CTRL_ATTR_MAPBASEINDEX, 2);
                SetBgAttribute(gUnknown_0203A144->unk_080, BG_CTRL_ATTR_VISIBLE, gUnknown_0203A144->unk_081);
                SetBgAttribute(gUnknown_0203A144->unk_080, BG_CTRL_ATTR_CHARBASEINDEX, gUnknown_0203A144->unk_082);
                SetBgAttribute(gUnknown_0203A144->unk_080, BG_CTRL_ATTR_PRIORITY, 1);
                SetBgAttribute(gUnknown_0203A144->unk_080, BG_CTRL_ATTR_SCREENSIZE, 1);
            }
            gUnknown_0203A144->unk_079 ++;
            return FALSE;
        default:
            return FALSE;
    }
    gUnknown_0203A144->unk_079 ++;
    return TRUE;
}

void sub_8123030(u16 a0, u32 a1)
{
    BlendPalettes(0x380, a1, a0);
    CpuCopy16(gPlttBufferFaded + 0x70, gPlttBufferUnfaded + 0x70, 0x60);
}

void sub_812305C(void)
{
    if (gUnknown_0203A144->unk_01c != NULL)
    {
        DestroySprite(gUnknown_0203A144->unk_01c);
        FreeSpriteTilesByTag(gUnknown_0203A144->unk_058);
        FreeSpritePaletteByTag(gUnknown_0203A144->unk_05a);
    }
    if (gUnknown_0203A144->unk_020 != NULL)
    {
        DestroySprite(gUnknown_0203A144->unk_020);
        FreeSpriteTilesByTag(gUnknown_0203A144->unk_070);
        FreeSpritePaletteByTag(gUnknown_0203A144->unk_072);
    }
}

u8 sub_81230AC(void)
{
    return gUnknown_0203A144->inputCallback();
}

u8 sub_81230C4(void)
{
    u8 input;

    input = INPUT_EVENT_NONE;
    gUnknown_0203A144->unk_07b = 0;
    gUnknown_0203A144->unk_07c = 0;
    if (gMain.heldKeys & DPAD_UP && gUnknown_0203A144->unk_056 > 2)
    {
        gUnknown_0203A144->unk_07c = -1;
        input = INPUT_EVENT_DPAD;
    }
    if (gMain.heldKeys & DPAD_DOWN && gUnknown_0203A144->unk_056 < 16)
    {
        gUnknown_0203A144->unk_07c = +1;
        input = INPUT_EVENT_DPAD;
    }
    if (gMain.heldKeys & DPAD_LEFT && gUnknown_0203A144->unk_054 > 1)
    {
        gUnknown_0203A144->unk_07b = -1;
        input = INPUT_EVENT_DPAD;
    }
    if (gMain.heldKeys & DPAD_RIGHT && gUnknown_0203A144->unk_054 < 28)
    {
        gUnknown_0203A144->unk_07b = +1;
        input = INPUT_EVENT_DPAD;
    }
    if (gMain.newKeys & A_BUTTON)
    {
        input = INPUT_EVENT_A_BUTTON;
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        input = INPUT_EVENT_B_BUTTON;
    }
    if (input == INPUT_EVENT_DPAD)
    {
        gUnknown_0203A144->unk_07a = 4;
        gUnknown_0203A144->inputCallback = _swiopen;
    }
    return input;
}
