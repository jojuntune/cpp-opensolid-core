import os
import re
import sys

errorFound = False

singleLineTerms = []
singleLineTerms.append('OPENSOLID_CORE_EXPORT')
singleLineTerms.append('OPENSOLID_IO_EXPORT')
singleLineTerms.append('OPENSOLID_PYTHON_EXPORT')
singleLineTerms.append('OPENSOLID_PYTHON_EXTENSION_EXPORT')

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
        # Strip away comments
        line = line.partition("//")[0];
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
        # Check for valid parentheses
        numOpeningParentheses = line.count('(')
        numClosingParentheses = line.count(')')
        if numOpeningParentheses - numClosingParentheses > 1:
            print('ERROR: More than one unmatched opening parenthesis found on line {0} of file {1}'.format(lineNumber, filePath))
            errorFound = True
        if numClosingParentheses - numOpeningParentheses > 1:
            print('ERROR: More than one unmatched closing parenthesis found on line {0} of file {1}'.format(lineNumber, filePath))
            errorFound = True
        if numOpeningParentheses > numClosingParentheses and line.rstrip()[-1] != '(':
            print('ERROR: Found unmatched opening parenthesis not at end of line on line {0} of file {1}'.format(lineNumber, filePath))
            errorFound = True
        if numClosingParentheses > numOpeningParentheses and line.lstrip()[0] != ')':
            print('ERROR: Found unmatched closing parenthesis not at beginning of line on line {0} of file {1}'.format(lineNumber, filePath))
            errorFound = True
        # Check for terms that should be on their own line
        # (ignore config.hpp where export macros are defined)
        if 'config.hpp' not in filePath and 'friend' not in line:
            for term in singleLineTerms:
                if term in line and line.strip() != term:
                    errorString = 'ERROR: Found \'{0}\' not on own line on line {1} of file {2}'
                    print(errorString.format(term, lineNumber, filePath))
                    errorFound = True
        # Make sure only .cpp files includ Eigen headers
        if not filePath.endswith('.cpp'):
            if "#include <Eigen" in line:
                print('ERROR: {0} has illegal Eigen include: {1}'.format(filePath, line.rstrip()))
                errorFound = True
        # Make sure *.declarations.hpp only include <OpenSolid/config.hpp> and possibly
        # <boost/intrusive_ptr.hpp> (for forward declaration of *Ptr types)
        if '.declarations.hpp' in filePath:
            allowedHeaders = ['<boost/intrusive_ptr.hpp>']
            if '#include' in line and not any(header in line for header in allowedHeaders):
                print('ERROR: {0} has illegal include: {1}'.format(filePath, line.rstrip()))
                errorFound = True

def checkIndentation(filePath, lineNumber, line, previousIndentation):
    global errorFound
    if not line.strip():
        # Empty line - ignore
        return previousIndentation
    trimmedLine = line.lstrip()
    numLeadingSpaces = len(line) - len(trimmedLine)
    if numLeadingSpaces % 4 != 0:
        print('ERROR: {0} leading spaces (not a multiple of 4) found on line {1} of file {2}'.format(numLeadingSpaces, lineNumber, filePath))
        errorFound = True
        return previousIndentation
    indentation = numLeadingSpaces // 4
    if trimmedLine.startswith(') : '): # Special case for constructors
        indentation += 1
    if previousIndentation is not None:
        indentationChange = indentation - previousIndentation
        if abs(indentationChange) > 1:
            print('ERROR: Indentation changes by {0} levels on line {1} of file {2}'.format(indentationChange, lineNumber, filePath))
            errorFound = True
    return indentation


def checkFile(filePath):
    global errorFound
    if filePath.endswith('.cpp') or filePath.endswith('.hpp'):
        previousIndentation = None
        for i, line in enumerate(open(filePath, 'rt')):
            checkLine(filePath, i + 1, line)
            previousIndentation = checkIndentation(filePath, i + 1, line, previousIndentation)


for path, directories, files in os.walk(sys.argv[1]):
    i = 0
    while i < len(directories):
        directory = directories[i]
        if directory in ['Bindings', 'External', 'IO', 'Python', 'UI', '.hg'] or directory.lower().startswith('build'):
            del directories[i]
        else:
            i = i + 1
    for filename in files:
        filePath = os.path.join(path, filename)
        checkFile(filePath)

# Print success message if no errors found
if errorFound:
    exit(1)
else:
    print('')
    print('All source code checks complete, no errors found')
    exit(0)
