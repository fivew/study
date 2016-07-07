#!/usr/bin/env python
# coding: utf-8

import thread
from time import sleep, ctime


sleeps = [i for i in range(3)]


def loops(seqno, sleeptime, lock):
    print "start loop(%d) :" % (seqno), ctime()
    sleep(sleeptime)
    lock.release()
    print "end loop(%d) :" % (seqno), ctime()


def threadExc():
    """
    thread 模块，主线程不会等待子线程结束再退出，这样会导致主线程退出，而终止子线程的运行
    """
    print "start thread test :", ctime()

    locks = []
    # set lock
    for i in range(len(sleeps)):
        lock = thread.allocate_lock()
        lock.acquire()
        locks.append(lock)

    # process
    for i in range(len(sleeps)):
        thread.start_new_thread(loops, (i, sleeps[i], locks[i]))

    # until child thread end, exit
    for i in range(len(sleeps)):
        while locks[i].locked():
            pass

    print "end thread test :", ctime()


def main():
    # sequenceExc()
    threadExc()

if __name__ == "__main__":
    main()
