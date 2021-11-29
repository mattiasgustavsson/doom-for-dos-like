#include "dos.h"

#include <stdarg.h>
int dosprint( const char* format, ... );
int dosprintv( const char* format, va_list args );

#ifdef __wasm__
#pragma clang diagnostic ignored "-Wunsequenced"
#pragma clang diagnostic ignored "-Wimplicit-int"
#pragma clang diagnostic ignored "-Wpointer-sign"
#pragma clang diagnostic ignored "-Wlogical-not-parentheses"
#pragma clang diagnostic ignored "-Wabsolute-value"
#endif

#pragma warning( disable: 4113 )
#pragma warning( disable: 4311 )
#pragma warning( disable: 4047 )
#pragma warning( disable: 4024 )
#pragma warning( disable: 4312 )
#pragma warning( disable: 4020 )
#pragma warning( disable: 4700 )
#pragma warning( disable: 4133 )
#pragma warning( disable: 4142 )

#ifdef _WIN32
#define strcasecmp stricmp
#define strncasecmp strnicmp
#else
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#endif

#define CONCAT_IMPL( x, y ) x##y
#define CONCAT( x, y ) CONCAT_IMPL( x, y )
#define rcsid CONCAT( rcsid, __COUNTER__ )

#include <stdio.h>

#define printf(x, ...) dosprint( x, ##__VA_ARGS__)
#define fprintf(y,x, ...) dosprint( x,##__VA_ARGS__)
#define vfprintf(y,x,a) dosprintv( x,a)
int doom_access( char const* _FileName, int _AccessMode ) {
    FILE* f = fopen( _FileName, "rb" );
    if( f ) {
        fclose(f);
        return 0;
    }
    return 1;
}

#define mousex doom_mousex
#define mousey doom_mousey
#define open doom_open
#define close doom_close
#define access doom_access
#include "doom/unistd.h"
#include "doom/am_map.c"
#include "doom/doomdef.c"
#include "doom/doomstat.c"
#include "doom/dstrings.c"
#include "doom/d_items.c"
#include "doom/d_main.c"
#include "doom/d_net.c"
#include "doom/f_finale.c"
#include "doom/f_wipe.c"
#include "doom/g_game.c"
#include "doom/hu_lib.c"
#include "doom/hu_stuff.c"
#include "doom/info.c"
#include "doom/i_main.c"
#include "doom/i_sound.c"
#include "doom/i_system.c"
#include "doom/i_video.c"
#include "doom/m_argv.c"
#include "doom/m_bbox.c"
#include "doom/m_cheat.c"
#include "doom/m_fixed.c"
#include "doom/m_random.c"
#include "doom/m_swap.c"
#include "doom/p_ceilng.c"
#include "doom/p_doors.c"
#include "doom/p_enemy.c"
#include "doom/p_floor.c"
#include "doom/p_inter.c"
#include "doom/p_lights.c"
#include "doom/p_map.c"
#include "doom/p_maputl.c"
#include "doom/p_mobj.c"
#include "doom/p_plats.c"
#include "doom/p_pspr.c"
#include "doom/p_saveg.c"
#include "doom/p_setup.c"
#include "doom/p_sight.c"
#include "doom/p_spec.c"
#include "doom/p_switch.c"
#include "doom/p_telept.c"
#include "doom/p_tick.c"
#include "doom/p_user.c"
#include "doom/r_bsp.c"
#include "doom/r_data.c"
#include "doom/r_draw.c"
#include "doom/r_main.c"
#include "doom/r_plane.c"
#include "doom/r_segs.c"
#include "doom/r_sky.c"
#include "doom/r_things.c"
#include "doom/sounds.c"
#undef BG
#include "doom/st_lib.c"
#include "doom/st_stuff.c"
#define channels xchannels
#include "doom/s_sound.c"
#undef channels
#include "doom/tables.c"
#include "doom/v_video.c"
#define anim_t wi_anim_t
#define anims wi_anims
#define time wi_time
#include "doom/wi_stuff.c"
#undef anims
#undef anim_t
#undef time
#include "doom/z_zone.c"

#undef open
#undef close
#undef mousex
#undef mousey

#include "doom/m_menu.c"
#include "doom/m_misc.c"
#define strupr xstrupr
#include "doom/w_wad.c"
#undef strupr

#include "doom/i_net.c"

#undef printf
#undef fprintf
#undef vfprintf
#undef doom_access

char* textline = NULL;
size_t textline_capacity = 0;
unsigned int attribute = 0x70;

int dosprint( const char* format, ... ) {
    if( screenwidth() != 80 ) return 0;
    va_list args;
	va_start( args, format );
    int res = dosprintv( format, args );
    va_end(args);
    return res;
	}
	

int dosprintv( const char* format, va_list args ) {
    if( screenwidth() != 80 ) return 0;
    if( !textline ) {
        textline_capacity = 256;
	    textline = (char*) malloc( textline_capacity );
        for( int i = 0; i < 50; ++i ) waitvbl();
    }

	size_t len = vsnprintf( textline, textline_capacity - 1, format, args );
	while( len < 0 || len >= textline_capacity ) {
		textline_capacity *= 2;
		textline = (char*) realloc( textline, textline_capacity );
		len = vsnprintf( textline, textline_capacity - 1, format, args );
	}
	
	const char* str = textline;
	while( *str ) {
		if( wherex() >= screenwidth() || *str == '\n' )  { 
            waitvbl();
			gotoxy( 0, wherey() +  1 ); 
		}
		while( wherey() >= screenheight() ) {
			memmove( ((unsigned short*)screenbuffer()), ((unsigned short*)screenbuffer()) + screenwidth(), screenwidth() * ( screenheight() - 1 ) * sizeof( unsigned short ) );
			memset( ((unsigned short*)screenbuffer()) + screenwidth() * ( screenheight() - 1 ), 0, screenwidth() * sizeof( unsigned short ) );
			gotoxy( wherex(), wherey() - 1 );
		}
		if( (unsigned) *str >= ' ' ) {
			((unsigned short*)screenbuffer())[ wherex() + screenwidth() * wherey() ] = ( ( attribute & 0xf0 ) << 4 ) | ( ( attribute & 0x0f ) << 12 ) | (unsigned char) *str;
            gotoxy( wherex() + 1, wherey() );
		} else if( *str == '\x8' ) { // Backspace
			int x = wherex();
			--x;
			gotoxy( x < 0 ? 0 : x, wherey() );
		}
		++str;
	}
	if( wherex() >= screenwidth() || *str == '\n' ) { 
        waitvbl();
        gotoxy( 0, wherey() + 1 );
	}
	while( wherey() >= screenheight() ) {
		memmove( ((unsigned short*)screenbuffer()), ((unsigned short*)screenbuffer()) + screenwidth(), screenwidth() * ( screenheight() - 1 ) * sizeof( unsigned short ) );
		memset( ((unsigned short*)screenbuffer()) + screenwidth() * ( screenheight() - 1 ), 0, screenwidth() * sizeof( unsigned short ) );
        gotoxy( 0, wherey() - 1 );
	}
	return len;
}

