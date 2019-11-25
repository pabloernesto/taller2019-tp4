# Recursive makes are intolerable otherwise
MAKEFLAGS += --no-print-directory

# targets
#########

target=client server common
TARGET := $(if $(MAKECMDGOALS),$(firstword $(MAKECMDGOALS)),all)

# reglas
########

# targets
.PHONY: all
all: $(target)

.PHONY: clean
clean: $(target)

.PHONY: $(target)
client server: common

$(target):
	$(MAKE) --directory=$@ $(TARGET)

.PHONY: install
install:
	cp --target-directory /usr/bin \
		client/micromachines.exe \
		server/micromachines-server.exe
	mkdir --parents /var/micromachines
	mkdir --parents /var/micromachines/Plugins
	cp --target-directory /var/micromachines/Plugins \
		server/Plugins/Mod.cpp \
		server/Plugins/Mod.h \
		server/Plugins/RaceModInterface.h \
		server/Plugins/CarModInterface.h

	cp --recursive --target-directory /var/micromachines \
		client/Fuentes \
		client/Imagenes \
		client/Sonidos
	cp --target-directory /var/micromachines \
		client/Ai.lua
	cp --target-directory /etc \
		common/Configuracion/micromachines.json

.PHONY: uninstall
uninstall:
	rm --force /usr/bin/micromachines.exe /usr/bin/micromachines-server.exe
	rm --force --recursive /var/micromachines
	rm --force /etc/micromachines.json
