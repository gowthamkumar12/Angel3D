import os
import sys
import subprocess
import shutil
from datetime import datetime

HERE = os.path.abspath(os.path.dirname(__file__))
sys.path.insert(0, HERE)

import fixpath
import scripts

logger = scripts.Logger()

possibleBuildCommands = ["-mclean", "-mbuild", "-doc"]
possibleBuildTypes    = ["DEBUG", 'RELEASE', "DIST"]

# Nothing special here, just printing a header
def printHeader():
  logger.info_no_date(' ______________________________________________________ ')
  logger.info_no_date('| .................................................... |')
  logger.info_no_date('| ..................... ANGEL3D ...................... |')
  logger.info_no_date('| .................................................... |')
  logger.info_no_date('|______________________________________________________|')

def printBuildCommands():
  logger.debug_no_date(' ______________________________________________________ ')
  logger.debug_no_date('|                                                      |')
  logger.debug_no_date('|                Possible build commands               |')
  logger.debug_no_date('|______________________________________________________|')
  logger.debug_no_date('|                         \\')
  for e in possibleBuildCommands:
    logger.debug_no_date("| " + e)
  logger.debug_no_date('|_________________________/')

def printBuildTypes():
  logger.debug_no_date(' ______________________________________________________ ')
  logger.debug_no_date('|                                                      |')
  logger.debug_no_date('|                  Possible build types                |')
  logger.debug_no_date('|______________________________________________________|')
  logger.debug_no_date('|                         \\')
  for e in possibleBuildTypes:
    logger.debug_no_date("| " + e)
  logger.debug_no_date('|_________________________/')

def printSuccess():
  logger.success_no_date(' ______________________________________________________ ')
  logger.success_no_date('|                                                      |')
  logger.success_no_date('|                      SUCCESS                         |')
  logger.success_no_date('|______________________________________________________|')

def printFail():
  logger.error_no_date(' ______________________________________________________ ')
  logger.error_no_date('|                                                      |')
  logger.error_no_date('|                       FAIL!                          |')
  logger.error_no_date('|______________________________________________________|')

# function to generated doxygen documents
def buildDoxygen():
  if os.path.exists('docs') and os.path.isdir('docs'):
    if os.path.exists('_out'):
      os.chdir('docs')
      command = ['doxygen']
      try:
        print("\n")
        logger.success("Starting doxygen documentation generation.")
        subprocess.run(command, check=True)
        print("\n")
        logger.success("Doxygen documentation generated successfully.")
        printSuccess()
      except subprocess.CalledProcessError as e:
        print("\n")
        logger.error(f"Doxygen documentation generation failed with error:\n {e}")
        printFail()
      os.chdir('..')
    else:
      os.makedirs('_out')
      buildDoxygen()
  else:
    print("\n")
    logger.error('No docs folder exists!')
    printFail()

# function to clean build folder
def cleanBuildFolder():
  if os.path.exists('_out') and os.path.isdir('_out'):
    shutil.rmtree('_out')
    print("\n")
    logger.success("Build folder (i.e., _out) removed")
    printSuccess()
  else:
    print("\n")
    logger.error("No build folder (i.e., _out) exists!")
    printFail()

# function to perform incremental build
def build(build_type):
  print("\n")
  logger.debug(f"Starting CMake build for {build_type} configuration.")
  if not os.path.exists('_out'):
    logger.debug("No build folder exists creating one!")
    os.makedirs('_out')
  os.chdir('_out')

  if not os.path.exists('CMakeCache.txt'):
    cmake_configuration = ['cmake', '-DCMAKE_EXPORT_COMPILE_COMMANDS=ON', f'-DCMAKE_BUILD_TYPE={build_type}', '..']
    try:
      logger.debug(f'Configuring project with CMake for {build_type}.')
      subprocess.run(cmake_configuration, check=True)
      logger.success(f'CMake configuration for {build_type} is success.')
    except subprocess.CalledProcessError as e:
      logger.error(f'CMake configuration for {build_type} failed with error:\n {e}.')
      printFail()

  cmake_build = ['cmake', '--build', '.', '--config', f'{build_type}']
  try:
    logger.debug(f'Building CMake project for {build_type}.')
    subprocess.run(cmake_build, check=True)
    print("\n")
    logger.success(f'CMake build for {build_type} is success.')
  except subprocess.CalledProcessError as e:
    print("\n")
    logger.error(f'CMake build for {build_type} failed with error:\n {e}.')
    printFail()

  os.chdir('..')
  printSuccess()

# main function
def main():
  os.chdir(os.path.join(HERE, '..'))

  printHeader()

  if len(sys.argv) == 1:
    logger.warning_no_date(' ______________________________________________________ ')
    logger.warning_no_date('|                                                      |')
    logger.warning_no_date('|                      WARNING!                        |')
    logger.warning_no_date('|                No Build-Command chosen!              |')
    logger.warning_no_date('|______________________________________________________|')
    printBuildCommands()
    sys.exit(-1)

  if sys.argv[1] not in possibleBuildCommands:
    logger.error_no_date(' ______________________________________________________ ')
    logger.error_no_date('|                                                      |')
    logger.error_no_date('|                        ERROR!                        |')
    logger.error_no_date('|             Invalid Build-Command chosen!            |')
    logger.error_no_date('|______________________________________________________|')
    printBuildCommands()
    sys.exit(-2)

  if sys.argv[1] == '-doc':
    buildDoxygen()

  if sys.argv[1] == '-mclean':
    cleanBuildFolder()

  if sys.argv[1] == "-mbuild":
    if len(sys.argv) == 2:
      logger.warning_no_date(' ______________________________________________________ ')
      logger.warning_no_date('|                                                      |')
      logger.warning_no_date('|                      WARNING!                        |')
      logger.warning_no_date('|                No Build-Type is chosen!              |')
      logger.warning_no_date('|______________________________________________________|')
      printBuildTypes()
      sys.exit(-3)

    if sys.argv[2] not in possibleBuildTypes:
      logger.error_no_date(' ______________________________________________________ ')
      logger.error_no_date('|                                                      |')
      logger.error_no_date('|                        ERROR!                        |')
      logger.error_no_date('|             Invalid Build-Type is chosen!            |')
      logger.error_no_date('|______________________________________________________|')
      printBuildTypes()
      sys.exit(-2)

    build(sys.argv[2])

if __name__ == '__main__':
  main()