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
	cp -t /usr/bin \
		client/micromachines.exe \
		server/micromachines-server.exe
	mkdir -p /var/micromachines
	cp -r -t /var/micromachines \
		client/Fuentes \
		client/Imagenes \
		client/Sonidos
	cp -t /etc \
		common/Configuracion/micromachines.json

.PHONY: uninstall
uninstall:
	rm /usr/micromachines.exe /usr/micromachines-server.exe
	rm -r /var/micromachines
	rm /etc/micromachines.json
