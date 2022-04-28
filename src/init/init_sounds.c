/*
** EPITECH PROJECT, 2021
** myrpg
** File description:
** init_sounds.c
*/

#include "../../include/rpg.h"

void init_sounds(rpg_t *rpg)
{
    rpg->sound.sound_list = malloc(sizeof(sound_list_t) * NBR_SOUND);
    create_sound("assets/sounds/main.ogg",
    true, &rpg->sound.sound_list[SOUND_MENU]);
    create_sound("assets/sounds/walk.ogg",
    false, &rpg->sound.sound_list[SOUND_WALK]);
    create_sound("assets/sounds/door.ogg",
    false, &rpg->sound.sound_list[SOUND_DOOR]);
    create_sound("assets/sounds/ambiant_cave.ogg",
    true, &rpg->sound.sound_list[SOUND_AMBIANT_CAVE]);
    create_sound("assets/sounds/die_player.ogg",
    true, &rpg->sound.sound_list[SOUND_DIE_PLAYER]);
    create_sound("assets/sounds/main_sound.ogg",
    true, &rpg->sound.sound_list[SOUND_MAIN]);
}
