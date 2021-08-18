/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const int startwithgaps[]    = { 1, 0, 0, 1, 0 };	/* 1 means gaps are used by default, this can be customized for each tag */
static const unsigned int gappx[]   = { 10 };   /* default gap between windows in pixels, this can be customized for each tag */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;   	/* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "Hack-Regular:size=10" };
static const char dmenufont[]       = "Hack-Regular:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_purple[]	    = "#4c2172";
static const char col_cyan[]        = "#005577";
static const char col_green[]	    = "#465e25";
static const char col_black[]       = "#000000";
static const char col_red[]         = "#ff0000";
static const char col_yellow[]      = "#ffff00";
static const char col_white[]       = "#ffffff";


static const char *colors[][3]      = {
	/*                  fg         bg         border   */
	[SchemeNorm] =   { col_gray3, col_gray1,  col_gray2 },
	[SchemeInv] =    { col_gray3, col_purple, col_gray2 },
	[SchemeSel]  =   { col_gray4, col_green,  col_green  },
	[SchemeNet] =	 { col_black, col_green,  col_green },
	[SchemeStat] =	 { col_white, col_cyan,   col_cyan },
	[SchemeDate] =   { col_black, col_yellow, col_yellow },
};

static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
	"picom", NULL,
	"dunst", NULL,
	"/usr/lib/polkit-kde-authentication-agent-1", NULL,
	"numlockx", "on", NULL,
	"emacs", "--daemon", NULL,
	"volumeicon", NULL,
	"nm-applet", NULL,
	"aslstatus", NULL,
	"xset", "r", "rate", "300", "50", NULL,
	"setxkbmap", "-option", "caps:swapescape", NULL,
	"xset", "b", "off", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "dev", "web", "vid", "game", "misc" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      		instance    title          tags mask    floating   monitor    scratch key */
	{ "Gimp",     		NULL,       NULL,            1 << 4,     1,           -1,        0  },
	{ "firefox",  		NULL,       NULL,            1 << 1,     0,           -1,        0  },
        { "Brave-browser", 	NULL,	    NULL,            1 << 1,     0,           -1,	 0  },
        { "Minecraft Launcher", NULL, 	    NULL, 	     1 << 3,     1,            0,	 0  },
        { "VirtualBox Manager",	NULL,	    NULL,	     1 << 4,     1,            1,        0  },
	{ "VirtualBox Machine", NULL,	    NULL,	     1 << 4,     0,            0,        0  },
	{ "zoom",		NULL,	    NULL,	     1 << 4,     0,            1,        0  },
	{ "mpv",                NULL,       NULL,            1 << 2,	 0,	      -1,	 0  },
	{ "vlc",                NULL,       NULL,            1 << 2,	 0,	      -1,	 0  },
	{ "DarkPlaces",         NULL,       NULL,            1 << 3,	 0,	       0,	 0  },
	{ "Minecraft* 1.17.1",  NULL,       NULL,            1 << 3,	 0,	       0,	 0  },
	{ NULL,             	NULL,      "scratchpad",     0,          1,           -1,       's' },
	{ NULL,	                NULL,      "fmscratchpad",   0,	         0,           -1,       'f' },
	{ NULL,	                NULL,      "calcscratchpad", 0, 	 1,           -1,       'c' },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TERMCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *roficmd[] = { "rofi", "-show", "drun", "-show-icons", NULL };
static const char *termcmd[]  = { "st", NULL };
/*First arg only serves to match against key in rules*/
static const char *scratchpadcmd[] = {"s", "st", "-t", "scratchpad", NULL};
static const char *rangercmd[] = {"f", "st", "-t", "fmscratchpad", "-e", "ranger", NULL};
static const char *calccmd[] = {"c", "st", "-t", "calcscratchpad", "-e", "R", NULL};

