/***********************************************************************************
  Snes9x - Portable Super Nintendo Entertainment System (TM) emulator.

  (c) Copyright 1996 - 2002  Gary Henderson (gary.henderson@ntlworld.com),
                             Jerremy Koot (jkoot@snes9x.com)

  (c) Copyright 2002 - 2004  Matthew Kendora

  (c) Copyright 2002 - 2005  Peter Bortas (peter@bortas.org)

  (c) Copyright 2004 - 2005  Joel Yliluoma (http://iki.fi/bisqwit/)

  (c) Copyright 2001 - 2006  John Weidman (jweidman@slip.net)

  (c) Copyright 2002 - 2006  funkyass (funkyass@spam.shaw.ca),
                             Kris Bleakley (codeviolation@hotmail.com)

  (c) Copyright 2002 - 2010  Brad Jorsch (anomie@users.sourceforge.net),
                             Nach (n-a-c-h@users.sourceforge.net),
                             zones (kasumitokoduck@yahoo.com)

  (c) Copyright 2006 - 2007  nitsuja

  (c) Copyright 2009 - 2010  BearOso,
                             OV2


  BS-X C emulator code
  (c) Copyright 2005 - 2006  Dreamer Nom,
                             zones

  C4 x86 assembler and some C emulation code
  (c) Copyright 2000 - 2003  _Demo_ (_demo_@zsnes.com),
                             Nach,
                             zsKnight (zsknight@zsnes.com)

  C4 C++ code
  (c) Copyright 2003 - 2006  Brad Jorsch,
                             Nach

  DSP-1 emulator code
  (c) Copyright 1998 - 2006  _Demo_,
                             Andreas Naive (andreasnaive@gmail.com),
                             Gary Henderson,
                             Ivar (ivar@snes9x.com),
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora,
                             Nach,
                             neviksti (neviksti@hotmail.com)

  DSP-2 emulator code
  (c) Copyright 2003         John Weidman,
                             Kris Bleakley,
                             Lord Nightmare (lord_nightmare@users.sourceforge.net),
                             Matthew Kendora,
                             neviksti

  DSP-3 emulator code
  (c) Copyright 2003 - 2006  John Weidman,
                             Kris Bleakley,
                             Lancer,
                             z80 gaiden

  DSP-4 emulator code
  (c) Copyright 2004 - 2006  Dreamer Nom,
                             John Weidman,
                             Kris Bleakley,
                             Nach,
                             z80 gaiden

  OBC1 emulator code
  (c) Copyright 2001 - 2004  zsKnight,
                             pagefault (pagefault@zsnes.com),
                             Kris Bleakley
                             Ported from x86 assembler to C by sanmaiwashi

  SPC7110 and RTC C++ emulator code used in 1.39-1.51
  (c) Copyright 2002         Matthew Kendora with research by
                             zsKnight,
                             John Weidman,
                             Dark Force

  SPC7110 and RTC C++ emulator code used in 1.52+
  (c) Copyright 2009         byuu,
                             neviksti

  S-DD1 C emulator code
  (c) Copyright 2003         Brad Jorsch with research by
                             Andreas Naive,
                             John Weidman

  S-RTC C emulator code
  (c) Copyright 2001 - 2006  byuu,
                             John Weidman

  ST010 C++ emulator code
  (c) Copyright 2003         Feather,
                             John Weidman,
                             Kris Bleakley,
                             Matthew Kendora

  Super FX x86 assembler emulator code
  (c) Copyright 1998 - 2003  _Demo_,
                             pagefault,
                             zsKnight

  Super FX C emulator code
  (c) Copyright 1997 - 1999  Ivar,
                             Gary Henderson,
                             John Weidman

  Sound emulator code used in 1.5-1.51
  (c) Copyright 1998 - 2003  Brad Martin
  (c) Copyright 1998 - 2006  Charles Bilyue'

  Sound emulator code used in 1.52+
  (c) Copyright 2004 - 2007  Shay Green (gblargg@gmail.com)

  SH assembler code partly based on x86 assembler code
  (c) Copyright 2002 - 2004  Marcus Comstedt (marcus@mc.pp.se)

  2xSaI filter
  (c) Copyright 1999 - 2001  Derek Liauw Kie Fa

  HQ2x, HQ3x, HQ4x filters
  (c) Copyright 2003         Maxim Stepin (maxim@hiend3d.com)

  NTSC filter
  (c) Copyright 2006 - 2007  Shay Green

  GTK+ GUI code
  (c) Copyright 2004 - 2010  BearOso

  Win32 GUI code
  (c) Copyright 2003 - 2006  blip,
                             funkyass,
                             Matthew Kendora,
                             Nach,
                             nitsuja
  (c) Copyright 2009 - 2010  OV2

  Mac OS GUI code
  (c) Copyright 1998 - 2001  John Stiles
  (c) Copyright 2001 - 2010  zones


  Specific ports contains the works of other authors. See headers in
  individual files.


  Snes9x homepage: http://www.snes9x.com/

  Permission to use, copy, modify and/or distribute Snes9x in both binary
  and source form, for non-commercial purposes, is hereby granted without
  fee, providing that this license information and copyright notice appear
  with all copies and any derived work.

  This software is provided 'as-is', without any express or implied
  warranty. In no event shall the authors be held liable for any damages
  arising from the use of this software or it's derivatives.

  Snes9x is freeware for PERSONAL USE only. Commercial users should
  seek permission of the copyright holders first. Commercial use includes,
  but is not limited to, charging money for Snes9x or software derived from
  Snes9x, including Snes9x or derivatives in commercial game bundles, and/or
  using Snes9x as a promotion for your commercial product.

  The copyright holders request that bug fixes and improvements to the code
  should be forwarded to them so everyone can benefit from the modifications
  in future versions.

  Super NES and Super Nintendo Entertainment System are trademarks of
  Nintendo Co., Limited and its subsidiary companies.
 ***********************************************************************************/


#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <X11/cursorfont.h>

#ifdef MITSHM
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/extensions/XShm.h>
#endif

#include "snes9x.h"
#include "memmap.h"
#include "ppu.h"
#include "controls.h"
#include "movie.h"
#include "logger.h"
#include "conffile.h"
#include "blit.h"
#include "display.h"

