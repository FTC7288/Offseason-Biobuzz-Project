#!/usr/bin/env bash

# TODO: add group to the opmode annotation

export LC_ALL=C.UTF-8

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

INPUT_DIR="TeamCode/src/main/cpp/main/opmodes"
OUTPUT_DIR="TeamCode/src/main/java/org/firstinspires/ftc/teamcode/opmodes"

AUTONOMOUS_TEMP_PATH="TeamCode/src/main/cpp/sdk/util/opmode_generator/templateAutonomous.java.template"
TELEOP_TEMP_PATH="TeamCode/src/main/cpp/sdk/util/opmode_generator/templateTeleop.java.template"

delete_output_files() {
  mkdir -p "$OUTPUT_DIR"
  find "$OUTPUT_DIR" -type f -name "*.java" | while read -r cur_file; do
    if grep -q 'Deletable_Java_File_Do_Not_Remove_String' "$cur_file"; then
      rm "$cur_file"
    fi
  done
}


scan_and_create_files() {
  find "$INPUT_DIR" -type f -name "*.cpp" | while read -r cur_file; do
    if grep -Po '(Autonomous|TeleOp)()' "$cur_file"; then
      opmode_type=$(grep -Po '(Autonomous|TeleOp)' "$cur_file")
      opmode_name=$(awk 'match($0, /(Autonomous|TeleOp)\(([^)]+)\)/, arr) {print arr[2]; exit}' "$cur_file")
      echo "$opmode_type"
      echo "$opmode_name"
      local cur_temp_dir=""
      if [ "$opmode_type" = "TeleOp" ]; then
        cur_temp_dir="$TELEOP_TEMP_PATH"
      elif [ "$opmode_type" = "Autonomous" ]; then
        cur_temp_dir="$AUTONOMOUS_TEMP_PATH"
      else
        echo "Could not load file"
      fi
      local cur_output_file="$OUTPUT_DIR/$opmode_name.java"
      cp "$cur_temp_dir" "$cur_output_file"
      sed -i "s/<class_name>/$opmode_name/g" "$cur_output_file"
    else
      echo "NO FILE FOUND"
    fi
  done
}

main() {
  delete_output_files
  scan_and_create_files
}

main