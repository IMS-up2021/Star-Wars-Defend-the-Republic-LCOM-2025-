# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}/controllers/
.PATH: ${.CURDIR}/game/

# source code files to be compiled

SRCS = main.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set

DPADD += ${LIBLCF}
LDADD += -llcf -lxpm -llm

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>