struct GUIData
{
	Display			*display;
	Screen			*screen;
	Visual			*visual;
	GC				gc;
	int				screen_num;
	int				depth;
	int				pixel_format;
	int				bytes_per_pixel;
	uint32			red_shift;
	uint32			blue_shift;
	uint32			green_shift;
	uint32			red_size;
	uint32			green_size;
	uint32			blue_size;
	Window			window;
	XImage			*image;
	uint8			*snes_buffer;
	uint8			*filter_buffer;
	uint8			*blit_screen;
	uint32			blit_screen_pitch;
	bool8			need_convert;
	Cursor			point_cursor;
	Cursor			cross_hair_cursor;
	int				video_mode;
	int				mouse_x;
	int				mouse_y;
	bool8			mod1_pressed;
	bool8			no_repeat;
#ifdef MITSHM
	XShmSegmentInfo	sm_info;
	bool8			use_shared_memory;
#endif
};

static struct GUIData	GUI;

typedef	std::pair<std::string, std::string>	strpair_t;
extern	std::vector<strpair_t>				keymaps;

typedef	void (* Blitter) (uint8 *, int, uint8 *, int, int, int);

#ifdef __linux
// Select seems to be broken in 2.x.x kernels - if a signal interrupts a
// select system call with a zero timeout, the select call is restarted but
// with an infinite timeout! The call will block until data arrives on the
// selected fd(s).
//
// The workaround is to stop the X library calling select in the first
// place! Replace XPending - which polls for data from the X server using
// select - with an ioctl call to poll for data and then only call the blocking
// XNextEvent if data is waiting.
#define SELECT_BROKEN_FOR_SIGNALS
#endif

enum
{
	VIDEOMODE_BLOCKY = 1,
	VIDEOMODE_TV,
	VIDEOMODE_SMOOTH,
	VIDEOMODE_SUPEREAGLE,
	VIDEOMODE_2XSAI,
	VIDEOMODE_SUPER2XSAI,
	VIDEOMODE_EPX,
	VIDEOMODE_HQ2X
};

static int ErrorHandler (Display *, XErrorEvent *);
static bool8 CheckForPendingXEvents (Display *);
static void SetXRepeat (bool8);
static void SetupImage (void);
static void TakedownImage (void);
static void Repaint (bool8);
static void Convert16To24 (int, int);
static void Convert16To24Packed (int, int);


void S9xExtraDisplayUsage (void)
{
	/*                               12345678901234567890123456789012345678901234567890123456789012345678901234567890 */

	S9xMessage(S9X_INFO, S9X_USAGE, "-setrepeat                      Allow altering keyboard auto-repeat");
	S9xMessage(S9X_INFO, S9X_USAGE, "");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v1                             Video mode: Blocky (default)");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v2                             Video mode: TV");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v3                             Video mode: Smooth");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v4                             Video mode: SuperEagle");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v5                             Video mode: 2xSaI");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v6                             Video mode: Super2xSaI");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v7                             Video mode: EPX");
	S9xMessage(S9X_INFO, S9X_USAGE, "-v8                             Video mode: hq2x");
	S9xMessage(S9X_INFO, S9X_USAGE, "");
}

void S9xParseDisplayArg (char **argv, int &i, int argc)
{
	if (!strcasecmp(argv[i], "-setrepeat"))
		GUI.no_repeat = FALSE;
	else
	if (!strncasecmp(argv[i], "-v", 2))
	{
		switch (argv[i][2])
		{
			case '1':	GUI.video_mode = VIDEOMODE_BLOCKY;		break;
			case '2':	GUI.video_mode = VIDEOMODE_TV;			break;
			case '3':	GUI.video_mode = VIDEOMODE_SMOOTH;		break;
			case '4':	GUI.video_mode = VIDEOMODE_SUPEREAGLE;	break;
			case '5':	GUI.video_mode = VIDEOMODE_2XSAI;		break;
			case '6':	GUI.video_mode = VIDEOMODE_SUPER2XSAI;	break;
			case '7':	GUI.video_mode = VIDEOMODE_EPX;			break;
			case '8':	GUI.video_mode = VIDEOMODE_HQ2X;		break;
		}
	}
	else
		S9xUsage();
}

