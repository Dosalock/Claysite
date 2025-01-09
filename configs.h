#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include "clay.h"

/* ------------consts------------ */
const Clay_Color COLOR_BACKDROP = (Clay_Color){15, 0, 40, 255};
const Clay_Color COLOR_BACKGROUND = (Clay_Color){20, 0, 50, 255};
const Clay_Color COLOR_ITEM = (Clay_Color){60, 9, 108, 255};
const Clay_Color COLOR_ITEM_HOVER = (Clay_Color) {130,45,170,255};
const Clay_Color COLOR_TEXT_1 = (Clay_Color){255, 158, 0, 255};
const Clay_Color COLOR_CONTAINER_BORDER = (Clay_Color){90, 24, 154, 255};

const Clay_Sizing C_EXPAND = (Clay_Sizing){CLAY_SIZING_GROW(), CLAY_SIZING_GROW()};

/* -----------configs----------- */

Clay_TextElementConfig btn_text_config =
	(Clay_TextElementConfig){.fontId = 2, .fontSize = 24, .textColor = COLOR_TEXT_1};

Clay_LayoutConfig set_container_config =
	(Clay_LayoutConfig){.layoutDirection = CLAY_TOP_TO_BOTTOM,
						.sizing = {CLAY_SIZING_FIXED(400), CLAY_SIZING_GROW()},
						.childGap = 4,
						.padding = {16, 16}};

#endif