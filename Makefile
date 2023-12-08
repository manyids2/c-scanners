PROJECT := c-scanners
SOURCES := $(wildcard scanners/*.c)
HEADERS := $(wildcard scanners/*.h)

$(PROJECT): main.c $(SOURCES) $(HEADERS)
	gcc main.c $(SOURCES) $(HEADERS) -g -o $(PROJECT) -Wall

run:
	bear -- make $(PROJECT)
	./$(PROJECT) go-functions /home/x/fd/code/go/go-tufte/markdown/markdown.go

clean:
	rm $(PROJECT)

# --- Treesitter ---
