/**------------------------------------------------------------------------
 * ?                                ABOUT
 * @author         :  Johan Karlsson
 * @email          :  j.ef.karlsson@gmail.com
 * @repo           :  Claysite
 * @createdOn      :  2025-01-15
 * @description    :  Main entry and render loop
 *------------------------------------------------------------------------**/


/*-------------------------------- Defines ------------------------------*/

/*------- Clay.h -------*/

#define CLAY_EXTEND_CONFIG_RECTANGLE                                           \
	Clay_String link;                                                          \
	bool cursor_pointer;                                                       \
	bool clicked;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT  bool disablePointerEvents;
#define CLAY_IMPLEMENTATION
#define RAYLIB_VECTOR2_TO_CLAY_VECTOR2( vector )                               \
	( Clay_Vector2 )                                                           \
	{                                                                          \
		.x = ( vector ).x, .y = ( vector ).y                                   \
	}


/*------- Debug -------*/
#define __DEBUG_LEVEL 0


/*-------------------------------- Includes ------------------------------*/

#include "clay.h"
#include "events.h"
#include "helper.h"
#include "objects.h"

/*-------------------------------- Globals ------------------------------*/

bool debug_mode_enabled = false;
double window_width = 1024, window_height = 768;
float animation_lerp_value     = -1.0f;
ScrollbarData scrollbar_data   = ( ScrollbarData ) { };
uint32_t ACTIVE_RENDERER_INDEX = 0;

/*-------------------------------- Functions ------------------------------*/

Clay_RenderCommandArray CreateLayout ( bool mobile_screen, float lerp_value )
{
	Clay_BeginLayout( );
	// MAKE UI IN HERE

	CLAY( CLAY_ID( "outer_container" ),
		  CLAY_RECTANGLE( {
			  .color = COLOR_BACKDROP
    } ),
		  CLAY_LAYOUT(
			  { .layoutDirection = CLAY_TOP_TO_BOTTOM,
				.sizing   = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
				.padding  = CLAY_PADDING_ALL( 16 ),
				.childGap = 8 } ) )
	{
		// Children

		CLAY( CLAY_ID( "header_bar" ),
			  CLAY_RECTANGLE( header_bar_rect_config ),
			  CLAY_LAYOUT( header_bar_layout_config ) )
		{
			CLAY( CLAY_ID( "header_button_container" ),
				  CLAY_LAYOUT( header_button_container_layout_config ) )
			{
				HeaderButton( "test" );
				HeaderButton( "test2asdf" );
			}
		}

		CLAY( CLAY_ID( "main_content" ),
			  CLAY_LAYOUT( main_content_layout_config ) )
		{
			CLAY( CLAY_ID( "left_sidebar" ),
				  CLAY_RECTANGLE( {
					  .color        = COLOR_BACKGROUND,
					  .cornerRadius = { 8, 8, 8, 8 },
            } ),
				  CLAY_LAYOUT( { .sizing = { CLAY_SIZING_FIXED( 200 ),
											 CLAY_SIZING_GROW( ) } } ) )
			{
			}
			CLAY( CLAY_ID( "main_background" ),
				  CLAY_RECTANGLE( main_background_rect_config ),
				  CLAY_LAYOUT( main_background_layout_config ) )
			{
				CLAY( CLAY_ID( "main_scroll_container" ),
					  CLAY_LAYOUT( main_scroll_container_layout_config ),
					  CLAY_SCROLL( { .vertical = true } )
					  // CLAY_BORDER( { .betweenChildren = { 2,
					  // {255,255,255,255} } } )
				)
				{
					SetInfoBox( 1 );
					SetInfoBox( 2 );
					SetInfoBox( 3 );
					SetInfoBox( 4 );
					SetInfoBox( 5 );
					SetInfoBox( 6 );
				}
			}
		}
	}

	return Clay_EndLayout( );
}


CLAY_WASM_EXPORT( "UpdateDrawFrame" )

