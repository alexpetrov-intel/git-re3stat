#include "builtin.h"
#include "trace.h"
#include "parse-options.h"
#include "config.h"
#include "revision.h"

static int git_walken_config(const char *var, const char *value, const struct config_context *ctx, void *cb){
    return git_default_config(var, value, ctx, cb);
}

int cmd_walken(int argc, const char **argv, const char *prefix){
    struct rev_info rev;
    // // -h handler
    // const char * const walken_usage[] = {
    //     N_("git_walken"),
    //     NULL,
    // };
    // struct option options = {
    //     OPT_END()
    // };

    // argc = parse_options(argc, argv, prefix, options, walken_usage, 0);

    git_config(git_walken_config, NULL);
    repo_init_revisions(the_repository, &rev, prefix); //left off here


    trace_printf(_("cmd_walken incomming...\n"));


    return 0;
}