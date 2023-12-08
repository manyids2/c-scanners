#!/bin/bash

SRC_PATH="$(realpath "$0")"
SRC_DIR="$(dirname "$SRC_PATH")"
echo "dirname : [$SRC_DIR]"

# Add the OG as well
git submodule add \
	"https://github.com/tree-sitter/tree-sitter" \
	"treesitters/tree-sitter"

LANGS="c go css html"
echo "Langs : [$LANGS]"

for lang in $LANGS; do
	echo "Downloading: $lang"
	git submodule add \
		"https://github.com/tree-sitter/tree-sitter-$lang" \
		"treesitters/tree-sitter-$lang"

	echo "Compiling: $lang"
	make -C \
		"treesitters/tree-sitter-$lang" \
		-f "$SRC_DIR/compile_parsers.makefile"

	echo "**/*.so" >> "treesitters/tree-sitter-$lang/.gitignore"
	echo "**/*.o" >> "treesitters/tree-sitter-$lang/.gitignore"
done

# Markdown is two stage
echo "Downloading: markdown"
git submodule add -b split_parser \
	"https://github.com/MDeiml/tree-sitter-markdown" \
	"treesitters/tree-sitter-markdown-temp"

echo "Compiling: markdown"
mv \
	"treesitters/tree-sitter-markdown-temp/tree-sitter-markdown" \
	"treesitters/tree-sitter-markdown"
make -C \
	"treesitters/tree-sitter-markdown" \
	-f "$SRC_DIR/compile_parsers.makefile"

echo "Compiling: markdown-inline"
mv \
	"treesitters/tree-sitter-markdown-temp/tree-sitter-markdown-inline" \
	"treesitters/tree-sitter-markdown-inline"
make -C \
	"treesitters/tree-sitter-markdown-inline" \
	-f "$SRC_DIR/compile_parsers.makefile"

rm -rf "treesitters/tree-sitter-markdown-temp"
