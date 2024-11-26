from __future__ import print_function
from datetime import datetime
from sys import stdout

class Logger:
  def __init__(self, timestamps=True):
    try:
      self.colorama = __import__('colorama')
      self.color_output = True
    except ImportError:
      # fallback solution: simply do not use color output
      self.color_output = False
    if self.color_output:
      self.colorama.init()
    self.show_timestamps = timestamps

  def __get_time(self):
    if self.show_timestamps:
      return datetime.now().strftime('[%H:%M:%S]')
    else:
      return ""

  def get_color_string(self, color, string):
    if self.color_output:
      color_string = ""
      if color.upper() == 'RED':
        color_string = color_string + self.colorama.Style.BRIGHT + self.colorama.Fore.RED
      if color.upper() == 'GREEN':
        color_string = color_string + self.colorama.Style.BRIGHT + self.colorama.Fore.GREEN
      if color.upper() == 'YELLOW':
        color_string = color_string + self.colorama.Style.BRIGHT + self.colorama.Fore.YELLOW
      if color.upper() == 'WHITE':
        color_string = color_string + self.colorama.Style.BRIGHT + self.colorama.Fore.WHITE
      if color.upper() == 'CYAN':
        color_string = color_string + self.colorama.Style.BRIGHT + self.colorama.Fore.CYAN
      if color.upper() == 'MAGENTA':
        color_string = color_string + self.colorama.Style.BRIGHT + self.colorama.Fore.MAGENTA
      return color_string + string + self.colorama.Style.RESET_ALL
    else:
      return ""

  def error(self, msg):
    print(self.get_color_string('RED', self.__get_time() + "[ERROR] " + msg))
    stdout.flush()

  def success(self, msg):
    print(self.get_color_string('GREEN', self.__get_time() + "[SUCCESS] " + msg))
    stdout.flush()

  def warning(self, msg):
    print(self.get_color_string('YELLOW', self.__get_time() + "[WARNING] " + msg))
    stdout.flush()

  def info(self, msg):
    print(self.get_color_string('WHITE', self.__get_time() + "[INFO] " + msg))
    stdout.flush()

  def debug(self, msg):
    print(self.get_color_string('CYAN', self.__get_time() + "[DEBUG] " + msg))
    stdout.flush()

  def separator(self, msg):
    print(self.get_color_string('MAGENTA', self.__get_time() + "[::::] " + msg))
    stdout.flush()

  ## No date logs
  def error_no_date(self, msg):
    print(self.get_color_string('RED', msg))
    stdout.flush()

  def success_no_date(self, msg):
    print(self.get_color_string('GREEN', msg))
    stdout.flush()

  def warning_no_date(self, msg):
    print(self.get_color_string('YELLOW', msg))
    stdout.flush()

  def info_no_date(self, msg):
    print(self.get_color_string('WHITE', msg))
    stdout.flush()

  def debug_no_date(self, msg):
    print(self.get_color_string('CYAN', msg))
    stdout.flush()

  def separator_no_date(self, msg):
    print(self.get_color_string('MAGENTA', msg))
    stdout.flush()
