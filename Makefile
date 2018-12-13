##
## makefile Oiram Sorb
## Christophe DUFOUR
## Walid BEN SAID
##

CC		=	gcc

CFLAGS		+=	-I $(DIRINC)	\
			-Wall -Wextra -W	\
			-g `sdl-config --cflags --libs` 



LDFLAGS		+=	-lm -lSDL_mixer -lSDL_image -lSDL_ttf

DIRLIB		+=	lib/

DIRSRC		+=	src/


DIRINC		+=	include/

SRC		+=	$(DIRSRC)events.c		\
			$(DIRSRC)jeu.c			\
			$(DIRSRC)map.c			\
			$(DIRSRC)perso.c		\
			$(DIRSRC)main.c			\
			$(DIRSRC)ennemies.c		\


OBJ		=	$(SRC:.c=.o)

EXEC		=	jeu

all:		$(EXEC)

$(EXEC):	$(OBJ)
		$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(EXEC)

re:		fclean all

.PHONY:		all clean fclean re
