#ifndef RE3STAT_H
#define RE3STAT_H

#include "rerere.h"
#include "commit.h"


void save_rr_stats(const char *path, struct rerere_id *id);
void write_commit(const char *path, const char *head_name, struct commit *commitptr);

#endif