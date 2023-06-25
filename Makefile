CC=gcc
LD=gcc
CFLAGS=-Ofast -g -fsanitize=address,undefined -Wall -Wextra -march=native -mtune=native -Isrc/include
LDFLAGS=-lasan -lubsan -lsqlite3 -ljson-c

compile=$(subst .c,.o,$(subst src,build,$(shell find -O3 . -type f -name '*.c' | grep -v 'pages/v1')))
includes=$(shell find -O3 . -type f -name '*.h')
vpath %.c src


S := 
all: bin/backend

uninstall:
	-userdel seshcord
	-rm -r /usr/local/bin/SeshCord
	-rm -r /usr/local/lib/seshcord

install: adduser /usr/local/bin/SeshCord/backend /etc/systemd/system/seshcord-backend.service /usr/local/lib/seshcord

adduser:
	cat /etc/passwd | grep "seshcord" > /dev/null 2>&1; if [ $$? = 0 ]; then userdel seshcord; fi
	useradd -M -r seshcord -s /sbin/nologin
/usr/local/bin/SeshCord/backend: bin/backend
	mkdir -p /usr/local/bin/SeshCord
	chmod 755 /usr/local/bin/SeshCord
	chown seshcord:seshcord /usr/local/bin/SeshCord
	install -m755 -o seshcord -g seshcord bin/backend /usr/local/bin/SeshCord/backend

/etc/systemd/system/seshcord-backend.service:
	install -m755 -o seshcord -g seshcord src/systemd.service /etc/systemd/system/seshcord-backend.service

/usr/local/lib/seshcord:
	mkdir -p /usr/local/lib/seshcord
	chmod 755 /usr/local/lib/seshcord
	chown seshcord:seshcord /usr/local/lib/seshcord

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
