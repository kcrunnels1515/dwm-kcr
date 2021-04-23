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
static const char col_purple[]	    = "#4c2172";
static const char col_cyan[]        = "#005577";
static const char col_green[]	    = "#465e25";


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeInv] = { col_gray3, col_purple, col_gray2 },
	[SchemeSel]  = { col_gray4, col_green,  col_green  },
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
	"dwmblocks", NULL,
	"xset", "r", "rate", "300", "50", NULL,
	"setxkbmap", "-option", "caps:swapescape", NULL,
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
	{ "Gimp",     NULL,       NULL,     	  0,            0,           -1,        0  },
	{ "mpv",      NULL,       NULL,     	  0,            1,           -1,        0  },
	{ "zoom",      NULL,       NULL,     	  0,            0,            1,        0  },
	{ "Zoom Meeting",      NULL,       NULL,     	  0,            0,            1,        0  },
	{ NULL,       NULL,    "scratchpad",	  0,            1,           -1,       's' },
	{ NULL,	      NULL,    "fmscratchpad",	  0,		0,	     -1,       'f' },
	{ NULL,	      NULL,    "calcscratchpad",  0,		1,	     -1,       'c' },
};

/* layout(s) */
static const int dirs[3]      = { DirHor, DirVer, DirVer }; /* tiling dirs */
static const float facts[3]   = { 1.1,    1.1,    1.1 };    /* tiling facts */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int attachdirection = 3;    /* 0 default, 1 above, 2 aside, 3 below, 4 bottom, 5 top */

/* window swallowing */
static const int swaldecay = 3;
static const int swalretroactive = 1;
static const char swalsymbol[] = "👅";

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[M]",      monocle },
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "HHH",      grid },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                      CHAIN,	KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,          CHAIN,	KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,            CHAIN,	KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask,CHAIN,	KEY,      toggletag,      {.ui = 1 << TAG} },

#define TILEKEYS(MOD,CHAIN,G,M,S) \
	{ MOD,	CHAIN,	XK_r, setdirs,  {.v = (int[])  { INC(G * +1),   INC(M * +1),   INC(S * +1) } } }, \
	{ MOD,	CHAIN,	XK_h, setfacts, {.v = (float[]){ INC(G * -0.1), INC(M * -0.1), INC(S * -0.1) } } }, \
	{ MOD,	CHAIN,	XK_l, setfacts, {.v = (float[]){ INC(G * +0.1), INC(M * +0.1), INC(S * +0.1) } } },

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

