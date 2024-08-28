#ifndef MASTER_LEVELS_H
#define MASTER_LEVELS_H

int get_level_info(FILE *db, int level_number);

int set_protection_flag(FILE *db, int level_number, int protection_flag);

#endif