/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"
#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif


static void screen_led_1_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.screen_1, guider_ui.screen_1_del, &guider_ui.screen_del, setup_scr_screen_1, LV_SCR_LOAD_ANIM_FADE_ON, 20, 20, false, true);
        break;
    }
    default:
        break;
    }
}

void events_init_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_led_1, screen_led_1_event_handler, LV_EVENT_ALL, ui);
}

// 设置界面中“确认/保存”按钮的事件回调函数
static void screen_1_btn_1_event_handler (lv_event_t *e)
{
    // 获取当前触发的事件类型 如点击、按下、释放等
    lv_event_code_t code = lv_event_get_code(e);

    // 从事件中获取 UI 结构体指针
	lv_ui *ui = lv_event_get_user_data(e);

    // 根据事件类型进行处理
    switch (code) {

    // 当按钮被点击时
    case LV_EVENT_CLICKED:
    {
        // 从第一个 spinbox 获取“小时”值
		g_hour = lv_spinbox_get_value(ui->screen_1_spinbox_1);

        // 从第二个 spinbox 获取“分钟”值
		g_min = lv_spinbox_get_value(ui->screen_1_spinbox_2);

        // 从第三个 spinbox 获取“秒”值
		g_sec = lv_spinbox_get_value(ui->screen_1_spinbox_3);

        // 将获取到的时间写入 RTC 硬件
		RTC_SetTime(g_hour, g_min, g_sec);

        // 切换回时钟主界面（screen）
		ui_load_scr_animation(&guider_ui,
                              &guider_ui.screen,          // 目标页面：时钟页面
                              guider_ui.screen_del,      // 目标页面释放函数
                              &guider_ui.screen_1_del,   // 当前设置页面释放函数
                              setup_scr_screen,          // 目标页面初始化函数
                              LV_SCR_LOAD_ANIM_NONE,     // 页面切换动画：无动画
                              20,                        // 动画延时（进入）
                              20,                        // 动画延时（退出）
                              false,                     // 不自动删除旧页面
                              true);                     // 立即加载新页面
		break;
    }

    // 其他未处理的事件
    default:
        break;
    }
}


void events_init_screen_1 (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->screen_1_btn_1, screen_1_btn_1_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
