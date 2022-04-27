/*
** EPITECH PROJECT, 2021
** myrpg
** File description:
** myrpg.c
*/

#include "../include/rpg.h"

int get_fps(rpg_t *rpg)
{
    rpg->begin.fps_disp.time = sfClock_getElapsedTime(rpg->begin.fps_disp.clock).microseconds;
    rpg->begin.fps_disp.fps = 1 / (rpg->begin.fps_disp.time / 1000000);
    sfClock_restart(rpg->begin.fps_disp.clock);
    return (rpg->begin.fps_disp.fps);
}

static void move_sound_box(rpg_t *rpg)
{
    int pos_x = rpg->all_events.mouse.pos.x;

    if (!rpg->sound.volume_active)
        return;
    if (pos_x >= 200 && pos_x <= 708) {
        rpg->spritesheet[SP_SOUND_SLIDER].pos.x = pos_x;
        rpg->sound.volume = (pos_x - 200) / 5.05;
    }
    rpg->sound.volume < 0 ? rpg->sound.volume = 0 : 0;
}

static void big_loop(rpg_t *rpg, sfColor *oui)
{
    *oui = my_rgb(*oui);
    get_fps(rpg);
    my_events(rpg);
    if ((rpg->all_events.q || rpg->all_events.c) && rpg->all_events.ctrl)
        sfRenderWindow_close(rpg->begin.window);
    // for (int i = 0; i < NBR_SP; ++i)
    //     sfSprite_setColor(rpg->spritesheet[i].sprite, *oui);
    if (rpg->all_events.page_down) {
        set_zoom(rpg->begin.view.view, get_zoom(rpg->begin.view.view) + 0.1);
        rpg->all_events.page_down = false;
    }
    if (rpg->all_events.page_up) {
        set_zoom(rpg->begin.view.view, get_zoom(rpg->begin.view.view) - 0.1);
        rpg->all_events.page_up = false;
    }
    move_sound_box(rpg);
    move_all_fps_independant(rpg);
    execute_all(rpg);
    check_click_buttons(rpg);
    check_mouse_on_all_buttons(rpg);
    draw_all(rpg);
}

void myrpg(void)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));
    sfColor oui = {255, 0, 0, 255};
    sfImage *img = sfImage_createFromFile("assets/img/logo.png");
    const sfUint8 *pixels = sfImage_getPixelsPtr(img);

    init_all(rpg);
    if (!rpg->begin.window || !rpg->begin.framebuffer)
        return;
    sfWindow_setFramerateLimit((sfWindow *)rpg->begin.window, 0);
    sfWindow_setIcon((sfWindow *)rpg->begin.window, 512, 512, pixels);
    rpg->begin.fps.clock = sfClock_create();
    play_sound(rpg->sound.sound_list[SOUND_MENU].sound, rpg->sound.volume);
    toggle_cursor(rpg->begin.window, false);
    while (sfRenderWindow_isOpen(rpg->begin.window)) {
        clean_window(&rpg->begin, sfBlack);
        big_loop(rpg, &oui);
    }
    destroy_all(rpg);
}
