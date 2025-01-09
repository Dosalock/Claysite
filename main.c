
#define CLAY_EXTEND_CONFIG_RECTANGLE                                           \
	Clay_String link;                                                          \
	bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT  bool disablePointerEvents;
#define CLAY_IMPLEMENTATION
#include "clay.h"

const Clay_Color COLOR_BACKDROP   = ( Clay_Color ) { 15, 0, 40, 255 };
const Clay_Color COLOR_BACKGROUND = ( Clay_Color ) { 20, 0, 50, 255 };
const Clay_Color COLOR_ITEM       = ( Clay_Color ) { 60, 9, 108, 255 };
const Clay_Color COLOR_TEXT_1     = ( Clay_Color ) { 255, 158, 0, 255 };
const Clay_Sizing C_EXPAND =
  ( Clay_Sizing ) { CLAY_SIZING_GROW( ), CLAY_SIZING_GROW( ) };
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
			.color = COLOR_BACKDROP
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
					.childAlignment = {                   0, CLAY_ALIGN_Y_CENTER },
					.padding        = {                  16,                  32 },
					.childGap       = 8,
            } ) )
			{
				//Clay_Dimensions s = Clay__MeasureText("BASED C"}  );
				CLAY(
					CLAY_ID("button_object"),
				  	CLAY_RECTANGLE( 
					{
						.color = COLOR_ITEM,

					} 
					),
				  	CLAY_LAYOUT( 
					{ 
						.sizing = C_EXPAND,
						.childAlignment = { 0, CLAY_ALIGN_Y_CENTER },
					}
					) )
				{
						
					CLAY_TEXT( CLAY_STRING( "BASED C" ),
								CLAY_TEXT_CONFIG( {
									.fontSize  = 24,
									.fontId    = 2,
									.textColor = COLOR_TEXT_1,
								} ) );
				
				}
				CLAY( CLAY_RECTANGLE( {
				  .color = COLOR_ITEM,

				} ) )
				{
					CLAY_TEXT(
					  CLAY_STRING( "PLSHEADER2" ),
					  CLAY_TEXT_CONFIG( { .fontSize  = 24,
										  .fontId    = 2,
										  .textColor = COLOR_TEXT_1 } ) );
				}
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
					.color        = COLOR_BACKGROUND,
					.cornerRadius = { 8, 8, 8, 8 },
            } ),
				  CLAY_LAYOUT( {
					.sizing = { CLAY_SIZING_GROW( ), CLAY_SIZING_GROW( ) },
				  } ) )
			{
				CLAY(
				  CLAY_ID( "set_information_container" ),
				  CLAY_LAYOUT( {
					.layoutDirection = CLAY_TOP_TO_BOTTOM,
					.sizing = { CLAY_SIZING_FIXED( 400 ), CLAY_SIZING_GROW( ) },
					.childGap = 16,
					.padding  = {                       16,                  16 }
                } ) )
				{
					CLAY( CLAY_ID( "set_information_bar" ),
						  CLAY_RECTANGLE( {
							.color        = COLOR_ITEM,
							.cornerRadius = { 8, 8, 8, 8 },
                    } ),
						  CLAY_LAYOUT( {
							.sizing          = { CLAY_SIZING_GROW( ),
												 CLAY_SIZING_FIXED( 50 ) },
							.layoutDirection = CLAY_TOP_TO_BOTTOM,
						  } ) )
					{
					}
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

	Clay_UpdateScrollContainers( true,
								 ( Clay_Vector2 ) { mouseWheelX, mouseWheelY },
								 deltaTime );

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