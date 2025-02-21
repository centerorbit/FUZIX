/*
A C version of "fuzfetch" - a simple system info tool for FUZIX

Inspired by neofetch, but tailored for FUZIX environments.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "hardware/clocks.h"
// #include "pico/unique_id.h"

#define UNKNOWN "Unknown"

typedef struct {
    const char *label;
    char value[128];
} sysinfo_t;

void print_ascii_logo() {
    printf("   +------------------+\n");
    printf("   |  [==]  [==]  [==] |\n");
    printf("   |  [==]  [==]  [==] |\n");
    printf("   |  [==]  [==]  [==] |\n");
    printf("   +------------------+\n");
    printf("      |  |      |  |\n");
    printf("      |  |      |  |\n");
}

void fetch_system_info() {
    sysinfo_t info[] = {
        { "OS", "FUZIX" },
        { "Kernel", "0.4" },
        { "Arch", "RP2040" },
        { "Hostname", UNKNOWN },
        { "Uptime", UNKNOWN },
        { "Shell", UNKNOWN },
        { "CPU Frequency", UNKNOWN },
        { "Unique ID", UNKNOWN },
        { "Memory", "264 KB SRAM" },
        { NULL, "" }
    };

    // Get Uptime
    FILE *fp = popen("uptime", "r");
    if (fp) {
        fgets(info[4].value, sizeof(info[4].value), fp);
        pclose(fp);
    }

    // Get Shell
    char *shell = getenv("SHELL");
    if (shell) {
        strncpy(info[5].value, shell, sizeof(info[5].value) - 1);
    }

    // // Get CPU Frequency
    // snprintf(info[6].value, sizeof(info[6].value), "%d MHz", frequency_count_khz(CLOCKS_FC0_SRC_VALUE_CLK_SYS) / 1000);

    // // Get Unique ID
    // pico_unique_id_t uid;
    // pico_get_unique_id(&uid);
    // snprintf(info[7].value, sizeof(info[7].value), "%02x%02x%02x%02x%02x%02x%02x%02x",
    //          uid.id[0], uid.id[1], uid.id[2], uid.id[3], uid.id[4], uid.id[5], uid.id[6], uid.id[7]);

    // for (int i = 0; info[i].label != NULL; i++) {
    //     printf("%s: %s\n", info[i].label, info[i].value[0] ? info[i].value : UNKNOWN);
    // }
}

int main(int argc, char **argv) {
    print_ascii_logo();
    printf("\n");
    fetch_system_info();
    return 0;
}
