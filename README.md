# 🐚 Shell Mate

> A sleek, no-fuss terminal command logger — minimal, powerful, and always watching (the useful stuff only 😉).

---

## ✨ Features

✅ Logs every meaningful command  
✅ Includes timestamp + working directory  
✅ Ignores noisy commands like `ls`, `clear`, etc.  
✅ Auto-trims the log file if it gets too big  
✅ Use `showlog` from *anywhere* to view the logs  
✅ Simple installation, lightweight footprint

---

## 🚀 Installation

```bash
git clone https://github.com/nandhra702/shell_mate.git
cd shell_mate
./install.sh
source ~/.bashrc
```

---

## 🧪 Test It Out

1. **Restart** your terminal  
2. Run a few shell commands (`cd`, `mkdir`, `nano`, etc.)  
3. Type `showlog` and check the command log!  
4. Verify `.bashrc` has this line:
   ```bash
   source ~/shell_mate/logger-trap.bash
   ```

---

## 💡 Roadmap Ideas

- [ ] `zoxide`-like smart directory jumping  
- [ ] Log search and filters (by date, dir, etc.)  
- [ ] Optional GUI overlay  
- [ ] Archive logs monthly  

---

## 🤝 Contribute

PRs and ideas welcome!  
If you’ve got feature requests or bug fixes, feel free to open an issue or submit a pull request.

---

## 📂 Project Structure

```
shell_mate/
├── logger-trap.bash     # Core logic for logging
├── install.sh           # Sets up the environment
├── showlog              # Executable to view logs
├── .logger_config       # Stores filters, thresholds
└── logs/                # Where your history lives
```

---

## ⚠️ Disclaimer

This tool is for **personal productivity use** only. Be mindful when using it on shared or sensitive systems.