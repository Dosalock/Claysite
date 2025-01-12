#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "clay.h"
#include "configs.h"
#include "helper.h"

void HeaderButton ( char *string )
{
	CLAY( CLAY_RECTANGLE( {
			.color        = COLOR_ITEM,
			.cornerRadius = { 4, 4, 4, 4 }
    } ),
		  CLAY_LAYOUT( {
			.sizing = { CLAY_SIZING_FIT(  .min = 100 ), CLAY_SIZING_PERCENT( 1.75 ) },
			.childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
		  } ) )
	{
		CLAY_TEXT( CharPtrToClayString( string ), &btn_text_config );
	}
}

void BodgeMargin ( int left_gap,
				   int right_gap,
				   int top_gap,
				   int bottom_gap,
				   int function_index,
				   void ( *function_pointer )( int ) )
{
	CLAY(
	  Clay__AttachId( Clay__HashString( CLAY_STRING( "margin_rect_top" ),
										top_gap + function_index,
										top_gap + function_index ) ),
	  CLAY_LAYOUT( {
		.sizing = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_FIXED( top_gap ) }
    } ),
	  CLAY_RECTANGLE( { .color = COLOR_MARGIN } ) )
	{
	}

	CLAY( CLAY_LAYOUT(
	  { .sizing = C_EXPAND, .layoutDirection = CLAY_LEFT_TO_RIGHT } ) )
	{
		CLAY( Clay__AttachId( Clay__HashString( CLAY_STRING( "margin_rect_left" ),
												left_gap + function_index,
												left_gap + function_index ) ),
			  CLAY_LAYOUT( {
				.sizing = { CLAY_SIZING_FIXED( left_gap ),
                           CLAY_SIZING_GROW( 0 ) }
        } ),
			  CLAY_RECTANGLE( { .color = COLOR_MARGIN } ) ) 
		{
		}
		CLAY( CLAY_LAYOUT(
		  { .sizing = C_EXPAND, .layoutDirection = CLAY_TOP_TO_BOTTOM } ) )
		{
			function_pointer( function_index );
		}

		CLAY( Clay__AttachId( Clay__HashString( CLAY_STRING( "margin_rect_right" ),
												right_gap + function_index,
												right_gap + function_index ) ),
			  CLAY_LAYOUT( {
				.sizing = { CLAY_SIZING_FIXED( right_gap ),
                           CLAY_SIZING_GROW( 0 ) }
        } ),
			  CLAY_RECTANGLE( { .color = COLOR_MARGIN } ) )
		{
		}
	}

	CLAY( Clay__AttachId( Clay__HashString( CLAY_STRING( "margin_rect_bottom" ),
											bottom_gap + function_index,
											bottom_gap + function_index ) ),
		  CLAY_LAYOUT( {
			.sizing = { CLAY_SIZING_GROW( 0 ),
                       CLAY_SIZING_FIXED( bottom_gap ) }
    } ),
		  CLAY_RECTANGLE( { .color = COLOR_MARGIN } ) )
	{
	}
}

void SetInfoBody ( int index )
{
	CLAY(
	  CLAY_IDI( "set_information_bar", index ),
	  CLAY_RECTANGLE( {
		.color = COLOR_ITEM,
		// change this to 8888 when collapsed
		.cornerRadius  = { 8, 8, 0, 0 },
		.cursorPointer = true
    } ),
	  CLAY_LAYOUT( { .sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_FIXED( 50 ) },
					 .layoutDirection = CLAY_LEFT_TO_RIGHT,
					 .childAlignment  = { 0, CLAY_ALIGN_Y_CENTER },
					 .padding         = { 8, 8 },
					 .childGap        = 8 } ),

	  CLAY_BORDER( set_information_bar_border_config ) )
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
			  CLAY_LAYOUT( {
				.padding = { 10, 4 }
        } ),
			  CLAY_RECTANGLE( {
				.cornerRadius  = CLAY_CORNER_RADIUS( 4 ),
				.cursorPointer = true,
				.color = Clay_Hovered( ) ? COLOR_ITEM_HOVER : COLOR_ITEM,
			  } ),
			  CLAY_BORDER_OUTSIDE_RADIUS( 1, COLOR_CONTAINER_BORDER, 4 ) )
		{
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
			  CLAY_RECTANGLE( set_information_dropdown_rect_config ) )
		{
			CLAY_TEXT(
			  CLAY_STRING( impsum ),
			  CLAY_TEXT_CONFIG( set_information_dropdown_text_config ) );
		}
	}
}

void SetInfoBox ( int index )
{
	CLAY( CLAY_IDI( "set_information_wrapper", index ),
		  CLAY_LAYOUT( layout_config_set_container ) )
	{
		CLAY( CLAY_IDI( "set_information_container", index ),
			  CLAY_LAYOUT( {
				.sizing = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
				.layoutDirection = CLAY_TOP_TO_BOTTOM
        } ),
			  CLAY_RECTANGLE( { .color        = { 0, 0, 0, 64 },
								.cornerRadius = { 0, 11, 11, 11 } } ) )
		{
			BodgeMargin( 0, 5, 0, 5, index, &SetInfoBody );
		}
	}
}
#endif
