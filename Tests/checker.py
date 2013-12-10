import os
import re
import sys

errorFound = False

singleLineTerms = []
singleLineTerms.append('inline')
singleLineTerms.append('OPENSOLID_CORE_EXPORT')
singleLineTerms.append('OPENSOLID_IO_EXPORT')
singleLineTerms.append('OPENSOLID_PYTHON_EXPORT')
singleLineTerms.append('OPENSOLID_PYTHON_EXTENSION_EXPORT')

def checkLineEnding(filePath, lineNumber, line):
    global errorFound
    # Check for carriage return characters
    if b'\r' in line:
        print('ERROR: Found carriage return on line {0} of file {1}'.format(lineNumber, filePath))
        errorFound = True

def checkLine(filePath, lineNumber, line):
    global errorFound
    global singleLineTerms
    if not line.lstrip().startswith('//'):
        # Check for overly long lines
        lineLength = len(line.rstrip())
        if lineLength > 100 and 'friend' not in line:
            print('ERROR: Line {0} of file {1} has length {2}'.format(lineNumber, filePath, lineLength))
            errorFound = True
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
        # Check for terms that should be on their own line
        # (ignore config.hpp where export macros are defined)
        if 'config.hpp' not in filePath and 'friend' not in line:
            for term in singleLineTerms:
                if term in line and line.strip() != term:
                    errorString = 'ERROR: Found \'{0}\' not on own line on line {1} of file {2}'
                    print(errorString.format(term, lineNumber, filePath))
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
    i = 0
    while i < len(directories):
        directory = directories[i]
        if directory in ['External', 'IO', 'Python', 'UI'] or directory.lower().startswith('build'):
            del directories[i]
        else:
            i = i + 1
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
