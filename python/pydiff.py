#!/usr/bin/env python
# coding: utf-8
import sys
import time


def dealFirstLine(line):
    """
    deal the line which only in the first file

    line -> str
    """

    print "%s" % (line.strip('\n'))


def dealSecondLine(line):
    """
    deal the line which only in the second file

    line -> str
    """

    print "\t%s" % (line.strip('\n'))


def dealCommonline(line):
    """
    deal the line which in first file and second file
    """

    print "\t\t%s" % (line.strip('\n'))


def dealFileEndpart(fd, func):
    """
    deal the fiel until EOF

    fd -> file object
    func -> process func for line
    """

    for line in fd.readlines():
        func(line)


def pydiff(firstfile, secondfile):
    """
    usage: pydiff file1 file2

    """

    fd1 = open(firstfile, "r")
    fd2 = open(secondfile, "r")

    readLine1 = True
    readLine2 = True
    line1 = ""
    line2 = ""

    while True:
        if readLine1:
            line1 = fd1.readline()
            readLine1 = False
        if readLine2:
            line2 = fd2.readline()
            readLine2 = False

        if not line1 or not line2:
            break

        if line1 == line2:
            dealCommonline(line1)
            readLine1 = True
            readLine2 = True
        elif line1 < line2:
            dealFirstLine(line1)
            readLine1 = True
        else:
            dealSecondLine(line2)
            readLine2 = True

    dealFileEndpart(fd1, dealFirstLine)
    dealFileEndpart(fd2, dealSecondLine)


if __name__ == "__main__":
    print "start pydiff....", time.ctime()
    pydiff(sys.argv[1], sys.argv[2])
    print "end pydiff....", time.ctime()
