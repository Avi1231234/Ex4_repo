#!/usr/bin/python3
import os.path
import datetime
from constants import *

"""
Fill in the required information in this file.
Once filled in, you may run the script and it will let you know if everything is in order.
"""

#############################################################################################################
######################################### Your information goes here ########################################
#############################################################################################################

"""[REQUIRED] Exercise Number. 1-6"""
EX_NUM = 4

SUBMISSION_DEADLINE = datetime.datetime(year=2022, month=12, day=28, hour=23, minute=59)
"""Date of submission deadline, used in order to calculate early submission bonuses 
(most likely only need to change month and day)"""

AUTOTEST_COMPILATION_WRAP_SYMBOLS = []

FORBIDDEN_FUNCTIONS = ['exit', 'malloc', 'realloc', 'calloc', 'free', 'strlen']

PUBLISH_SCHOOL_SOLUTION = False

"""[REQUIRED] List of Required Source Files In Submission. For example: ["file1.c", "file2.c"]"""
REQUIRED_SRC_FILES = ["Matrix.cpp", "Activation.cpp", "Dense.cpp", "MlpNetwork.cpp"]

"""[REQUIRED] List of Required Header Files In Submission. For example: ["file1.h", "file2.h"]"""
REQUIRED_HDR_FILES = ["Matrix.h", "Activation.h", "Dense.h", "MlpNetwork.h"]

"""[OPTIONAL] List of Optional Files In Submission. For example: ["optional.c"]. May be an empty list."""
OPTIONAL_FILES = []

REQUIRED_OTHER_FILES = []
"""[REQUIRED] List of Required Header Files In Submission. For example: ["file1", "file2"]"""

"""[OPTIONAL] List of Required Files For Bonus Submission. For example: ["bonus.c"]. May be an empty list"""
BONUS_FILES = []

"""[OPTIONAL] List of Forbidden Files In Submission. For example: ["main.c"]. May be an empty list."""
FORBIDDEN_FILES = []

"""[REQUIRED] boolean describing whether or not the students' submission contains a main method."""
SUBMISSION_HAS_MAIN = False

"""[OPTIONAL] string containing preprocessor definition to pass in compilation command if bonus was 
submitted. For example: "BONUS_SUBMITTED". Required if BONUS_FILES is not empty."""
BONUS_MACRO = ""

"""[OPTIONAL] Subset of IOTests to preform for presubmit. Only if students' submission contains a main
 method. For example: {1, 3, 7}."""
PRESUBMIT_IO_TESTS = {}

PRESUBMIT_AST_TESTS = {1}
"""[OPTIONAL] Subset of AST Tests to preform for presubmit. For example: {1, 3, 7}."""

"""[OPTIONAL] List of Additional Presubmit Sources For example: ["Presubmit_helper.c"]"""
PRESUBMIT_ADDITIONAL_SRCS = []

"""[OPTIONAL] List of Autotests Additional Sources. For example: ["autotest_helper.c"]"""
AUTOTESTS_ADDITIONAL_SRCS = []

"""[OPTIONAL] Number of Standalone Tests. 0 if none."""
UNIT_TESTS_NUM = 31

"""[OPTIONAL] Number of Comparison Tests. 0 if none."""
COMPARISON_TESTS_NUM = 0

MAKEFILE_TESTS = {}
"""[OPTIONAL] Dictionary where keys are makefile targets and values are lists of files that should be
created by target. For example: {'all': ['some_file.o', 'some_program']} """

AST_TESTS_NUM = 1
"""[OPTIONAL] Number of AST Tests. 0 if none"""

PRESUBMIT_MAKEFILE_TESTS = {}
"""[OPTIONAL] Subset of Makefile Targets to execute for presubmit. For example: {all, lib}."""

"""[REQUIRED FOR PREVIOUS OPTION] string containing the name of a python script that receives 2 arguments.
	For example: "compare.py" ."""
COMPARISON_SCRIPT = "diff.py"

# """[REQUIRED FOR PREVIOUS OPTION] Enum of Student Output type. STUDENT_OUTPUT enum - FILE or STDOUT.
# 	For example: STUDENT_OUTPUT.STDOUT"""
# COMPARISON_STUDENT_OUTPUT = STUDENT_OUTPUT.STDOUT

"""[OPTIONAL] string containing prefix path to student output file, if previous option was FILE. 
The test number will be appended after the prefix. For example: "stu_out_" means the output for test number
# will be found at stu_out_# """
COMPARISON_STUDENT_OUTPUT_PATH = ""

"""[OPTIONAL] Number of Bonus Tests. 0 if none"""
BONUS_TESTS_NUM = 0

"""[OPTIONAL] Number of IO Tests. 0 if none."""
IO_TESTS_NUM = 0

"""[REQUIRED FOR PREVIOUS OPTION] string containing the name of a python script that receives 2 arguments.
	For example: "compare.py" ."""
IO_COMPARISON_SCRIPT = "diff.py"

# """[REQUIRED FOR PREVIOUS OPTION] Enum of Student Output type. STUDENT_OUTPUT enum - FILE or STDOUT.
# 	For example: STUDENT_OUTPUT.STDOUT"""
# IO_STUDENT_OUTPUT = STUDENT_OUTPUT.STDOUT

