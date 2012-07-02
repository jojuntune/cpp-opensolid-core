import os
import re
import sys

what_template_error_type_pattern = re.compile('return "\w+Error<[\w\s,]+>"')
what_error_type_pattern = re.compile('return "(\w+Error)"')
all_error_types = set()

bound_error_type_pattern = re.compile('class_<(\w+)>\("_\\1", no_init\)')
bound_error_types = set()

checked_opensolid_error_type_pattern = re.compile('checkForOpenSolidError<(\w+)>')
checked_opensolid_error_types = set()

checked_python_error_type_pattern = re.compile('checkForPythonError<(\w+)>')
checked_python_error_types = set()

error_found = False

# Get all source lines as tuples (filename, line number, line)
all_source_lines = []
for path, directories, files in os.walk(sys.argv[1]):
    if 'External' in directories:
        directories.remove('External')
    if 'Build' in directories:
        directories.remove('Build')
    for filename in files:
        if filename.endswith('.hpp') or filename.endswith('.cpp'):
            file_path = os.path.join(path, filename)
            for i, line in enumerate(open(file_path, 'rb')):
                all_source_lines.append((file_path, i + 1, line))

# Loop through all source file lines to look for errors
for filename, line_number, line in all_source_lines:
    # Check for tab characters
    if '\t' in line:
        print('ERROR: Found tab character on line {0} of file {1}'.format(line_number, filename))
        error_found = True
    # Check for carriage return characters
    if '\r' in line:
        print('ERROR: Found carriage return  on line {0} of file {1}'.format(line_number, filename))
        error_found = True
    # Check for what() in error type returning a template specialization
    if what_template_error_type_pattern.search(line):
        message = 'ERROR: what() returns specialization of an error type on line {0} of file {1}'
        print(message.format(line_number, filename))
        error_found = True
    # Collect error types as found in what()
    what_error_type_match = what_error_type_pattern.search(line)
    if what_error_type_match:
        all_error_types.add(what_error_type_match.group(1))
    # Collect bound error types
    bound_error_type_match = bound_error_type_pattern.search(line)
    if bound_error_type_match:
        bound_error_types.add(bound_error_type_match.group(1))
    # Collect checked OpenSolid error types
    checked_opensolid_error_type_match = checked_opensolid_error_type_pattern.search(line)
    if checked_opensolid_error_type_match:
        checked_opensolid_error_types.add(checked_opensolid_error_type_match.group(1))
    # Collect checked OpenSolid error types
    checked_python_error_type_match = checked_python_error_type_pattern.search(line)
    if checked_python_error_type_match:
        checked_python_error_types.add(checked_python_error_type_match.group(1))

# Check if any error types are not bound for use in Python; Python-related
# errors do not need to be bound since they will never occur within scripts
unbound_error_types = set()
for error_type in all_error_types - bound_error_types:
    if 'Python' not in error_type:
        unbound_error_types.add(error_type)
if unbound_error_types:
    print('ERROR: {0} unbound error types'.format(len(unbound_error_types)))
    for error_type in sorted(unbound_error_types):
        print('  ' + error_type)
    error_found = True
    
# Check for error types not checked for and re-thrown
unchecked_error_types = all_error_types - checked_opensolid_error_types - checked_python_error_types
unchecked_error_types.remove("UnexpectedPythonError")
unchecked_error_types.remove("ConversionToPythonError")
unchecked_error_types.remove("ConversionFromPythonError")
if unchecked_error_types:
    print('ERROR: {0} unchecked error types'.format(len(unchecked_error_types)))
    for error_type in sorted(unchecked_error_types):
        print('  ' + error_type)
    error_found = True
    
# Print all error types
# print('Error types: {0}'.format(len(all_error_types)))
# for error_type in sorted(all_error_types):
#     print('  ' + error_type)

# Print success message if no errors found
if error_found:
    exit(1)
else:
    print('')
    print('All source code checks complete, no errors found')
    exit(0)
