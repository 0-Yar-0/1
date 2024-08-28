#ifndef MASTER_MASTER_EVENTS_H
#define MASTER_MASTER_EVENTS_H

int get_last_status(FILE *db, int module_id);

int set_protected_mode(FILE *db, int id);

#endif