const char * S9xParseDisplayConfig (ConfigFile &conf, int pass)
{
	if (pass != 1)
		return ("Unix/X11");

	if (!conf.GetBool("Unix::ClearAllControls", false))
	{
		keymaps.push_back(strpair_t("K00:k",            "Joypad1 Right"));
		keymaps.push_back(strpair_t("K00:Right",        "Joypad1 Right"));
		keymaps.push_back(strpair_t("K00:h",            "Joypad1 Left"));
		keymaps.push_back(strpair_t("K00:Left",         "Joypad1 Left"));
		keymaps.push_back(strpair_t("K00:j",            "Joypad1 Down"));
		keymaps.push_back(strpair_t("K00:n",            "Joypad1 Down"));
		keymaps.push_back(strpair_t("K00:Down",         "Joypad1 Down"));
		keymaps.push_back(strpair_t("K00:u",            "Joypad1 Up"));
		keymaps.push_back(strpair_t("K00:Up",           "Joypad1 Up"));
		keymaps.push_back(strpair_t("K00:Return",       "Joypad1 Start"));
		keymaps.push_back(strpair_t("K00:space",        "Joypad1 Select"));
		keymaps.push_back(strpair_t("K00:S+d",          "Joypad1 ToggleTurbo A"));
		keymaps.push_back(strpair_t("K00:C+d",          "Joypad1 ToggleSticky A"));
		keymaps.push_back(strpair_t("K00:d",            "Joypad1 A"));
		keymaps.push_back(strpair_t("K00:S+c",          "Joypad1 ToggleTurbo B"));
		keymaps.push_back(strpair_t("K00:C+c",          "Joypad1 ToggleSticky B"));
		keymaps.push_back(strpair_t("K00:c",            "Joypad1 B"));
		keymaps.push_back(strpair_t("K00:S+s",          "Joypad1 ToggleTurbo X"));
		keymaps.push_back(strpair_t("K00:C+s",          "Joypad1 ToggleSticky X"));
		keymaps.push_back(strpair_t("K00:s",            "Joypad1 X"));
		keymaps.push_back(strpair_t("K00:S+x",          "Joypad1 ToggleTurbo Y"));
		keymaps.push_back(strpair_t("K00:C+x",          "Joypad1 ToggleSticky Y"));
		keymaps.push_back(strpair_t("K00:x",            "Joypad1 Y"));
		keymaps.push_back(strpair_t("K00:S+a",          "Joypad1 ToggleTurbo L"));
		keymaps.push_back(strpair_t("K00:S+v",          "Joypad1 ToggleTurbo L"));
		keymaps.push_back(strpair_t("K00:C+a",          "Joypad1 ToggleSticky L"));
		keymaps.push_back(strpair_t("K00:C+v",          "Joypad1 ToggleSticky L"));
		keymaps.push_back(strpair_t("K00:a",            "Joypad1 L"));
		keymaps.push_back(strpair_t("K00:v",            "Joypad1 L"));
		keymaps.push_back(strpair_t("K00:S+z",          "Joypad1 ToggleTurbo R"));
		keymaps.push_back(strpair_t("K00:C+z",          "Joypad1 ToggleSticky R"));
		keymaps.push_back(strpair_t("K00:z",            "Joypad1 R"));

		keymaps.push_back(strpair_t("K00:KP_Left",      "Joypad2 Left"));
		keymaps.push_back(strpair_t("K00:KP_Right",     "Joypad2 Right"));
		keymaps.push_back(strpair_t("K00:KP_Up",        "Joypad2 Up"));
		keymaps.push_back(strpair_t("K00:KP_Down",      "Joypad2 Down"));
		keymaps.push_back(strpair_t("K00:KP_Enter",     "Joypad2 Start"));
		keymaps.push_back(strpair_t("K00:KP_Add",       "Joypad2 Select"));
		keymaps.push_back(strpair_t("K00:Prior",        "Joypad2 A"));
		keymaps.push_back(strpair_t("K00:Next",         "Joypad2 B"));
		keymaps.push_back(strpair_t("K00:Home",         "Joypad2 X"));
		keymaps.push_back(strpair_t("K00:End",          "Joypad2 Y"));
		keymaps.push_back(strpair_t("K00:Insert",       "Joypad2 L"));
		keymaps.push_back(strpair_t("K00:Delete",       "Joypad2 R"));

		keymaps.push_back(strpair_t("K00:A+F4",         "SoundChannel0"));
		keymaps.push_back(strpair_t("K00:C+F4",         "SoundChannel0"));
		keymaps.push_back(strpair_t("K00:A+F5",         "SoundChannel1"));
		keymaps.push_back(strpair_t("K00:C+F5",         "SoundChannel1"));
		keymaps.push_back(strpair_t("K00:A+F6",         "SoundChannel2"));
		keymaps.push_back(strpair_t("K00:C+F6",         "SoundChannel2"));
		keymaps.push_back(strpair_t("K00:A+F7",         "SoundChannel3"));
		keymaps.push_back(strpair_t("K00:C+F7",         "SoundChannel3"));
		keymaps.push_back(strpair_t("K00:A+F8",         "SoundChannel4"));
		keymaps.push_back(strpair_t("K00:C+F8",         "SoundChannel4"));
		keymaps.push_back(strpair_t("K00:A+F9",         "SoundChannel5"));
		keymaps.push_back(strpair_t("K00:C+F9",         "SoundChannel5"));
		keymaps.push_back(strpair_t("K00:A+F10",        "SoundChannel6"));
		keymaps.push_back(strpair_t("K00:C+F10",        "SoundChannel6"));
		keymaps.push_back(strpair_t("K00:A+F11",        "SoundChannel7"));
		keymaps.push_back(strpair_t("K00:C+F11",        "SoundChannel7"));
		keymaps.push_back(strpair_t("K00:A+F12",        "SoundChannelsOn"));
		keymaps.push_back(strpair_t("K00:C+F12",        "SoundChannelsOn"));

		keymaps.push_back(strpair_t("K00:S+1",          "BeginRecordingMovie"));
		keymaps.push_back(strpair_t("K00:S+2",          "EndRecordingMovie"));
		keymaps.push_back(strpair_t("K00:S+3",          "LoadMovie"));
		keymaps.push_back(strpair_t("K00:A+F1",         "SaveSPC"));
		keymaps.push_back(strpair_t("K00:C+F1",         "SaveSPC"));
		keymaps.push_back(strpair_t("K00:F10",          "LoadOopsFile"));
		keymaps.push_back(strpair_t("K00:A+F2",         "LoadFreezeFile"));
		keymaps.push_back(strpair_t("K00:C+F2",         "LoadFreezeFile"));
		keymaps.push_back(strpair_t("K00:F11",          "LoadFreezeFile"));
		keymaps.push_back(strpair_t("K00:A+F3",         "SaveFreezeFile"));
		keymaps.push_back(strpair_t("K00:C+F3",         "SaveFreezeFile"));
		keymaps.push_back(strpair_t("K00:F12",          "SaveFreezeFile"));
		keymaps.push_back(strpair_t("K00:F1",           "QuickLoad000"));
		keymaps.push_back(strpair_t("K00:F2",           "QuickLoad001"));
		keymaps.push_back(strpair_t("K00:F3",           "QuickLoad002"));
		keymaps.push_back(strpair_t("K00:F4",           "QuickLoad003"));
		keymaps.push_back(strpair_t("K00:F5",           "QuickLoad004"));
		keymaps.push_back(strpair_t("K00:F6",           "QuickLoad005"));
		keymaps.push_back(strpair_t("K00:F7",           "QuickLoad006"));
		keymaps.push_back(strpair_t("K00:F8",           "QuickLoad007"));
		keymaps.push_back(strpair_t("K00:F9",           "QuickLoad008"));
		keymaps.push_back(strpair_t("K00:S+F1",         "QuickSave000"));
		keymaps.push_back(strpair_t("K00:S+F2",         "QuickSave001"));
		keymaps.push_back(strpair_t("K00:S+F3",         "QuickSave002"));
		keymaps.push_back(strpair_t("K00:S+F4",         "QuickSave003"));
		keymaps.push_back(strpair_t("K00:S+F5",         "QuickSave004"));
		keymaps.push_back(strpair_t("K00:S+F6",         "QuickSave005"));
		keymaps.push_back(strpair_t("K00:S+F7",         "QuickSave006"));
		keymaps.push_back(strpair_t("K00:S+F8",         "QuickSave007"));
		keymaps.push_back(strpair_t("K00:S+F9",         "QuickSave008"));

		keymaps.push_back(strpair_t("K00:Scroll_Lock",  "Pause"));
		keymaps.push_back(strpair_t("K00:CS+Escape",    "Reset"));
		keymaps.push_back(strpair_t("K00:S+Escape",     "SoftReset"));
		keymaps.push_back(strpair_t("K00:Escape",       "ExitEmu"));
		keymaps.push_back(strpair_t("K00:Tab",          "EmuTurbo"));
		keymaps.push_back(strpair_t("K00:S+Tab",        "ToggleEmuTurbo"));
		keymaps.push_back(strpair_t("K00:A+equal",      "IncEmuTurbo"));
		keymaps.push_back(strpair_t("K00:A+minus",      "DecEmuTurbo"));
		keymaps.push_back(strpair_t("K00:C+equal",      "IncTurboSpeed"));
		keymaps.push_back(strpair_t("K00:C+minus",      "DecTurboSpeed"));
		keymaps.push_back(strpair_t("K00:equal",        "IncFrameRate"));
		keymaps.push_back(strpair_t("K00:minus",        "DecFrameRate"));
		keymaps.push_back(strpair_t("K00:S+equal",      "IncFrameTime"));
		keymaps.push_back(strpair_t("K00:S+minus",      "DecFrameTime"));
		keymaps.push_back(strpair_t("K00:6",            "SwapJoypads"));
		keymaps.push_back(strpair_t("K00:Print",        "Screenshot"));

		keymaps.push_back(strpair_t("K00:1",            "ToggleBG0"));
		keymaps.push_back(strpair_t("K00:2",            "ToggleBG1"));
		keymaps.push_back(strpair_t("K00:3",            "ToggleBG2"));
		keymaps.push_back(strpair_t("K00:4",            "ToggleBG3"));
		keymaps.push_back(strpair_t("K00:5",            "ToggleSprites"));
		keymaps.push_back(strpair_t("K00:0",            "ToggleHDMA"));
		keymaps.push_back(strpair_t("K00:9",            "ToggleTransparency"));
		keymaps.push_back(strpair_t("K00:BackSpace",    "ClipWindows"));
		keymaps.push_back(strpair_t("K00:A+Escape",     "Debugger"));

		keymaps.push_back(strpair_t("M00:B0",           "{Mouse1 L,Superscope Fire,Justifier1 Trigger}"));
		keymaps.push_back(strpair_t("M00:B1",           "{Justifier1 AimOffscreen Trigger,Superscope AimOffscreen}"));
		keymaps.push_back(strpair_t("M00:B2",           "{Mouse1 R,Superscope Cursor,Justifier1 Start}"));
		keymaps.push_back(strpair_t("M00:Pointer",      "Pointer Mouse1+Superscope+Justifier1"));
		keymaps.push_back(strpair_t("K00:grave",        "Superscope ToggleTurbo"));
		keymaps.push_back(strpair_t("K00:slash",        "Superscope Pause"));
	}

	GUI.no_repeat = !conf.GetBool("Unix/X11::SetKeyRepeat", TRUE);

	if (conf.Exists("Unix/X11::VideoMode"))
	{
		GUI.video_mode = conf.GetUInt("Unix/X11::VideoMode", VIDEOMODE_BLOCKY);
		if (GUI.video_mode < 1 || GUI.video_mode > 8)
			GUI.video_mode = VIDEOMODE_BLOCKY;
	}
	else
		GUI.video_mode = VIDEOMODE_BLOCKY;

	return ("Unix/X11");
}

