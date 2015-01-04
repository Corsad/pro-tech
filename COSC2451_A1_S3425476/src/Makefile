CC=clang
LIBS= -lncurses -lm -lmenu
OBJS = $(SOURCES:.c=.o)
SOURCES = move.c board.c drawMenu.c moveable.c pt_utils.c highScore.c random.c khanhAI.c huyAI.c
HEADERS = move.h board.h drawMenu.h moveable.h pt_utils.h highScore.h player.h random.h khanhAI.h huyAI.h
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
