/*
** EPITECH PROJECT, 2021
** myrpg
** File description:
** myrpg.c
*/

#include "../include/rpg.h"

void draw_spritesheets(beginning_t *begin, spritesheet_t *spritesheet)
{
    for (int i = 0; i < NBR_SPRITE; ++i)
        if (spritesheet[i].active)
            draw_one_sprite(begin, spritesheet[i].sprite, spritesheet[i].rect,
            spritesheet[i].pos);
}

void draw_all(rpg_t *rpg)
{
    sfSprite_setTexture(rpg->begin.sprite, rpg->begin.texture, sfFalse);
    sfTexture_updateFromPixels(rpg->begin.texture,
    rpg->begin.framebuffer, WIDTH, HEIGHT, 0, 0);
    sfRenderWindow_drawSprite(rpg->begin.window,
    rpg->begin.sprite, NULL);
    draw_spritesheets(&rpg->begin, rpg->spritesheet);
    sfRenderWindow_display(rpg->begin.window);
}

void big_loop(rpg_t *rpg)
{
    my_events(&rpg->begin, &rpg->all_events);
    move_all_fps_independant(rpg);
    if (rpg->screen[MENU].active) {
        set_view(rpg, rpg->screen[MENU].view_pos);
        manage_menu(rpg);
    }
    check_click_buttons(rpg);
    draw_all(rpg);
}

void myrpg(void)
{
    rpg_t rpg;

    init_all(&rpg);
    if (!rpg.begin.window || !rpg.begin.framebuffer)
        return;
    sfWindow_setFramerateLimit((sfWindow *)rpg.begin.window, 120);
    rpg.begin.fps.clock = sfClock_create();
    while (sfRenderWindow_isOpen(rpg.begin.window)) {
        clean_window(&rpg.begin, sfBlack);
        big_loop(&rpg);
    }
    destroy_all(&rpg.begin);
}
