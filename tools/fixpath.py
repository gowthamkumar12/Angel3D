import sys
from os.path import normpath, dirname, join, isdir

# Get the absolute paths for 'colorama' and 'scripts' relative to this script
local_colorama_module = normpath(join(dirname(__file__), '../Vendor/colorama'))
local_script_module = normpath(join(dirname(__file__), 'scripts'))

# Check if the directories exist before inserting them into sys.path
if isdir(local_colorama_module):
    sys.path.insert(0, local_colorama_module)
else:
  print(f"Warning: {local_colorama_module} does not exist.")

if isdir(local_script_module):
    sys.path.insert(1, local_script_module)
else:
  print(f"Warning: {local_script_module} does not exist.")
