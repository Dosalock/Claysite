#ifndef __OBJECTS_H__
#define __OBJECTS_H__

#include "clay.h"
#include "configs.h"
#include "helper.h"

void DosaButton(char* string)
{
	Clay_String btn_title = (Clay_String){strlen(string), string};

	CLAY(CLAY_RECTANGLE({.color = COLOR_ITEM, .cornerRadius = {4, 4, 4, 4}}),
		 CLAY_LAYOUT({
			 .sizing = {CLAY_SIZING_FIT({.min = 128}), CLAY_SIZING_PERCENT(1.75)},
			 .childAlignment = {CLAY_ALIGN_X_CENTER, CLAY_ALIGN_Y_CENTER},
		 }))
	{
		CLAY_TEXT(btn_title, &btn_text_config);
	}
}

#endif
