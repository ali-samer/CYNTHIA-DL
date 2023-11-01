import os
import subprocess
import sys

if len(sys.argv) != 2:
    print("Usage: python build_and_install.py <project_directory_path>")
    sys.exit(1)

project_dir = sys.argv[1]
os.chdir(project_dir)
cmake_command = ['cmake', '.']
subprocess.run(cmake_command, check=True)
make_command = ['make']
subprocess.run(make_command, check=True)
sudo_make_install_command = ['sudo', 'make', 'install']
subprocess.run(sudo_make_install_command, check=True)

print("Project successfully built and installed.")
