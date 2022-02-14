test:
	bash ./test.sh
printf:
	gcc -Wall -Wextra -Werror ft_printf.c -I./libft/includes -L./libft/ -lft -D TEST -o printf

ft_printf:
	gcc -Wall -Wextra -Werror ft_printf.c --I./libft/includes L./libft/ -lft -D TEST -D FT_PRINTF -o ft_printf

clean:
	rm printf ft_printf
