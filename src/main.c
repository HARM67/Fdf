#include "fdf.h"

int main(int ac, char **av)
{
	t_app	app;

	ft_bzero(&app, sizeof(t_app));
	app.ac = ac; 
	app.av = av;
	app_init(&app);
	app_run(&app);
	return (0);
}
