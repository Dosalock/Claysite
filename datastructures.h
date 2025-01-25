typedef struct{
	float x;
	float y;
}Coordinate;


typedef struct{
	int32_t head;
	int32_t tail;
	Clay_TextElementConfig *text_config;
	Clay_ElementId *parent_id;
	union {
		Clay_String contents;
		Clay_String before_selection;
		Clay_String selection;
		Clay_String after_selection;
	};
}Textbox;