Clay_RenderCommandArray
	UpdateDrawFrame ( float width,
					  float height,
					  float mouse_wheel_X,
					  float mouse_wheel_y,
					  float mouse_position_X,
					  float mouse_position_y,
					  bool is_touch_down,
					  bool is_mouse_down,
					  bool arrow_key_down_pressed_this_frame,
					  bool arrow_key_up_pressed_this_frame,
					  bool d_key_pressed_this_frame,
					  float delta_time )
{
	window_width  = width;
	window_height = height;
	Clay_SetCullingEnabled( ACTIVE_RENDERER_INDEX == 1 );
	Clay_SetExternalScrollHandlingEnabled( ACTIVE_RENDERER_INDEX == 0 );

	Clay_SetLayoutDimensions( ( Clay_Dimensions ) { width, height } );

	Clay_SetPointerState(
		( Clay_Vector2 ) { mouse_position_X, mouse_position_y },
		is_mouse_down || is_touch_down );
	Clay_ScrollContainerData scroll_container_data =
		Clay_GetScrollContainerData(
			Clay_GetElementId( CLAY_STRING( "OuterScrollContainer" ) ) );

	if ( delta_time == delta_time )
	{ // NaN propagation can cause pain here
		animation_lerp_value += delta_time;
		if ( animation_lerp_value > 1 )
		{
			animation_lerp_value -= 2;
		}
	}
	// Clay_Dimensions c = Clay__MeasureText(&CLAY_STRING("A"),
	// &set_information_dropdown_text_config); float c_x = ( c.width ) / 2.0f;
	// float c_y = ( c.height ) / 2.0f;
	Clay_ElementId textbox_id =
		Clay_GetElementIdWithIndex( CLAY_STRING( "set_information_dropdown" ),
									2 );

	//Clay_ElementData textbox_data = Clay_GetElementData(textbox_id);
	// Coordinate mouse = GetMouseHighlightCoordinates(mouse_position_X,
	// mouse_position_y, textbox_id); highlight_text_offset_x = (c.width *
	// mouse.x); highlight_text_offset_y = (c.height * mouse.y);
	char *string = "Tesing string to see if this is even possible";
	int static_head     = 5;
	int static_tail     = 15;
	Clay_String before = {.chars = string, .length = static_head};
	Clay_String selection = {.chars = string + static_head, .length = static_tail - static_head};
	Clay_String after = {.chars = string, .length = strlen(string) - static_tail};

	Textbox first_attempt = {};

	first_attempt.contents = (Clay_String){.chars = string, .length = strlen(string)};
	first_attempt.parent_id = &textbox_id;
	first_attempt.text_config = &set_information_dropdown_text_config;
	first_attempt.head = static_head;
	first_attempt.tail = static_tail;
	first_attempt.before_selection = before;
	first_attempt.selection = selection;
	first_attempt.after_selection = after;


	Clay_Dimensions highlight_dimensions = Clay__MeasureText(&first_attempt.selection, &set_information_dropdown_text_config);

	Clay_LayoutElementHashMapItem *parent_container = Clay__GetHashMapItem(textbox_id.id);

	// clang-format off
	floating_element_test_config = ( Clay_FloatingElementConfig ) {
		.attachment = {.element = CLAY_ATTACH_POINT_LEFT_TOP, .parent = CLAY_ATTACH_POINT_LEFT_TOP},
		.expand = { 
			.width  = ( highlight_dimensions.width/6.0f ),
			.height = ( highlight_dimensions.height/2.0f ),
		},
		.parentId = Clay_GetElementIdWithIndex(
						CLAY_STRING( "set_information_dropdown" ),
						2 )
						.id,
		.zIndex     = 3,
		
		.pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_PASSTHROUGH,
		.offset = { 
			.x = parent_container->layoutElement->layoutConfig->padding.left + highlight_dimensions.width/6.0f,
			.y = first_attempt.text_config->fontSize   
		}
		// clang-format on
	};

if ( d_key_pressed_this_frame )
{
	debug_mode_enabled = !debug_mode_enabled;

	Clay_SetDebugModeEnabled( debug_mode_enabled );
}
Clay__debugViewHighlightColor = ( Clay_Color ) { 105, 210, 231, 120 };

if ( !is_mouse_down )
{
	scrollbar_data.mouse_down = false;
}
if ( is_mouse_down
	 && Clay_PointerOver(
		 Clay_GetElementIdWithIndex( CLAY_STRING( "set_information_button" ),
									 1 ) ) )
{
	// Clay_ElementId c = Clay_GetElementIdWithIndex( CLAY_STRING(
	// "set_information_button" ),1 );
}

if ( is_mouse_down && !scrollbar_data.mouse_down
	 && Clay_PointerOver( Clay_GetElementId( CLAY_STRING( "ScrollBar" ) ) ) )
{
	scrollbar_data.click_origin =
		( Clay_Vector2 ) { mouse_position_X, mouse_position_y };
	scrollbar_data.position_origin = *scroll_container_data.scrollPosition;
	scrollbar_data.mouse_down      = true;
}
else if ( scrollbar_data.mouse_down )
{
	if ( scroll_container_data.contentDimensions.height > 0 )
	{
		Clay_Vector2 ratio = ( Clay_Vector2 ) {
			scroll_container_data.contentDimensions.width
				/ scroll_container_data.scrollContainerDimensions.width,
			scroll_container_data.contentDimensions.height
				/ scroll_container_data.scrollContainerDimensions.height,
		};
		if ( scroll_container_data.config.vertical )
		{
			scroll_container_data.scrollPosition->y =
				scrollbar_data.position_origin.y
				+ ( scrollbar_data.click_origin.y - mouse_position_y )
					  * ratio.y;
		}
		if ( scroll_container_data.config.horizontal )
		{
			scroll_container_data.scrollPosition->x =
				scrollbar_data.position_origin.x
				+ ( scrollbar_data.click_origin.x - mouse_position_X )
					  * ratio.x;
		}
	}
}

if ( arrow_key_down_pressed_this_frame )
{
	if ( scroll_container_data.contentDimensions.height > 0 )
	{
		scroll_container_data.scrollPosition->y =
			scroll_container_data.scrollPosition->y - 50;
	}
}
else if ( arrow_key_up_pressed_this_frame )
{
	if ( scroll_container_data.contentDimensions.height > 0 )
	{
		scroll_container_data.scrollPosition->y =
			scroll_container_data.scrollPosition->y + 50;
	}
}

Clay_UpdateScrollContainers( is_touch_down,
							 ( Clay_Vector2 ) { mouse_wheel_X, mouse_wheel_y },
							 delta_time );
bool is_mobile_screen = window_width < 750;

if ( debug_mode_enabled )
{
	is_mobile_screen  = window_width < 950;
	window_width     -= 400;
}
return CreateLayout( is_mobile_screen,
					 animation_lerp_value < 0 ? ( animation_lerp_value + 1 )
											  : ( 1 - animation_lerp_value ) );
}

// Dummy main() to please cmake - TODO get wasm working with cmake on this
// example
int main ( )
{
	return 0;
}