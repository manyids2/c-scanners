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
OUTPUT_DIR := bin

$(OUTPUT_DIR)/ts-json: treesitters/json.c
	cd treesitters && gcc                 \
	-I tree-sitter/lib/include            \
	json.c utils.c  utils.h               \
	tree-sitter-json/src/parser.c         \
	tree-sitter/libtree-sitter.a          \
	-g -Wall                              \
	-o ../$(OUTPUT_DIR)/ts-json

run-ts-json:
	bear -- make $(OUTPUT_DIR)/ts-json
	./$(OUTPUT_DIR)/ts-json ./treesitters/tree-sitter-json/package.json

$(OUTPUT_DIR)/ts-go: treesitters/go.c
	cd treesitters && gcc                 \
	-I tree-sitter/lib/include            \
	go.c utils.c  utils.h                 \
	tree-sitter-go/src/parser.c           \
	tree-sitter/libtree-sitter.a          \
	-g -Wall                              \
	-o ../$(OUTPUT_DIR)/ts-go

run-ts-go:
	bear -- make $(OUTPUT_DIR)/ts-go
	./$(OUTPUT_DIR)/ts-go /home/x/fd/code/go/go-tufte/main.go
