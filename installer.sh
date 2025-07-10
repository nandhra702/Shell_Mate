#!/bin/bash

# Copy showlog to ~/.local/bin
mkdir -p ~/.local/bin
cp logger/showlog ~/.local/bin/showlog
chmod +x ~/.local/bin/showlog

# Ensure ~/.local/bin is in PATH
if ! echo "$PATH" | grep -q "$HOME/.local/bin"; then
  echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bashrc
  export PATH="$HOME/.local/bin:$PATH"
fi

# Add trap script to ~/.bashrc if not already added
if ! grep -q "logger-trap.bash" ~/.bashrc; then
  echo "" >> ~/.bashrc
  echo "# Command Logger Trap" >> ~/.bashrc
  echo "source ~/command-logger/script/logger-trap.bash" >> ~/.bashrc
fi

echo "!!!!  Command Logger installed !!!!"
echo "→ Restart terminal or run: source ~/.bashrc"
