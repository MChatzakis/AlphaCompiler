#############################################################
#                  Alpha Compiler Script                    #
#                                                           #
# This script runs all the test for Alpha Compiler,         #
# if there exists a folder organized with folders           #
# following the format seen in file harvesting.             #
#                                                           #
# Manos Chatzakis, Nikos Fanourakis                         #
#############################################################

import os
import subprocess

compilerName = "calc"
rootDirectory = "./../tests"

do1 = 0
do2 = 1
do3 = 0
printTests = 1

phase1_tests = []
phase2_tests = []
phase3_tests = []


def printAllTests():
    print("Tests run by the script:")
    if do1:
        for i in range(len(phase1_tests)):
            print(phase1_tests[i])
    if do2:
        for i in range(len(phase2_tests)):
            print(phase2_tests[i])
    if do3:
        for i in range(len(phase3_tests)):
            print(phase3_tests[i])


for path, subdirs, files in os.walk(rootDirectory + "/phase1/"):
    for name in files:
        phase1_tests.append(os.path.join(path, name))

for path, subdirs, files in os.walk(rootDirectory + "/phase2/"):
    for name in files:
        phase2_tests.append(os.path.join(path, name))

for path, subdirs, files in os.walk(rootDirectory + "/phase3/"):
    for name in files:
        phase3_tests.append(os.path.join(path, name))

#print("Phase 1:", phase1_tests)
#print("Phase 2:", phase2_tests)
#print("Phase 3:", phase3_tests)

command = "make"
print(command)
out = subprocess.getoutput(command)
print(out)

if do1:
    for i in range(len(phase1_tests)):
        command = "./" + compilerName + " -i " + phase1_tests[i]
        print(command)
        out = subprocess.getoutput(command)
        print(out)

        if out.find("Segmentation") > -1 or out.find("Assertion") > -1 or out.find("Aborted (core dumped)") > -1:
            print("The last test file failed! -- Exiting...")
            exit()

if do2:
    for i in range(len(phase2_tests)):
        command = "./" + compilerName + " -i " + phase2_tests[i]
        print(command)
        out = subprocess.getoutput(command)
        print(out)

        if out.find("Segmentation") > -1 or out.find("Aborted (core dumped)") > -1:
            print("The last test file failed! -- Exiting...")
            exit()

if do3:
    for i in range(len(phase3_tests)):
        command = "./" + compilerName + " -i " + phase3_tests[i]
        print(command)
        out = subprocess.getoutput(command)
        print(out)

        if out.find("Segmentation") > -1 or out.find("Assertion") > -1 or out.find("Aborted (core dumped)") > -1:
            print("The last test file failed! -- Exiting...")
            exit()

command = "make clean"
print(command)
out = subprocess.getoutput(command)
print(out)

if printTests:
    print("==========================================")
    printAllTests()
