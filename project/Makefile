CC    = gcc
CFLAGS      = -Wall -Werror -Wno-format-zero-length -Wno-unused-variable

SOURCEDIR = source
OBJECTDIR = build

EXCLUDE     = '*test*'
# Sources for the main program, excludes test scripts
SOURCES := $(patsubst $(SOURCEDIR)/%, %, $(shell find $(SOURCEDIR) -name '*.c'  ! -name $(EXCLUDE)  ! -path $(EXCLUDE)))
OBJECTS := $(addprefix $(OBJECTDIR)/, $(SOURCES:.c=.o))

EXECUTABLES = elevator que_test

.DEFAULT_GOAL := elevator

elevator: $(OBJECTS) 
	$(CC) -o $(addprefix $(OBJECTDIR)/, $@) $^ $(LDFLAGS) $(CFLAGS)

que_test : $(OBJECTDIR)/que.o $(OBJECTDIR)/que_test.o
	$(CC) -o $(addprefix $(OBJECTDIR)/, $@) $(OBJECTDIR)/que.o $(OBJECTDIR)/que_test.o $(CFLAGS)

timer_test : $(OBJECTDIR)/timer.o $(OBJECTDIR)/timer_test.o
	$(CC) -o $(addprefix $(OBJECTDIR)/, $@) $(OBJECTDIR)/timer.o $(OBJECTDIR)/timer_test.o $(CFLAGS)

$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(CC) -o $@ -c $(CFLAGS) $<

.PHONY: all rebuild clean

all: $(EXECUTABLES) 

rebuild: clean all
	
clean:
	rm -rf $(OBJECTDIR)


