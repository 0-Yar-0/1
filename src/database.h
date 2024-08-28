#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

typedef struct {
    int module_id;
    char module_name[50];
    int memory_level;
    int memory_cell;
    int deleted;
} MODULE;

typedef struct {
    int event_id;
    int module_id;
    int new_status;
    char date[11];
    char time[9];
} STATUS_EVENT;

typedef struct {
    int level_number;
    int cell_count;
    int protection_flag;
} LEVEL;

typedef MODULE ENTITY;

ENTITY *select(FILE *db, int id);
int insert(FILE *db, ENTITY *entity);
int update(FILE *db, int id, ENTITY *entity);
int delete(FILE *db, int id);
int get_all_active_modules(FILE *db);
int set_protected_mode(FILE *db, int id);
int move_module(FILE *db, int id, int level, int cell);
int set_protection_flag(FILE *db, int level, int flag);

#endif /* DATABASE_H */
