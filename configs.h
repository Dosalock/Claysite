#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include "clay.h"

#define impsum "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."


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
	(Clay_TextElementConfig){.fontId = 2, .fontSize = 24, .textColor = COLOR_TEXT_1, .disablePointerEvents = true};

Clay_LayoutConfig set_container_config =
	(Clay_LayoutConfig){.layoutDirection = CLAY_TOP_TO_BOTTOM,
						.sizing = {CLAY_SIZING_FIXED(400), CLAY_SIZING_FIT()},
						.childGap = 0,
						.padding = {8, 8}};

#endif