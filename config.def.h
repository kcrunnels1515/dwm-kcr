/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int igappx    = 5;        /* size of inner gaps */
static const unsigned int ogappx    = 5;        /* size of outer gaps */
static const int gapsforone	    = 0;	/* 1 enable gaps when only one window is open */
/* static const Gap default_gap	    = {.isgap = 1, .realgap = 10, .gappx =10}; */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;     /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= True;               /* False means bottom tab bar */

static const char *fonts[]          = { "Hack-Regular:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_green[]	    = "#465e25";
/* static const char col_
static const char col_
static const char col_ */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_green,  col_green  },
};

static const char *const autostart[] = {
	"nitrogen", "--restore", NULL,
	"picom", "--config", "/usr/local/share/dwm/picom.conf", NULL,
	"dunst", NULL,
	"/usr/lib/polkit-kde-authentication-agent-1", NULL,
	"numlockx", "on", NULL,
	"emacs", "--daemon", NULL,
	"volumeicon", NULL,
	"nm-applet", NULL, 
/*	"xrandr", "--output", "HDMI1", "--auto", "--right-of", "VGA1", NULL, */
	"dwmblocks", NULL,
	NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor    scratch key */
	{ "Gimp",     NULL,       NULL,       0,            0,           -1,        0  },
	{ "mpv",      NULL,       NULL,       0,            1,           -1,        0  },
	{ "firefox",  NULL,       NULL,       1 << 8,       0,           -1,        0  },
	{ NULL,       NULL,   "scratchpad",   0,            1,           -1,       's' },
};

/* layout(s) */
static const int dirs[3]      = { DirHor, DirVer, DirVer }; /* tiling dirs */
static const float facts[3]   = { 1.1,    1.1,    1.1 };    /* tiling facts */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define TILEKEYS(MOD,G,M,S) \
	{ MOD, XK_r, setdirs,  {.v = (int[])  { INC(G * +1),   INC(M * +1),   INC(S * +1) } } }, \
	{ MOD, XK_h, setfacts, {.v = (float[]){ INC(G * -0.1), INC(M * -0.1), INC(S * -0.1) } } }, \
	{ MOD, XK_l, setfacts, {.v = (float[]){ INC(G * +0.1), INC(M * +0.1), INC(S * +0.1) } } },

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

static Key keys[] = {
	/* modifier                     key        function        argument */
/*	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } }, */
	{ MODKEY|ShiftMask, 		XK_Return, spawn,          SHCMD("/usr/local/share/dwm/dmenu_run-better.sh")},
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_z,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_i,      setigaps,       {.i = +2 } },
	{ MODKEY|ControlMask,           XK_i,      setigaps,       {.i = -2 } },
	{ MODKEY|ShiftMask|ControlMask, XK_i,      setigaps,       {.i = 0  } },
	{ MODKEY|ShiftMask,             XK_o,      setogaps,       {.i = +2 } },
	{ MODKEY|ControlMask,           XK_o,      setogaps,       {.i = -2 } },
	{ MODKEY|ShiftMask|ControlMask, XK_o,      setogaps,       {.i = 0  } },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_s,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY, 			XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY,                       XK_Delete,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	/* Start extra keybinds */
	{ ControlMask|Mod1Mask,		XK_f,	   spawn,	   TERMCMD("ranger")},
	{ ControlMask|Mod1Mask,		XK_e,	   spawn,	   SHCMD("emacsclient -c -a 'nvim'")},
	{ ControlMask|Mod1Mask,		XK_t,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-system-actions.sh")},
	{ ControlMask|Mod1Mask,		XK_d,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-zathura.sh")},
	{ ControlMask|Mod1Mask,		XK_s,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-surfraw.sh")},
	{ MODKEY|Mod1Mask,		XK_b,	   spawn,	   SHCMD("/usr/local/share/dwm/bmks")},
	{ MODKEY|Mod1Mask,		XK_y,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenuyt.sh")},
	{ ControlMask|Mod1Mask,		XK_t,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-system-actions.sh")},
	{ ControlMask|Mod1Mask,		XK_d,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-zathura.sh")},
	{ ControlMask|Mod1Mask,		XK_s,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-surfraw.sh")},
	{ MODKEY|Mod1Mask,		XK_b,	   spawn,	   SHCMD("/usr/local/share/dwm/bmks")},
	{ MODKEY|Mod1Mask,		XK_y,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenuyt.sh")},
	{ MODKEY,			XK_c,	   spawn,	   SHCMD("/usr/local/share/dwm/plumb")},
	{ MODKEY|Mod1Mask,		XK_m,	   spawn,	   SHCMD("/usr/local/share/dwm/mapper.sh")},
	{ MODKEY|Mod1Mask,		XK_c,	   spawn,	   TERMCMD("R")},
/* End extra keybinds */
	{ MODKEY,                       XK_comma,   viewtoleft,     {0} },
	{ MODKEY,                       XK_period,  viewtoright,    {0} },
	{ MODKEY|ShiftMask,             XK_comma,   tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             XK_period,  tagtoright,     {0} },
	{ MODKEY,                       XK_bracketleft,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_bracketright, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_bracketright, tagmon,         {.i = +1 } },
	{ MODKEY, 			XK_KP_End,    movetoedge,       {.v = "-1 1" } },
	{ MODKEY, 			XK_KP_Down,   movetoedge,       {.v = "0 1" } },
	{ MODKEY, 			XK_KP_Next,   movetoedge,       {.v = "1 1" } },
	{ MODKEY, 			XK_KP_Left,   movetoedge,       {.v = "-1 0" } },
	{ MODKEY, 			XK_KP_Begin,  movetoedge,       {.v = "0 0" } },
	{ MODKEY, 			XK_KP_Right,  movetoedge,       {.v = "1 0" } },
	{ MODKEY, 			XK_KP_Home,   movetoedge,       {.v = "-1 -1" } },
	{ MODKEY, 			XK_KP_Up,     movetoedge,       {.v = "0 -1" } },
	{ MODKEY, 			XK_KP_Prior,  movetoedge,       {.v = "1 -1" } },
	TILEKEYS(MODKEY,                                           1, 0, 0)
	TILEKEYS(MODKEY|ShiftMask,                                 0, 1, 0)
	TILEKEYS(MODKEY|ControlMask,                               0, 0, 1)
	TILEKEYS(MODKEY|ShiftMask|ControlMask,                     1, 1, 1)
	{ MODKEY|ShiftMask,             XK_t,      setdirs,        {.v = (int[]){ DirHor, DirVer, DirVer } } },
	{ MODKEY|ControlMask,           XK_t,      setdirs,        {.v = (int[]){ DirVer, DirHor, DirHor } } },
	/*
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY,	                XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	*/
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,		XK_r,		quit,	  {1} },
	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
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
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

void
setlayoutex(const Arg *arg)
{
	setlayout(&((Arg) { .v = &layouts[arg->i] }));
}

void
viewex(const Arg *arg)
{
	view(&((Arg) { .ui = 1 << arg->ui }));
}

void
viewall(const Arg *arg)
{
	view(&((Arg){.ui = ~0}));
}

void
toggleviewex(const Arg *arg)
{
	toggleview(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagex(const Arg *arg)
{
	tag(&((Arg) { .ui = 1 << arg->ui }));
}

void
toggletagex(const Arg *arg)
{
	toggletag(&((Arg) { .ui = 1 << arg->ui }));
}

void
tagall(const Arg *arg)
{
	tag(&((Arg){.ui = ~0}));
}

