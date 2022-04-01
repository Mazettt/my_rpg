/*
** EPITECH PROJECT, 2021
** myrpg
** File description:
** animate_player.c
*/

#include "../../include/rpg.h"

void animate_player(rpg_t *rpg)
{
    sfColor color = get_color_from_player(rpg->imgs_colors.main_map,
    rpg->spritesheet[SP_PLAYER].pos);
    float time_player =
    sfClock_getElapsedTime(rpg->spritesheet[SP_PLAYER].clock).microseconds;

    if (!rpg->all_events.down && !rpg->all_events.up && !rpg->all_events.left
    && !rpg->all_events.right)
        rpg->spritesheet[SP_PLAYER].rect.left = 0;
    else if (time_player >= 200000) {
        rpg->spritesheet[SP_PLAYER].rect.left += 48;
        if (rpg->all_events.down)
            rpg->spritesheet[SP_PLAYER].rect.top = 0;
        if (rpg->all_events.up)
            rpg->spritesheet[SP_PLAYER].rect.top = 64 * 3;
        if (rpg->all_events.left)
            rpg->spritesheet[SP_PLAYER].rect.top = 64 * 1;
        if (rpg->all_events.right)
            rpg->spritesheet[SP_PLAYER].rect.top = 64 * 2;
        if (rpg->spritesheet[SP_PLAYER].rect.left >= 192)
            rpg->spritesheet[SP_PLAYER].rect.left = 0;
        sfClock_restart(rpg->spritesheet[SP_PLAYER].clock);
    }

    if (!rpg->screen[SC_MAIN_MAP].active)
        return;
    if (color.g == 255 && rpg->spritesheet[SP_PLAYER].rect.top < 256)
        rpg->spritesheet[SP_PLAYER].rect.top += 256;
    else if (color.g != 255 && rpg->spritesheet[SP_PLAYER].rect.top >= 256)
        rpg->spritesheet[SP_PLAYER].rect.top -= 256;
}