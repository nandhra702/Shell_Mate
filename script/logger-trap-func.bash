log_command() {
  local cmd="$BASH_COMMAND"
  local formatted_date
  formatted_date=$(date "+%d %B %Y")

  IGNORE_CMDS=("cd" "clear" "history" "cat ~/logger.txt")
  IGNORE_PREFIXES=("ls" "cat" "history" "clear")

  for ignored in "${IGNORE_CMDS[@]}"; do
    [[ "$cmd" == "$ignored" ]] && return
  done

  for prefix in "${IGNORE_PREFIXES[@]}"; do
    if [[ "$cmd" == "$prefix"* ]]; then
      return
    fi
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
}

trap 'log_command' DEBUG
