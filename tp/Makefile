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
