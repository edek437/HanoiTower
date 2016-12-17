#!/usr/bin/env bash

print_program_info() {
  cat <<HTEOF
Welcome to hanoi tower solver. This program is solving
hanoi tower problem with user defined number of pegs and
disks with one od followinh methods:
- A* algortihm (ASTART)
- Bread-first search (BFS)
HTEOF
}

is_int() {
  [[ $1 =~ ^-?[0-9]+$ ]]
}

while :; do
  print_program_info
  echo "Pick method or write Q to quit porgram"
  read algorithm
  if [[ $algorithm != ASTAR && $algorithm != BFS && $algorithm != Q ]]; then
    echo "Option $algorithm not recognized. Please pick algorith again or quit."
  fi
  if [[ $algorithm == Q ]]; then
    echo "Good bye!"
    break
  fi
  echo "How many pegs?"
  read pegs_number
  if ! is_int "$pegs_number"; then
    echo "Pegs number is not valid number. Please try again"
    continue
  fi
  echo "How big tower?"
  read tower_height
  if ! is_int "$tower_height"; then
    echo "Tower height is not a valid int. Please try again."
    continue
  fi
  echo "Running HanoiTower solver for $pegs_number pegs and tower height $tower_height with algorithm $algorithm"
  RESULT_FILE="/tmp/HanoiTowerSolver_$(date +%s).txt"
  build/HanoiTowers --algorithm "$algorithm" --pegs "$pegs_number" --towers "$tower_height" > "$RESULT_FILE"
  echo "Program finished with status $?. Results saved to file $RESULT_FILE"
done
