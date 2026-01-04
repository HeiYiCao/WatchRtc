/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen_1(lv_ui *ui)
{
    //Write codes screen_1
    ui->screen_1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_1, 240, 320);
    lv_obj_set_scrollbar_mode(ui->screen_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1, lv_color_hex(0x4826c4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_spinbox_1
    ui->screen_1_spinbox_1 = lv_spinbox_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_spinbox_1, 93, 50);
    lv_obj_set_width(ui->screen_1_spinbox_1, 44);
    lv_obj_set_height(ui->screen_1_spinbox_1, 41);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_1, 2, 2);
    lv_spinbox_set_range(ui->screen_1_spinbox_1, 0, 23);
    lv_coord_t screen_1_spinbox_1_h = lv_obj_get_height(ui->screen_1_spinbox_1);
    ui->screen_1_spinbox_1_btn_plus = lv_btn_create(ui->screen_1);
    lv_obj_set_size(ui->screen_1_spinbox_1_btn_plus, screen_1_spinbox_1_h, screen_1_spinbox_1_h);
    lv_obj_align_to(ui->screen_1_spinbox_1_btn_plus, ui->screen_1_spinbox_1, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_1_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_1_btn_plus, lv_screen_1_spinbox_1_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_1_btn_minus = lv_btn_create(ui->screen_1);
    lv_obj_set_size(ui->screen_1_spinbox_1_btn_minus, screen_1_spinbox_1_h, screen_1_spinbox_1_h);
    lv_obj_align_to(ui->screen_1_spinbox_1_btn_minus, ui->screen_1_spinbox_1, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_1_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_1_btn_minus, lv_screen_1_spinbox_1_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_1, 93, 50);

    //Write style for screen_1_spinbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_1, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_1, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_1, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_1, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_1, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_1, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_1_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_1_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_1_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_1_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_1_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_1_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_1_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_1_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_1_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_1_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_1_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_1_btn_plus, &style_screen_1_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_1_btn_minus, &style_screen_1_spinbox_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_spinbox_2
    ui->screen_1_spinbox_2 = lv_spinbox_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_spinbox_2, 93, 107);
    lv_obj_set_width(ui->screen_1_spinbox_2, 44);
    lv_obj_set_height(ui->screen_1_spinbox_2, 41);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_2, 2, 2);
    lv_spinbox_set_range(ui->screen_1_spinbox_2, 0, 59);
    lv_coord_t screen_1_spinbox_2_h = lv_obj_get_height(ui->screen_1_spinbox_2);
    ui->screen_1_spinbox_2_btn_plus = lv_btn_create(ui->screen_1);
    lv_obj_set_size(ui->screen_1_spinbox_2_btn_plus, screen_1_spinbox_2_h, screen_1_spinbox_2_h);
    lv_obj_align_to(ui->screen_1_spinbox_2_btn_plus, ui->screen_1_spinbox_2, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_2_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_2_btn_plus, lv_screen_1_spinbox_2_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_2_btn_minus = lv_btn_create(ui->screen_1);
    lv_obj_set_size(ui->screen_1_spinbox_2_btn_minus, screen_1_spinbox_2_h, screen_1_spinbox_2_h);
    lv_obj_align_to(ui->screen_1_spinbox_2_btn_minus, ui->screen_1_spinbox_2, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_2_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_2_btn_minus, lv_screen_1_spinbox_2_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_2, 93, 107);

    //Write style for screen_1_spinbox_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_2, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_2, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_2, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_2, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_2, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_2, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_2, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_2, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_2_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_2_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_2_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_2_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_2_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_2_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_2_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_2_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_2_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_2_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_2_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_2_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_2_btn_plus, &style_screen_1_spinbox_2_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_2_btn_minus, &style_screen_1_spinbox_2_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_spinbox_3
    ui->screen_1_spinbox_3 = lv_spinbox_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_spinbox_3, 93, 167);
    lv_obj_set_width(ui->screen_1_spinbox_3, 44);
    lv_obj_set_height(ui->screen_1_spinbox_3, 41);
    lv_spinbox_set_digit_format(ui->screen_1_spinbox_3, 2, 2);
    lv_spinbox_set_range(ui->screen_1_spinbox_3, 0, 59);
    lv_coord_t screen_1_spinbox_3_h = lv_obj_get_height(ui->screen_1_spinbox_3);
    ui->screen_1_spinbox_3_btn_plus = lv_btn_create(ui->screen_1);
    lv_obj_set_size(ui->screen_1_spinbox_3_btn_plus, screen_1_spinbox_3_h, screen_1_spinbox_3_h);
    lv_obj_align_to(ui->screen_1_spinbox_3_btn_plus, ui->screen_1_spinbox_3, LV_ALIGN_OUT_RIGHT_MID, 5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_3_btn_plus, LV_SYMBOL_PLUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_3_btn_plus, lv_screen_1_spinbox_3_increment_event_cb, LV_EVENT_ALL, NULL);
    ui->screen_1_spinbox_3_btn_minus = lv_btn_create(ui->screen_1);
    lv_obj_set_size(ui->screen_1_spinbox_3_btn_minus, screen_1_spinbox_3_h, screen_1_spinbox_3_h);
    lv_obj_align_to(ui->screen_1_spinbox_3_btn_minus, ui->screen_1_spinbox_3, LV_ALIGN_OUT_LEFT_MID, -5, 0);
    lv_obj_set_style_bg_img_src(ui->screen_1_spinbox_3_btn_minus, LV_SYMBOL_MINUS, 0);
    lv_obj_add_event_cb(ui->screen_1_spinbox_3_btn_minus, lv_screen_1_spinbox_3_decrement_event_cb, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_spinbox_3, 93, 167);

    //Write style for screen_1_spinbox_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_spinbox_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_spinbox_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_spinbox_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_spinbox_3, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_spinbox_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_spinbox_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_spinbox_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_spinbox_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_spinbox_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_3, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_spinbox_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_spinbox_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for screen_1_spinbox_3, Part: LV_PART_CURSOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_spinbox_3, lv_color_hex(0xffffff), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_spinbox_3, &lv_font_montserratMedium_12, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_spinbox_3, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_spinbox_3, 255, LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_spinbox_3, lv_color_hex(0x2195f6), LV_PART_CURSOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_spinbox_3, LV_GRAD_DIR_NONE, LV_PART_CURSOR|LV_STATE_DEFAULT);

    //Write style state: LV_STATE_DEFAULT for &style_screen_1_spinbox_3_extra_btns_main_default
    static lv_style_t style_screen_1_spinbox_3_extra_btns_main_default;
    ui_init_style(&style_screen_1_spinbox_3_extra_btns_main_default);

    lv_style_set_text_color(&style_screen_1_spinbox_3_extra_btns_main_default, lv_color_hex(0xffffff));
    lv_style_set_text_font(&style_screen_1_spinbox_3_extra_btns_main_default, &lv_font_montserratMedium_12);
    lv_style_set_text_opa(&style_screen_1_spinbox_3_extra_btns_main_default, 255);
    lv_style_set_bg_opa(&style_screen_1_spinbox_3_extra_btns_main_default, 255);
    lv_style_set_bg_color(&style_screen_1_spinbox_3_extra_btns_main_default, lv_color_hex(0x2195f6));
    lv_style_set_bg_grad_dir(&style_screen_1_spinbox_3_extra_btns_main_default, LV_GRAD_DIR_NONE);
    lv_style_set_border_width(&style_screen_1_spinbox_3_extra_btns_main_default, 0);
    lv_style_set_radius(&style_screen_1_spinbox_3_extra_btns_main_default, 5);
    lv_style_set_shadow_width(&style_screen_1_spinbox_3_extra_btns_main_default, 0);
    lv_obj_add_style(ui->screen_1_spinbox_3_btn_plus, &style_screen_1_spinbox_3_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_add_style(ui->screen_1_spinbox_3_btn_minus, &style_screen_1_spinbox_3_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes screen_1_btn_1
    ui->screen_1_btn_1 = lv_btn_create(ui->screen_1);
    ui->screen_1_btn_1_label = lv_label_create(ui->screen_1_btn_1);
    lv_label_set_text(ui->screen_1_btn_1_label, "->");
    lv_label_set_long_mode(ui->screen_1_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->screen_1_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->screen_1_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->screen_1_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->screen_1_btn_1, 84, 229);
    lv_obj_set_size(ui->screen_1_btn_1, 60, 29);

    //Write style for screen_1_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_btn_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_btn_1, &lv_font_SourceHanSerifSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of screen_1.


    //Update current screen layout.
    lv_obj_update_layout(ui->screen_1);

    //Init events for screen.
    events_init_screen_1(ui);
}
