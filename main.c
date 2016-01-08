#include "mlx.h"

int main(void)
{
	int		i;
	int		j;
	void	*mlx;
	void	*win;

	i = 0;
	j = 0;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 420, 420, "42");
	while (i < 100)
	{
		while (j < 100)
		{
			mlx_pixel_put(mlx, win, i + 100, j + 100, 0xff0000);
			j++;
		}
		j = 0;
		i++;
	}
	while (1);
	return (0);
}
