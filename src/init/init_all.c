/*
** EPITECH PROJECT, 2021
** myworld
** File description:
** init_all.c
*/

#include "../../include/rpg.h"

static void init_all_events_mouse(events_t *events)
{
    events->mouse.left = false;
    events->mouse.left_released = false;
    events->mouse.right = false;
    events->mouse.move_x = 0;
    events->mouse.move_y = 0;
    events->mouse.pos = (sfVector2i){0, 0};
    events->mouse.pos_view = (sfVector2f){0, 0};
    events->mouse_wheel.up = false;
    events->mouse_wheel.down = false;
    events->mouse_wheel.click = false;
}

void init_all_events(events_t *events)
{
    events->left = false;
    events->right = false;
    events->up = false;
    events->down = false;
    events->page_up = false;
    events->page_down = false;
    events->z = false;
    events->q = false;
    events->s = false;
    events->d = false;
    events->e = false;
    events->c = false;
    events->escape = false;
    events->space = false;
    events->ctrl = false;
    events->tab = false;
    events->enter = false;
    init_all_events_mouse(events);
}

static void init_player_boss_stats(player_stats_t *player_stats, boss_stats_t *boss_stats)
{
    player_stats->incr_pos.x = 0;
    player_stats->incr_pos.y = 0;
    player_stats->money = 0;
    player_stats->attack = false;
    player_stats->speed = 1.0;
    player_stats->life = 20.0;
    player_stats->mana = 0.0;
    player_stats->damage = 1;
    player_stats->knowledge = 1;
    player_stats->last_damage = sfClock_create();
    boss_stats->damage = 1;
    boss_stats->inc_pos = 0.25;
    boss_stats->life = 20;
    boss_stats->status = ST_IDLE;
    boss_stats->time_next_it = 0;
    boss_stats->movement = sfClock_create();
    boss_stats->rush_to_player = false;
}

static void init_fps(rpg_t *rpg)
{
    rpg->begin.fps.clock = sfClock_create();
    rpg->begin.fps.timer = 0;
    rpg->begin.fps_disp.fps_text = create_text((init_text_t){100, "", sfWhite,
    {WIDTH / 2, HEIGHT / 2}, "assets/fonts/Sriracha-Regular.ttf"});
    rpg->begin.fps_disp.legende = create_text((init_text_t){100, "FPS: ", sfWhite,
    {WIDTH / 2, HEIGHT / 2}, "assets/fonts/Sriracha-Regular.ttf"});
    rpg->begin.fps_disp.clock = sfClock_create();
    rpg->begin.fps_disp.display_clock = sfClock_create();
    rpg->begin.fps_disp.time = 0;
    rpg->begin.fps_disp.fps = 0;
}

void init_all(rpg_t *rpg)
{
    rpg->index_old_s = 0;
    rpg->player_stats.skin = SP_PLAYER;
    rpg->sound.volume = 0;
    rpg->sound.volume_active = false;
    init_fps(rpg);
    init_all_events(&rpg->all_events);
    init_imgs(rpg);
    init_screens(rpg);
    rpg->spritesheet = malloc(sizeof(spritesheet_t) * NBR_SP);
    init_view(rpg);
    init_spritesheets(rpg->spritesheet);
    init_sounds(rpg);
    init_csfml(&rpg->begin);
    init_player_boss_stats(&rpg->player_stats, &rpg->boss_stats);
    init_quests(rpg);
    init_inventory(&rpg->player_stats.inventory, rpg);
}
