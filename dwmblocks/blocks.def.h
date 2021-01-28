//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	{"Mem:", "free -h | awk '/^Mem/ { print $3\"/\"$2 }' | sed s/i//g",	5,		0},
	{ "  ", "iw wlp3s0 info | grep ssid | sed 's/	ssid//'", 60, 0},
/*	{ "Bat: ",	"acpi | awk '{print $4}' | sed 's/,/	/'",	15,	0}, */
	{"", "date '+%b %d (%a) %I:%M%p'",					5,		0},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim[] = " | ";
static unsigned int delimLen = 5;
