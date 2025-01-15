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
	bool cursorPointer;
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
#include "objects.h"


/*-------------------------------- Globals ------------------------------*/

bool debug_mode_enabled = false;
double window_width = 1024, window_height = 768;
float animation_lerp_value     = -1.0f;
ScrollbarData scrollbarData    = ( ScrollbarData ) { };
uint32_t ACTIVE_RENDERER_INDEX = 0;

typedef struct
{
	Clay_Vector2 clickOrigin;
	Clay_Vector2 positionOrigin;
	bool mouseDown;
} ScrollbarData;

/*-------------------------------- Functions ------------------------------*/

Clay_RenderCommandArray CreateLayout ( bool mobileScreen, float lerpValue )
{
	Clay_BeginLayout( );
	// MAKE UI IN HERE

	CLAY(
	  CLAY_ID( "outer_container" ),
	  CLAY_RECTANGLE( {
		.color = COLOR_BACKDROP
    } ),
	  CLAY_LAYOUT( { .layoutDirection = CLAY_TOP_TO_BOTTOM,
					 .sizing = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
					 .padding  = CLAY_PADDING_ALL( 16 ),
					 .childGap = 8 } ) )
	{
		// Children

		CLAY( CLAY_ID( "header_bar" ),
			  CLAY_RECTANGLE( {
				.color        = COLOR_BACKGROUND,
				.cornerRadius = { 8, 8, 8, 8 }
        } ),
			  CLAY_LAYOUT( { .sizing = {
							   .width  = CLAY_SIZING_GROW( ),
							   .height = CLAY_SIZING_FIXED( 90 ),
							 } } ) )
		{
			CLAY( CLAY_ID( "button_container" ),
				  CLAY_LAYOUT( {
					.layoutDirection = CLAY_LEFT_TO_RIGHT,
					.sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_GROW( ) },
					.childAlignment = { 0, CLAY_ALIGN_Y_CENTER },
					.padding        = { 16, 16, 32, 32 },
					.childGap       = 8,
            } ) )
			{
				HeaderButton( "test" );

				HeaderButton( "test2asdf" );
			}
		}

		CLAY( CLAY_ID( "main_content" ),
			  CLAY_LAYOUT( {
				.sizing   = { CLAY_SIZING_GROW( ), CLAY_SIZING_GROW( ) },
				.childGap = 8,
        } ) )
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
				  CLAY_RECTANGLE( {
					.color        = { 40, 1, 60, 255 },
					.cornerRadius = {  8, 8,  8,   8 },
            } ),
				  CLAY_LAYOUT( {
					.sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_FIT( ) },
					.layoutDirection = CLAY_TOP_TO_BOTTOM,
				  } ) )
			{
				CLAY(
				  CLAY_ID( "OuterScrollContainer" ),
				  CLAY_LAYOUT( {
					.sizing = { CLAY_SIZING_GROW( 0 ), CLAY_SIZING_GROW( 0 ) },
					.layoutDirection = CLAY_TOP_TO_BOTTOM
                } ),
				  CLAY_SCROLL( { .vertical = true } )
				  // CLAY_BORDER( { .betweenChildren = { 2, {255,255,255,255} }
				  // } )
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

Clay_RenderCommandArray UpdateDrawFrame ( float width,
										  float height,
										  float mouseWheelX,
										  float mouseWheelY,
										  float mousePositionX,
										  float mousePositionY,
										  bool isTouchDown,
										  bool isMouseDown,
										  bool arrowKeyDownPressedThisFrame,
										  bool arrowKeyUpPressedThisFrame,
										  bool dKeyPressedThisFrame,
										  float deltaTime )
{
	window_width  = width;
	window_height = height;
	Clay_SetCullingEnabled( ACTIVE_RENDERER_INDEX == 1 );
	Clay_SetExternalScrollHandlingEnabled( ACTIVE_RENDERER_INDEX == 0 );

	Clay_SetLayoutDimensions( ( Clay_Dimensions ) { width, height } );

	Clay_SetPointerState( ( Clay_Vector2 ) { mousePositionX, mousePositionY },
						  isMouseDown || isTouchDown );
	Clay_ScrollContainerData scrollContainerData = Clay_GetScrollContainerData(
	  Clay_GetElementId( CLAY_STRING( "OuterScrollContainer" ) ) );

	if ( deltaTime == deltaTime )
	{ // NaN propagation can cause pain here
		animation_lerp_value += deltaTime;
		if ( animation_lerp_value > 1 )
		{
			animation_lerp_value -= 2;
		}
	}


	if ( dKeyPressedThisFrame )
	{
		debug_mode_enabled = !debug_mode_enabled;

		Clay_SetDebugModeEnabled( debug_mode_enabled );
	}
	Clay__debugViewHighlightColor = ( Clay_Color ) { 105, 210, 231, 120 };

	if ( !isMouseDown )
	{
		scrollbarData.mouseDown = false;
	}
	if ( isMouseDown
		 && Clay_PointerOver(
		   Clay_GetElementIdWithIndex( CLAY_STRING( "set_information_button" ),
									   1 ) ) )
	{
	}

	if ( isMouseDown && !scrollbarData.mouseDown
		 && Clay_PointerOver(
		   Clay_GetElementId( CLAY_STRING( "ScrollBar" ) ) ) )
	{
		scrollbarData.clickOrigin =
		  ( Clay_Vector2 ) { mousePositionX, mousePositionY };
		scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
		scrollbarData.mouseDown      = true;
	}
	else if ( scrollbarData.mouseDown )
	{
		if ( scrollContainerData.contentDimensions.height > 0 )
		{
			Clay_Vector2 ratio = ( Clay_Vector2 ) {
				scrollContainerData.contentDimensions.width
				  / scrollContainerData.scrollContainerDimensions.width,
				scrollContainerData.contentDimensions.height
				  / scrollContainerData.scrollContainerDimensions.height,
			};
			if ( scrollContainerData.config.vertical )
			{
				scrollContainerData.scrollPosition->y =
				  scrollbarData.positionOrigin.y
				  + ( scrollbarData.clickOrigin.y - mousePositionY ) * ratio.y;
			}
			if ( scrollContainerData.config.horizontal )
			{
				scrollContainerData.scrollPosition->x =
				  scrollbarData.positionOrigin.x
				  + ( scrollbarData.clickOrigin.x - mousePositionX ) * ratio.x;
			}
		}
	}

	if ( arrowKeyDownPressedThisFrame )
	{
		if ( scrollContainerData.contentDimensions.height > 0 )
		{
			scrollContainerData.scrollPosition->y =
			  scrollContainerData.scrollPosition->y - 50;
		}
	}
	else if ( arrowKeyUpPressedThisFrame )
	{
		if ( scrollContainerData.contentDimensions.height > 0 )
		{
			scrollContainerData.scrollPosition->y =
			  scrollContainerData.scrollPosition->y + 50;
		}
	}

	Clay_UpdateScrollContainers( isTouchDown,
								 ( Clay_Vector2 ) { mouseWheelX, mouseWheelY },
								 deltaTime );
	bool isMobileScreen = window_width < 750;

	if ( debug_mode_enabled )
	{
		isMobileScreen  = window_width < 950;
		window_width   -= 400;
	}
	return CreateLayout( isMobileScreen,
						 animation_lerp_value < 0
						   ? ( animation_lerp_value + 1 )
						   : ( 1 - animation_lerp_value ) );
}

// Dummy main() to please cmake - TODO get wasm working with cmake on this
// example
int main ( )
{
	return 0;
}