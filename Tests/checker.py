import os
import re
import sys

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

# Print success message if no errors found
if error_found:
    exit(1)
else:
    print('')
    print('All source code checks complete, no errors found')
    exit(0)
