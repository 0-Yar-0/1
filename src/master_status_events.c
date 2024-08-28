#include <stdio.h>
#include "database.h"
#include <stdio.h>
#include <string.h>
#include "master_status_events.h"

int get_last_status(FILE *db, int module_id) {
    STATUS_EVENT event;
    STATUS_EVENT last_event;
    int found = 0;
    
    fseek(db, 0, SEEK_SET);
    while (fread(&event, sizeof(STATUS_EVENT), 1, db)) {
        if (event.module_id == module_id) {
            last_event = event;
            found = 1;
        }
    }

    if (found) {
        printf("Last status of module %d: %d on %s at %s\n", module_id, last_event.new_status, last_event.date, last_event.time);
        return last_event.new_status;
    }

    return -1;  // No status found
}

int set_protected_mode(FILE *db, int id) {
    STATUS_EVENT event;

    event.module_id = id;
    strcpy(event.date, "27.08.2024");

    fseek(db, 0, SEEK_END);
    fwrite(&event, sizeof(STATUS_EVENT), 1, db);

    fseek(db, 0, SEEK_END);
    fwrite(&event, sizeof(STATUS_EVENT), 1, db);

    return 0;
}

