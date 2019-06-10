#include "ft_printf.h"

static	int		write_data(t_arg *specs, int total_len, int fd)
{
	write(fd, specs->origin, total_len);
	free(specs->origin);
	free(specs);
	return (total_len);
}

int				ft_printf(const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vprintf(format, ap);
	va_end(ap);
	return (ret);
}

int				ft_vprintf(const char *format, va_list ap)
{
	return (ft_vdprintf(1, format, ap));
}

int				ft_dprintf(int fd, const char *format, ...)
{
	va_list		ap;
	int			ret;

	va_start(ap, format);
	ret = ft_vdprintf(fd, format, ap);
	va_end(ap);
	return (ret);
}

int				ft_vdprintf(int fd, const char *restrict f, va_list ap)
{
	t_arg	*specs;

	specs = NULL;
	if (!f || !(specs = create_specs(specs)))
		return (-1);
	while (*f)
	{
		if (*f == '%' && handle_perc((char **)&f, specs, ap))
		{
			if (specs->type == '%')
				print_perc(specs, *f);
			else
				parse_struct(specs, ap);
		}
		else if (*f)
			ft_strncat_move((char *)f, 1, specs);
		if (*f)
			f++;
	}
	if (specs->origin)
		return (write_data(specs, specs->string - specs->origin, fd));
	return (0);
}