static Key keys[] = {
	/* modifier                     chain key   key        function        argument */
/*	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = dmenucmd } }, */
	{ MODKEY|ShiftMask, 		-1,	XK_Return, spawn,          SHCMD("/usr/local/share/dwm/dmenu_run-better.sh")},
	{ MODKEY,	                -1,	XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             -1,	XK_d,      spawn,          {.v = roficmd } },
	{ MODKEY,                       -1,	XK_grave,  togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY|ShiftMask,             -1,	XK_grave,  togglescratch,  {.v = rangercmd } },
	{ MODKEY,                       -1,	XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,             -1,	XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,	XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,                       -1,	XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       -1,	XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ControlMask,             -1,	XK_j,      pushdown,       {.i = +1 } },
	{ MODKEY|ControlMask,             -1,	XK_k,      pushup,         {.i = -1 } },
	{ MODKEY,                       -1,	XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       -1,	XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       -1,	XK_z,      zoom,           {0} },
	{ MODKEY,                       -1,	XK_Tab,    view,           {0} },
	{ MODKEY,	                -1,	XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             -1,	XK_i,      setigaps,       {.i = +2 } },
	{ MODKEY|ControlMask,           -1,	XK_i,      setigaps,       {.i = -2 } },
	{ MODKEY|ShiftMask|ControlMask, -1,	XK_i,      setigaps,       {.i = 0  } },
	{ MODKEY|ShiftMask,             -1,	XK_o,      setogaps,       {.i = +2 } },
	{ MODKEY|ControlMask,           -1,	XK_o,      setogaps,       {.i = -2 } },
	{ MODKEY|ShiftMask|ControlMask, -1,	XK_o,      setogaps,       {.i = 0  } },
	{ MODKEY,                       -1,	XK_m,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       -1,	XK_t,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       -1,	XK_s,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       -1,	XK_g,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY, 			-1,	XK_f,      togglefullscr,  {0} },
	{ MODKEY,                       -1,	XK_space,  setlayout,      {0} },
	{ MODKEY,                       -1,	XK_Delete,  togglefloating, {0} },
	{ MODKEY,                       -1,	XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             -1,	XK_0,      tag,            {.ui = ~0 } },
	/* Start extra keybinds */
	{ MODKEY|Mod1Mask,		-1,	XK_w,	   spawn,	   SHCMD("xdotool mousemove_relative -- 0 -10")},
	{ MODKEY|Mod1Mask,		-1,	XK_s,	   spawn,	   SHCMD("xdotool mousemove_relative -- 0 10")},
	{ MODKEY|Mod1Mask,		-1,	XK_a,	   spawn,	   SHCMD("xdotool mousemove_relative -- -10 0")},
	{ MODKEY|Mod1Mask,		-1,	XK_d,	   spawn,	   SHCMD("xdotool mousemove_relative -- 10 0")},
	{ MODKEY,			-1,	XK_o,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenufm")},
	{ MODKEY,			XK_n,	XK_j,	   spawn,	   SHCMD("xdotool click --clearmodifiers 1")},
	{ MODKEY,			XK_n,	XK_k,	   spawn,	   SHCMD("xdotool click --clearmodifiers 3")},
	{ MODKEY,			XK_v,	XK_f,	   spawn,	   TERMCMD("ranger")},
	{ MODKEY,			XK_v,	XK_e,	   spawn,	   SHCMD("emacsclient -c -a 'nvim'")},
	{ MODKEY,			XK_v,	XK_t,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-system-actions.sh")},
	{ MODKEY,			-1,	XK_Escape, spawn,	   SHCMD("xkill")},
	{ MODKEY,			XK_v,	XK_s,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-surfraw.sh")},
	{ MODKEY|Mod1Mask,		-1,	XK_b,	   spawn,	   SHCMD("/usr/local/share/dwm/bmks")},
	{ MODKEY,			XK_v,	XK_y,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenuyt.sh")},
	{ MODKEY,			-1,	XK_c,	   spawn,	   SHCMD("/usr/local/share/dwm/plumb")},
	{ MODKEY|Mod1Mask,		-1,	XK_m,	   spawn,	   SHCMD("/usr/local/share/dwm/mapper.sh")},
	{ MODKEY,			XK_v,	XK_w,	   spawn,	   SHCMD("brave")},
	{ MODKEY,			XK_v,	XK_m,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenumount.sh")},
	{ MODKEY,			XK_v,	XK_u,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenuumount.sh")},
	{ MODKEY,			XK_v,	XK_r,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-scrot.sh")},
	{ MODKEY,			XK_v,	XK_o,	   spawn,	   SHCMD("/usr/local/share/dwm/dmenu-emoji.sh")},
	{ MODKEY,			XK_v,	XK_slash,  spawn,	   SHCMD("groff -mandoc -Tpdf /usr/local/man/man1/dwm.1 | zathura -")},
	{ MODKEY,		        XK_v,	XK_c,  	   togglescratch,  {.v = calccmd } },
/* End extra keybinds */
	{ MODKEY,                       -1,	XK_comma,   viewtoleft,     {0} },
	{ MODKEY,                       -1,	XK_period,  viewtoright,    {0} },
	{ MODKEY|ShiftMask,             -1,	XK_comma,   tagtoleft,      {0} },
	{ MODKEY|ShiftMask,             -1,	XK_period,  tagtoright,     {0} },
	{ MODKEY,                       -1,	XK_bracketleft,  focusmon,       {.i = -1 } },
	{ MODKEY,                       -1,	XK_bracketright, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             -1,	XK_bracketleft,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             -1,	XK_bracketright, tagmon,         {.i = +1 } },
	{ MODKEY,                       -1,	XK_u,      swalstopsel,    {0} },
	{ MODKEY, 			-1,	XK_KP_End,    movetoedge,       {.v = "-1 1" } },
	{ MODKEY, 			-1,	XK_KP_Down,   movetoedge,       {.v = "0 1" } },
	{ MODKEY, 			-1,	XK_KP_Next,   movetoedge,       {.v = "1 1" } },
	{ MODKEY, 			-1,	XK_KP_Left,   movetoedge,       {.v = "-1 0" } },
	{ MODKEY, 			-1,	XK_KP_Begin,  movetoedge,       {.v = "0 0" } },
	{ MODKEY, 			-1,	XK_KP_Right,  movetoedge,       {.v = "1 0" } },
	{ MODKEY, 			-1,	XK_KP_Home,   movetoedge,       {.v = "-1 -1" } },
	{ MODKEY, 			-1,	XK_KP_Up,     movetoedge,       {.v = "0 -1" } },
	{ MODKEY, 			-1,	XK_KP_Prior,  movetoedge,       {.v = "1 -1" } },
	TILEKEYS(MODKEY,                                  -1,        1, 0, 0)
	TILEKEYS(MODKEY|ShiftMask,                        -1,        0, 1, 0)
	TILEKEYS(MODKEY|ControlMask,                      -1,        0, 0, 1)
	TILEKEYS(MODKEY|ShiftMask|ControlMask,            -1,        1, 1, 1)
	{ MODKEY|ShiftMask,         -1,   XK_t,      setdirs,        {.v = (int[]){ DirHor, DirVer, DirVer } } },
	{ MODKEY|ControlMask,       -1,   XK_t,      setdirs,        {.v = (int[]){ DirVer, DirHor, DirHor } } },
	/*
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
	{ MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = +5 } },
	{ MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
	{ MODKEY,	                XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
	*/
	TAGKEYS(                        -1,	XK_1,                      0)
	TAGKEYS(                        -1,	XK_2,                      1)
	TAGKEYS(                        -1,	XK_3,                      2)
	TAGKEYS(                        -1,	XK_4,                      3)
	TAGKEYS(                        -1,	XK_5,                      4)
	TAGKEYS(                        -1,	XK_6,                      5)
	TAGKEYS(                        -1,	XK_7,                      6)
	TAGKEYS(                        -1,	XK_8,                      7)
	TAGKEYS(                        -1,	XK_9,                      8)
	{ MODKEY|ShiftMask,		-1,	XK_r,		quit,	  {1} },
	{ MODKEY|ShiftMask,             -1,	XK_x,      quit,           {0} },
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
	{ ClkClientWin,         MODKEY|Mod1Mask, Button1,      movemouse,      {.i = 1} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkClientWin,         MODKEY|Mod1Mask, Button3,      resizemouse,    {.i = 1} },
	{ ClkClientWin,         MODKEY|ShiftMask, Button1,      swalmouse,      {0} },
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

static const char *dwmfifo = "/tmp/dwm.fifo";
static Command commands[] = {
	{ "term",            spawn,          {.v = termcmd} },
	{ "quit",            quit,           {0} },
	{ "restart",         quit,           {1} },
	{ "togglebar",       togglebar,      {0} },
	{ "focusstack+",     focusstack,     {.i = +1} },
	{ "focusstack-",     focusstack,     {.i = -1} },
	{ "incnmaster+",     incnmaster,     {.i = +1} },
	{ "incnmaster-",     incnmaster,     {.i = -1} },
	{ "rotatestack-",    rotatestack,    {.i = +1 } },
	{ "rotatestack+",    rotatestack,    {.i = -1 } },
	{ "pushdown",	     pushdown,       {.i = +1 } },
	{ "pushup",	     pushup,         {.i = -1 } },
	{ "zoom",            zoom,           {0} },
	{ "swapview",        view,           {0} },
	{ "killclient",      killclient,     {0} },
	{ "setlayout-mono",  setlayout,      {.v = &layouts[0]} },
	{ "setlayout-tiled", setlayout,      {.v = &layouts[1]} },
	{ "setlayout-float", setlayout,      {.v = &layouts[2]} },
	{ "setlayout-grid",  setlayout,      {.v = &layouts[0]} },
	{ "togglelayout",    setlayout,      {0} },
	{ "togglefloating",  togglefloating, {0} },
	{ "togglefullscr",   togglefullscr,  {0} },
	{ "viewall",         view,           {.ui = ~0} },
	{ "sendall",         tag,            {.ui = ~0} },
	{ "focusmon+",       focusmon,       {.i = +1} },
	{ "focusmon-",       focusmon,       {.i = -1} },
	{ "tagmon+",         tagmon,         {.i = +1} },
	{ "tagmon-",         tagmon,         {.i = -1} },
	{ "view1",           view,           {.ui = 1 << 0} },
	{ "view2",           view,           {.ui = 1 << 1} },
	{ "view3",           view,           {.ui = 1 << 2} },
	{ "view4",           view,           {.ui = 1 << 3} },
	{ "view5",           view,           {.ui = 1 << 4} },
	{ "view6",           view,           {.ui = 1 << 5} },
	{ "view7",           view,           {.ui = 1 << 6} },
	{ "view8",           view,           {.ui = 1 << 7} },
	{ "view9",           view,           {.ui = 1 << 8} },
	{ "toggleview1",     toggleview,     {.ui = 1 << 0} },
	{ "toggleview2",     toggleview,     {.ui = 1 << 1} },
	{ "toggleview3",     toggleview,     {.ui = 1 << 2} },
	{ "toggleview4",     toggleview,     {.ui = 1 << 3} },
	{ "toggleview5",     toggleview,     {.ui = 1 << 4} },
	{ "toggleview6",     toggleview,     {.ui = 1 << 5} },
	{ "toggleview7",     toggleview,     {.ui = 1 << 6} },
	{ "toggleview8",     toggleview,     {.ui = 1 << 7} },
	{ "toggleview9",     toggleview,     {.ui = 1 << 8} },
	{ "tag1",            tag,            {.ui = 1 << 0} },
	{ "tag2",            tag,            {.ui = 1 << 1} },
	{ "tag3",            tag,            {.ui = 1 << 2} },
	{ "tag4",            tag,            {.ui = 1 << 3} },
	{ "tag5",            tag,            {.ui = 1 << 4} },
	{ "tag6",            tag,            {.ui = 1 << 5} },
	{ "tag7",            tag,            {.ui = 1 << 6} },
	{ "tag8",            tag,            {.ui = 1 << 7} },
	{ "tag9",            tag,            {.ui = 1 << 8} },
	{ "toggletag1",      toggletag,      {.ui = 1 << 0} },
	{ "toggletag2",      toggletag,      {.ui = 1 << 1} },
	{ "toggletag3",      toggletag,      {.ui = 1 << 2} },
	{ "toggletag4",      toggletag,      {.ui = 1 << 3} },
	{ "toggletag5",      toggletag,      {.ui = 1 << 4} },
	{ "toggletag6",      toggletag,      {.ui = 1 << 5} },
	{ "toggletag7",      toggletag,      {.ui = 1 << 6} },
	{ "toggletag8",      toggletag,      {.ui = 1 << 7} },
	{ "toggletag9",      toggletag,      {.ui = 1 << 8} },
	{ "viewtoleft",      viewtoleft,     {0} },
	{ "viewtoright",     viewtoright,    {0} },
	{ "viewtoleft",      tagtoleft,      {0} },
	{ "viewtoright",     tagtoright,     {0} },
	{ "stopswal",        swalstopsel,    {0} },
	{ "move1",	     movetoedge,     {.v = "-1 1" } },
	{ "move2",	     movetoedge,     {.v = "0 1" } },
	{ "move3",	     movetoedge,     {.v = "1 1" } },
	{ "move4",	     movetoedge,     {.v = "-1 0" } },
	{ "move5",	     movetoedge,     {.v = "0 0" } },
	{ "move6",	     movetoedge,     {.v = "1 0" } },
	{ "move7",	     movetoedge,     {.v = "-1 -1" } },
	{ "move8",	     movetoedge,     {.v = "0 -1" } },
	{ "move9",	     movetoedge,     {.v = "1 -1" } },
	{ "tilenorm",	     setdirs,        {.v = (int[]){ DirHor, DirVer, DirVer } } },
	{ "tiletop",	     setdirs,        {.v = (int[]){ DirVer, DirHor, DirHor } } },
	{ "innergapsinc",	setigaps,       {.i = +2 } },
	{ "innergapsdec",	setigaps,       {.i = -2 } },
	{ "innergapsoff",	setigaps,       {.i = 0  } },
	{ "outergapsinc",	setogaps,       {.i = +2 } },
	{ "outergapsdec",	setogaps,       {.i = -2 } },
	{ "outergapsoff",	setogaps,       {.i = 0  } },
};
