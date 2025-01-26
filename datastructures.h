#ifndef _DATASTRUCTURES_H__
#define _DATASTRUCTURES_H__

typedef struct{
	float x;
	float y;
}Coordinate;


typedef struct{
	uint32_t head;
	uint32_t tail;
	Clay_TextElementConfig *text_config;
	Clay_ElementId *parent_id;
	union {
		Clay_String contents;
		Clay_String before_selection;
		Clay_String selection;
		Clay_String after_selection;
	};
}Textbox;
#endif