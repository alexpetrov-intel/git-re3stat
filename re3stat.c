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
	FILE *f;
	struct object_id oid;
	struct commit *commitptr = NULL;
	struct strbuf prettybuf = STRBUF_INIT;

	printf("===== RE3-STAT =====\n");
	printf("Current variant id: %s\n", id->collection->name);
	printf("Is working on path: %s\n", path);

	if(repo_get_oid(the_repository, "MERGE_HEAD", &oid) == 0) {

		//write to file
		printf("Writing current MERGE_HEAD to %s", rerere_path(id, "merge_list"));
		f = fopen(rerere_path(id, "merge_list"), "a");
		if (f){
			commitptr = lookup_commit(the_repository, &oid);
			strbuf_reset(&prettybuf);
			pp_commit_easy(CMIT_FMT_ONELINE, commitptr, &prettybuf);

			fputs(oid_to_hex(&oid), f);
			fputs(" ", f);
			fputs(prettybuf.buf, f);
			fputs("\n", f);
		} else {
			printf("Could not open file");
		}

		fclose(f);
	} else {
		printf("No MERGE_HEAD");
	}

	if(repo_get_oid(the_repository, "ORIG_HEAD", &oid) == 0) {
		commitptr = lookup_commit(the_repository, &oid);
		strbuf_reset(&prettybuf);
		strbuf_addstr(&prettybuf, "\nOn to ORIG_HEAD: \n");
		strbuf_addstr(&prettybuf, oid_to_hex(&oid));
		strbuf_addstr(&prettybuf, " - ");
		pp_commit_easy(CMIT_FMT_ONELINE, commitptr, &prettybuf);
		puts(prettybuf.buf);

	} else {
		printf("no ORIG_HEAD");
	}

	strbuf_release(&prettybuf);
	printf("====================\n");
}

void write_commit(const char *path, const char *head_name, struct commit *commitptr) {

}