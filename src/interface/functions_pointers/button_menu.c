/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** button_menu.c
*/

#include "../../../include/rpg.h"

SCREENS_INT

void how_play(rpg_t *rpg)
{
    sfSprite_setColor(rpg->spritesheet[SP_BACKGROUND_HOW_PLAY].sprite,
    (sfColor){255, 255, 255, 140});
    toggle_spritesheet_scene(rpg, false, SC_MENU);
    toggle_spritesheet_scene(rpg, true, SC_HOW_PLAY);
}

void set_player(rpg_t *rpg)
{
    sfSprite_setScale(rpg->spritesheet[rpg->player_stats.skin].sprite,
    (sfVector2f){0.7, 0.7});
}

void launch_game(rpg_t *rpg)
{
    rpg->spritesheet[rpg->player_stats.skin].pos =
    (sfVector2f){SPAWN_X, SPAWN_Y};
    rpg->begin.view.center = (sfVector2f){SPAWN_X, SPAWN_Y};
    set_player(rpg);
    toggle_spritesheet_scene(rpg, false, SC_MENU);
    toggle_spritesheet_scene(rpg, false, SC_CUSTOM_SKINS);
    toggle_spritesheet_scene(rpg, true, SC_MAIN_MAP);
}

void quit_game(rpg_t *rpg)
{
    sfRenderWindow_close(rpg->begin.window);
}

void display_custom_skins(rpg_t *rpg)
{
    sfSprite_setColor(rpg->spritesheet[SP_BACKGROUND_SC_MENU].sprite,
    (sfColor){255, 255, 255, 180});
    toggle_spritesheet_scene(rpg, false, SC_MENU);
    toggle_spritesheet_scene(rpg, true, SC_CUSTOM_SKINS);
}

void buttun_resume_game(rpg_t *rpg)
{
    printf("RESUME %d\n", rpg->index_old_s);
    toggle_spritesheet_scene(rpg, false, SC_PAUSE);
}

void buttun_option_game(rpg_t *rpg)
{
    printf("OPTION %d\n", rpg->index_old_s);
    disable_all_screens_gameplay(rpg);
    toggle_spritesheet_scene(rpg, true, SC_OPTION);
    sfView_setCenter(rpg->begin.view.view, rpg->screen[SC_OPTION].view_pos);
}

void buttun_leave_game(rpg_t *rpg)
{
    printf("LEAVE %d\n", rpg->index_old_s);
    disable_all_screens_gameplay(rpg);
    toggle_spritesheet_scene(rpg, false, SC_PAUSE);
    toggle_spritesheet_scene(rpg, true, SC_MENU);
}
