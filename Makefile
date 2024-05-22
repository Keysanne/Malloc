LIB=		libft_malloc_$(HOSTTYPE).so
LINK=		libft_malloc.so
COMPILER= 	gcc 
OBJS=		${FILES:.c=.o}
FILES=		malloc.c	\
			free.c		\
			realloc.c	\
			utils.c		

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

all: ${LIB}

${LIB}: ${OBJS}
			ar rc ${LIB} ${OBJS}
			ranlib ${LIB}
			ln -s $(LIB) $(LINK)

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES}

clean:
		rm -f ${OBJS}

fclean: clean
		unlink $(LINK)
		rm -f ${LIB}

re: fclean all