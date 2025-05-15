# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/controllers/
.PATH: ${.CURDIR}/controllers/video/
.PATH: ${.CURDIR}/controllers/keyboardMouse/
.PATH: ${.CURDIR}/controllers/timer/
.PATH: ${.CURDIR}/game/

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -DPROJ

# source code files to be compiled
SRCS = main.c \
       controllers/video/graphics.c \
       controllers/keyboardMouse/keyboard.c \
       controllers/keyboardMouse/KBC.c \
       controllers/timer/timer.c \
       controllers/keyboardMouse/mouse.c \
       manager.c \
       controllers/utils.c

# object files to be generated with paths
OBJS = main.o \
       controllers/video/graphics.o \
       controllers/keyboardMouse/keyboard.o \
       controllers/keyboardMouse/KBC.o \
       controllers/timer/timer.o \
       controllers/keyboardMouse/mouse.o \
       manager.o \
       controllers/utils.o

# rules to ensure object files are placed in their respective directories
controllers/video/graphics.o: controllers/video/graphics.c
	${CC} ${CFLAGS} -c $< -o $@

controllers/keyboardMouse/keyboard.o: controllers/keyboardMouse/keyboard.c
	${CC} ${CFLAGS} -c $< -o $@

controllers/keyboardMouse/KBC.o: controllers/keyboardMouse/KBC.c
	${CC} ${CFLAGS} -c $< -o $@

controllers/timer/timer.o: controllers/timer/timer.c
	${CC} ${CFLAGS} -c $< -o $@

controllers/keyboardMouse/mouse.o: controllers/keyboardMouse/mouse.c
	${CC} ${CFLAGS} -c $< -o $@

controllers/utils.o: controllers/utils.c
	${CC} ${CFLAGS} -c $< -o $@

manager.o: manager.c
	${CC} ${CFLAGS} -c $< -o $@

main.o: main.c
	${CC} ${CFLAGS} -c $< -o $@

# additional dependencies and libraries
DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
