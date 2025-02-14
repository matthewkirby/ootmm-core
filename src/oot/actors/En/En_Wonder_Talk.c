#include <combo.h>

static const char kIcons[] = {
    0x6c,
    0x6d,
    0x6e,
    0x6b,
    0x66,
    0x67,
    0x68,
    0x69,
    0x6a,
};

static void hintSingleDungeon(char** b, int index)
{
    comboTextAppendStr(b, TEXT_FAST TEXT_ICON);
    **b = kIcons[index];
    ++(*b);
    comboTextAppendRegionName(b, gComboData.hints.dungeonRewards[index], TF_PREPOS | TF_CAPITALIZE);
    comboTextAppendStr(b, "...");
}

static void hintDungeons(GameState_Play* play)
{
    char* b;
    char* start;
    int base;
    int count;
    int isChild;

    b = play->msgCtx.textBuffer;
    isChild = gSave.age == AGE_CHILD;
    base = isChild ? 0 : 3;
    count = isChild ? 3 : 6;

    comboTextAppendHeader(&b);
    for (int i = 0; i < count; ++i)
    {
        hintSingleDungeon(&b, base + i);

        if ((i == (count - 1)) && !isChild)
        {
            comboTextAppendStr(&b, TEXT_SIGNAL TEXT_END);
        }
        else
        {
            comboTextAppendStr(&b, TEXT_BB);
        }
    }

    if (isChild)
    {
        start = b;
        comboTextAppendStr(&b, TEXT_ICON "\x08" TEXT_FAST "It is also written that reuniting the " TEXT_COLOR_YELLOW "Spiritual Stones ");
        comboTextAppendClearColor(&b);
        comboTextAppendStr(&b, "leads to ");
        comboTextAppendNpcReward(&b, NPC_OOT_OCARINA_TIME_ITEM, GI_OOT_OCARINA_TIME);
        comboTextAppendStr(&b, " and ");
        comboTextAppendNpcReward(&b, NPC_OOT_OCARINA_TIME_SONG, GI_OOT_SONG_TIME);
        comboTextAppendStr(&b, "." TEXT_SIGNAL TEXT_END);
        comboTextAutoLineBreaks(start);
    }
}

int EnWonderTalk_TalkedTo(Actor* this, GameState_Play* play)
{
    if (ActorTalkedTo(this))
    {
        if ((this->variable & 0xf800) == 0x0800)
        {
            hintDungeons(play);
        }
        return 1;
    }
    return 0;
}

PATCH_CALL(0x80aab0ec, EnWonderTalk_TalkedTo);
