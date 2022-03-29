/*
** EPITECH PROJECT, 2021
** B-MUL-200-MLH-2-1-myrpg-martin.d-herouville
** File description:
** init_main_map.c
*/

#include "../../include/rpg.h"

void init_player(spritesheet_t *spritesheet, beginning_t *begin)
{
    set_one_sprite("assets/img/player.png", &spritesheet[S_PLAYER],
    begin, (init_sprite_t){{WIDTH / 1.715, HEIGHT / 1.7}, {0.9, 0.9},
    {0, 0, 48, 62}, false, true});
}

void init_spritesheets(spritesheet_t *spritesheet, beginning_t *begin)
{
    init_background_main_map(spritesheet, begin);
    init_player(spritesheet, begin);
}
