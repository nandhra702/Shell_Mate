# Command Logger

A lightweight terminal command logger with filtering and log rotation.

--

## Features
- Logs timestamp + command + working directory
- Skips noisy commands like `ls`, `clear`
- Auto-trims log file if too large
- Includes `showlog` command
- Can be accessed from anywhere just by typing 'showlog'

--

## Installation

```bash
git clone https://github.com/nandhra702/shell_mate.git
cd command-logger
./install.sh
source ~/.bashrc

--

## Test It

1. Restart your terminal
2. Run a few commands
3. Type `showlog` and confirm it opens your logger
4. Check if `.bashrc` has the `source logger-trap.bash` line

--
