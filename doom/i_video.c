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
//	DOOM graphics stuff for X11, UNIX.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: i_x.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

#include "doomdef.h"
#include "doomtype.h"

void I_InitGraphics (void)
{
}


void I_ShutdownGraphics(void)
{
}

// Takes full 8 bit values.
void I_SetPalette (byte* palette)
{
}


void I_UpdateNoBlit (void)
{
}

void I_FinishUpdate (void)
{
}

void I_WaitVBL(int count) 
{
}

void I_ReadScreen (byte* scr)
{
}

