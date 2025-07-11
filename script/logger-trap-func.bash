log_command() {
  local code=$?
  local cmd
  cmd=$(fc -ln -1)  # last user command from history
  local formatted_date
  formatted_date=$(date "+%d %B %Y")

  IGNORE_CMDS=("cd" "clear" "history" "showlog")
  IGNORE_PREFIXES=("ls" "cat" "history" "clear")

  for ignored in "${IGNORE_CMDS[@]}"; do
    [[ "$cmd" == "$ignored" ]] && return
  done

  for prefix in "${IGNORE_PREFIXES[@]}"; do
    [[ "$cmd" == "$prefix"* ]] && return
  done

  local venv=""
  if [[ -n "$VIRTUAL_ENV" ]]; then
    venv="(venv: $(basename "$VIRTUAL_ENV"))"
  fi

  echo "$formatted_date || $(pwd) || $venv: $cmd" >> ~/logger.txt

  local line_count
  line_count=$(wc -l < ~/logger.txt)
  if (( line_count > 50 )); then
    tail -n +21 ~/logger.txt > ~/.logger_tmp && mv ~/.logger_tmp ~/logger.txt
  fi

  if [[ "$code" =~ ^[0-9]+$ ]] && [ "$code" -eq 127 ]; then
    echo "COMMAND NOT FOUND. MAYBE A SPELLING MISTAKE?"
  fi
}

export PROMPT_COMMAND=log_command