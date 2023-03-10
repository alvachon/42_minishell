
# --- PROJECT -
NAME			= minishell
UNAME_S		 	= 	$(shell uname -s)
REL_PATH		=	$(shell pwd)
# --- FILE ----
INCL_DIR		= ./includes
SRCS_DIR		= ./srcs
OBJS_DIR		= ./objs
SRCS			= $(SRCS_DIR)/minishell.c \
				  $(SRCS_DIR)/init.c \
				  $(SRCS_DIR)/lexer.c \
				  $(SRCS_DIR)/message.c \
				  $(SRCS_DIR)/z_echo.c
OBJS 			= $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
HDRS_FILE		= minishell.h
HDRS			= $(addprefix $(INCL_DIR)/, $(HDRS_FILE))
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HDRS)
	@$(CC) $(CFLAGS) -c $< -o $@
#
# --- FLAGS ---
AR				= ar
ARFLAGS			= rcs
CC				= gcc
CFLAGS			= -Wall -Wextra -Werror
RLFLAGS			= -lreadline -lncurses
# --- LIBRARY -
LIBFT_A 		= libft.a
LIBFT_DIR		= includes/libft
#
READLINE_A		= libreadline.a
RHISTORY_A		= libhistory.a
READLINE_DIR	= includes/librd
# --- MAKE ----
LIBFT			= $(LIBFT_DIR)/$(LIBFT_A)
READLINE_CONF	= $(READLINE_DIR)/Makefile
READLINE		= $(READLINE_DIR)/$(READLINE_A)
RHISTORY		= $(READLINE_DIR)/$(RHISTORY_A)
# --- COLOR ---
YELLOW			= '\033[0;33m'
GREEN			= '\033[0;32m'
GRAY			= '\033[2;37m'
RESET_COLOR		= '\033[0m'
# --- COMMAND -
REMOVE			= rm -rf
#
#
#
all: init $(READLINE_CONF) $(READLINE) $(LIBFT) $(NAME)

$(READLINE):
	@echo $(YELLOW) "\nIncoming :\n" $(RESET_COLOR)
	@make -s -C $(READLINE_DIR)
	@echo $(GREEN) "\nCompilation of readline lib done.\n" $(RESET_COLOR)

$(READLINE_CONF):
	@echo $(YELLOW) "\nIncoming :\n" $(RESET_COLOR)
	@cd $(READLINE_DIR) && ./configure --silent
	@echo $(GREEN) "\nConfiguration of readline lib done.\n" $(RESET_COLOR)

$(LIBFT):
	@echo $(YELLOW) "\nIncoming :\n" $(RESET_COLOR)
	@make -s -C $(LIBFT_DIR)
	@echo $(GREEN) "\nCompilation of libft lib done.\n" $(RESET_COLOR)

$(NAME): $(OBJS)
	@echo $(YELLOW) "\nIncoming :\n" $(RESET_COLOR)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) $(RHISTORY) $(RLFLAGS) $(LIBFT) -o $(NAME)
	@echo $(GREEN) "\nCompilation of minishell done.\n" $(RESET_COLOR)

init:
	@mkdir -p $(OBJS_DIR)

clean:
	@echo $(YELLOW) "\nRemoving object:\n" $(RESET_COLOR)
	$(REMOVE) $(OBJS) $(OBJS_DIR)
	@make -s -C $(LIBFT_DIR) clean
	@echo $(RESET_COLOR)$(GREEN) "OK - - - - - - - - - - \n" $(RESET_COLOR)

fclean: clean
	@echo $(YELLOW) "\nRemoving .a:\n" $(RESET_COLOR)
	@make -s -C $(LIBFT_DIR) fclean
	@make -s -C $(READLINE_DIR) clean
	$(REMOVE) $(NAME)
	$(REMOVE) minishell.dSYM
	@echo $(RESET_COLOR)$(GREEN) "OK - - - - - - - - - - \n" $(RESET_COLOR)

re: fclean all

.PHONY:	all clean fclean re init