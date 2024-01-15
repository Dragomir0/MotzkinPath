#!/usr/bin/env bats

setup() {
  # Path to the motzkin program
  MOTZKIN_PROGRAM="./motzkin"
}

@test "Should fail with no arguments" {
  run $MOTZKIN_PROGRAM
  [ "$status" -eq 1 ]
  [ "${lines[0]}" = "error: wrong number of arguments" ]
}

@test "Should fail with invalid argument" {
  run $MOTZKIN_PROGRAM "a"
  [ "$status" -eq 1 ]
  [ "${lines[0]}" = "error: invalid character 'a' in path at position 0" ]
}

@test "Should fail if path goes below axis" {
  run $MOTZKIN_PROGRAM "ddr"
  [ "$status" -eq 1 ]
  [ "${lines[0]}" = "error: the path cannot go below the horizontal axis" ]
}

@test "Should fail if path ends above axis" {
  run $MOTZKIN_PROGRAM "uur"
  [ "$status" -eq 1 ]
  [ "${lines[0]}" = "error: the path cannot end above the horizontal axis" ]
}

@test "Should fail if path is too wide" {
  run $MOTZKIN_PROGRAM "$(printf 'r%.0s' {1..41})"
  [ "$status" -eq 1 ]
  [ "${lines[0]}" = "error: the path cannot be wider than 40" ]
}

@test "Should pass with correct sample path 'urudd'" {
  run $MOTZKIN_PROGRAM "urudd"

  [ "$status" -eq 0 ]

  expected_output='<?xml version="1.0"?>
<svg width="500" height="200" viewBox="-8 -8 500 300" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
  <g id="grid">
    <line x1="0" y1="0" x2="500" y2="0" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="0" y1="100" x2="500" y2="100" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="0" y1="200" x2="500" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="0" y1="0" x2="0" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="100" y1="0" x2="100" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="200" y1="0" x2="200" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="300" y1="0" x2="300" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="400" y1="0" x2="400" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
    <line x1="500" y1="0" x2="500" y2="200" stroke="black" stroke-width="1" stroke-dasharray="4 2"/>
  </g>
  <g id="steps">
    <line x1="0" y1="200" x2="100" y2="100" stroke="red" stroke-width="3" stroke-dasharray="none"/>
    <line x1="100" y1="100" x2="200" y2="100" stroke="red" stroke-width="3" stroke-dasharray="none"/>
    <line x1="200" y1="100" x2="300" y2="0" stroke="red" stroke-width="3" stroke-dasharray="none"/>
    <line x1="300" y1="0" x2="400" y2="100" stroke="red" stroke-width="3" stroke-dasharray="none"/>
    <line x1="400" y1="100" x2="500" y2="200" stroke="red" stroke-width="3" stroke-dasharray="none"/>
  </g>
<g id="points">
    <circle cx="0" cy="200" r="7" fill="blue"/>
    <circle cx="100" cy="100" r="7" fill="blue"/>
    <circle cx="200" cy="100" r="7" fill="blue"/>
    <circle cx="300" cy="0" r="7" fill="blue"/>
    <circle cx="400" cy="100" r="7" fill="blue"/>
    <circle cx="500" cy="200" r="7" fill="blue"/>
  </g>
</svg>'

  [ "$output" = "$expected_output" ]  # Compare the actual output with the expected output
}