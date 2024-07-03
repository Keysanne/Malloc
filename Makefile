LIB=		libft_malloc_$(HOSTTYPE).so
LINK=		libft_malloc.so
COMPILER= 	gcc 
OBJS=		${FILES:.c=.o}
FILES=		malloc.c		\
			free.c			\
			realloc.c		\
			malloc_utils.c	\
			show_alloc_mem.c

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: ${LIB}

${LIB}: ${OBJS}
		ar rc ${LIB} ${OBJS}
		ln -sf $(LIB) $(LINK)
		ranlib ${LIB}

%.o:	%.c
		$(COMPILER) -c $< -o $@

clean:
		rm -f ${OBJS}
		make clean -C libft_malloc

fclean: clean
		rm -f ${LIB} libft raw
		unlink $(LINK)
		make fclean -C libft_malloc

test:
	make -C libft_malloc
	gcc main_libft.c libft_malloc/libft -o libft
	gcc main_raw.c libft_malloc.so -o raw

re: fclean all
