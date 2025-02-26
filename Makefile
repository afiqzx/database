
CC=gcc
CFLAGS=-Wall
CFLAGSDBG=-g
CFLAGSOPT=-O2

OBJDIR:= objdir
# add object file by comma
OBJS=$(addprefix $(OBJDIR)/,main.o)

EXECUTABLE=db_cli

.PHONY:clean

$(OBJDIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(CFLAGSDBG) -c -o $@ $^

$(EXECUTABLE): $(OBJS)
	$(CC) $(OBJS) -o db_cli

$(OBJS): | $(OBJDIR)

$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -rf $(OBJDIR)
	rm -r db_cli
