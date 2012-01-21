import fileinput
import re

error_code_declarations = {} # int -> (line number, file)
error_code_pattern = re.compile('static\s+const\s+int\s+error_code\s+=\s+(\d+);')

for line in fileinput.input():
    # Get current line number and filename for purposes of error reporting
    line_number = fileinput.filelineno()
    filename = fileinput.filename()
    # Check for duplicate error codes
    error_code_match = re.search(error_code_pattern, line)
    if error_code_match:
        error_code = int(error_code_match.group(1))
        if error_code_declarations.has_key(error_code):
            message = 'ERROR: Error code {0} on line {1} of file {2} '\
                'already encountered at line {3} of file {4}'
            previous_line_number = error_code_declarations[error_code][0]
            previous_filename = error_code_declarations[error_code][1]
            arguments = (
                error_code,
                line_number,
                filename,
                previous_line_number,
                previous_filename
            )
            print(message.format(*arguments))
            exit(1)
        else:
            error_code_declarations[error_code] = (line_number, filename)
    # Check for tab characters
    if '\t' in line:
        print('ERROR: Found tab character on line {0} of file {1}'.format(line_number, filename))
    # Check for carriage return characters
    if '\r' in line:
        print('ERROR: Found carriage return  on line {0} of file {1}'.format(line_number, filename))

used_error_codes = error_code_declarations.keys()
max_used_error_code = max(used_error_codes)
missing_error_codes = set(range(1, max_used_error_code + 1)) - set(used_error_codes)
message = 'Available error codes: {0}, {1}+'
arguments = (
    ', '.join(str(error_code) for error_code in missing_error_codes),
    max_used_error_code + 1
)
print(message.format(*arguments))
for error_code in used_error_codes:
    line_number = error_code_declarations[error_code][0]
    filename = error_code_declarations[error_code][1]
    message = 'Error code {0} declared at line {1} of file {2}'
    arguments = (error_code, line_number, filename)
    print(message.format(*arguments))
    
print('')
print('All source code checks complete, no errors found')
