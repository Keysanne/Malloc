LIB=		libft
COMPILER= 	gcc 
OBJS=		${FILES:.c=.o}
FILES=		ft_calloc.c 	\
			ft_itoa.c		\
			ft_split.c		\
			ft_strdup.c		\
			ft_strjoin.c	\
			ft_strtrim.c	\
			ft_substr.c

all: ${LIB}

${LIB}: ${OBJS}
		ar rc ${LIB} ${OBJS} ../libft_malloc.so
		ranlib ${LIB}

${OBJS}: ${FILES}
		${COMPILER} -c ${FILES}

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f ${LIB}

re: fclean all
