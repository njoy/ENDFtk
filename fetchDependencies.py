#! /usr/bin/env python

'''
A handy python script for working with component-based projects
using submodules. This script is written a subset of python compatible
with both Python 2 (version 2.6 or later) and Python 3 (any), so you
shouldn't need to worry about which python version you're using.

Within the NJOY21 scheme, each project repository composes a submodule
for each of the project's (first-order) dependencies. This can lead to
low-level projects (logging, testing, etc) being cloned many times when
cloning recursively. This inflates the time required to clone the project,
bloats the source directory, and the buffer-busting wave of terminal
output just gives a false impression of the complexity of the project.

In addition, submodules have the peculiarity of being associated with
a particular commit rather than a particular branch. As a result,
when a project is updated, any other project depending upon it must also
be updated to benefit. This can amount to considerable overhead when 
working on low-level projects.

This script addresses both problems. Subproject repositories are cloned
only once and follow the same composition scheme assumed by the CMake
configuration script. After cloning, the subproject repository is updated
to the development branch.

The latter behavior may be disabled by invoking the script with the
--no_update flag.
'''

try:
  import argparse
  import subprocess
  import os

  isWindows = (os.name == "nt")

  def smart_clone( cloned_repositories,
                   update_to_development ):
    ''' 
    A happy recursive function to clone components once, only once, and
    with the expected composition
    '''
    import re

    start_list_pattern = re.compile('\s*list\(\s*APPEND\s*subprojects.*\n',
                                    re.IGNORECASE)
    
    comment_line_pattern = re.compile('\s*\#.*')
    subprojects = list()

    if (os.path.exists("subprojects.cmake")):
        with open("subprojects.cmake", "r") as f:

            hasContent = False
            for line in f:
                if (start_list_pattern.match(line) != None):
                    hasContent = True
                    break

            if (not hasContent): return
            
            for line in f:
                if (not comment_line_pattern.match(line)):
                    line = line.replace('"', '')
                    closing_position = line.find(')')
                    line = line[:closing_position].strip()
                    if (line != ""):
                        subprojects.append(line)
                    if (closing_position != -1):
                        break

        for subproject in subprojects:
            if (not (subproject in cloned_repositories)):
                print("")
                print("----------------------------------------")
                print("Fetching " + subproject + "...")
                print("----------------------------------------")
                print("")
                if isWindows:
                  subprocess.Popen(["powershell",
                                    "git",
                                    "submodule",
                                    "update",
                                    "-q",
                                    "--init", 
                                    "--",
                                    subproject])

                else:
                  subprocess.call(["git",
                                   "submodule",
                                   "update",
                                   "--init",
                                   "--",
                                   subproject])
                
                os.chdir(subproject)
                print("")
                if (update_to_development):
                    print("Updating to deploy-ready branch...")
                    print("")
                    if isWindows:
                      subprocess.Popen(["powershell",
                                        "git",
                                        "pull",
                                        "-q",
                                        "origin",
                                        "master"])
                    else:
                      subprocess.call(["git",
                                       "pull",
                                       "origin",
                                       "master"])
                cloned_repositories.add(subproject)
                smart_clone( cloned_repositories,
                             update_to_development )
                os.chdir("..")
                
  # end smart_clone function
                
  parser = argparse.ArgumentParser()
  parser.add_argument('--no_update', action='store_true')
  update_to_development = not parser.parse_args().no_update
  cloned_repositories = set()

  print("")
  print("----------------------------------------")
  print("Fetching commonCMakeScripts...")
  print("----------------------------------------")
  print("")
  if isWindows:
    subprocess.Popen(["powershell",
                      "git",
                      "submodule",
                      "update",
                      "-q",
                      "--init",
                      "--",
                      "commonCMakeScripts"])
  else:
    subprocess.call(["git",
                     "submodule",
                     "update",
                     "--init",
                     "--",
                     "commonCMakeScripts"])
  print("")
  if (update_to_development):
      print("Updating to deploy-ready branch...")
      print("")
      os.chdir("commonCMakeScripts")
      if isWindows:
        subprocess.Popen(["powershell",
                          "git",
                          "pull",
                          "-q",
                          "origin",
                          "master"])
      else:
        subprocess.call(["git",
                         "pull",
                         "origin",
                         "master"])
      os.chdir("..")
    
  smart_clone( cloned_repositories, update_to_development )
except:
  import pdb
  pdb.set_trace()