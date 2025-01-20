/**------------------------------------------------------------------------
 * ?                                ABOUT
 * @author         :  Johan Karlsson
 * @email          :  j.ef.karlsson@gmail.com
 * @repo           :  Claysite
 * @createdOn      :  2025-01-15
 * @description    :  Style configurations for clay.h
 *------------------------------------------------------------------------**/
#ifndef __CONFIGS_H__
#define __CONFIGS_H__

#include "clay.h"


/*-------------------------------- Defines ------------------------------*/

int highlight_text_offset_x = 0;
int highlight_text_offset_y = 0;
#define GLOBAL_FONT_SCALING_FACTOR 1.0f
/*--------------- Text filler ----------------*/
const Clay_String cs = CLAY_STRING_CONST("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod " \
	"tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "    \
	"veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea " \
	"commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "  \
	"velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "       \
	"occaecat cupidatat non proident, sunt in culpa qui officia deserunt "     \
	"mollit anim id est laborum.");

#define impsum                                                                 \
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod " \
	"tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim "    \
	"veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea " \
	"commodo consequat. Duis aute irure dolor in reprehenderit in voluptate "  \
	"velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint "       \
	"occaecat cupidatat non proident, sunt in culpa qui officia deserunt "     \
	"mollit anim id est laborum."


/*------------------ Colors -----------------*/

#if __DEBUG_LEVEL > 1

#define COLOR_DROPSHADOW ( Clay_Color ) { 255, 0, 255, 255 }

#else

#define COLOR_DROPSHADOW       ( Clay_Color ) { 0, 0, 0, 64 }
#define COLOR_BACKDROP         ( Clay_Color ) { 15, 0, 40, 255 }
#define COLOR_BACKGROUND       ( Clay_Color ) { 20, 0, 50, 255 }
#define COLOR_ITEM             ( Clay_Color ) { 60, 9, 108, 255 }
#define COLOR_ITEM_HOVER       ( Clay_Color ) { 130, 45, 170, 255 }
#define COLOR_TEXT_1           ( Clay_Color ) { 255, 158, 0, 255 }
#define COLOR_TEXT_2           ( Clay_Color ) { 255, 158, 0, 255 }
#define COLOR_CONTAINER_BORDER ( Clay_Color ) { 90, 24, 154, 255 }

#endif


/*-------------------------------- Configs ------------------------------*/

// Sizing const for exand all
const Clay_Sizing C_EXPAND =
  ( Clay_Sizing ) { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) };


Clay_TextElementConfig btn_text_config =
  ( Clay_TextElementConfig ) { .fontId               = 2,
							   .fontSize             = 24,
							   .textColor            = COLOR_TEXT_1,
							   .disablePointerEvents = true };

Clay_TextElementConfig set_information_dropdown_text_config = {
	.fontId    = 2,
	.fontSize  = 18,
	.textColor = COLOR_TEXT_2,
	.wrapMode = CLAY_TEXT_WRAP_WORDS,
	.lineHeight = 16
};


/*------------------ Border Configs -----------------*/

/*------- Generic -------*/

Clay_BorderElementConfig drop_shadow = {
	.bottom       = { 7, COLOR_DROPSHADOW },
	.right        = { 7, COLOR_DROPSHADOW },
	.cornerRadius = { 0, 12, 12, 15 }
};


/*------- Set Information -------*/

Clay_BorderElementConfig set_information_bar_open_border_config = {
	.bottom       = { 2, COLOR_CONTAINER_BORDER },
	.top          = { 2, COLOR_CONTAINER_BORDER },
	.left         = { 2, COLOR_CONTAINER_BORDER },
	.right        = { 2, COLOR_CONTAINER_BORDER },
	.cornerRadius = { 8, 8, 0, 0 }
};

Clay_BorderElementConfig set_information_bar_closed_border_config = {
	.bottom       = { 2, COLOR_CONTAINER_BORDER },
	.top          = { 2, COLOR_CONTAINER_BORDER },
	.left         = { 2, COLOR_CONTAINER_BORDER },
	.right        = { 2, COLOR_CONTAINER_BORDER },
	.cornerRadius = { 8, 8, 8, 8 }
};

