/*
 * Copyright (c) 2005 William Pitcock, et al.
 * The rights to this code are as documented under doc/LICENSE.
 *
 * Meow!
 */

#include "atheme-compat.h"

static service_t *sandcatserv = NULL;

static void
sandcatserv_cmd_meow(sourceinfo_t *si, int parc, char *parv[])
{
	command_success_nodata(si, "Meow!");
}

static void
sandcatserv_cmd_help(sourceinfo_t *si, int parc, char *parv[])
{
	command_help(si, si->service->commands);
}

static command_t sandcatserv_meow = {
	.name           = "MEOW",
	.desc           = N_("Makes the cute little kitty-cat meow!"),
	.access         = AC_NONE,
	.maxparc        = 0,
	.cmd            = &sandcatserv_cmd_meow,
	.help           = { .path = "" },
};

static command_t sandcatserv_help = {
	.name           = "HELP",
	.desc           = N_("Displays contextual help information."),
	.access         = AC_NONE,
	.maxparc        = 1,
	.cmd            = &sandcatserv_cmd_help,
	.help           = { .path = "help" },
};

static void
mod_init(module_t *const restrict m)
{
	sandcatserv = service_add("sandcatserv", NULL);

	service_bind_command(sandcatserv, &sandcatserv_meow);
	service_bind_command(sandcatserv, &sandcatserv_help);
}

static void
mod_deinit(const module_unload_intent_t intent)
{
	service_unbind_command(sandcatserv, &sandcatserv_meow);
	service_unbind_command(sandcatserv, &sandcatserv_help);

	service_delete(sandcatserv);
}

SIMPLE_DECLARE_MODULE_V1("contrib/ircd_sandcatserv", MODULE_UNLOAD_CAPABILITY_OK)
