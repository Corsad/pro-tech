CC=clang
LIBS= -lncurses -lm -lmenu
OBJS = $(SOURCES:.c=.o)
SOURCES = Simplify.c drawMenu.c moveable.c pt_utils.c highScore.c player.c
HEADERS = Simplify.h drawMenu.h moveable.h pt_utils.h highScore.h player.h
EXECS = drawMenu

all: $(EXECS)

drawMenu: $(OBJS) $(HEADERS)
	$(CC) -o drawMenu $(OBJS) $(LIBS)

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $<

.PHONY: clean
clean:
	rm *.o 
	
.PHONY: cleanall
cleanall:
	rm *.o *~ $(EXECS)
