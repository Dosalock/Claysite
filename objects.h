#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "clay.h"
#include "configs.h"
#include "helper.h"

void HeaderButton ( char* string )
{
	CLAY( CLAY_RECTANGLE( {
			.color        = COLOR_ITEM,
			.cornerRadius = { 4, 4, 4, 4 }
    } ),
		  CLAY_LAYOUT( {
			.sizing         = { CLAY_SIZING_FIT(  ),
								CLAY_SIZING_PERCENT( 1.75 ) },
			.childAlignment = { CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER },
		  } ) )
	{
		CLAY_TEXT( CharPtrToClayString( string ), &btn_text_config );
	}
}

void SetInfoBox ( int index )
{
	CLAY( CLAY_IDI( "set_information_container", index ),
		  CLAY_LAYOUT( set_container_config ) )
	{
		CLAY( CLAY_IDI( "set_information_bar", index ),
			  CLAY_RECTANGLE( {
				.color = COLOR_ITEM,
				// change this to 8888 when collapsed
				.cornerRadius  = { 8, 8, 0, 0 },
				.cursorPointer = true
        } ),
			  CLAY_LAYOUT(
				{ .sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_FIXED( 50 ) },
				  .layoutDirection = CLAY_LEFT_TO_RIGHT,
				  .childAlignment  = { 0, CLAY_ALIGN_Y_CENTER },
				  .padding         = { 8, 8 },
				  .childGap        = 8 } ),
			  CLAY_BORDER_OUTSIDE( { 2, COLOR_CONTAINER_BORDER } ) )
		{
			// Left aligned and right aligned text with a spacer
			CLAY_TEXT( CLAY_STRING( "SET TEXT" ), &btn_text_config );
			CLAY( CLAY_LAYOUT( {
			  .sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_FIT( ) }
            } ) )
			{
			}
			CLAY_TEXT( CLAY_STRING( "SET TEXT 2" ), &btn_text_config );

			CLAY( CLAY_LAYOUT( {
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


		// Set text block dropdown, box, text, and border
		CLAY( CLAY_IDI( "set_information_dropdown", index ),
			  CLAY_LAYOUT( {
				.sizing  = { CLAY_SIZING_FIT( ), CLAY_SIZING_FIT( ) },
				.padding = {                  8,                  8 }
        } ),
			  CLAY_RECTANGLE( {
				.color        = { 200, 200, 200, 255 },
				.cornerRadius = { 0, 0, 8, 8 },
			  } ),
			  CLAY_BORDER_OUTSIDE( { 1, COLOR_CONTAINER_BORDER } ) )
		{
			CLAY_TEXT( CLAY_STRING( impsum ),
					   CLAY_TEXT_CONFIG( {
						 .fontId    = 2,
						 .fontSize  = 18,
						 .textColor = { 0, 0, 0, 255 }
            } ) );
		}
	}
}
#endif
