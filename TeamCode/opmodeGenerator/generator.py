from pathlib import Path
import re
import shutil

INPUT_DIR = "TeamCode/src/main/cpp/main"
OUTPUT_DIR = "TeamCode/src/main/java/org/firstinspires/ftc/teamcode/opmodes"

AUTONOMOUS_PATH = "TeamCode/opmodeGenerator/templateAutonomous.java"
TELEOP_PATH = "TeamCode/opmodeGenerator/templateTeleop.java"

REGEX_PATTERN = r'(?P<type>TeleOp|Autonomous)\s*\(\s*(?P<name>\w+),\s*(?P<group>\w+)\)'

def deleteCurFiles():
    outputFiles = Path(OUTPUT_DIR)
    for outputFile in outputFiles.rglob('*.java'):
        match = re.search("Deletable_Java_File_Do_Not_Remove_String", outputFile.read_text())
        if match:
            print(f"Deleting: {outputFile}")
            outputFile.unlink()


def createCurFiles():
    inputFiles = Path(INPUT_DIR)
    for inputFile in inputFiles.rglob('*.cpp'):
        match = re.search(REGEX_PATTERN, inputFile.read_text())
        if match:
            newPath = ""
            if match.group('type') == 'TeleOp':
                shutil.copy(TELEOP_PATH, OUTPUT_DIR)
                newPath = f"{OUTPUT_DIR}/{match.group('name')}.java"
                shutil.move(f"{OUTPUT_DIR}/templateTeleop.java", newPath)

            elif match.group('type') == 'Autonomous':
                shutil.copy(AUTONOMOUS_PATH, OUTPUT_DIR)
                newPath = f"{OUTPUT_DIR}/{match.group('name')}.java"
                shutil.move(f"{OUTPUT_DIR}/templateAutonomous.java", newPath)

            with open(newPath, 'r') as file:
                data = file.read()

            data = data.replace('<class_name>', match.group('name'))
            data = data.replace('<group_name>', match.group('group'))

            with open(newPath, 'w') as file:
                file.write(data)
            print(f"Done Generating : {match.group('name')}")


deleteCurFiles()
createCurFiles()