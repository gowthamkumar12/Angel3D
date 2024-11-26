import os
from subprocess import call
from datetime import datetime

import fixpath
import scripts

logger = scripts.Logger()

# Nothing special here, just printing a header
def printHeader():
  logger.info_no_date(' ______________________________________________________ ')
  logger.info_no_date('| .................................................... |')
  logger.info_no_date('| ..................... ANGEL3D ...................... |')
  logger.info_no_date('| .................................................... |')
  logger.info_no_date('|______________________________________________________|')

def main():
  printHeader()

if __name__ == '__main__':
  main()