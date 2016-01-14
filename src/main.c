#include "fdf.h"

int main(void)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app_init(&app);
	app_run(&app);
	return (0);
}
