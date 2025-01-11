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