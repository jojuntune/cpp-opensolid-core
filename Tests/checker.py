import os
import re
import sys

errorFound = False

def checkLineEnding(filePath, lineNumber, line):
    global errorFound
    # Check for carriage return characters
    if b'\r' in line:
        print('ERROR: Found carriage return on line {0} of file {1}'.format(lineNumber, filePath))
        errorFound = True

def checkLine(filePath, lineNumber, line):
    global errorFound
    if not line.lstrip().startswith('//'):
        # Strip out contents of string literals
        line = str.join('""', line.split('"')[::2])
        # Check for tab characters
        if '\t' in line:
            print('ERROR: Found tab character on line {0} of file {1}'.format(lineNumber, filePath))
            errorFound = True
        # Check for valid brace placement
        if 'enum' not in line and 'UniqueErrorCode' not in line:
            # Check to ensure opening braces are always the last character on their line
            # (except in enum definitions)
            if '{' in line and line.rstrip()[-1] != '{':
                errorString = 'ERROR: Found opening brace not at end of line on line {0} of file {1}'
                print(errorString.format(lineNumber, filePath))
                errorFound = True
            # Check to ensure closing braces are always the first character on their line
            # (except in enum definitions)
            if '}' in line and line.lstrip()[0] != '}':
                errorString = 'ERROR: Found closing brace not at beginning of line on line {0} of file {1}'
                print(errorString.format(lineNumber, filePath))
                errorFound = True

def checkHeader(filePath):
    global errorFound
    for i, line in enumerate(open(filePath, 'rb')):
        checkLineEnding(filePath, i + 1, line)
    for i, line in enumerate(open(filePath, 'rt')):
        checkLine(filePath, i + 1, line)

def checkSource(filePath):
    global errorFound
    for i, line in enumerate(open(filePath, 'rb')):
        checkLineEnding(filePath, i + 1, line)
    for i, line in enumerate(open(filePath, 'rt')):
        checkLine(filePath, i + 1, line)

for path, directories, files in os.walk(sys.argv[1]):
    ignoredDirectories = ['External', 'Build', 'IO', 'Python', 'UI']
    for ignoredDirectory in ignoredDirectories:
        if ignoredDirectory in directories:
            directories.remove(ignoredDirectory)
    for filename in files:
        filePath = os.path.join(path, filename)
        if filename.endswith('.hpp'):
            checkHeader(filePath)
        elif filename.endswith('.cpp'):
            checkSource(filePath)

# Print success message if no errors found
if errorFound:
    exit(1)
else:
    print('')
    print('All source code checks complete, no errors found')
    exit(0)
