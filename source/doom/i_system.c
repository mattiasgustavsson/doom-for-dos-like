// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
// $Log:$
//
// DESCRIPTION:
//
//-----------------------------------------------------------------------------

#include "doomtype.h"
#include "doomdef.h"
#include "doomstat.h"
#include "d_ticcmd.h"
#include <stdarg.h>
#include <time.h>


void I_Init (void)
{
    I_InitSound();
    I_InitGraphics();
}


int	mb_used = 6;

// Called by startup code
// to get the ammount of memory to malloc
// for the zone management.
byte*	I_ZoneBase (int *size)
{
    *size = mb_used*1024*1024;
    return (byte *) malloc (*size);
}



#ifndef _WIN32
#include <sys/time.h>
long long timeInMilliseconds(void) {
    struct timeval tv;

    gettimeofday(&tv,NULL);
    return (((long long)tv.tv_sec)*1000)+(tv.tv_usec/1000);
}
#endif


// Called by D_DoomLoop,
// returns current time in tics.
int I_GetTime (void)
{
    #ifdef _WIN32
        return clock()/(CLOCKS_PER_SEC/TICRATE);
    #else 
        return timeInMilliseconds()/(1000/TICRATE);
    #endif
}


//
// Called by D_DoomLoop,
// called before processing any tics in a frame
// (just after displaying a frame).
// Time consuming syncronous operations
// are performed here (joystick reading).
// Can call D_PostEvent.
//
void I_StartFrame (void)
{
}


//
// Called by D_DoomLoop,
// called before processing each tic in a frame.
// Quick syncronous operations are performed here.
// Can call D_PostEvent.
void I_StartTic (void)
{
    static int prev[ KEYCOUNT ] = { 0 };
    int keys[ KEYCOUNT ];
    for( int i = 0; i < KEYCOUNT; ++i ) keys[ i ] = keystate( i );

    for( int i = 0; i < KEYCOUNT; ++i ) 
    {
        int key = 0;

        switch( i )
        {
            case KEY_UP: key = KEY_UPARROW; break;
            case KEY_DOWN: key = KEY_DOWNARROW; break;
            case KEY_LEFT: key = KEY_LEFTARROW; break;
            case KEY_RIGHT: key = KEY_RIGHTARROW; break;
            case KEY_ESCAPE: key = KEY_ESCAPE; break;
            case KEY_SHIFT: key = KEY_RSHIFT; break;
            case KEY_CONTROL: key = KEY_RCTRL; break;
            case KEY_RMENU: key = KEY_RALT; break;
            case KEY_LMENU: key = KEY_LALT; break;
            case KEY_RETURN: key = KEY_ENTER; break;
			case KEY_PAUSE: key = KEY_PAUSE; break;
		    case KEY_SPACE: key = ' '; break;
            default:
                key = tolower( i );
        }

        if( keys[ i ] && !prev[ i ] )
            {
            event_t ev;
            ev.type = ev_keydown;
            ev.data1 = key;
            D_PostEvent( &ev );
            }
        else if( !keys[ i ] && prev[ i ] )
            {       
            event_t ev;
            ev.type = ev_keyup;
            ev.data1 = key;
            D_PostEvent( &ev );
            }
        prev[ i ] = keys[ i ];
	}

}

// Asynchronous interrupt functions should maintain private queues
// that are read by the synchronous functions
// to be converted into events.

// Either returns a null ticcmd,
// or calls a loadable driver to build it.
// This ticcmd will then be modified by the gameloop
// for normal input.

ticcmd_t	emptycmd;

ticcmd_t* I_BaseTiccmd (void)
{
    return &emptycmd;
}


// Called by M_Responder when quit is selected.
// Clean exit, displays sell blurb.
void I_Quit (void)
{
    D_QuitNetGame ();
    I_ShutdownSound();
    I_ShutdownMusic();
    M_SaveDefaults ();
    I_ShutdownGraphics();
    exit(0);
}



// Allocates from low memory under dos,
// just mallocs under unix
byte* I_AllocLow (int length)
{
    byte*	mem;
        
    mem = (byte *)malloc (length);
    memset (mem,0,length);
    return mem;
}

void I_Tactile (int on, int off, int total)
{
  // UNUSED.
  on = off = total = 0;
}


void I_Error (char *error, ...)
{
    va_list	argptr;

    // Message first.
    va_start (argptr,error);
    fprintf (stderr, "Error: ");
    vfprintf (stderr,error,argptr);
    fprintf (stderr, "\n");
    va_end (argptr);

    fflush( stderr );
    waitvbl();
    swapbuffers();
    waitvbl();

    // Shutdown. Here might be other errors.
    if (demorecording)
	G_CheckDemoStatus();

    D_QuitNetGame ();
    I_ShutdownGraphics();
    
    exit(-1);
}

