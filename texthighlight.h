#ifndef __TEXTHIGHLIGHT_H__
#define __TEXTHIGHLIGHT_H__


#include "clay.h"
#include "configs.h"
#include "datastructures.h"
#include "helper.h"
#include "objects.h"

void RenderHighlight ( Clay_ElementId parent_id,
					   uint32_t remote_index,
					   uint32_t remote_substring_length )
{
	char string[]    = "Testing string to see if this is even possible\0";
	char *string_ptr = string;
	uint32_t substring_length = remote_substring_length + 1;
	uint32_t index            = remote_index;
	uint32_t l_head           = index;
	uint32_t l_tail           = index + substring_length;
	/*
	WASM Says: BEFORE; SELECTION; AFTER index.html:356:29
	WASM Says: <empty string> index.html:356:29
	WASM Says: Testing string to index.html:356:29
	WASM Says: see if this is even possibl index.html:356:29
	*/
	consoleLogC( CLAY_STRING( "BEFORE;" ) );
	Clay_String before = { .chars = string_ptr, .length = l_head};
	consoleLogC( before );
	consoleLogC( CLAY_STRING( "SELECTION;" ) );
	Clay_String selection = { .chars  = ( string_ptr + l_head + 1 ),
							  .length = l_tail - l_head };
	consoleLogC( selection );
	consoleLogC( CLAY_STRING( "AFTER" ) );
	Clay_String after = { .chars  = ( string_ptr + l_tail ),
						  .length = 46 - l_tail };
	consoleLogC( after );

	textbox.contents    = ( Clay_String ) { .chars = string, .length = 46 };
	textbox.parent_id   = &parent_id;
	textbox.text_config = &set_information_dropdown_text_config;
	textbox.head        = l_head;
	textbox.tail        = l_tail;
	textbox.before_selection = before;
	textbox.selection        = selection;
	textbox.after_selection  = after;


	// Clay_Dimensions highlight_dimensions =
	// 	Clay__MeasureText( &textbox.selection,
	// 					   &set_information_dropdown_text_config );
	Clay_Dimensions one_character =
		Clay__MeasureText( &CLAY_STRING( "a" ),
						   &set_information_dropdown_text_config );

	Clay_LayoutElementHashMapItem *parent_container =
		Clay__GetHashMapItem( parent_id.id );

	float one_character_width  = one_character.width / 2.0f;
	float one_character_height = one_character.height / 2.0f;

	// clang-format off
	floating_element_test_config = ( Clay_FloatingElementConfig ) {
		.parentId = parent_id.id,
		.attachment = {.element = CLAY_ATTACH_POINT_LEFT_TOP, .parent = CLAY_ATTACH_POINT_LEFT_TOP},
		.expand = { 
			.width  = ( one_character_width * substring_length ),
			.height = ( one_character_height ),
		},
		.zIndex     = 3,
		
		.pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_PASSTHROUGH,
		.offset = { 
			.x = (float)parent_container->layoutElement->layoutConfig->padding.left
				 + (one_character_width) 
				 + ((one_character_width) * ((float)input_index)*2.0f) ,
			.y = textbox.text_config->fontSize   
		}
		// clang-format on
	};
}
#endif