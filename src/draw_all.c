/*
** EPITECH PROJECT, 2021
** my_rpg
** File description:
** draw_all.c
*/

#include "../include/rpg.h"

void draw_sfimage(sfRenderWindow *window, sfImage *image, sfVector2f pos,
sfIntRect rect)
{
    sfTexture *texture = sfTexture_createFromImage(image, NULL);
    sfSprite *sprite = sfSprite_create();
    sfImage_createMaskFromColor(image, (sfColor){0, 0, 0, 100}, 100);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setTexture(sprite, texture, sfFalse);
    sfSprite_setTextureRect(sprite, rect);
    sfRenderWindow_drawSprite(window, sprite, NULL);
}

static void draw_spritesheets(beginning_t *begin, spritesheet_t *spritesheet)
{
    sfVector2i po = sfMouse_getPositionRenderWindow(begin->window);
    spritesheet[SP_CURSOR].pos =
    sfRenderWindow_mapPixelToCoords(begin->window, po, begin->view.view);
    for (int i = 0; i < NBR_SP - 1; ++i)
        if (spritesheet[i].active)
            draw_one_sprite(begin, spritesheet[i].sprite, spritesheet[i].rect,
            spritesheet[i].pos);
}

void draw_inventory(inventory_t inventory,
spritesheet_t *spritesheet, rpg_t *rpg)
{
    int enum_sprite_place = 0;

    for (int i = SP_ITEM_SHOVEL; i <= SP_FLASK_DRUNK; ++i)
        rpg->spritesheet[i].active = false;
    for (int i = 0; i < 12; ++i) {
        enum_sprite_place = inventory.inventory_case[i].item_spritesheet;
        if (enum_sprite_place >= SP_ITEM_SHOVEL
        && enum_sprite_place <= SP_FLASK_DRUNK) {
            spritesheet[enum_sprite_place].active = true;
            sfSprite_setRotation(spritesheet[enum_sprite_place].sprite, 0);
            spritesheet[enum_sprite_place].pos = (i == 11 ?
            rpg->all_events.mouse.pos_view : inventory.inventory_case[i].pos);
        }
    }
}

void draw_all_text(rpg_t *rpg)
{
    send_chat_bubble(rpg, "assets/quest_dialog/soldiers.txt", QUEST_SOLDIER);
    send_chat_bubble(rpg, "assets/quest_dialog/seller.txt", QUEST_SELLER);
    if (rpg->screen[SC_OPTION].active)
        draw_text_fps_settings(rpg);
    if (rpg->params.show_fps)
        draw_fps(rpg);
    if (rpg->screen[SC_INVENTORY].active)
        write_text(rpg->begin.window, rpg->player_stats.inventory.money);
}

void draw_main_item(rpg_t *rpg)
{
    int item_nb = rpg->player_stats.inventory.inventory_case[I_ATTACK].item_spritesheet;
    sfVector2f pos_main_item = rpg->spritesheet[rpg->player_stats.skin].pos;
    sfVector2f scale_item;
    sfVector2f scale_item2;

    if (item_nb != -1) {
        scale_item = sfSprite_getScale(rpg->spritesheet[item_nb].sprite);
        scale_item2 = sfSprite_getScale(rpg->spritesheet[item_nb].sprite);
        scale_item.x /= 2;
        scale_item.y /= 2;
        pos_main_item.x -= 20;
        pos_main_item.y += 5;
        sfSprite_setScale(rpg->spritesheet[item_nb].sprite, scale_item);
        // sfSprite_rotate(rpg->spritesheet[item_nb].sprite, 90);
        draw_one_sprite(&rpg->begin, rpg->spritesheet[item_nb].sprite,
        rpg->spritesheet[item_nb].rect, pos_main_item);
        sfSprite_setScale(rpg->spritesheet[item_nb].sprite, scale_item2);
        // sfSprite_rotate(rpg->spritesheet[item_nb].sprite, -90);
    }
}

void draw_all(rpg_t *rpg)
{
    sfSprite_setTexture(rpg->begin.sprite, rpg->begin.texture, sfFalse);
    sfTexture_updateFromPixels(rpg->begin.texture,
    rpg->begin.framebuffer, WIDTH, HEIGHT, 0, 0);
    sfRenderWindow_drawSprite(rpg->begin.window,
    rpg->begin.sprite, NULL);
    if (rpg->screen[SC_INVENTORY].active)
        draw_inventory(rpg->player_stats.inventory, rpg->spritesheet, rpg);
    if (rpg->screen[SC_MAIN_MAP].active && !rpg->screen[SC_INVENTORY].active
    && check_if_in_inventory(rpg, SP_ITEM_PRISONER_PEE) == -1)
        rpg->spritesheet[SP_ITEM_PRISONER_PEE].active = true;
    else if (!rpg->screen[SC_INVENTORY].active)
        rpg->spritesheet[SP_ITEM_PRISONER_PEE].active = false;
    draw_spritesheets(&rpg->begin, rpg->spritesheet);
    if (!rpg->screen[SC_INVENTORY].active)
        draw_main_item(rpg);
    draw_all_text(rpg);
    if (rpg->spritesheet[SP_CURSOR].active)
        draw_one_sprite(&rpg->begin, rpg->spritesheet[SP_CURSOR].sprite,
        rpg->spritesheet[SP_CURSOR].rect, rpg->spritesheet[SP_CURSOR].pos);
    sfRenderWindow_display(rpg->begin.window);
    // printf("%f %f\n", rpg->spritesheet[SP_CURSOR].pos.x, rpg->spritesheet[SP_CURSOR].pos.y);
}
