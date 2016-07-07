#!/usr/bin/env python
# coding: utf-8

import thread
from time import sleep, ctime


def loop1():
    print "start loop 1 :", ctime()
    sleep(4)
    print "end loop1 :", ctime()


def loop2():
    print "start loop 2 :", ctime()
    sleep(2)
    print "end loop2 :", ctime()


def sequenceExc():
    print "start seq :", ctime()
    loop1()
    loop2()
    print "start end :", ctime()


def threadExc():
    """
    thread 模块，主线程不会等待子线程结束再退出，这样会导致主线程退出，而终止子线程的运行
    """
    print "start thread test :", ctime()
    thread.start_new_thread(loop2, ())
    thread.start_new_thread(loop1, ())
    sleep(6)
    print "end thread test :", ctime()


def main():
    # sequenceExc()
    threadExc()

if __name__ == "__main__":
    main()
