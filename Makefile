# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: itkimura <itkimura@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 14:48:02 by itkimura          #+#    #+#              #
#    Updated: 2022/03/28 22:07:16 by itkimura         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Werror -Wextra
SRCS_DIR = ./srcs/
SRC_FILES = ft_printf.c print.c nbr.c str.c float.c format.c test.c
SRCS		= $(addprefix	$(SRCS_DIR), $(SRC_FILES))
OBJS		= $(addprefix	$(OBJS_DIR), $(SRC_FILES:.c=.o))
OBJS_DIR = ./objects/
INCL = -I ./includes/ -I ./libft/includes/
LIBFT = ./libft/libft.a


all: $(NAME)

$(NAME): $(OBJS)
	 make -s fclean -C ./libft && make -s -C ./libft
	 cp $(LIBFT) ./$(NAME)
	 ar rc $(NAME) $(OBJS)
	 ranlib $(NAME)

$(OBJS_DIR)%.o:	$(SRCS_DIR)%.c
	 mkdir -p $(OBJS_DIR)
	 gcc $(FLAGS) $(INCL) -o $@ -c $<

makelibft:

clean:
	@ rm -rf $(OBJS_DIR)
	@ make -s clean -C ./libft

fclean: clean
	@ rm -f $(NAME)
	@ make -s fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
