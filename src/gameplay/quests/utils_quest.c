/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** utils_quest.c
*/

#include "../../../include/rpg.h"

static int draw_bubulle_npc(rpg_t *rpg, sfSprite *sprite,
sfIntRect rect, sfVector2f pos)
{
    if (rpg->screen[SC_INVENTORY].active)
        return (0);
    draw_one_sprite(&rpg->begin, sprite, rect, pos);
    return (1);
}

void send_chat_bubble(rpg_t *rpg, char *filepath, int quest_id)
{
    int put_txt = 0;
    sfVector2f pos_player = rpg->spritesheet[rpg->player_stats.skin].pos;
    sfVector2f pos_dialog = sfText_getPosition(rpg->quest[quest_id].dialog);

    if (rpg->quest[quest_id].active != 1)
        return;
    pos_player.y -= 50;
    pos_player.x -= 20;
    if (rpg->quest[quest_id].speaker == 0) {
        put_txt = draw_bubulle_npc(rpg, rpg->quest[quest_id].bubulle.sprite,
        rpg->quest[quest_id].bubulle.rect, rpg->quest[quest_id].bubulle.pos);
        if (put_txt)
            write_text(rpg->begin.window, rpg->quest[quest_id].dialog);
    } else if (rpg->quest[quest_id].speaker == 1) {
        put_txt = draw_bubulle_npc(rpg, rpg->spritesheet[SP_BUBBLE_CHAT].sprite,
        rpg->spritesheet[SP_BUBBLE_CHAT].rect, pos_player);
        pos_player.y -= 20;
        pos_player.x -= 25;
        sfText_setPosition(rpg->quest[quest_id].dialog, pos_player);
        if (put_txt)
            write_text(rpg->begin.window, rpg->quest[quest_id].dialog);
        sfText_setPosition(rpg->quest[quest_id].dialog, pos_dialog);
    }
    if (rpg->all_events.enter) {
        rpg->all_events.enter = false;
        if (get_chat_into_file(filepath, quest_id, rpg) == 0)
            rpg->quest[quest_id].active = -1;
    }
}

void quest_launch(rpg_t *rpg, int i_quest, char *filepath)
{
    if (rpg->quest[i_quest].active != 0) {
        if (rpg->quest[i_quest].active <= 1
        || check_if_in_inventory(rpg, rpg->quest[i_quest].active) == -1)
            return;
        else
            remove_item_inventory(rpg, rpg->quest[i_quest].active);
    }
    rpg->quest[i_quest].active = 1;
    get_chat_into_file(filepath, i_quest, rpg);
}

int check_status_dialog(quest_t *quest)
{
    for (int i = 0; i < NBR_QUEST; ++i)
        if (quest[i].active == 1)
            return (1);
    return (0);
}
