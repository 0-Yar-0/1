#ifndef MASTER_MODULES_H
#define MASTER_MODULES_H

int get_all_active_modules(FILE *db);

int move_module(FILE *db, int module_id, int new_level, int new_cell);

#endif