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
		gcc *.o

		# ar rc ${LIB} ${OBJS}
		# ranlib ${LIB}
		# ln -s $(LIB) $(LINK)

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES}

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${LIB}

		# unlink $(LINK)

re: fclean all