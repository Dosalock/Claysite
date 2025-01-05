
#define CLAY_EXTEND_CONFIG_RECTANGLE                                           \
	Clay_String link;                                                          \
	bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT  bool disablePointerEvents;
#define CLAY_IMPLEMENTATION
#include "clay.h"

double window_width = 1024, window_height = 768;
float animationLerpValue       = -1.0f;
float modelPageOneZRotation    = 0;
uint32_t ACTIVE_RENDERER_INDEX = 0;
bool debugModeEnabled          = false;

typedef struct
{
	Clay_Vector2 clickOrigin;
	Clay_Vector2 positionOrigin;
	bool mouseDown;
} ScrollbarData;

ScrollbarData scrollbarData = ( ScrollbarData ) { };

Clay_RenderCommandArray CreateLayout ( bool mobileScreen, float lerpValue )
{
	Clay_BeginLayout( );
	// MAKE UI IN HERE
	CLAY( CLAY_ID( "outer_container" ),
		  CLAY_RECTANGLE( {
			.color = { 43, 41, 51, 255 }
    } ),
		  CLAY_LAYOUT(
			{ .layoutDirection = CLAY_TOP_TO_BOTTOM,
			  .sizing   = { .width = window_width, .height = window_height },
			  .padding  = { 16, 16 },
			  .childGap = 8 } ) )
	{
		// Children

		CLAY( CLAY_ID( "header_bar" ),
			  CLAY_RECTANGLE( {
				.color        = { 90, 90, 90, 255 },
				.cornerRadius = {  8,  8,  8,   8 }
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
					.childAlignment = {                   0, CLAY_ALIGN_Y_CENTER },
					.padding        = {                  16,                  32 },
					.childGap       = 8
            } ) )
			{
				CLAY_TEXT( CLAY_STRING( "BASED C" ),
						   CLAY_TEXT_CONFIG( {
							 .fontSize  = 24,
							 .fontId    = 2,
							 .textColor = { 200, 200, 200, 255 }
                } ) );
				CLAY_TEXT( CLAY_STRING( "PLSHEADER2" ),
						   CLAY_TEXT_CONFIG( {
							 .fontSize  = 24,
							 .fontId    = 2,
							 .textColor = { 200, 200, 200, 255 }
                } ) );
			}
		}

		CLAY( CLAY_ID( "main_content" ),
			  CLAY_LAYOUT( {
				.sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_GROW( ) },
        } ) )
		{
			CLAY( CLAY_ID( "main_background" ),
				  CLAY_RECTANGLE( {
					.color        = { 155 * debugModeEnabled, 128, 0, 255 },
					.cornerRadius = {                      8,   8, 8,   8 },
            } ),
				  CLAY_LAYOUT( {
					.sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_GROW( ) },
				  } ) )
			{
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
	Clay_SetLayoutDimensions( ( Clay_Dimensions ) { width, height } );
	if ( deltaTime == deltaTime )
	{ // NaN propagation can cause pain here
		animationLerpValue += deltaTime;
		if ( animationLerpValue > 1 )
		{
			animationLerpValue -= 2;
		}
	}


	Clay_SetPointerState( ( Clay_Vector2 ) { mousePositionX, mousePositionY },
						  isMouseDown || isTouchDown );

	Clay_UpdateScrollContainers(true, (Clay_Vector2) { mouseWheelX, mouseWheelY }, deltaTime);

	if ( dKeyPressedThisFrame )
	{
		debugModeEnabled = !debugModeEnabled;

		Clay_SetDebugModeEnabled( debugModeEnabled );
	}
	Clay__debugViewHighlightColor = ( Clay_Color ) { 105, 210, 231, 120 };


	if ( !isMouseDown )
	{
		scrollbarData.mouseDown = false;
	}

	if ( isMouseDown && !scrollbarData.mouseDown
		 && Clay_PointerOver(
		   Clay_GetElementId( CLAY_STRING( "ScrollBar" ) ) ) )
	{
		Clay_ScrollContainerData scrollContainerData =
		  Clay_GetScrollContainerData(
			Clay_GetElementId( CLAY_STRING( "OuterScrollContainer" ) ) );
		scrollbarData.clickOrigin =
		  ( Clay_Vector2 ) { mousePositionX, mousePositionY };
		scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
		scrollbarData.mouseDown      = true;
	}
	else if ( scrollbarData.mouseDown )
	{
		Clay_ScrollContainerData scrollContainerData =
		  Clay_GetScrollContainerData(
			Clay_GetElementId( CLAY_STRING( "OuterScrollContainer" ) ) );
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
		Clay_ScrollContainerData scrollContainerData =
		  Clay_GetScrollContainerData(
			Clay_GetElementId( CLAY_STRING( "OuterScrollContainer" ) ) );
		if ( scrollContainerData.contentDimensions.height > 0 )
		{
			scrollContainerData.scrollPosition->y =
			  scrollContainerData.scrollPosition->y - 50;
		}
	}
	else if ( arrowKeyUpPressedThisFrame )
	{
		Clay_ScrollContainerData scrollContainerData =
		  Clay_GetScrollContainerData(
			Clay_GetElementId( CLAY_STRING( "OuterScrollContainer" ) ) );
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
	if ( debugModeEnabled )
	{
		isMobileScreen = window_width < 950;
	}
	return CreateLayout( isMobileScreen,
						 animationLerpValue < 0 ? ( animationLerpValue + 1 )
												: ( 1 - animationLerpValue ) );
}

// Dummy main() to please cmake - TODO get wasm working with cmake on this
// example
int main ( )
{
	return 0;
}