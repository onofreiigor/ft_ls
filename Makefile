NAME = ft_ls
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SOURCES_FLD_1 = src

INCLUDES_FLD_1 = include

OBJECTS_FLD = obj

PRINTF_FLD = printf

PRINTF = printf/libftprintf.a

OBJECTS_1 =\
	$(OBJECTS_FLD)/ft_create_list.o\
	$(OBJECTS_FLD)/ft_errors.o\
	$(OBJECTS_FLD)/ft_output.o\
	$(OBJECTS_FLD)/ft_output2.o\
	$(OBJECTS_FLD)/ft_r.o\
	$(OBJECTS_FLD)/ft_work_list.o\
	$(OBJECTS_FLD)/ft_pre_lists.o\
	$(OBJECTS_FLD)/ft_dif_func.o\
	$(OBJECTS_FLD)/main.o


INCLUDES_1 =\
	$(INCLUDES_FLD_1)/ls.h


all : $(NAME)

$(NAME) : $(PRINTF) $(OBJECTS_1) $(INCLUDES_1)
	$(CC) -I $(INCLUDES_FLD_1) $(PRINTF) $(CFLAGS) $(OBJECTS_1) -o $(NAME)

debug :
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -g $(SOURCES_FLD_1)/*.c -o $(NAME)_deb

clean :
	rm -rf $(OBJECTS_FLD)

fclean : clean
	make fclean -C $(PRINTF_FLD)
	rm -f $(NAME)

re : fclean all

dclean :
	rm -rf $(NAME)_deb*

dre : dclean debug

check_printf :
	make -C $(PRINTF_FLD)

$(OBJECTS_FLD)/ft_create_list.o : $(SOURCES_FLD_1)/ft_create_list.c $(HEADERS_1)
	@mkdir -p $(OBJECTS_FLD)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_create_list.c -o $(OBJECTS_FLD)/ft_create_list.o

$(OBJECTS_FLD)/ft_errors.o : $(SOURCES_FLD_1)/ft_errors.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_errors.c -o $(OBJECTS_FLD)/ft_errors.o

$(OBJECTS_FLD)/ft_output.o : $(SOURCES_FLD_1)/ft_output.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_output.c -o $(OBJECTS_FLD)/ft_output.o

$(OBJECTS_FLD)/ft_output2.o : $(SOURCES_FLD_1)/ft_output2.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_output2.c -o $(OBJECTS_FLD)/ft_output2.o

$(OBJECTS_FLD)/ft_r.o : $(SOURCES_FLD_1)/ft_r.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_r.c -o $(OBJECTS_FLD)/ft_r.o

$(OBJECTS_FLD)/ft_work_list.o : $(SOURCES_FLD_1)/ft_work_list.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_work_list.c -o $(OBJECTS_FLD)/ft_work_list.o

$(OBJECTS_FLD)/ft_pre_lists.o : $(SOURCES_FLD_1)/ft_pre_lists.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_pre_lists.c -o $(OBJECTS_FLD)/ft_pre_lists.o

$(OBJECTS_FLD)/ft_dif_func.o : $(SOURCES_FLD_1)/ft_dif_func.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/ft_dif_func.c -o $(OBJECTS_FLD)/ft_dif_func.o

$(OBJECTS_FLD)/main.o : $(SOURCES_FLD_1)/main.c $(HEADERS_1)
	$(CC) -I $(INCLUDES_FLD_1) $(CFLAGS) -c $(SOURCES_FLD_1)/main.c -o $(OBJECTS_FLD)/main.o

$(PRINTF) :
	make -C $(PRINTF_FLD)
