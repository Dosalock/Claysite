
#define CLAY_EXTEND_CONFIG_RECTANGLE                                                               \
	Clay_String link;                                                                              \
	bool cursorPointer;
#define CLAY_EXTEND_CONFIG_IMAGE Clay_String sourceURL;
#define CLAY_EXTEND_CONFIG_TEXT bool disablePointerEvents;
#define CLAY_IMPLEMENTATION
#include "clay.h"
#include "objects.h"

double window_width = 1024, window_height = 768;
float animationLerpValue = -1.0f;
float modelPageOneZRotation = 0;
uint32_t ACTIVE_RENDERER_INDEX = 0;
bool debugModeEnabled = false;
Clay_Color COLOR_SET_CONTAINER_HOVER = COLOR_ITEM;

typedef struct
{
	Clay_Vector2 clickOrigin;
	Clay_Vector2 positionOrigin;
	bool mouseDown;
} ScrollbarData;

ScrollbarData scrollbarData = (ScrollbarData){};

Clay_RenderCommandArray CreateLayout(bool mobileScreen, float lerpValue)
{
	Clay_BeginLayout();
	// MAKE UI IN HERE

	CLAY(CLAY_ID("outer_container"),
		 CLAY_RECTANGLE({.color = COLOR_BACKDROP}),
		 CLAY_LAYOUT({.layoutDirection = CLAY_TOP_TO_BOTTOM,
					  .sizing = {.width = window_width, .height = window_height},
					  .padding = {16, 16},
					  .childGap = 8}))
	{
		// Children

		CLAY(CLAY_ID("header_bar"),
			 CLAY_RECTANGLE({.color = COLOR_BACKGROUND, .cornerRadius = {8, 8, 8, 8}}),
			 CLAY_LAYOUT({.sizing = {
							  .width = CLAY_SIZING_GROW(),
							  .height = CLAY_SIZING_FIXED(90),
						  }}))
		{
			CLAY(CLAY_ID("button_container"),
				 CLAY_LAYOUT({
					 .layoutDirection = CLAY_LEFT_TO_RIGHT,
					 .sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_GROW()},
					 .childAlignment = {0, CLAY_ALIGN_Y_CENTER},
					 .padding = {16, 32},
					 .childGap = 8,
				 }))
			{
				DosaButton("test");

				DosaButton("test2asdf");
			}
		}

		CLAY(CLAY_ID("main_content"),
			 CLAY_LAYOUT({
				 .sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_GROW()},
				 .childGap = 8,
			 }))
		{
			CLAY(CLAY_ID("left_sidebar"),
				 CLAY_RECTANGLE({
					 .color = COLOR_BACKGROUND,
					 .cornerRadius = {8, 8, 8, 8},
				 }),
				 CLAY_LAYOUT({.sizing = {CLAY_SIZING_FIXED(200), CLAY_SIZING_GROW()}}))
			{ }
			CLAY(CLAY_ID("main_background"),
				 CLAY_RECTANGLE({
					 .color = COLOR_BACKGROUND,
					 .cornerRadius = {8, 8, 8, 8},
				 }),
				 CLAY_LAYOUT({
					 .sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_GROW()},
				 }))
			{
				CLAY(CLAY_ID("set_information_container"), CLAY_LAYOUT(set_container_config))
				{
					CLAY(CLAY_ID("set_information_bar"),
						 CLAY_RECTANGLE({.color = COLOR_SET_CONTAINER_HOVER,
										 .cornerRadius = {8, 8, 8, 8},
										 .cursorPointer = true}),
						 CLAY_LAYOUT({.sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(50)},
									  .layoutDirection = CLAY_LEFT_TO_RIGHT,
									  .childAlignment = {0, CLAY_ALIGN_Y_CENTER},
									  .padding = {8, 8}}),
						 CLAY_BORDER_OUTSIDE_RADIUS(2, COLOR_CONTAINER_BORDER, 8))
					{
						// Left aligned and right aligned text with a spacer
						//CLAY_TEXT(CLAY_STRING("SET TEXT"), &btn_text_config);
						CLAY(CLAY_LAYOUT({.sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_FIT()}})) { }
						//CLAY_TEXT(CLAY_STRING("SET TEXT 2"), &btn_text_config);
						CLAY(CLAY_LAYOUT({.padding = {8, 4}}),
							 CLAY_RECTANGLE({
								 .cornerRadius = CLAY_CORNER_RADIUS(4),
								 .cursorPointer = true,
								 .link = CLAY_STRING("https://discord.gg/b4FTWkxdvT"),
								 .color = Clay_Hovered() ? COLOR_ITEM : COLOR_ITEM_HOVER,
							 }),
							 CLAY_BORDER_OUTSIDE_RADIUS(1, COLOR_CONTAINER_BORDER, 4))
						{
							CLAY_TEXT(CLAY_STRING("Discord"),
									  CLAY_TEXT_CONFIG({.disablePointerEvents = true,
														.fontId = 2,
														.fontSize = 24,
														.textColor = {61, 26, 5, 255}}));
						}
					}

					CLAY(CLAY_ID("set_information_dropdown"),
						 CLAY_LAYOUT({.sizing = {CLAY_SIZING_GROW(), CLAY_SIZING_FIXED(100)}}),
						 CLAY_RECTANGLE({.color = {200, 200, 200, 255}}))
					{ }
				}
			}
		}
	}

	return Clay_EndLayout();
}

