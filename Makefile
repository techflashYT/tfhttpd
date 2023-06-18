CC=gcc
LD=gcc
CFLAGS=-Ofast -g -fsanitize=address,undefined -Wall -Wextra -march=native -mtune=native -Isrc/include
LDFLAGS=-lasan -lubsan

compile=$(subst .c,.o,$(subst src,build,$(shell find -O3 . -type f -name '*.c' | grep -v 'pages/v1')))
includes=$(shell find -O3 . -type f -name '*.h')
vpath %.c src


S := 
all: bin/backend

install: /usr/local/bin/SeshCord/backend /usr/lib/systemd/system/seshcord-backend.service
/usr/local/bin/SeshCord/backend: bin/backend
	mkdir -p /usr/local/bin/SeshCord
	install -m755 bin/backend /usr/local/bin/SeshCord/backend

/usr/lib/systemd/system/seshcord-backend.service:
	install -m755 src/systemd.service /usr/lib/systemd/system/seshcord-backend.service

run: install
	systemctl restart seshcord-backend
clean:
	@rm -rf bin build

bin/backend: $(compile)
	@$(info $S CCLD  $(subst ./build/,,$(compile)) ==> $@)
	@mkdir -p $(@D)
	@$(LD) $(LDFLAGS) $(compile) -o $@
build/%.o: %.c $(includes)
	@$(info $S CC    $@)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@