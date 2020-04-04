#!/usr/bin/env python

import sys
import re
import datetime

from sys import argv
from io import open

def printUsage():
    print("""
A Python script to merge multiple Si534x regsiter congirurations into a single file

Usage:
  ./SiMerge.py SiRegOutFile.h SiRegInFile1.h SiRegInFile2.h [SiRegFile3.h] []
""")


def printHeader(outfile, infiles):
    outfile.write("""
/******************************************************************************
 * Si534x Register Configuration header file
 *
""")
    outfile.write(" * Inputs: " + infiles + "\n");
    outfile.write(" *\n * Timestamp: " + datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S"))
    outfile.write("""
 *
 *****************************************************************************/

""")

def extractRegType(infile, outfile):
    content = infile.read()
    typedef_regex = r"(?s)(typedef struct).*?(_register_t;)"
    matches = re.finditer(typedef_regex, content, re.MULTILINE)

    for matchNum, match in enumerate(matches, start=1):
        # print ( match.group())
        outfile.write(match.group())
        outfile.write("\n\n")

def extractPreamblePostamble(infile, outfile):
    content = infile.read();
    preamble_regex = r"(?s)(Start configuration preamble).*?(End configuration preamble)"
    matches = re.finditer(preamble_regex, content, re.MULTILINE)

    for matchNum, match in enumerate(matches, start=1):
        # print ( match.group())
        outfile.write("si5344_revd_register_t const si5344_preamble[] = {\n")
        outfile.write("    /* " + match.group() + " */")
        outfile.write("\n};\n\n")
    
    postamble_regex = r"(?s)(Start configuration postamble).*?(End configuration postamble)"
    matches = re.finditer(postamble_regex, content, re.MULTILINE)

    for matchNum, match in enumerate(matches, start=1):
        # print ( match.group())
        outfile.write("si5344_revd_register_t const si5344_postamble[] = {\n")
        outfile.write("    /* " + match.group() + " */")
        outfile.write("\n};\n\n") 

def extractRegisters(infile, outfile, arrayName):
    content = infile.read()
    preamble_regex = r"(?s)(Start configuration registers).*?(End configuration registers)"
    matches = re.finditer(preamble_regex, content, re.MULTILINE)

    for matchNum, match in enumerate(matches, start=1):
        # print ( match.group())
        outfile.write("si5344_revd_register_t const " + arrayName + "[] = {\n")
        outfile.write("    /* " + match.group() + " */")
        outfile.write("\n};\n\n")
    
def printFooter(outfile, extractedRegs):
    outfile.write("""
typedef struct 
{
    const char * name;
    const si5344_revd_register_t * const configArr;
    const size_t configLen;
} si534x_config_t;

si534x_config_t si534xConfig[] = {""")
    for reg in extractedRegs:
        outfile.write("\n    { \"" + reg + "\",\n")
        outfile.write("        " + reg +",\n")
        outfile.write("        sizeof(" + reg + ")/sizeof(si5344_revd_register_t)\n    },")

    outfile.write("\n};\n")




def getArrayName(filename):
    # Si5344-RevD-DeWille01-Registers_225792_SingleIn.h =>
    # si5344_revd_dewille01_registers_225792_singlein
    filename = filename.lower()
    if filename.endswith(".h"):
        filename = filename[:-4]
    filename = filename.replace("-", "_")
    return filename

# It starts here
if sys.version_info[0] < 3:
    print("Please use python3 to run this script!")
    quit()
if len(argv) < 3:
    printUsage()
    quit()

with open(argv[1], "w") as outfile:
    print("Printing header...\n")
    printHeader(outfile, ",".join(argv[2:]))
   
    # igore errors as input file contains non-ansi character(s)
    with open(argv[2], errors="ignore") as infile:
        print("Extracting register typedef...\n");
        extractRegType(infile, outfile)

    with open(argv[2], errors="ignore") as infile:
        print("Extracting preamble and postamble...\n");
        extractPreamblePostamble(infile, outfile)

    extractedRegs = []
    for i in range(2, len(argv)):
        print("Extracting register configuration from " + argv[i] + "\n")
        arrayName = getArrayName(argv[i])
        extractedRegs.append(arrayName)
        with open(argv[i], errors="ignore") as infile:
            extractRegisters(infile, outfile, arrayName)

    printFooter(outfile, extractedRegs)

    print("Done")
    


