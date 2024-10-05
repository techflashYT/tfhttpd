CC ?= gcc
LD ?= gcc
CFLAGS ?= -Ofast -g -fsanitize=address,undefined -Wall -Wextra -march=native -mtune=native
CFLAGS += -Isrc/include
LDFLAGS ?= -lasan -lubsan

OUT := bin/tfhttpd

compile=$(subst .c,.o,$(subst src,build,$(shell find -O3 . -type f -name '*.c' | grep -v 'pages/v1')))
includes=$(shell find -O3 . -type f -name '*.h')
vpath %.c src


S := 
all: $(OUT)

clean:
	@rm -rf bin build

$(OUT): $(compile)
	@$(info $S CCLD  $(subst ./build/,,$(compile)) ==> $@)
	@mkdir -p $(@D)
	@$(CC) $(LDFLAGS) $(compile) -o $@
build/%.o: %.c $(includes)
	@$(info $S CC    $@)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@
