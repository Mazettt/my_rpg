/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** button_menu.c
*/

#include "../../include/rpg.h"
extern int screen_menu[];
extern int screen_game[];

void launch_game(rpg_t *rpg)
{
    rpg->screen[MENU].active = false;
    rpg->screen[GAME].active = true;
    active_spritesheet_scene(false, screen_menu, rpg->spritesheet);
    active_spritesheet_scene(true, screen_game, rpg->spritesheet);
}
