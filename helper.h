#ifndef __HELPER_H__
#define __HELPER_H__
#ifdef CLAY_WASM
__attribute__(( import_module( "clay" ), import_name( "consoleLog" ) )) void
	js_consoleLog ( Clay_String* message );
#else
void ( *js_consoleLog )( Clay_String* message );
#endif

#include "datastructures.h"

float FloatModulo ( const float *value, const float *divisor )
{
	float local_value   = *value;
	float local_divisor = *divisor;

	while ( local_value > local_divisor )
	{
		local_value -= local_divisor;
	}
	return local_value;
}

// Note this is exposed to C through C linkage
void consoleLogC ( Clay_String message )
{
#ifdef CLAY_WASM
	js_consoleLog( &message );
#else
	if ( js_consoleLog )
	{
		js_consoleLog( &message );
	}
#endif
}

size_t strlen ( const char* str )
{
	const char* s;
	for ( s = str; *s; ++s )
		;
	return ( s - str );
}

Clay_String CharPtrToClayString ( char* string )
{
	return ( Clay_String ) { strlen( string ), string };
}

typedef struct
{
	Clay_Vector2 click_origin;
	Clay_Vector2 position_origin;
	bool mouse_down;
} ScrollbarData;

char* int_to_string ( int num, char* buffer, int* buffer_index )
{
	if ( num == 0 )
	{
		buffer[( *buffer_index )++] = '0';
		return buffer;
	}

	bool isNegative = false;
	if ( num < 0 && isNegative == false )
	{
		isNegative = true;
		num        = -num;
	}

	int temp[10]; // temporary array to store digits
	int i = 0;
	while ( num > 0 )
	{
		temp[i++]  = num % 10;
		num       /= 10;
	}

	if ( isNegative )
	{
		buffer[( *buffer_index )++] = '-';
	}

	for ( int j = i - 1; j >= 0; j-- )
	{
		buffer[( *buffer_index )++] = temp[j] + '0';
	}
	return buffer;
}

// Main float to string function
// Function to convert a float to a string in WASM memory
int float_to_string_wasm ( float f, char* buffer )
{
	int buffer_index = 0;
	bool isNegative  = false;

	// Handle sign
	if ( f < 0.0f && isNegative == false )
	{
		isNegative = true;
		f          = -f;
	}

	// Integer part
	int integerPart = ( int )f;
	int_to_string( integerPart, buffer, &buffer_index );

	// Decimal part
	float decimalPart = f - ( float )integerPart;
	if ( decimalPart > 0.0f )
	{
		buffer[buffer_index++] = '.';

		int precision = 6; // Number of decimal places - Adjust as needed
		for ( int i = 0; i < precision; i++ )
		{
			decimalPart            *= 10.0f;
			int digit               = ( int )decimalPart;
			buffer[buffer_index++]  = digit + '0';
			decimalPart            -= digit;
		}
	}

	// Null termination
	buffer[buffer_index] = '\0';
	return buffer_index; // Return the length for convenience
}

inline const char* ElementTypeToString ( Clay__ElementConfigType config )
{
	switch ( config )
	{
		case CLAY__ELEMENT_CONFIG_TYPE_NONE:
			return "None";
		case CLAY__ELEMENT_CONFIG_TYPE_RECTANGLE:
			return "Rectangle";
		case CLAY__ELEMENT_CONFIG_TYPE_BORDER_CONTAINER:
			return "Border";
		case CLAY__ELEMENT_CONFIG_TYPE_FLOATING_CONTAINER:
			return "Floating";
		case CLAY__ELEMENT_CONFIG_TYPE_SCROLL_CONTAINER:
			return "Scroll";
		case CLAY__ELEMENT_CONFIG_TYPE_IMAGE:
			return "Image";
		case CLAY__ELEMENT_CONFIG_TYPE_TEXT:
			return "Text";
		case CLAY__ELEMENT_CONFIG_TYPE_CUSTOM:
			return "Custom";
		default:
			return "ERR";
	}
}

Clay_TextElementConfig* GetTextElementConfig ( Clay_ElementId ID )
{
	Clay_LayoutElementHashMapItem* text_box_hash_map =
		Clay__GetHashMapItem( ID.id );
	return text_box_hash_map->layoutElement->elementConfigs.internalArray
		->config.textElementConfig;
}

/**
 * @brief Get the X and Y mulipliers for text highlighting based on mouse
 * posisition
 *
 * @param mouse_position_x - Mouse x position, usually retrieved from
 * UpdateDrawFrame
 * @param mouse_position_y - Mouse y position, usually retrieved from
 * UpdateDrawFrame
 * @param ID - Clay_ElementId of the parent element that houses the text
 *
 * @return Coordiante x and y as mulitpliers for the .offset in a Clay floating
 * element
 */
Coordinate GetMouseHighlightCoordinates ( float mouse_position_x,
										  float mouse_position_y,
										  Textbox textbox )
{
	Clay_ElementData box_data = Clay_GetElementData( *textbox.parent_id );

	Clay_Dimensions c = Clay__MeasureText(&textbox.selection, textbox.text_config);

	float normalized_mouse_x = ( mouse_position_x - box_data.boundingBox.x );
	float normalized_mouse_y = ( mouse_position_y - box_data.boundingBox.y );

	// Better rounding
	normalized_mouse_x -= (c.width / 2.0f);
	normalized_mouse_y -= (c.height / 2.0f);

	float indexed_mouse_x = normalized_mouse_x / ( c.width );
	float indexed_mouse_y = normalized_mouse_y / ( c.height );

	return ( Coordinate ) { .x = indexed_mouse_x, .y = indexed_mouse_y };
}
#endif