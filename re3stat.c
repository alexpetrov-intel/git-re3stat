#define USE_THE_REPOSITORY_VARIABLE

#include "builtin.h"
#include "hex.h"
#include "object-name.h"
#include "pretty.h"
#include "re3stat.h"
#include "rerere.h"
#include "revision.h"
#include "strbuf.h"

struct rerere_dir {
	int status_alloc, status_nr;
	unsigned char *status;
	char name[FLEX_ARRAY];
};

void save_rr_stats(const char *path, struct rerere_id *id)
{
	printf("===== RE3-STAT =====\n");
	// printf("Current variant id: %s\n", id->collection->name);
	// printf("Is working on path: %s\n", path);

	write_history(id, "MERGE_HEAD", "merge_heads");
	write_history(id, "ORIG_HEAD", "orig_heads");
	write_history_file(id, path, "touched_files");

	printf("====================\n");
}

void write_history(struct rerere_id *id, const char *ref_name, const char *stat_name)
{
	FILE *f;
	struct object_id oid;
	struct commit *commit = NULL;
	struct strbuf outbuf = STRBUF_INIT;

	if(repo_get_oid(the_repository, ref_name, &oid) != 0){
		printf(_("No usable %s for logs"), ref_name);
		return;
	}

	strbuf_reset(&outbuf);
	commit = lookup_commit(the_repository, &oid);

	strbuf_addstr(&outbuf, oid_to_hex(&oid));
	strbuf_addstr(&outbuf, " ");
	pp_commit_easy(CMIT_FMT_ONELINE, commit, &outbuf);


	printf("Writing current MERGE_HEAD to %s", rerere_path(id, stat_name));
	f = fopen(rerere_path(id, stat_name), "a");
	if (!f){
		printf("Error writing to file");
		return;
	}

	fputs(outbuf.buf, f);
	fclose(f);
}

void write_history_file(struct rerere_id *id, const char *path, const char *stat_name) {
	FILE *f;

	printf("Writing current MERGE_HEAD to %s", rerere_path(id, stat_name));
	f = fopen(rerere_path(id, stat_name), "a");
	if (!f){
		printf("Error writing to file");
		return;
	}

	fputs(path, f);
	fputs("\n", f);
	fclose(f);
}