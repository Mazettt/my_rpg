/*
** EPITECH PROJECT, 2021
** myrpg
** File description:
** myrpg.c
*/

#include "../include/rpg.h"

int get_current_screen(rpg_t *rpg)
{
    for (int i = 0; i < NBR_SC; ++i) {
        if (rpg->screen[i].active)
            return (i);
    }
    return (-1);
}

static void modify_zoom(rpg_t *rpg)
{
    if (rpg->all_events.page_down) {
        set_zoom(rpg->begin.view.view, get_zoom(rpg->begin.view.view) + 0.1);
        rpg->all_events.page_down = false;
    }
    if (rpg->all_events.page_up) {
        set_zoom(rpg->begin.view.view, get_zoom(rpg->begin.view.view) - 0.1);
        rpg->all_events.page_up = false;
    }
}

static void big_loop(rpg_t *rpg, sfColor *drunk)
{
    set_view(rpg, rpg->begin.view.center);
    *drunk = my_rgb(*drunk);
    modify_zoom(rpg);
    if (rpg->all_events.tab)
        send_notif(rpg, "ouiiiiiiiiiiii");
    make_drunk(rpg, *drunk);
    draw_notif(rpg);
    move_sound_box(rpg);
    move_all_fps_independant(rpg);
    execute_all(rpg);
    check_click_buttons(rpg);
    check_mouse_on_all_buttons(rpg);
    draw_all(rpg);
}

int open_or_not_file(rpg_t *rpg, char *file_backup)
{
    if (file_backup == NULL)
        toggle_spritesheet_scene(rpg, true, SC_MENU);
    else {
        if (open_file(file_backup, rpg) == 1) {
            write(2, "ERROR: Can't open backup file\n", 30);
            destroy_all(rpg);
            return (1);
        }
        re_create_window(rpg, rpg->params.fullscreen);
    }
    return (0);
}

void myrpg(bool no_sound, char *file_backup)
{
    rpg_t *rpg = malloc(sizeof(rpg_t));
    sfColor drunk = {255, 0, 0, 255};
    init_all(rpg, no_sound);
    if (!rpg->begin.window || !rpg->begin.framebuffer)
        return;
    play_sound(rpg->sound.sound_list[SOUND_MENU].sound,
    rpg->sound.volume_music);
    if (open_or_not_file(rpg, file_backup) == 1)
        return;
    // rpg->screen[SC_CUTSCENE_BEGIN].active = true;
    while (sfRenderWindow_isOpen(rpg->begin.window)) {
        clean_window(&rpg->begin, sfBlack);
        get_fps(rpg);
        my_events(rpg);
        if ((rpg->all_events.c) && rpg->all_events.ctrl)
        sfRenderWindow_close(rpg->begin.window);
        if (rpg->all_events.ctrl && rpg->all_events.s) {
            save_file("save", rpg);
            rpg->all_events.s = false;
        }
        if (rpg->screen[SC_CUTSCENE_BEGIN].active)
            cutsceens_begin(rpg);
        else
            big_loop(rpg, &drunk);
    }
    destroy_all(rpg);
}
