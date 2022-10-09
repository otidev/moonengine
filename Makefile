CC = gcc
AR = ar

OBJDIR = obj

ENGINEDIR = engine
ENGINESRCS = $(wildcard $(ENGINEDIR)/*.c)
ENGINEINCS = $(wildcard $(ENGINEDIR)/*.h)
ENGINEOBJS = $(patsubst $(ENGINEDIR)/%.c, $(OBJDIR)/%.o, $(ENGINESRCS))
LIBTYPE ?= STATIC
LINK =

CFLAGS = -I lib/include -I $(ENGINEDIR) -Wall -Wextra
ENGINENAME = libmoon.a
ENGINE = lib/$(ENGINENAME)
DEBUG =# -DDEBUG

ifeq ($(OS), Windows_NT)
	LIBS = -L lib -l:"$(ENGINENAME)" -lSDL2main -lSDL2_ttf.dll -lSDL2_image -lSDL2.dll -lSDL2_mixer.dll
else
	LIBS = -L lib -l:"$(ENGINENAME)" -lSDL2_ttf -lSDL2_image -lSDL2 -lSDL2_mixer
endif


ifeq ($(LIBTYPE), DYNAMIC)
	DLLLIB = -shared -Wl,--out-implib,lib/moon.dll.a
	ENGINENAME = moon.dll.a
	ENGINE = lib/moon.dll
endif

ifeq ($(LIBTYPE), STATIC)
	LINK = $(AR) rcs $(ENGINE) $(ENGINEOBJS)
else ifeq ($(LIBTYPE), DYNAMIC)
	LINK = gcc -o $(ENGINE) $(DLLLIB) $(ENGINEOBJS) $(patsubst -l:"$(ENGINENAME)",, $(LIBS))
endif

all: $(ENGINE)
example: bin/game.exe

$(OBJDIR)/%.o: $(ENGINEDIR)/%.c
	gcc $^ -c -I lib/include -I $(ENGINEDIR) -Wall $(DEBUG) --std=c99 -o $@

$(ENGINE): $(ENGINESRCS) $(ENGINEOBJS) $(ENGINEINCS)
	$(LINK)

bin/game.exe: main.c $(ENGINE)
	gcc $< -o $@ $(LIBS) $(CFLAGS)

clean:
	rm $(OBJDIR)/*.o $(ENGINE) lib/$(ENGINENAME) bin/game.exe 
reset: clean all