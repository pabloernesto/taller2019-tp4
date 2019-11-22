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
#./exe
CLIENT_SRC = client/micromachines.exe
SERVER_SRC = server/micromachines-server.exe
EXE_DEST = /usr/bin

#media
FONT_SRC = client/Fuentes
IMG_SRC = client/Imagenes
SOUND_SRC = client/Sonidos
MEDIA_DEST = /var/micromachines 
CONFIG_SRC = common/Configuracion/micromachines.json
CONFIG_DEST = /etc
#config


# CLIENT_DEST = /usr/bin/micromachines.exe
# SERVER_DEST = /usr/bin/micromachines-server.exe


install:
	# mkdir -p $(EXE_DEST)
	cp $(CLIENT_SRC) $(EXE_DEST)
	cp $(SERVER_SRC) $(EXE_DEST)
	mkdir -p $(MEDIA_DEST)
	cp -R $(FONT_SRC) $(MEDIA_DEST)
	cp -R $(IMG_SRC) $(MEDIA_DEST)
	cp -R $(SOUND_SRC) $(MEDIA_DEST)
	cp -R $(CONFIG_SRC) $(CONFIG_DEST)

.PHONY: uninstall
uninstall:
	rm $(EXE_DEST)/$(notdir $(CLIENT_SRC))
	rm $(EXE_DEST)/$(notdir $(SERVER_SRC))
	rm -R $(MEDIA_DEST)
	rm -R $(CONFIG_DEST)