Clay_BorderElementConfig set_information_dropdown_border_config = {
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


/*------------------ Rect Configs -----------------*/

/*------- Header -------*/

Clay_RectangleElementConfig header_bar_rect_config = {
	.color        = COLOR_BACKGROUND,
	.cornerRadius = { 8, 8, 8, 8 }
};

Clay_RectangleElementConfig header_button_rect_config = {
	.color        = COLOR_ITEM,
	.cornerRadius = { 4, 4, 4, 4 }
};


/*------- Main -------*/

Clay_RectangleElementConfig main_background_rect_config = {
	.color        = { 40, 1, 60, 255 },
	.cornerRadius = {  8, 8,  8,   8 },
};


/*------- Set Information -------*/

Clay_RectangleElementConfig set_information_dropdown_rect_config = {
	.color        = COLOR_BACKGROUND,
	.cornerRadius = { 0, 0, 8, 8 }
};

Clay_RectangleElementConfig set_information_dropdown_rect_hidden_config = {
	.color        = { 0, 0, 0, 255 },
	.cornerRadius = { 0, 0, 0,   0 }
};

Clay_RectangleElementConfig set_information_bar_open_rect_config = {
	.color         = COLOR_ITEM,
	.cornerRadius  = { 8, 8, 0, 0 },
	.cursor_pointer = true
};

Clay_RectangleElementConfig set_information_bar_rect_closed_config = {
	.color         = COLOR_ITEM,
	.cornerRadius  = { 8, 8, 8, 8 },
	.cursor_pointer = true
};

Clay_RectangleElementConfig set_information_button_rect_config = {
	.cornerRadius  = CLAY_CORNER_RADIUS( 4 ),
	.cursor_pointer = true,
	.color         = COLOR_ITEM
};

Clay_RectangleElementConfig set_information_button_hover_rect_config = {
	.cornerRadius  = CLAY_CORNER_RADIUS( 4 ),
	.cursor_pointer = true,
	.color         = COLOR_ITEM_HOVER
};

/*------------------ Layout Configs -----------------*/


/*------- Header -------*/

Clay_LayoutConfig header_bar_layout_config = { 
	.sizing = {
	.width  = CLAY_SIZING_GROW( 0 ),
	.height = CLAY_SIZING_FIXED( 90 ),
	} 
};

Clay_LayoutConfig header_button_container_layout_config = {
	.layoutDirection = CLAY_LEFT_TO_RIGHT,
	.sizing          = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
	.childAlignment  = { 0, CLAY_ALIGN_Y_CENTER },
	.padding         = { 16, 16, 32, 32 },
	.childGap        = 8,
};

Clay_LayoutConfig header_button_layout_config = {
	.sizing = { CLAY_SIZING_FIT(.min = 100 ), CLAY_SIZING_PERCENT( 1.75 ) },
	.childAlignment = {          CLAY_ALIGN_X_CENTER,         CLAY_ALIGN_Y_CENTER }
};


/*------- Main Content --------*/

Clay_LayoutConfig main_content_layout_config = {
	.sizing   = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
	.childGap = 8,
};

Clay_LayoutConfig main_background_layout_config = {
	.sizing          = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_FIT( ) },
	.layoutDirection = CLAY_TOP_TO_BOTTOM,
};

Clay_LayoutConfig main_scroll_container_layout_config = {
	.sizing          = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
	.layoutDirection = CLAY_TOP_TO_BOTTOM
};

/*------- Set Information -------*/

Clay_LayoutConfig set_information_button_layout_config = {
	.padding = { 10, 10, 4, 4 }
};

Clay_LayoutConfig set_information_wrapper_layout_config = {
	.layoutDirection = CLAY_TOP_TO_BOTTOM,
	.sizing          = { CLAY_SIZING_FIXED( 400 ), CLAY_SIZING_FIT( ) },
	.padding         = { 8, 8, 8, 8 }
};

Clay_LayoutConfig set_information_container_layout_config = {
	.sizing          = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
	.layoutDirection = CLAY_TOP_TO_BOTTOM,
	.padding         = { 0, 5, 0, 5 }
};

Clay_LayoutConfig set_information_bar_layout_config = {
	.sizing          = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_FIXED( 50 ) },
	.layoutDirection = CLAY_LEFT_TO_RIGHT,
	.childAlignment  = { 0, CLAY_ALIGN_Y_CENTER },
	.padding         = { 8, 8, 8, 8 },
	.childGap        = 8
};

Clay_LayoutConfig set_information_dropdown_layout_open_config = {
	.sizing  = { CLAY_SIZING_FIT( ), CLAY_SIZING_FIT( ) },
	.padding = { 8, 8, 8, 8 }
};

Clay_LayoutConfig set_information_dropdown_layout_closed_config = {
	.sizing  = { { 0 }, { 0 } },
	.padding = {     0,     0 }
};


/*------- Floating Element Configs -------*/
Clay_FloatingElementConfig floating_element_test_config;

#endif