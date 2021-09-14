CC=g++
#CC=clang++

# ^ i need to cross compile w/ clang because i use vim+coc+clangd
# g++ is the actual compiler, ignore clang for now

CFLAGS  = -g -std=c++20 -Wall -Wformat 
CFLAGS += -Iinclude/ -Isrc/

SRCDIR = src/

LIBS= -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lglfw -lGL -lGLEW 

OUTDIR=out/
EXE=out/cobalt

OBJ_ABBREV=.o

# TODO make this auto-generated
$(shell mkdir $(OUTDIR))
$(shell mkdir $(OUTDIR)src)
$(shell mkdir $(OUTDIR)src/sys)

# generate list of object files and relative paths
GAME_SOURCES=src
SOURCES = $(shell find $(GAME_SOURCES) -maxdepth 2 -type f \( -name "*.cpp" \))
SRCDIRS = $(shell find $(SRCDIR) -type d -print)
$(shell cd $(OUTDIR))
$(shell mkdir -p $(SRCDIRS))
$(shell cd ..)
OBJ_NAMES = $(addsuffix $(OBJ_ABBREV), $(basename $(SOURCES)))
OBJS = $(addprefix $(OUTDIR), $(OBJ_NAMES))

.PHONY: all clean run rebuild list_objects list_sources list_headers list_cflags list_srcdir

all: $(EXE)
	@echo Build Complete for Cobalt Engine

$(OUTDIR)%.o: %.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


$(EXE): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

run: $(EXE) $(OBJS)
	./$(EXE) 

clean:
	-@rm -rf $(EXE) $(OBJS)

rebuild:
	-@$(MAKE) clean
	@$(MAKE)


list_objects:
	-@echo "Objects are $(OBJS)"

list_headers:
	-@echo "Headers are $(LIBS)"

list_cflags:
	-@echo "Compiler flags are $(CFLAGS)"

list_sources:
	-@echo "Sources are $(SOURCES)"

list_srcdir:
	-@echo "srcdir $(SRCDIR)"
