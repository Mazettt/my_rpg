/*
** EPITECH PROJECT, 2021
** myworld
** File description:
** init_all.c
*/

#include "../include/rpg.h"

events_t init_all_events(void)
{
    return ((events_t){.left = false, .right = false, .up = false,
    .down = false, .page_up = false, .page_down = false, .z = false, .s = false,
    .q = false, .d = false, .escape = false,
    .space = false, .ctrl = false, .tab = false, .enter = false, .mouse =
    {.left = false, .left_released = false, .right = false, .move_x = 0,
    .move_y = 0, .pos = {0, 0}}, .mouse_wheel = {.up = false, .down = false,
    .click = false}});
}

void init_all(rpg_t *rpg)
{
    rpg->begin.fps.timer = 0;
    rpg->begin.fps.clock = sfClock_create();
    rpg->all_events = init_all_events();
    rpg->spritesheet = malloc(sizeof(spritesheet_t) * NBR_SPRITE);
    rpg->begin.view.view = sfView_createFromRect((sfFloatRect)
    {0, 0, 1920, 1080});
    rpg->begin.view.center = (sfVector2f){1090, 613};
    sfView_zoom(rpg->begin.view.view , 0.4);
    init_csfml(&rpg->begin);
    init_spritesheets(rpg->spritesheet, &rpg->begin);
}
