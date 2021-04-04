#!/usr/bin/python

current_contest="CONTEST_ID"  # Change HERE !!!

# Python 2->3 libraries that were renamed.
try:
  from urllib2 import urlopen
except:
  from urllib.request import urlopen
try:
  from HTMLParser import HTMLParser
except:
  from html.parser import HTMLParser

from subprocess import call

import argparse
import os
import re

FOLDER = 'samples'
SAMPLE_INPUT='input'
SAMPLE_OUTPUT='output'
MY_OUTPUT='my_output'

RED_F='\033[31m'
GREEN_F='\033[32m'
BOLD='\033[1m'
NORM='\033[0m'
TIME_CMD='`which time` -o time.out -f "(%es)"'
TIME_AP='`cat time.out`'

# Problems parser.
class CodeforcesProblemParser(HTMLParser):
  def __init__(self, problem):
    HTMLParser.__init__(self)
    self.num_tests = 0
    self.testcase = None
    self.start_copy = False
    self.problem = problem

  def handle_starttag(self, tag, attrs):
    if tag == 'div':
      if attrs == [('class', 'input')]:
        self.num_tests += 1
        self.testcase = open(
          '%s/%s_%s_%d' % (FOLDER, SAMPLE_INPUT, self.problem, self.num_tests), 'wb')
      elif attrs == [('class', 'output')]:
        self.testcase = open(
          '%s/%s_%s_%d' % (FOLDER, SAMPLE_OUTPUT, self.problem, self.num_tests), 'wb')
    elif tag == 'pre':
      if self.testcase != None:
        self.start_copy = True

  def handle_endtag(self, tag):
    if tag == 'br':
      if self.start_copy:
        self.testcase.write('\n'.encode('ascii', 'ignore'))
        self.end_line = True
    if tag == 'pre':
      if self.start_copy:
        if not self.end_line:
          self.testcase.write('\n'.encode('ascii', 'ignore'))
        self.testcase.close()
        self.testcase = None
        self.start_copy = False

  def handle_entityref(self, name):
    if self.start_copy:
      self.testcase.write(self.unescape(('&%s;' % name)).encode('ascii', 'ignore'))

  def handle_data(self, data):
    if self.start_copy:
      self.testcase.write(data.strip('\n').encode('ascii', 'ignore'))
      self.end_line = False

# Contest parser.
class CodeforcesContestParser(HTMLParser):

  def __init__(self, contest):
    HTMLParser.__init__(self)
    self.contest = contest
    self.start_contest = False
    self.start_problem = False
    self.name = ''
    self.problem_name = ''
    self.problems = []
    self.problem_names = []

  def handle_starttag(self, tag, attrs):
    if self.name == '' and attrs == [('style', 'color: black'), ('href', '/contest/%s' % (self.contest))]:
        self.start_contest = True
    elif tag == 'option':
      if len(attrs) == 1:
        regexp = re.compile(r"'[A-Z][0-9]?'") # The attrs will be something like: ('value', 'X'), or ('value', 'X1')
        string = str(attrs[0])
        search = regexp.search(string)
        if search is not None:
          self.problems.append(search.group(0).split("'")[-2])
          self.start_problem = True

  def handle_endtag(self, tag):
    if tag == 'a' and self.start_contest:
      self.start_contest = False
    elif self.start_problem:
      self.problem_names.append(self.problem_name)
      self.problem_name = ''
      self.start_problem = False

  def handle_data(self, data):
    if self.start_contest:
      self.name = data
    elif self.start_problem:
      self.problem_name += data

# Parses each problem page.
def parse_problem(contest, problem):
  url = 'http://codeforces.com/contest/%s/problem/%s' % (contest, problem)
  html = urlopen(url).read()
  parser = CodeforcesProblemParser(problem)
  parser.feed(html.decode('utf-8'))
  # .encode('utf-8') Should fix special chars problems?
  return parser.num_tests

# Parses the contest page.
def parse_contest(contest):
  url = 'http://codeforces.com/contest/%s' % (contest)
  html = urlopen(url).read()
  parser = CodeforcesContestParser(contest)
  parser.feed(html.decode('utf-8'))
  return parser

# Generates the test script.
def generate_test_script(num_tests, problem):

  with open('samples/test_%s.sh' % problem, 'w') as test:
    test.write(
      '#!/bin/bash\n'
      'make '+problem+'\n'
      'INPUT_NAME='+FOLDER+'/'+SAMPLE_INPUT+'_'+problem+'_\n'
      'OUTPUT_NAME='+FOLDER+'/'+SAMPLE_OUTPUT+'_'+problem+'_\n'
      'MY_OUTPUT='+FOLDER+'/'+MY_OUTPUT+'_'+problem+'_\n'
      'rm -f $MY_OUTPUT*\n')
    test.write(
      'for test_file in $INPUT_NAME*\n'
      'do\n'
      '  i=$((${{#INPUT_NAME}}))\n'
      '  test_case=${{test_file:$i}}\n'
      '  if ! {5} ./{7} < $INPUT_NAME$test_case > $MY_OUTPUT$test_case; then\n'
      '    echo {1}{4}Sample test \#$test_case: Runtime Error{2} {6}\n'
      '    echo ========================================\n'
      '    echo Sample Input \#$test_case\n'
      '    cat $INPUT_NAME$test_case\n'
      '  else\n'
      '    if diff --brief --ignore-space-change $MY_OUTPUT$test_case $OUTPUT_NAME$test_case &>/dev/null; then\n'
      '      echo {1}{3}Sample test \#$test_case: Accepted{2} {6}\n'
      '      rm $MY_OUTPUT$test_case\n'
      '    else\n'
      '      echo {1}{4}Sample test \#$test_case: Wrong Answer{2} {6}\n'
      '      echo ========================================\n'
      '      echo Sample Input \#$test_case\n'
      '      cat $INPUT_NAME$test_case\n'
      '      echo ========================================\n'
      '      echo Sample Output \#$test_case\n'
      '      cat $OUTPUT_NAME$test_case\n'
      '      echo ========================================\n'
      '      echo My Output \#$test_case\n'
      '      cat $MY_OUTPUT$test_case\n'
      '      echo ========================================\n'
      '    fi\n'
      '  fi\n'
      'done\n'
      'rm -f time.out\n'
      .format(num_tests, BOLD, NORM, GREEN_F, RED_F, TIME_CMD, TIME_AP, problem))
  call(['chmod', '+x', 'samples/test_%s.sh' % problem])


if __name__ == '__main__':
  parser = argparse.ArgumentParser()
  parser.add_argument('problem', help="")
  args = parser.parse_args()

  contest = current_contest
  target_problem = args.problem

  if not os.path.isdir('./samples'):
    # Find contest and problems.
    print ('Parsing contest %s, please wait...' % (contest))
    content = parse_contest(contest)
    print (BOLD+GREEN_F+'*** Round name: '+content.name+' ***'+NORM)
    print ('Contest has %d problems!' % (len(content.problems)))

    # Find problems and test cases.
    for index, problem in enumerate(content.problems):
      call(['mkdir', '-p', 'samples'])
      print ('Downloading Problem %s: %s...' % (problem, content.problem_names[index]))
      num_tests = parse_problem(contest, problem)
      print('%d sample test(s) found.' % num_tests)
      generate_test_script(num_tests, problem)
  
  call(['samples/test_%s.sh' % target_problem])