#include "movestack.c"
static Key keys[] = {
	/* modifier                     chain key  key        function        argument */
        /* Basic utils */
	{ MODKEY|ShiftMask, 		-1,         XK_Return, spawn,          SHCMD("/usr/local/share/scripts/dmenu_run-better.sh")},
	{ MODKEY,	                -1,         XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             -1,         XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,                       -1,         XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             -1,	    XK_q,      killunsel,      {0} },
	{ MODKEY|ShiftMask,             -1,         XK_x,      quit,           {0} },
	{ MODKEY|ShiftMask,             -1,	    XK_r,      quit,           {1} },
	/* Scratchpads */
	{ MODKEY,                       -1,         XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             -1,         XK_grave,  togglescratch,  {.v = rangercmd } },
	{ MODKEY,		        XK_v,	    XK_c,      togglescratch,  {.v = calccmd } },
	/* Launchers */
	{ MODKEY,			-1,	    XK_o,	spawn,	       SHCMD("/usr/local/share/scripts/dmenufm")},
	{ Mod1Mask,                     XK_q,	    XK_f,	spawn,	       TERMCMD("ranger")},
	{ Mod1Mask,                     XK_q,	    XK_t,	spawn,	       SHCMD("systemctl suspend")},
	{ MODKEY,			-1,	    XK_Escape,  spawn,	       SHCMD("xkill")},
	{ Mod1Mask,                     XK_q,	    XK_s,	spawn,	       SHCMD("/usr/local/share/scripts/dmenu-surfraw.sh")},
	{ MODKEY|Mod1Mask,		-1,	    XK_b,	spawn,	       SHCMD("/usr/local/share/scripts/bmks")},
	{ Mod1Mask,                     XK_q,	    XK_y,	spawn,	       SHCMD("/usr/local/share/scripts/dmenuyt.sh")},
	{ MODKEY,			-1,	    XK_c,	spawn,	       SHCMD("/usr/local/share/scripts/plumb")},
	{ MODKEY|Mod1Mask,		-1,	    XK_m,	spawn,	       SHCMD("/usr/local/share/scripts/mapper.sh")},
	{ Mod1Mask,                     XK_q,	    XK_w,	spawn,	       SHCMD("brave")},
	{ Mod1Mask,                     XK_q,	    XK_m,	spawn,	       SHCMD("minecraft-launcher")},
	{ Mod1Mask,                     XK_d,	    XK_m,	spawn,	       SHCMD("/usr/local/share/scripts/dmenumount.sh")},
	{ Mod1Mask,                     XK_d,	    XK_u,	spawn,	       SHCMD("/usr/local/share/scripts/dmenuumount.sh")},
	{ Mod1Mask,                     XK_d,	    XK_r,	spawn,	       SHCMD("/usr/local/share/scripts/dmenu-scrot.sh")},
	{ Mod1Mask,                     XK_d,	    XK_o,	spawn,	       SHCMD("/usr/local/share/scripts/dmenu-emoji.sh")},
	{ MODKEY|Mod1Mask,              -1,         XK_f,       spawn,         SHCMD("pcmanfm")},
	{ ControlMask,                  XK_e,       XK_e,       spawn,         SHCMD("emacsclient -c -a 'emacs'")},
	{ ControlMask,                  XK_e,       XK_b,       spawn,         SHCMD("emacsclient -c -a 'emacs' --eval '(ibuffer)'")},
	{ ControlMask,                  XK_e,       XK_d,       spawn,         SHCMD("emacsclient -c -a 'emacs' --eval '(dired nil)'")},
	{ ControlMask,                  XK_e,       XK_a,       spawn,         SHCMD("emacsclient -c -a 'emacs' --eval '(emms)' --eval '(emms-play-directory-tree \"~/music\")'")},

	/* change screen layout and appearance */
	{ MODKEY,                       -1,         XK_b,      togglebar,      {0} },
	{ MODKEY,                       -1,         XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       -1,         XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             -1,	    XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,	    XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       -1,         XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       -1,         XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       -1,         XK_s,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       -1,         XK_space,  setlayout,      {0} },
	{ MODKEY,                       -1,         XK_Delete, togglefloating, {0} },
	{ MODKEY,                       -1,	    XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       -1,	    XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY,                       -1,	    XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             -1,	    XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY|ShiftMask,             -1,	    XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	/* Focusing windows and monitors */
	{ MODKEY,                       -1,         XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,         XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       -1,         XK_z,      zoom,           {0} },
	{ MODKEY,                       -1,         XK_Tab,    view,           {0} },
	{ MODKEY,                       -1,         XK_0,      view,      {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,         XK_0,      tag,       {.ui = ~0 } },
	{ MODKEY,                       -1,         XK_bracketleft,  focusmon,       {.i = -1 } },
	{ MODKEY,                       -1,         XK_bracketright, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,         XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,         XK_bracketright, tagmon,         {.i = +1 } },
	{ MODKEY,                       -1,         XK_comma,   viewtoleft,     {0} },
	{ MODKEY,                       -1,         XK_period,  viewtoright,    {0} },
	{ MODKEY|ShiftMask,             -1,	    XK_comma,   tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             -1,	    XK_period,  tagtoright,     {0} },
	TAGKEYS(                        -1,         XK_1,                      0)
	TAGKEYS(                        -1,         XK_2,                      1)
	TAGKEYS(                        -1,         XK_3,                      2)
	TAGKEYS(                        -1,         XK_4,                      3)
	TAGKEYS(                        -1,         XK_5,                      4)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTagBar,            0,              Button4,        viewtoleft,     {0} },
	{ ClkTagBar,            0,              Button5,        viewtoright,    {0} },
};
