import fileinput
import re

what_template_error_type_pattern = re.compile('return "\w+Error<[\w\s,]+>"')
what_error_type_pattern = re.compile('return "(\w+Error)"')
what_error_types = set()

bound_error_type_pattern = re.compile('class_<(\w+)>\("_\\1", no_init\)')
bound_error_types = set()

error_found = False

# Loop through all source file lines to look for errors
for line in fileinput.input(mode='rb'):
    # Get current line number and filename for purposes of error reporting
    line_number = fileinput.filelineno()
    filename = fileinput.filename()
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
        what_error_types.add(what_error_type_match.group(1))
    # Collect bound error types
    bound_error_type_match = bound_error_type_pattern.search(line)
    if bound_error_type_match:
        bound_error_types.add(bound_error_type_match.group(1))

# Check if any error types are not bound for use in Python
unbound_error_types = what_error_types - bound_error_types
# Conversion to/from Python errors do not need to be bound, since they will
# never occur inside Python scripts
unbound_error_types.remove('ConversionToPythonError')
unbound_error_types.remove('ConversionFromPythonError')
if unbound_error_types:
    print('ERROR: {0} unbound error types'.format(len(unbound_error_types)))
    for error_type in sorted(unbound_error_types):
        print('  ' + error_type)
    error_found = True

# Print success message if no errors found
if error_found:
    exit(1)
else:
    print('')
    print('All source code checks complete, no errors found')