"""[OPTIONAL] string containing prefix path to student output file, if previous option was FILE. 
The test number will be appended after the prefix. For example: "stu_out_" means the output for test number
# will be found at stu_out_# """
IO_STUDENT_OUTPUT_PATH = ""

"""[OPTIONAL] Number of Positive Compilation Tests. 0 if none."""
P_COMPILATION_TESTS_NUM = 12

"""[OPTIONAL] Number of Negative Compilation Tests. 0 if none"""
N_COMPILATION_TESTS_NUM = 1

#############################################################################################################
#############################################################################################################
#############################################################################################################


if __name__ == '__main__':
    print("Validating information")
    errors = ""
    if EX_NUM not in [1, 2, 3, 4, 5, 6]:
        errors += f"Error: Specified EX_NUM: {EX_NUM} is invalid (must be a number between 1 and 6).\n"
    for f in REQUIRED_SRC_FILES:
        if not os.path.isfile(os.path.join(DIR_SCHOOL_SOL, f)):
            errors += f"Error: Specified required source file {f} not found in directory {DIR_SCHOOL_SOL}.\n"
    for f in REQUIRED_SRC_FILES:
        if not os.path.isfile(os.path.join(DIR_SCHOOL_SOL, f)):
            errors += f"Error: Specified required header file {f} not found in directory {DIR_SCHOOL_SOL}.\n"
    for f in BONUS_FILES:
        if not os.path.isfile(os.path.join(DIR_SCHOOL_SOL, f)):
            errors += f"Error: Specified bonus file {f} not found in directory {DIR_SCHOOL_SOL}.\n"
    if BONUS_FILES and not BONUS_MACRO:
        errors += f"Error: Specified files for bonus submissions but no preprocessor definition.\n"
    for f in PRESUBMIT_ADDITIONAL_SRCS:
        if not os.path.isfile(os.path.join(DIR_PRESUB_SRC, f)):
            errors += f"Error: Specified presubmit additinal source file {f} not found in directory {DIR_PRESUB_SRC}.\n"
    if SUBMISSION_HAS_MAIN:
        if not IO_TESTS_NUM:
            errors += f"Error: If the submission includes a main function, I/O tests must be used.\n"
        if not PRESUBMIT_IO_TESTS:
            errors += f"Warning: No I/O Tests for presubmit means it will only check compilation.\n"
        if max(PRESUBMIT_IO_TESTS) > IO_TESTS_NUM:
            errors += f"Error: Presubmit specifies I/O test {max(PRESUBMIT_IO_TESTS)}, but the number of specified I/O tests is {IO_TESTS_NUM}\n"
    if not SUBMISSION_HAS_MAIN and not os.path.isfile(
            os.path.join(DIR_PRESUB_SRC, "presubmit.c")) and not os.path.isfile(
        os.path.join(DIR_PRESUB_SRC, "presubmit.cpp")):
        errors += f"Error: Main presubmit source file (presubmit.c/cpp) not found in directory {DIR_PRESUB_SRC}.\n"
    for f in AUTOTESTS_ADDITIONAL_SRCS:
        if not os.path.isfile(os.path.join(DIR_AUTOTESTS_SRC, f)):
            errors += f"Error: Specified autotests additinal source file {f} not found in directory {DIR_AUTOTESTS_SRC}.\n"
    for i in range(1, UNIT_TESTS_NUM):
        if not os.path.isfile(os.path.join(DIR_AUTOTESTS_SRC, f"{UNIT_TESTS_PREFIX}{i}.cpp")):
            errors += f"Error: Specified {UNIT_TESTS_NUM} standalone tests, but {UNIT_TESTS_PREFIX}{i}  was not found in directory {DIR_AUTOTESTS_SRC}.\n"
    for i in range(1, COMPARISON_TESTS_NUM):
        if not os.path.isfile(os.path.join(DIR_AUTOTESTS_SRC, f"{COMPARISON_TESTS_PREFIX}{i}")):
            errors += f"Error: Specified {COMPARISON_TESTS_NUM} standalone tests, but {COMPARISON_TESTS_PREFIX}{i}  was not found in directory {DIR_AUTOTESTS_SRC}.\n"
    for i in range(1, P_COMPILATION_TESTS_NUM):
        if not os.path.isfile(os.path.join(DIR_AUTOTESTS_SRC, f"{P_COMPILATION_TESTS_PREFIX}{i}.cpp")):
            errors += f"Error: Specified {P_COMPILATION_TESTS_NUM} standalone tests, but {P_COMPILATION_TESTS_PREFIX}{i}  was not found in directory {DIR_AUTOTESTS_SRC}.\n"
    for i in range(1, N_COMPILATION_TESTS_NUM):
        if not os.path.isfile(os.path.join(DIR_AUTOTESTS_SRC, f"{N_COMPILATION_TESTS_PREFIX}{i}.cpp")):
            errors += f"Error: Specified {N_COMPILATION_TESTS_NUM} standalone tests, but {N_COMPILATION_TESTS_PREFIX}{i}  was not found in directory {DIR_AUTOTESTS_SRC}.\n"
    if not os.path.isfile(os.path.join(DIR_ERRORCODES, f"ex{EX_NUM}.errorcodes")):
        errors += f"Error: file ex{EX_NUM}.errorcodes not found in {DIR_ERRORCODES}\n"
    if errors:
        print("Dang, found some errors:\n", errors)
