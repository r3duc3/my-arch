/* File indicating AC is present */
#define AC_FILE		"/sys/class/power_supply/AC/online"

/* Directory for battery presence */
#define BAT_DIR		"/sys/class/power_supply/BAT1"

/* File with battery value */
#define BAT_CAPFILE	BAT_DIR "/capacity"

/* File with battery drain information in milliwatts */
#define BAT_DRAIN_FILE	BAT_DIR "/power_now"

/* Which sound card volume to display */
#define SOUNDCARD	"default"

#define SOUNDCONTROL	"Master"
