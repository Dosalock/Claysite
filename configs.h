#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include "clay.h"

#define impsum                                                                 \
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod " \
	"tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "    \
	"veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea " \
	"commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "  \
	"velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "       \
	"occaecat cupidatat non proident, sunt in culpa qui officia deserunt "     \
	"mollit anim id est laborum."


/* ------------defines------------ */
#if __DEBUG_LEVEL > 1
#define COLOR_MARGIN ( Clay_Color ) { 255, 0, 255, 255 }
#else
#define COLOR_MARGIN ( Clay_Color ) { 0, 0, 0, 0 } 
#endif
 


#define COLOR_BACKDROP         ( Clay_Color ) { 15, 0, 40, 255 }
#define COLOR_BACKGROUND       ( Clay_Color ) { 20, 0, 50, 255 }
#define COLOR_ITEM             ( Clay_Color ) { 60, 9, 108, 255 }
#define COLOR_ITEM_HOVER       ( Clay_Color ) { 130, 45, 170, 255 }
#define COLOR_TEXT_1           ( Clay_Color ) { 255, 158, 0, 255 }
#define COLOR_TEXT_2           ( Clay_Color ) { 255, 158, 0, 255 }
#define COLOR_CONTAINER_BORDER ( Clay_Color ) { 90, 24, 154, 255 }

const Clay_Sizing C_EXPAND =
  ( Clay_Sizing ) { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) };

/* -----------configs----------- */

Clay_TextElementConfig btn_text_config =
  ( Clay_TextElementConfig ) { .fontId               = 2,
							   .fontSize             = 24,
							   .textColor            = COLOR_TEXT_1,
							   .disablePointerEvents = true };

Clay_LayoutConfig layout_config_set_container = ( Clay_LayoutConfig ) {
	.layoutDirection = CLAY_TOP_TO_BOTTOM,
	.sizing          = { CLAY_SIZING_FIXED( 400 ), CLAY_SIZING_FIT( ) },
	// .childGap        = 16,
	.padding = {						8,                  8 }
};

Clay_BorderElementConfig set_information_bar_border_config = {
	.bottom       = { 2, COLOR_CONTAINER_BORDER },
	.top          = { 2, COLOR_CONTAINER_BORDER },
	.left         = { 2, COLOR_CONTAINER_BORDER },
	.right        = { 2, COLOR_CONTAINER_BORDER },
	.cornerRadius = { 8, 8, 0, 0 }
};

Clay_BorderElementConfig set_information_dropdown_border_config = {
	// .bottom       = { 2, COLOR_CONTAINER_BORDER },
	// .top          = { 2, COLOR_CONTAINER_BORDER },
	// .left         = { 2, COLOR_CONTAINER_BORDER },
	// .right        = { 2, COLOR_CONTAINER_BORDER },
	.bottom       = { 6, { 0, 0, 0, 64 } },
	.right        = { 6, { 0, 0, 0, 64 } },
	.cornerRadius = { 0, 0, 0, 11 }
};

Clay_BorderElementConfig set_information_dropdown_border_hidden_config = {
	.bottom       = { 0, { 0, 0, 0, 0 } },
	.top          = { 0, { 0, 0, 0, 0 } },
	.left         = { 0, { 0, 0, 0, 0 } },
	.right        = { 0, { 0, 0, 0, 0 } },
	.cornerRadius = { 0, 0, 0, 0 }
};

Clay_RectangleElementConfig set_information_dropdown_rect_config = {
	.color        = COLOR_BACKGROUND,
	.cornerRadius = { 0, 0, 8, 8 }
};

Clay_RectangleElementConfig set_information_dropdown_rect_hidden_config = {
	.color        = { 0, 0, 0, 255 },
	.cornerRadius = { 0, 0, 0,   0 }
};

Clay_LayoutConfig set_information_dropdown_layout_open_config = {
	.sizing  = { CLAY_SIZING_FIT( ), CLAY_SIZING_FIT( ) },
	.padding = {				  8,                  8 }
};

Clay_LayoutConfig set_information_dropdown_layout_closed_config = {
	.sizing  = { { 0 }, { 0 } },
	.padding = {     0,     0 }
};

Clay_TextElementConfig set_information_dropdown_text_config = {
	.fontId    = 2,
	.fontSize  = 18,
	.textColor = COLOR_TEXT_2
};

#endif