CLAY_WASM_EXPORT("UpdateDrawFrame")

Clay_RenderCommandArray UpdateDrawFrame(float width,
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
										float deltaTime)
{
	window_width = width;
	window_height = height;

	Clay_SetLayoutDimensions((Clay_Dimensions){width, height});
	Clay_UpdateScrollContainers(true, (Clay_Vector2){mouseWheelX, mouseWheelY}, deltaTime);
	Clay_SetPointerState((Clay_Vector2){mousePositionX, mousePositionY},
						 isMouseDown || isTouchDown);
	Clay_ScrollContainerData scrollContainerData =
		Clay_GetScrollContainerData(Clay_GetElementId(CLAY_STRING("OuterScrollContainer")));
	Clay_LayoutElementHashMapItem* perfPage =
		Clay__GetHashMapItem(Clay_GetElementId(CLAY_STRING("PerformancePageOuter")).id);

	if(deltaTime == deltaTime)
	{ // NaN propagation can cause pain here
		animationLerpValue += deltaTime;
		if(animationLerpValue > 1)
		{
			animationLerpValue -= 2;
		}
	}
	if(Clay_PointerOver(Clay_GetElementId(CLAY_STRING("set_information_bar"))))
	{
		COLOR_SET_CONTAINER_HOVER = COLOR_ITEM_HOVER;
	}
	else
	{
		COLOR_SET_CONTAINER_HOVER = COLOR_ITEM;
	}

	if(dKeyPressedThisFrame)
	{
		debugModeEnabled = !debugModeEnabled;

		Clay_SetDebugModeEnabled(debugModeEnabled);
	}
	Clay__debugViewHighlightColor = (Clay_Color){105, 210, 231, 120};

	if(!isMouseDown)
	{
		scrollbarData.mouseDown = false;
	}

	if(isMouseDown && !scrollbarData.mouseDown &&
	   Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ScrollBar"))))
	{
		scrollbarData.clickOrigin = (Clay_Vector2){mousePositionX, mousePositionY};
		scrollbarData.positionOrigin = *scrollContainerData.scrollPosition;
		scrollbarData.mouseDown = true;
	}
	else if(scrollbarData.mouseDown)
	{
		if(scrollContainerData.contentDimensions.height > 0)
		{
			Clay_Vector2 ratio = (Clay_Vector2){
				scrollContainerData.contentDimensions.width /
					scrollContainerData.scrollContainerDimensions.width,
				scrollContainerData.contentDimensions.height /
					scrollContainerData.scrollContainerDimensions.height,
			};
			if(scrollContainerData.config.vertical)
			{
				scrollContainerData.scrollPosition->y =
					scrollbarData.positionOrigin.y +
					(scrollbarData.clickOrigin.y - mousePositionY) * ratio.y;
			}
			if(scrollContainerData.config.horizontal)
			{
				scrollContainerData.scrollPosition->x =
					scrollbarData.positionOrigin.x +
					(scrollbarData.clickOrigin.x - mousePositionX) * ratio.x;
			}
		}
	}

	if(arrowKeyDownPressedThisFrame)
	{
		if(scrollContainerData.contentDimensions.height > 0)
		{
			scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y - 50;
		}
	}
	else if(arrowKeyUpPressedThisFrame)
	{
		if(scrollContainerData.contentDimensions.height > 0)
		{
			scrollContainerData.scrollPosition->y = scrollContainerData.scrollPosition->y + 50;
		}
	}

	Clay_UpdateScrollContainers(isTouchDown, (Clay_Vector2){mouseWheelX, mouseWheelY}, deltaTime);
	bool isMobileScreen = window_width < 750;

	if(debugModeEnabled)
	{
		isMobileScreen = window_width < 950;
		window_width -= 400;
	}
	return CreateLayout(isMobileScreen,
						animationLerpValue < 0 ? (animationLerpValue + 1)
											   : (1 - animationLerpValue));
}

// Dummy main() to please cmake - TODO get wasm working with cmake on this
// example
int main()
{
	return 0;
}