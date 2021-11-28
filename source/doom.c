#pragma warning( disable: 4113 )
#pragma warning( disable: 4311 )
#pragma warning( disable: 4047 )
#pragma warning( disable: 4024 )
#pragma warning( disable: 4312 )
#pragma warning( disable: 4020 )
#pragma warning( disable: 4700 )
#pragma warning( disable: 4133 )
#pragma warning( disable: 4142 )

#define strcasecmp stricmp
#define strncasecmp strnicmp

#define CONCAT_IMPL( x, y ) x##y
#define CONCAT( x, y ) CONCAT_IMPL( x, y )
#define rcsid CONCAT( rcsid, __COUNTER__ )

#define open doom_open
#define close doom_close
//#define vldoor_e #error door
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

#include <io.h>
#include "doom/m_menu.c"
#include "doom/m_misc.c"
#define strupr xstrupr
#include "doom/w_wad.c"
#undef strupr

#include "doom/i_net.c"
