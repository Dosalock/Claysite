#ifndef __EVENTS_H__
#define __EVENTS_H__


#include "clay.h"
static int32_t cursorTextIndex = 0;

int32_t FindCursorPositionInText ( Clay_RenderCommand *renderCommand )
{
	Clay_Context *context = Clay_GetCurrentContext( );

	Clay_LayoutElementHashMapItem *hashMapItem = Clay__GetHashMapItem(
	  Clay__HashString( CLAY_STRING( "Text" ),
						0,
						Clay_GetElementId( CLAY_STRING( "TextBoxOuter" ) ).id )
		.id );
	if ( hashMapItem == &CLAY__LAYOUT_ELEMENT_HASH_MAP_ITEM_DEFAULT )
	{
		return -1;
	}
	int32_t characterIndex = 0;
	float currentLineY     = renderCommand->boundingBox.y;
	// loop through each wrapped line in the text
	for ( int32_t i = 0; i < hashMapItem->layoutElement->childrenOrTextContent
							   .textElementData->wrappedLines.length;
		  i++ )
	{
		Clay__WrappedTextLine wrappedLine =
		  hashMapItem->layoutElement->childrenOrTextContent.textElementData
			->wrappedLines.internalArray[i];
		// if the point is within this line in Y
		if ( context->pointerInfo.position.y > currentLineY
			 && context->pointerInfo.position.y
				  < ( currentLineY
					  + hashMapItem->layoutElement->dimensions.height
						  / hashMapItem->layoutElement->childrenOrTextContent
							  .textElementData->wrappedLines.length ) )
		{
			float xOffset = renderCommand->boundingBox.x;
			// loop through each character in the current line
			for ( int32_t c = 0; c < wrappedLine.line.length; c++ )
			{
				Clay_String letter = { .length = 1,
									   .chars  = &wrappedLine.line.chars[c] };

				float charWidth =
				  Clay__MeasureText(
					&letter,
					hashMapItem->layoutElement->elementConfigs.internalArray[0]
					  .config.textElementConfig )
					.width;
				xOffset += charWidth;
				if ( xOffset > context->pointerInfo.position.x )
				{
					return characterIndex
						   + c; // return the correct character index
				}
			}
			return characterIndex
				   + wrappedLine.line.length; // return the index after all
											  // characters in the line
		}
		characterIndex += wrappedLine.line.length;
		currentLineY   += hashMapItem->layoutElement->dimensions.height
						/ hashMapItem->layoutElement->childrenOrTextContent
							.textElementData->wrappedLines.length;
	}
	return -1;
}

void RenderCursor ( Clay_BoundingBox boundingBox,
					int32_t cursorIndex,
					Clay_TextElementConfig *config )
{
	float x                                    = 0;
	float y                                    = boundingBox.y;
	//Clay_Context *context                      = Clay_GetCurrentContext( );
	Clay_LayoutElementHashMapItem *hashMapItem = Clay__GetHashMapItem(
	  Clay__HashString( CLAY_STRING( "Text" ),
						0,
						Clay_GetElementId( CLAY_STRING( "TextBoxOuter" ) ).id )
		.id );
	if ( hashMapItem != &CLAY__LAYOUT_ELEMENT_HASH_MAP_ITEM_DEFAULT )
	{
		
		for ( int32_t i = 0;
			  i < hashMapItem->layoutElement->childrenOrTextContent
					.textElementData->wrappedLines.length;
			  i++ )
		{
			if ( cursorTextIndex
				 >= hashMapItem->layoutElement->childrenOrTextContent
					  .textElementData->wrappedLines.internalArray[i]
					  .line.length )
			{
				cursorTextIndex -=
				  hashMapItem->layoutElement->childrenOrTextContent
					.textElementData->wrappedLines.internalArray[i]
					.line.length;
				y += hashMapItem->layoutElement->dimensions.height
					 / hashMapItem->layoutElement->childrenOrTextContent
						 .textElementData->wrappedLines.length;
			}
			else
			{
				for ( int32_t c = 0; c < cursorTextIndex; c++ )
				{
					Clay_String letter = {
						.length = 1,
						.chars =
						  &( hashMapItem->layoutElement->childrenOrTextContent
							   .textElementData->wrappedLines.internalArray[i]
							   .line.chars[c] )
					};
					x += Clay__MeasureText( &letter, config ).width;
				}
				break;
			}
		}
		CLAY( CLAY_RECTANGLE( {
		  .color = { 255, 0, 255, 255 }
        } ) )
		{
            CLAY_FLOATING(
				{ .offset   = { .x = boundingBox.x + x, .y = y },
				  .expand   = { .width = 100, .height = 100 },
				  .zIndex   = 3,
				  .parentId = Clay_GetElementId(CLAY_STRING("main_background")).id } );
		}
	}
}

#endif