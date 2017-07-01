# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frmarinh <frmarinh@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/20 17:57:50 by frmarinh          #+#    #+#              #
#    Updated: 2017/06/27 16:30:12 by frmarinh         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_FAMINE	=	Famine

NAME		=   Famine
NAMEBASE    =   $(shell basename $(NAME))
LENGTHNAME	=	`printf "%s" $(NAMEBASE) | wc -c`
MAX_COLS	=	$$(echo "$$(tput cols)-24-$(LENGTHNAME)"|bc)

CC			=	gcc -ggdb
#FLAGS		=	-Wall -Wextra -Werror
FLAGS_O		=

SRCDIR_FAMINE		=	srcs/
OBJDIR_FAMINE		=	objs/

INCDIR				=	includes/
LIBFT_DIR			=	libft/
LIBFT_LIB			=	$(LIBFT_DIR)libft.a

SRCBASE_FAMINE	=	\
					main.c
INCS			=	$(addprefix $(INCDIR), $(INCBASE))

SRCS_FAMINE			=	$(addprefix $(SRCDIR_FAMINE), $(SRCBASE_FAMINE))
OBJS_FAMINE			=	$(addprefix $(OBJDIR_FAMINE), $(SRCBASE_FAMINE:.c=.o))

.SILENT:

all:		$(NAME)

$(NAME):
	if test -f $(NAME_FAMINE) ; then												\
		echo "make: Nothing to be done for \`all\`.";				        		\
	else																			\
		make FAMINE && 																\
		echo "\r\033[38;5;184m👥  AUTHOR(s): \033[0m\033[K" && 						\
		echo "\r\033[38;5;15m`cat auteur | sed s/^/\ \ \ \ -/g`\033[0m\033[K" &&	\
		echo "\033[38;5;44m☑️  ALL    $(NAMEBASE) is done\033[0m\033[K";				\
	fi

$(OBJDIR_FAMINE):
	mkdir -p $(OBJDIR_FAMINE)
	mkdir -p $(dir $(OBJS_FAMINE))

$(OBJDIR_FAMINE)%.o : $(SRCDIR_FAMINE)%.c | $(OBJDIR_FAMINE)
	$(CC) $(FLAGS) -MMD -c $< -o $@											\
		-I $(LIBFT_DIR)$(INCDIR)											\
		-I $(INCDIR)
	printf "\r\033[38;5;11m%s%*.*s\033[0m\033[K"							\
		"⌛  MAKE          wait ..."										\
		$(MAX_COLS) $(MAX_COLS) "($(@))"

fcleanlib:	fclean
	make -C $(LIBFT_DIR) fclean

re:			fclean all

relib:		fclean fcleanlib all

.PHONY:		fclean fcleanlib clean re relib

FAMINE: $(OBJDIR_FAMINE) $(OBJS_FAMINE)
	make -C $(LIBFT_DIR)
	$(CC) $(FLAGS) $(FLAGS_O) -o $(NAME_FAMINE) $(OBJS_FAMINE) $(LIBFT_LIB)
	echo "\r\033[38;5;22m📗  MAKE $(NAME_FAMINE)"

clean:
	printf "\r\033[38;5;11m⌛  CLEAN  $(NAME_FAMINE) pls wait ...\033[0m\033[K"
	if [[ `rm -R $(OBJDIR_FAMINE) &> /dev/null 2>&1; echo $$?` == "0" ]]; then	\
		echo "\r\033[38;5;124m📕  CLEAN  $(NAME_FAMINE)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi

fclean:		clean
	printf "\r\033[38;5;11m⌛  FCLEAN $(NAME_FAMINE) pls wait ...\033[0m\033[K"
	if [[ `rm $(NAME_FAMINE) &> /dev/null 2>&1; echo $$?` == "0" ]]; then			\
		echo "\r\033[38;5;124m📕  FCLEAN $(NAME_FAMINE)\033[0m\033[K";			\
	else																	    \
		printf "\r";														    \
	fi

-include $(OBJS:.o=.d)
