CC = clang
CFLAGS = -Wall -std=c99
LDFLAGS =

SRCDIR = src
OBJDIR = build

SRCS = $(shell find $(SRCDIR) -name "*.c")
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

.PHONY = clean

false: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(OBJDIR)/$@

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(subst $(SRCDIR)/,$(OBJDIR)/,$(dir $<))
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)