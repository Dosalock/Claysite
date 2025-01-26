/**------------------------------------------------------------------------
 * ?                                ABOUT
 * @author         :  Johan Karlsson
 * @email          :  j.ef.karlsson@gmail.com
 * @repo           :  Claysite
 * @createdOn      :  2025-01-15
 * @description    :  Object/widget creation | Buttons, boxes etc.
 *------------------------------------------------------------------------**/

#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "clay.h"
#include "configs.h"
#include "helper.h"

bool pressed_last_frame = false;
uint32_t input_index = 0;
uint32_t input_index_substring_length = 0;

Clay_RectangleElementConfig *test_ptr;
Clay_BorderElementConfig *test_border_ptr;
Textbox textbox = {};

void HeaderButton ( char *string )
{
	CLAY( CLAY_RECTANGLE( header_button_rect_config ),
		  CLAY_LAYOUT( header_button_layout_config ) )
	{
		CLAY_TEXT( CharPtrToClayString( string ), &btn_text_config );
	}
}

void SetInfoBody ( int index )
{
	CLAY( CLAY_IDI( "set_information_bar", index ),
		  CLAY_RECTANGLE( *test_ptr ),
		  CLAY_LAYOUT( set_information_bar_layout_config ),
		  CLAY_BORDER( *test_border_ptr ) )
	{
		// Left aligned and right aligned text with a spacer
		CLAY_TEXT( CLAY_STRING( "SET TEXT" ), &btn_text_config );
		CLAY( CLAY_LAYOUT( {
		  .sizing = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_FIT( ) }
        } ) )
		{
		}
		CLAY_TEXT( CLAY_STRING( "SET TEXT 2" ), &btn_text_config );

		CLAY( CLAY_IDI( "set_information_button", index ),
			  CLAY_LAYOUT( set_information_button_layout_config ),
			  CLAY_RECTANGLE( Clay_Hovered( )
								? set_information_button_hover_rect_config
								: set_information_button_rect_config ),
			  CLAY_BORDER_OUTSIDE_RADIUS( 1, COLOR_CONTAINER_BORDER, 4 ) )
		{
			// todo  this should probably not be a character
			CLAY_TEXT( CLAY_STRING( ">" ),
					   CLAY_TEXT_CONFIG( {
						 .textColor            = COLOR_TEXT_1,
						 .disablePointerEvents = true,
						 .fontId               = 2,
						 .fontSize             = 24,
					   } ) );
		}
	}

	if ( index % 2 == 0 )
	{
		// Set text block dropdown, box, text, and border
		CLAY( CLAY_IDI( "set_information_dropdown", index ),
			  CLAY_LAYOUT( set_information_dropdown_layout_open_config ),
			  CLAY_RECTANGLE( set_information_dropdown_rect_config ),
			  CLAY_TEXT(CLAY_STRING( "Testing string to see if this is even possible\0" ), CLAY_TEXT_CONFIG(set_information_dropdown_text_config)) )
		{
			// CLAY_TEXT(
			//   CLAY_STRING( impsum ),
			//   CLAY_TEXT_CONFIG( set_information_dropdown_text_config ) );
		}
	}
}

void SetInfoBox ( int index )
{
	CLAY( CLAY_IDI( "set_information_wrapper", index ),
		  CLAY_LAYOUT( set_information_wrapper_layout_config ) )
	{
		CLAY( CLAY_IDI( "set_information_container", index ),
			  CLAY_LAYOUT( set_information_container_layout_config ),
			  CLAY_BORDER( drop_shadow ) )
		{
			// BodgeMargin( 0, 5, 0, 5, index, &SetInfoBody );
			SetInfoBody( index );
			if (index == 2 )
			{
				// Clay_ElementData parent_data =
				// Clay_GetElementData(Clay_GetElementIdWithIndex(CLAY_STRING("set_information_dropdown"),
				// 2));


			

				CLAY( CLAY_RECTANGLE( {
						.color = { 255, 255, 255, 100 }
                } ),
					  CLAY_FLOATING( floating_element_test_config ) );
			}
		}
	}
}
#endif
