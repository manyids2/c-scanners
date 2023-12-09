#!/bin/bash

set -euo pipefail
OLD_PWD="$(pwd)"
trap 'cd $OLD_PWD' EXIT

SRC_PATH="$(realpath "$0")"
SRC_DIR="$(dirname "$SRC_PATH")"
echo "dirname : [$SRC_DIR]"
cd "$SRC_DIR"

lang="$1"
echo "Lang : [$lang]"

case $lang in
og)
	# Add the OG as well
	git submodule add \
		"https://github.com/tree-sitter/tree-sitter" \
		"treesitters/tree-sitter"
	make -C \
		"treesitters/tree-sitter" \
		-f "treesitters/tree-sitter/Makefile"
	;;

markdown)
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
		-f "compile_parsers.makefile"

	echo "Compiling: markdown-inline"
	mv \
		"treesitters/tree-sitter-markdown-temp/tree-sitter-markdown-inline" \
		"treesitters/tree-sitter-markdown-inline"
	make -C \
		"treesitters/tree-sitter-markdown-inline" \
		-f "compile_parsers.makefile"

	rm -rf "treesitters/tree-sitter-markdown-temp"
	;;

*)
	echo "Downloading: $lang"
	git submodule add \
		"https://github.com/tree-sitter/tree-sitter-$lang" \
		"treesitters/tree-sitter-$lang"

	echo "Compiling: $lang"
	make -C \
		"treesitters/tree-sitter-$lang" \
		-f "compile_parsers.makefile"

	echo "**/*.so" >>"treesitters/tree-sitter-$lang/.gitignore"
	echo "**/*.o" >>"treesitters/tree-sitter-$lang/.gitignore"
	;;
esac