static void FatalError (const char *str)
{
	fprintf(stderr, "%s\n", str);
	S9xExit();
}

static int ErrorHandler (Display *display, XErrorEvent *event)
{
#ifdef MITSHM
	GUI.use_shared_memory = FALSE;
#endif
	return (0);
}

void S9xInitDisplay (int argc, char **argv)
{
	GUI.display = XOpenDisplay(NULL);
	if (GUI.display == NULL)
		FatalError("Failed to connect to X server.");

	GUI.screen     = DefaultScreenOfDisplay(GUI.display);
	GUI.screen_num = XScreenNumberOfScreen(GUI.screen);
	GUI.visual     = DefaultVisualOfScreen(GUI.screen);

	XVisualInfo	plate, *matches;
	int			count;

	plate.visualid = XVisualIDFromVisual(GUI.visual);
	matches = XGetVisualInfo(GUI.display, VisualIDMask, &plate, &count);
	if (!count)
		FatalError("Your X Window System server is unwell!");

	GUI.depth = matches[0].depth;
	if ((GUI.depth != 15 && GUI.depth != 16 && GUI.depth != 24) || (matches[0].c_class != TrueColor))
		FatalError("Requiers 15, 16, 24 or 32-bit color depth supporting TrueColor.");

	GUI.red_shift   = ffs(matches[0].red_mask)   - 1;
	GUI.green_shift = ffs(matches[0].green_mask) - 1;
	GUI.blue_shift  = ffs(matches[0].blue_mask)  - 1;
	GUI.red_size    = matches[0].red_mask   >> GUI.red_shift;
	GUI.green_size  = matches[0].green_mask >> GUI.green_shift;
	GUI.blue_size   = matches[0].blue_mask  >> GUI.blue_shift;
	if (GUI.depth == 16 && GUI.green_size == 63)
		GUI.green_shift++;

	XFree(matches);

	switch (GUI.depth)
	{
		default:
		case 32:
		case 24:
			S9xSetRenderPixelFormat(RGB555);
			GUI.pixel_format = 555;
			break;

		case 16:
			if (GUI.red_size != GUI.green_size || GUI.blue_size != GUI.green_size)
			{
				// 565 format
				if (GUI.green_shift > GUI.blue_shift && GUI.green_shift > GUI.red_shift)
					S9xSetRenderPixelFormat(GBR565);
				else
				if (GUI.red_shift > GUI.blue_shift)
					S9xSetRenderPixelFormat(RGB565);
				else
					S9xSetRenderPixelFormat(BGR565);

				GUI.pixel_format = 565;
				break;
			}
			// FALL ...
		case 15:
			if (GUI.green_shift > GUI.blue_shift && GUI.green_shift > GUI.red_shift)
				S9xSetRenderPixelFormat(GBR555);
			else
			if (GUI.red_shift > GUI.blue_shift)
				S9xSetRenderPixelFormat(RGB555);
			else
				S9xSetRenderPixelFormat(BGR555);

			GUI.pixel_format = 555;
			break;
	}

	S9xBlitFilterInit();
	S9xBlit2xSaIFilterInit();
	S9xBlitHQ2xFilterInit();

	XSetWindowAttributes	attrib;

	memset(&attrib, 0, sizeof(attrib));
	attrib.background_pixel = BlackPixelOfScreen(GUI.screen);
	attrib.colormap = XCreateColormap(GUI.display, RootWindowOfScreen(GUI.screen), GUI.visual, AllocNone);

	GUI.window = XCreateWindow(GUI.display, RootWindowOfScreen(GUI.screen),
							   (WidthOfScreen(GUI.screen) - SNES_WIDTH * 2) / 2, (HeightOfScreen(GUI.screen) - SNES_HEIGHT_EXTENDED * 2) / 2,
							   SNES_WIDTH * 2, SNES_HEIGHT_EXTENDED * 2, 0, GUI.depth, InputOutput, GUI.visual, CWBackPixel | CWColormap, &attrib);

	static XColor	bg, fg;
	static char		data[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	Pixmap			bitmap;

	bitmap = XCreateBitmapFromData(GUI.display, GUI.window, data, 8, 8);
	GUI.point_cursor = XCreatePixmapCursor(GUI.display, bitmap, bitmap, &fg, &bg, 0, 0);
	XDefineCursor(GUI.display, GUI.window, GUI.point_cursor);
	GUI.cross_hair_cursor = XCreateFontCursor(GUI.display, XC_crosshair);

	GUI.gc = DefaultGCOfScreen(GUI.screen);

	XSizeHints	Hints;
	XWMHints	WMHints;

	memset((void *) &Hints, 0, sizeof(XSizeHints));
	memset((void *) &WMHints, 0, sizeof(XWMHints));

	Hints.flags      = PSize | PMinSize | PMaxSize;
	Hints.min_width  = Hints.max_width  = Hints.base_width  = SNES_WIDTH * 2;
	Hints.min_height = Hints.max_height = Hints.base_height = SNES_HEIGHT_EXTENDED * 2;
	WMHints.input    = True;
	WMHints.flags    = InputHint;

	XSetWMHints(GUI.display, GUI.window, &WMHints);
	XSetWMNormalHints(GUI.display, GUI.window, &Hints);
	XSelectInput(GUI.display, GUI.window, FocusChangeMask | ExposureMask | KeyPressMask | KeyReleaseMask | StructureNotifyMask | ButtonPressMask | ButtonReleaseMask);

	XMapRaised(GUI.display, GUI.window);
	XClearWindow(GUI.display, GUI.window);

	SetupImage();

	switch (GUI.depth)
	{
		default:
		case 32:
			GUI.bytes_per_pixel = 4;
			break;

		case 24:
			if (GUI.image->bits_per_pixel == 24)
				GUI.bytes_per_pixel = 3;
			else
				GUI.bytes_per_pixel = 4;
			break;

		case 15:
		case 16:
			GUI.bytes_per_pixel = 2;
			break;
	}
}

void S9xDeinitDisplay (void)
{
	S9xTextMode();
	TakedownImage();
	XSync(GUI.display, False);
	XCloseDisplay(GUI.display);
	S9xBlitFilterDeinit();
	S9xBlit2xSaIFilterDeinit();
	S9xBlitHQ2xFilterDeinit();
}

static void TakedownImage (void)
{
	if (GUI.snes_buffer)
	{
		free(GUI.snes_buffer);
		GUI.snes_buffer = NULL;
	}

	if (GUI.filter_buffer)
	{
		free(GUI.filter_buffer);
		GUI.filter_buffer = NULL;
	}

	if (GUI.image)
	{
	#ifdef MITSHM
		if (GUI.use_shared_memory)
		{
			XShmDetach(GUI.display, &GUI.sm_info);
			GUI.image->data = NULL;
			XDestroyImage(GUI.image);
			if (GUI.sm_info.shmaddr)
				shmdt(GUI.sm_info.shmaddr);
			if (GUI.sm_info.shmid >= 0)
				shmctl(GUI.sm_info.shmid, IPC_RMID, 0);
			GUI.image = NULL;
		}
		else
	#endif
		{
			XDestroyImage(GUI.image);
			GUI.image = NULL;
		}
	}

	S9xGraphicsDeinit();
}

static void SetupImage (void)
{
	TakedownImage();

#ifdef MITSHM
	GUI.use_shared_memory = TRUE;

	int		major, minor;
	Bool	shared;

	if (!XShmQueryVersion(GUI.display, &major, &minor, &shared) || !shared)
		GUI.image = NULL;
	else
		GUI.image = XShmCreateImage(GUI.display, GUI.visual, GUI.depth, ZPixmap, NULL, &GUI.sm_info, SNES_WIDTH * 2, SNES_HEIGHT_EXTENDED * 2);

	if (!GUI.image)
		GUI.use_shared_memory = FALSE;
	else
	{
		GUI.sm_info.shmid = shmget(IPC_PRIVATE, GUI.image->bytes_per_line * GUI.image->height, IPC_CREAT | 0777);
		if (GUI.sm_info.shmid < 0)
		{
			XDestroyImage(GUI.image);
			GUI.use_shared_memory = FALSE;
		}
		else
		{
			GUI.image->data = GUI.sm_info.shmaddr = (char *) shmat(GUI.sm_info.shmid, 0, 0);
			if (!GUI.image->data)
			{
				XDestroyImage(GUI.image);
				shmctl(GUI.sm_info.shmid, IPC_RMID, 0);
				GUI.use_shared_memory = FALSE;
			}
			else
			{
				GUI.sm_info.readOnly = False;

				XSetErrorHandler(ErrorHandler);
				XShmAttach(GUI.display, &GUI.sm_info);
				XSync(GUI.display, False);

				// X Error handler might clear GUI.use_shared_memory if XShmAttach failed.
				if (!GUI.use_shared_memory)
				{
					XDestroyImage(GUI.image);
					shmdt(GUI.sm_info.shmaddr);
					shmctl(GUI.sm_info.shmid, IPC_RMID, 0);
				}
			}
		}
	}

	if (!GUI.use_shared_memory)
	{
		fprintf(stderr, "use_shared_memory failed, switching to XPutImage.\n");
#endif
		GUI.image = XCreateImage(GUI.display, GUI.visual, GUI.depth, ZPixmap, 0, NULL, SNES_WIDTH * 2, SNES_HEIGHT_EXTENDED * 2, BitmapUnit(GUI.display), 0);
		GUI.image->data = (char *) malloc(GUI.image->bytes_per_line * GUI.image->height);
		if (!GUI.image || !GUI.image->data)
			FatalError("XCreateImage failed.");
#ifdef MITSHM
	}
#endif

#ifdef LSB_FIRST
	GUI.image->byte_order = LSBFirst;
#else
	GUI.image->byte_order = MSBFirst;
#endif

	GFX.Pitch = SNES_WIDTH * 2 * 2;
	GUI.snes_buffer = (uint8 *) calloc(GFX.Pitch * ((SNES_HEIGHT_EXTENDED + 4) * 2), 1);
	if (!GUI.snes_buffer)
		FatalError("Failed to allocate GUI.snes_buffer.");

	GFX.Screen = (uint16 *) (GUI.snes_buffer + (GFX.Pitch * 2 * 2));

	GUI.filter_buffer = (uint8 *) calloc((SNES_WIDTH * 2) * 2 * (SNES_HEIGHT_EXTENDED * 2), 1);
	if (!GUI.filter_buffer)
		FatalError("Failed to allocate GUI.filter_buffer.");

	if (GUI.depth == 15 || GUI.depth == 16)
	{
		GUI.blit_screen_pitch = GUI.image->bytes_per_line;
		GUI.blit_screen       = (uint8 *) GUI.image->data;
		GUI.need_convert      = FALSE;
	}
	else
	{
		GUI.blit_screen_pitch = (SNES_WIDTH * 2) * 2;
		GUI.blit_screen       = GUI.filter_buffer;
		GUI.need_convert      = TRUE;
	}

	S9xGraphicsInit();
}

void S9xPutImage (int width, int height)
{
	static int	prevWidth = 0, prevHeight = 0;
	int			copyWidth, copyHeight;
	Blitter		blitFn = NULL;

	if (GUI.video_mode == VIDEOMODE_BLOCKY || GUI.video_mode == VIDEOMODE_TV || GUI.video_mode == VIDEOMODE_SMOOTH)
		if ((width <= SNES_WIDTH) && ((prevWidth != width) || (prevHeight != height)))
			S9xBlitClearDelta();

	if (width <= SNES_WIDTH)
	{
		copyWidth  = width  * 2;
		copyHeight = height * 2;

		switch (GUI.video_mode)
		{
			case VIDEOMODE_BLOCKY:		blitFn = S9xBlitPixScaled16;		break;
			case VIDEOMODE_TV:			blitFn = S9xBlitPixScaledTV16;		break;
			case VIDEOMODE_SMOOTH:		blitFn = S9xBlitPixSmooth16;		break;
			case VIDEOMODE_SUPEREAGLE:	blitFn = S9xBlitPixSuperEagle16;	break;
			case VIDEOMODE_2XSAI:		blitFn = S9xBlitPix2xSaI16;			break;
			case VIDEOMODE_SUPER2XSAI:	blitFn = S9xBlitPixSuper2xSaI16;	break;
			case VIDEOMODE_EPX:			blitFn = S9xBlitPixEPX16;			break;
			case VIDEOMODE_HQ2X:		blitFn = S9xBlitPixHQ2x16;			break;
		}
	}
	else
	if (height <= SNES_HEIGHT_EXTENDED)
	{
		copyWidth  = width;
		copyHeight = height * 2;

		switch (GUI.video_mode)
		{
			default:					blitFn = S9xBlitPixHiRes16;			break;
			case VIDEOMODE_TV:			blitFn = S9xBlitPixHiResTV16;		break;
		}
	}
	else
	{
		copyWidth  = width;
		copyHeight = height;

		blitFn = S9xBlitPixSmall16;
	}

	blitFn((uint8 *) GFX.Screen, GFX.Pitch, GUI.blit_screen, GUI.blit_screen_pitch, width, height);

	if (height < prevHeight)
	{
		int	p = GUI.blit_screen_pitch >> 2;
		for (int y = SNES_HEIGHT * 2; y < SNES_HEIGHT_EXTENDED * 2; y++)
		{
			uint32	*d = (uint32 *) (GUI.blit_screen + y * GUI.blit_screen_pitch);
			for (int x = 0; x < p; x++)
				*d++ = 0;
		}
	}

	if (GUI.need_convert)
	{
		if (GUI.bytes_per_pixel == 3)
			Convert16To24Packed(copyWidth, copyHeight);
		else
			Convert16To24(copyWidth, copyHeight);
	}

	Repaint(TRUE);

	prevWidth  = width;
	prevHeight = height;
}

static void Convert16To24 (int width, int height)
{
	if (GUI.pixel_format == 565)
	{
		for (int y = 0; y < height; y++)
		{
			uint16	*s = (uint16 *) (GUI.blit_screen + y * GUI.blit_screen_pitch);
			uint32	*d = (uint32 *) (GUI.image->data + y * GUI.image->bytes_per_line);

			for (int x = 0; x < width; x++)
			{
				uint32	pixel = *s++;
				*d++ = (((pixel >> 11) & 0x1f) << (GUI.red_shift + 3)) | (((pixel >> 6) & 0x1f) << (GUI.green_shift + 3)) | ((pixel & 0x1f) << (GUI.blue_shift + 3));
			}
		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			uint16	*s = (uint16 *) (GUI.blit_screen + y * GUI.blit_screen_pitch);
			uint32	*d = (uint32 *) (GUI.image->data + y * GUI.image->bytes_per_line);

			for (int x = 0; x < width; x++)
			{
				uint32	pixel = *s++;
				*d++ = (((pixel >> 10) & 0x1f) << (GUI.red_shift + 3)) | (((pixel >> 5) & 0x1f) << (GUI.green_shift + 3)) | ((pixel & 0x1f) << (GUI.blue_shift + 3));
			}
		}
	}
}

static void Convert16To24Packed (int width, int height)
{
	if (GUI.pixel_format == 565)
	{
		for (int y = 0; y < height; y++)
		{
			uint16	*s = (uint16 *) (GUI.blit_screen + y * GUI.blit_screen_pitch);
			uint8	*d = (uint8 *)  (GUI.image->data + y * GUI.image->bytes_per_line);

		#ifdef LSB_FIRST
			if (GUI.red_shift < GUI.blue_shift)
		#else
			if (GUI.red_shift > GUI.blue_shift)
		#endif
			{
				for (int x = 0; x < width; x++)
				{
					uint32	pixel = *s++;
					*d++ = (pixel >> (11 - 3)) & 0xf8;
					*d++ = (pixel >>  (6 - 3)) & 0xf8;
					*d++ = (pixel & 0x1f) << 3;
				}
			}
			else
			{
				for (int x = 0; x < width; x++)
				{
					uint32	pixel = *s++;
					*d++ = (pixel & 0x1f) << 3;
					*d++ = (pixel >>  (6 - 3)) & 0xf8;
					*d++ = (pixel >> (11 - 3)) & 0xf8;
				}
			}
		}
	}
	else
	{
		for (int y = 0; y < height; y++)
		{
			uint16	*s = (uint16 *) (GUI.blit_screen + y * GUI.blit_screen_pitch);
			uint8	*d = (uint8 *)  (GUI.image->data + y * GUI.image->bytes_per_line);

		#ifdef LSB_FIRST
			if (GUI.red_shift < GUI.blue_shift)
		#else
			if (GUI.red_shift > GUI.blue_shift)
		#endif
			{
				for (int x = 0; x < width; x++)
				{
					uint32	pixel = *s++;
					*d++ = (pixel >> (10 - 3)) & 0xf8;
					*d++ = (pixel >>  (5 - 3)) & 0xf8;
					*d++ = (pixel & 0x1f) << 3;
				}
			}
			else
			{
				for (int x = 0; x < width; x++)
				{
					uint32	pixel = *s++;
					*d++ = (pixel & 0x1f) << 3;
					*d++ = (pixel >>  (5 - 3)) & 0xf8;
					*d++ = (pixel >> (10 - 3)) & 0xf8;
				}
			}
		}
	}
}

static void Repaint (bool8 isFrameBoundry)
{
#ifdef MITSHM
	if (GUI.use_shared_memory)
	{
		XShmPutImage(GUI.display, GUI.window, GUI.gc, GUI.image, 0, 0, 0, 0, SNES_WIDTH * 2, SNES_HEIGHT_EXTENDED * 2, False);
		XSync(GUI.display, False);
	}
	else
#endif
		XPutImage(GUI.display, GUI.window, GUI.gc, GUI.image, 0, 0, 0, 0, SNES_WIDTH * 2, SNES_HEIGHT_EXTENDED * 2);

	Window			root, child;
	int				root_x, root_y, x, y;
	unsigned int	mask;

	// Use QueryPointer to sync X server and as a side effect also gets current pointer position for SNES mouse emulation.
	XQueryPointer(GUI.display, GUI.window, &root, &child, &root_x, &root_y, &x, &y, &mask);

	if (x >= 0 && y >= 0 && x < SNES_WIDTH * 2 && y < SNES_HEIGHT_EXTENDED * 2)
	{
		GUI.mouse_x = x >> 1;
		GUI.mouse_y = y >> 1;

		if (mask & Mod1Mask)
		{
			if (!GUI.mod1_pressed)
			{
				GUI.mod1_pressed = TRUE;
				XDefineCursor(GUI.display, GUI.window, GUI.cross_hair_cursor);
			}
		}
		else
		if (GUI.mod1_pressed)
		{
			GUI.mod1_pressed = FALSE;
			XDefineCursor(GUI.display, GUI.window, GUI.point_cursor);
		}
	}

	if (Settings.DumpStreams && isFrameBoundry)
		S9xVideoLogger(GUI.image->data, SNES_WIDTH * 2, SNES_HEIGHT_EXTENDED * 2, GUI.bytes_per_pixel, GUI.image->bytes_per_line);
}

void S9xTextMode (void)
{
	SetXRepeat(TRUE);
}

void S9xGraphicsMode (void)
{
	SetXRepeat(FALSE);
}

static bool8 CheckForPendingXEvents (Display *display)
{
#ifdef SELECT_BROKEN_FOR_SIGNALS
	int	arg = 0;

	return (XEventsQueued(display, QueuedAlready) || (ioctl(ConnectionNumber(display), FIONREAD, &arg) == 0 && arg));
#else
	return (XPending(display));
#endif
}

void S9xProcessEvents (bool8 block)
{
	while (block || CheckForPendingXEvents(GUI.display))
	{
		XEvent	event;

		XNextEvent(GUI.display, &event);
		block = FALSE;

		switch (event.type)
		{
			case KeyPress:
			case KeyRelease:
				S9xReportButton(((event.xkey.state & (ShiftMask | Mod1Mask | ControlMask | Mod4Mask)) << 8) | event.xkey.keycode, event.type == KeyPress);
			#if 1
				{
					KeyCode	kc = XKeysymToKeycode(GUI.display, XKeycodeToKeysym(GUI.display, event.xkey.keycode, 0));
					if (event.xkey.keycode != kc)
						S9xReportButton(((event.xkey.state & (ShiftMask | Mod1Mask | ControlMask | Mod4Mask)) << 8) | kc, event.type == KeyPress);
				}
			#endif
				break;

			case FocusIn:
				SetXRepeat(FALSE);
				XFlush(GUI.display);
				break;

			case FocusOut:
				SetXRepeat(TRUE);
				XFlush(GUI.display);
				break;

			case ConfigureNotify:
				break;

			case ButtonPress:
			case ButtonRelease:
				S9xReportButton(0x40000000 | (event.xbutton.button - 1), event.type == ButtonPress);
				break;

			case Expose:
				Repaint(FALSE);
				break;
		}
	}
}

const char * S9xSelectFilename (const char *def, const char *dir1, const char *ext1, const char *title)
{
	static char	s[PATH_MAX + 1];
	char		buffer[PATH_MAX + 1];

	SetXRepeat(TRUE);

	printf("\n%s (default: %s): ", title, def);
	fflush(stdout);

	SetXRepeat(FALSE);

	if (fgets(buffer, PATH_MAX + 1, stdin))
	{
		char	drive[_MAX_DRIVE + 1], dir[_MAX_DIR + 1], fname[_MAX_FNAME + 1], ext[_MAX_EXT + 1];

		char	*p = buffer;
		while (isspace(*p))
			p++;
		if (!*p)
		{
			strncpy(buffer, def, PATH_MAX + 1);
			buffer[PATH_MAX] = 0;
			p = buffer;
		}

		char	*q = strrchr(p, '\n');
		if (q)
			*q = 0;

		_splitpath(p, drive, dir, fname, ext);
		_makepath(s, drive, *dir ? dir : dir1, fname, *ext ? ext : ext1);

		return (s);
	}

	return (NULL);
}

void S9xMessage (int type, int number, const char *message)
{
	const int	max = 36 * 3;
	static char	buffer[max + 1];

	fprintf(stdout, "%s\n", message);
	strncpy(buffer, message, max + 1);
	buffer[max] = 0;
	S9xSetInfoString(buffer);
}

const char * S9xStringInput (const char *message)
{
	static char	buffer[256];

	printf("%s: ", message);
	fflush(stdout);

	if (fgets(buffer, sizeof(buffer) - 2, stdin))
		return (buffer);

	return (NULL);
}

void S9xSetTitle (const char *string)
{
	XStoreName(GUI.display, GUI.window, string);
	XFlush(GUI.display);
}

static void SetXRepeat (bool8 state)
{
	if (state)
		XAutoRepeatOn(GUI.display);
	else
		XAutoRepeatOff(GUI.display);
}

s9xcommand_t S9xGetDisplayCommandT (const char *n)
{
	s9xcommand_t	cmd;

	cmd.type         = S9xBadMapping;
	cmd.multi_press  = 0;
	cmd.button_norpt = 0;
	cmd.port[0]      = 0xff;
	cmd.port[1]      = 0;
	cmd.port[2]      = 0;
	cmd.port[3]      = 0;

	return (cmd);
}

char * S9xGetDisplayCommandName (s9xcommand_t cmd)
{
	return (strdup("None"));
}

void S9xHandleDisplayCommand (s9xcommand_t cmd, int16 data1, int16 data2)
{
	return;
}

bool8 S9xMapDisplayInput (const char *n, s9xcommand_t *cmd)
{
	int	i, d;

	if (!isdigit(n[1]) || !isdigit(n[2]) || n[3] != ':')
		goto unrecog;

	d = ((n[1] - '0') * 10 + (n[2] - '0')) << 24;

	switch (n[0])
	{
		case 'K':
		{
			KeyCode	kc;
			KeySym	ks;

			d |= 0x00000000;

			for (i = 4; n[i] != '\0' && n[i] != '+'; i++) ;

			if (n[i] == '\0' || i == 4)
				i = 4;
			else
			{
				for (i = 4; n[i] != '+'; i++)
				{
					switch (n[i])
					{
						case 'S': d |= ShiftMask   << 8; break;
						case 'C': d |= ControlMask << 8; break;
						case 'A': d |= Mod1Mask    << 8; break;
						case 'M': d |= Mod4Mask    << 8; break;
						default:  goto unrecog;
					}
				}

				i++;
			}

			if ((ks = XStringToKeysym(n + i)) == NoSymbol)
				goto unrecog;
			if ((kc = XKeysymToKeycode(GUI.display, ks)) == 0)
				goto unrecog;

			d |= kc & 0xff;

			return (S9xMapButton(d, *cmd, false));
		}

		case 'M':
		{
			char	*c;
			int		j;

			d |= 0x40000000;

			if (!strncmp(n + 4, "Pointer", 7))
			{
				d |= 0x8000;

				if (n[11] == '\0')
					return (S9xMapPointer(d, *cmd, true));

				i = 11;
			}
			else
			if (n[4] == 'B')
				i = 5;
			else
				goto unrecog;

			d |= j = strtol(n + i, &c, 10);

			if ((c != NULL && *c != '\0') || j > 0x7fff)
				goto unrecog;

			if (d & 0x8000)
				return (S9xMapPointer(d, *cmd, true));

			return (S9xMapButton(d, *cmd, false));
		}

		default:
			break;
	}

unrecog:
	char	*err = new char[strlen(n) + 34];

	sprintf(err, "Unrecognized input device name '%s'", n);
	perror(err);
	delete [] err;

	return (false);
}

bool S9xDisplayPollButton (uint32 id, bool *pressed)
{
	return (false);
}

bool S9xDisplayPollAxis (uint32 id, int16 *value)
{
	return (false);
}

bool S9xDisplayPollPointer (uint32 id, int16 *x, int16 *y)
{
	if ((id & 0xc0008000) != 0x40008000)
		return (false);

	int	d = (id >> 24) & 0x3f,
		n = id & 0x7fff;

	if (d != 0 || n != 0)
		return (false);

	*x = GUI.mouse_x;
	*y = GUI.mouse_y;

	return (true);
}

void S9xSetPalette (void)
{
	return;
}
