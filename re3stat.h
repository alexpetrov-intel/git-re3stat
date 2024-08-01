#ifndef RE3STAT_H
#define RE3STAT_H

#include "rerere.h"
#include "commit.h"


void save_rr_stats(const char *path, struct rerere_id *id);
void write_history(struct rerere_id *id, const char *head_name, const char *stat_name);
void write_history_file(struct rerere_id *id, const char *path, const char *stat_name);

#endif