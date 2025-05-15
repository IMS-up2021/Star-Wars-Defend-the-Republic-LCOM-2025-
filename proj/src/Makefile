# name of the program (Minix service)
PROG=proj

BINDIR = ${.CURDIR}

.PATH: ${.CURDIR}/controllers/
.PATH: ${.CURDIR}/controllers/video/
.PATH: ${.CURDIR}/game/

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CFLAGS += -pedantic -DPROJ



# source code files to be compiled

SRCS = main.c controllers/video/graphics.c controllers/keyboardMouse/keyboard.c controllers/keyboardMouse/KBC.c controllers/timer/timer.c controllers/keyboardMouse/mouse.c manager.c 

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set

DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>