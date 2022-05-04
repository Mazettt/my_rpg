/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** button_house.c
*/

#include "../../../include/rpg.h"

void open_big_maps(rpg_t *rpg)
{
    if (!rpg->spritesheet[SP_MINIMAP].active)
        rpg->spritesheet[SP_MINIMAP].active = true;
    else
        rpg->spritesheet[SP_MINIMAP].active = false;
}

void make_night(rpg_t *rpg)
{
    sfColor c = {255, 255, 255, 255};

    while (get_clock_time(rpg->spritesheet[SP_BED_SLEEP].c_anim)
    <= SECOND_TO_MICRO(5)) {
        if (get_clock_time(rpg->spritesheet[SP_BED_SLEEP].c_attack) >= SECOND_TO_MICRO(0.02)) {
            --c.a;
            for (int i = 0; i < NBR_SP; ++i)
                sfSprite_setColor(rpg->spritesheet[i].sprite, c);
            sfClock_restart(rpg->spritesheet[SP_BED_SLEEP].c_attack);
        }
        clean_window(&rpg->begin, sfBlack);
        draw_all(rpg);
    }
    for (int i = 0; i < NBR_SP; ++i)
        sfSprite_setColor(rpg->spritesheet[i].sprite, (sfColor){255, 255, 255, 255});
}

void button_bed_saving(rpg_t *rpg)
{
    if (!rpg->spritesheet[SP_BED_SLEEP].rect.left) {
        rpg->spritesheet[SP_BED_SLEEP].rect.left +=
        rpg->spritesheet[SP_BED_SLEEP].rect.width;
        rpg->spritesheet[rpg->player_stats.skin].active = false;
        rpg->spritesheet[SP_BED_SLEEP].c_anim = sfClock_create();
        draw_all(rpg);
        make_night(rpg);
        save_file("save", rpg);
        send_notif(rpg, "Game saved!");
    } else {
        rpg->spritesheet[SP_BED_SLEEP].rect.left -=
        rpg->spritesheet[SP_BED_SLEEP].rect.width;
        rpg->spritesheet[rpg->player_stats.skin].active = true;
    }
}
