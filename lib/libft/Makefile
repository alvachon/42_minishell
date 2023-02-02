# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/19 08:48:33 by fboulang          #+#    #+#              #
#    Updated: 2022/04/19 08:48:55 by fboulang         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

AR = ar rc

ARB = ar rs

CC = gcc

CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

SRCS = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
		ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
		ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strnstr.c \
		ft_strrchr.c ft_tolower.c ft_toupper.c ft_substr.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_putendl_fd.c ft_putnbr_fd.c ft_strmapi.c ft_striteri.c \
		ft_itoa.c

SRCSB = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c

OBJS = $(SRCS:.c=.o)

OBJB = $(SRCSB:.c=.o)

all: $(NAME) $(SRCS)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS) 

clean: 
	$(RM) $(OBJS) $(OBJB)

bonus: $(NAME) $(OBJB)
	$(ARB) $(NAME) $(OBJB)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
