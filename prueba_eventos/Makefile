# Recursive makes are intolerable otherwise
MAKEFLAGS += --no-print-directory

# targets
#########

target=cliente servidor common
TARGET := $(if $(MAKECMDGOALS),$(firstword $(MAKECMDGOALS)),all)

# reglas
########

# targets
.PHONY: all
all: $(target)

.PHONY: clean
clean: $(target)

.PHONY: $(target)
cliente servidor: common

$(target):
	$(MAKE) --directory=$@ $(TARGET)
