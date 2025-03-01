/* Enable to make ^Z dump the inode table for debug */
#undef CONFIG_IDUMP
/* Enable to make ^A drop back into the monitor */
#undef CONFIG_MONITOR
/* Profil syscall support (not yet complete) */
#undef CONFIG_PROFIL
/* Multiple processes in memory at once */
#define CONFIG_MULTI

/* Select a banked memory set up */
#define CONFIG_BANK_FIXED
/* This is the number of banks of user memory available (maximum) */
#define MAX_MAPS	63		/* 2MB... minus the high one */
/* How big is each bank - in our case 32K, 48K is actually more common. This
   is hardware dependant */
#define MAP_SIZE	0x8000
/* How many banks do we have in our address space */
#define CONFIG_BANKS	2	/* 2 x 32K */

/*
 *	Define the program loading area (needs to match kernel.def)
 */
#define PROGBASE    0x0000  /* Base of user  */
#define PROGLOAD    0x0100  /* Load and run here */
#define PROGTOP     0x7E00  /* Top of program, base of U_DATA stash */
#define PROC_SIZE   32 	    /* Memory needed per process including stash */

/* 	So much RAM we don't bother with swap */
#define CONFIG_TD_NUM		4
/* RC2014 style CF IDE */
#define CONFIG_TD_IDE
#define CONFIG_TINYIDE_8BIT
#define CONFIG_TINYIDE_INDIRECT
#define IDE_IS_8BIT(x)	1

#define BOOTDEVICENAMES "hd#"

/* We will resize the buffers available after boot. This is the normal setting */
#define CONFIG_DYNAMIC_BUFPOOL

/* Larger transfers (including process execution) should go directly not via
   the buffer cache. For all small (eg bit) systems this is the right setting
   as it avoids polluting the small cache with data when it needs to be full
   of directory and inode information */
#define CONFIG_LARGE_IO_DIRECT(x)	1

/* Specify this if there is a real time clock capable of reporting seconds. It
   will be used to lock the kernel time better to reality. Other details like
   Y2K support, or even supporting dates as well don't matter */
#define CONFIG_RTC_DS1302
#define CONFIG_RTC
/* Specify that there is a full real time clock that can supply the date and
   time to the system. */
#define CONFIG_RTC_FULL
/* Set this if the system has no proper real time clock (or has configurations
   where it lacks one). This is not usually needed but for platforms it is also
   see platform-sbcv2/main.c on what is needed */
#define CONFIG_NO_CLOCK
/* Set how often we actually poll this RTC in ticks - 1 means always. On the
   SBCv2 it's slow so don't sync often. If we have no timer tick then we will
   read the RTC regularly as needed - and it'll suck accordingly regardless
   of this setting */
#define CONFIG_RTC_INTERVAL	100
/*
 * How fast does the clock tick (if present), or how many times a second do
 * we simulate if not. For a machine without video 10 is a good number. If
 * you have video you probably want whatever vertical sync/blank interrupt
 * rate the machine has. For many systems it's whatever the hardware gives
 * you.
 *
 * Note that this needs to be divisible by 10 and at least 10. If your clock
 * is a bit slower you may need to fudge things somewhat so that the kernel
 * gets 10 timer interrupt calls per second. 
 */
#define TICKSPERSEC 10	    /* Ticks per second */

/* Core networking support */
#define CONFIG_NET
/* With a WizNet card */
#define CONFIG_NET_WIZNET
#define CONFIG_NET_W5100
/* Or native (eg SLIP) */
/*#define CONFIG_NET_NATIVE */

/*
 *	The device (major/minor) for the console and boot up tty attached to
 *	init at start up. 512 is the major 2, so all the tty devices are
 *	512 + n where n is the tty.
 */
#define BOOT_TTY (512 + 1)      /* Set this to default device for stdio, stderr */
                          /* In this case, the default is the first TTY device */
/*
 *	If you have a mechanism to pass in a root device configuration then
 *	this holds the address of the buffer (eg a CP/M command line or similar).
 *	If the configuration is fixed then this can be a string holding the
 *	configuration. NULL means 'prompt the user'.
 */
#define CMDLINE	NULL	  /* Location of root dev name */

/* Device parameters */
#define NUM_DEV_TTY 1	  /* How many tty devices does the platform support */
#define TTYDEV   BOOT_TTY /* Device used by kernel for messages, panics */
#define NBUFS    5        /* Number of block buffers. Must be 4+ and must match
                             kernel.def */
#define NMOUNTS	 4	  /* Number of mounts at a time */

/* This can optionally be set to force a default baud rate, eg if the system
   console should match a firmware set rate */
#define TTY_INIT_BAUD B115200	/* Actually fixed */

#define plt_copyright()
