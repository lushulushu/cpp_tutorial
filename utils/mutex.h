// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: qli@mobvoi.com (Qian Li)
// Created on: Apr 22, 2014
//
// A pthread mutex wrapper.

#ifndef UTILS_MUTEX_H_
#define UTILS_MUTEX_H_

#include <pthread.h>

class Mutex {
public:
    Mutex();
    ~Mutex();

    void Lock();
    void Unlock();

private:
    friend class Condition;
    pthread_mutex_t mutex_;
};

class MutexLock {
public:
    explicit MutexLock(Mutex* mutex);
    ~MutexLock();

    // If want to release mutex explicit, call Unlock function.
    // If NOT, ~MutexLock() will unlock auto.
    void Unlock();
private:
    Mutex* mutex_;
};

class SharedMutex {
public:
    SharedMutex();
    ~SharedMutex();

    //  Get a Shared Read Lock
    void ReadLock();
    //  Get an Exclusive Write Lock
    void WriteLock();

    //  Get a Shared Read Lock with No Wait
    bool TryReadLock();
    //  Get an Exclusive Write Lock with No Wait
    bool TryWriteLock();

    //  Unlock an Exclusive Write or Shared Read Lock
    void Unlock();

private:
    pthread_rwlock_t rwlock_;
};

class ReadLock {
public:
    explicit ReadLock(SharedMutex* mutex);
    ~ReadLock();

private:
    SharedMutex* mutex_;
};

class WriteLock {
public:
    explicit WriteLock(SharedMutex* mutex);
    ~WriteLock();

private:
    SharedMutex* mutex_;
};

/// Wrapper for pthread_cond_t.
class Condition {
public:
    Condition();
    ~Condition();

    void Wait(Mutex *mu);
    void Broadcast();
    bool WaitWithTimeout(Mutex *mu, int millis);

    void Signal();
    void SignalAll();
private:
    pthread_cond_t cv_;
};

#endif  // UTILS_MUTEX_H_
