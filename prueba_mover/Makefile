PROGS = hola.txt
PROGS_PATH = hola
UNINST = $(PROGS_PATH)/$(PROGS)

.PHONY: install
install: #$(PROGS)
	mkdir -p $(PROGS_PATH)
	cp $(PROGS) $(PROGS_PATH)

.PHONY: uninstall
uninstall: #$(UNINST)
	rm $(UNINST)