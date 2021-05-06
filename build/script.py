import os
import subprocess

compilerName = "calc"

do1 = 0
do2 = 0
do3 = 0

phase1_tests = []
phase2_tests = []
phase3_tests = []

for path, subdirs, files in os.walk('./../tests/phase1/'):
    for name in files:
        phase1_tests.append(os.path.join(path, name))

for path, subdirs, files in os.walk('./../tests/phase2/'):
    for name in files:
        phase2_tests.append(os.path.join(path, name))

for path, subdirs, files in os.walk('./../tests/phase3/'):
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