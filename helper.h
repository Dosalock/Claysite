size_t strlen ( const char* str )
{
	const char* s;
	for ( s = str; *s; ++s )
		;
	return ( s - str );
}

Clay_String CharPtrToClayString ( char* string ) { 
	return ( Clay_String ) { strlen( string ), string };
}

typedef struct
{
	Clay_Vector2 click_origin;
	Clay_Vector2 position_origin;
	bool mouse_down;
} ScrollbarData;