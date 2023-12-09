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

NVIM_DIR="/home/x/.local/share/nvim-astro/lazy/nvim-treesitter/queries/$lang"
rsync -avr "$NVIM_DIR/" "./treesitters/tree-sitter-$lang/queries/"

