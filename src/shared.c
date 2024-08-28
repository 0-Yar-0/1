#include <stdlib.h>
#include "database.h"

ENTITY *select(FILE *db, int id) {
    ENTITY *entity = malloc(sizeof(ENTITY));
    if (entity == NULL) return NULL;

    fseek(db, id * sizeof(ENTITY), SEEK_SET);
    fread(entity, sizeof(ENTITY), 1, db);
    return entity;
}

int delete(FILE *db, int id) {
    ENTITY *entity = select(db, id);
    if (entity == NULL) return -1;

    entity->deleted = 1;
    fseek(db, id * sizeof(ENTITY), SEEK_SET);
    fwrite(entity, sizeof(ENTITY), 1, db);
    free(entity);
    return 0;
}

int insert(FILE *db, ENTITY *entity) {
    fseek(db, 0, SEEK_END);
    fwrite(entity, sizeof(ENTITY), 1, db);
    return 0;
}

int update(FILE *db, int id, ENTITY *entity) {
    fseek(db, id * sizeof(ENTITY), SEEK_SET);
    fwrite(entity, sizeof(ENTITY), 1, db);
    return 0;
}
