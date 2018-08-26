// Copyright 2014 Mobvoi Inc. All Rights Reserved.
// Author: spye@mobvoi.com (Shunping Ye)

#include "sys/time.h"

#include "utils/macro.h"
#include "utils/mutex.h"

void timeval2timespec(timeval *const tv,
                      timespec *ts,
                      int64_t offset_milli) {
    const int64_t ten_9 = 1000000000LL;
    const int64_t ten_6 = 1000000LL;
    const int64_t ten_3 = 1000LL;
    int64_t now_nsec = (int64_t)tv->tv_sec * ten_9;
    now_nsec += (int64_t)tv->tv_usec * ten_3;
    int64_t then_nsec = now_nsec + offset_milli * ten_6;
    ts->tv_sec  = then_nsec / ten_9;
    ts->tv_nsec = then_nsec % ten_9;
}

Mutex::Mutex() {
    pthread_mutex_init(&mutex_, 0);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex_);
}

void Mutex::Lock() {
    pthread_mutex_lock(&mutex_);
}

void Mutex::Unlock() {
    pthread_mutex_unlock(&mutex_);
}

MutexLock::MutexLock(Mutex* mutex)
        : mutex_(mutex) {
    mutex_->Lock();
}

MutexLock::~MutexLock() {
    if (mutex_) {
        mutex_->Unlock();
    }
}

void MutexLock::Unlock() {
    mutex_->Unlock();
    mutex_ = NULL;
}

SharedMutex::SharedMutex() {
    CHECK_EQ(pthread_rwlock_init(&rwlock_, NULL), 0) << "Fail to init rwlock";
}

SharedMutex::~SharedMutex() {
    CHECK_EQ(pthread_rwlock_destroy(&rwlock_), 0) << "Fail to destroy rwlock";
}

void SharedMutex::ReadLock() {
    pthread_rwlock_rdlock(&rwlock_);
}

void SharedMutex::WriteLock() {
    pthread_rwlock_wrlock(&rwlock_);
}

bool SharedMutex::TryReadLock() {
    return pthread_rwlock_tryrdlock(&rwlock_) == 0;
}

bool SharedMutex::TryWriteLock() {
    return pthread_rwlock_trywrlock(&rwlock_) == 0;
}

void SharedMutex::Unlock() {
    pthread_rwlock_unlock(&rwlock_);
}

ReadLock::ReadLock(SharedMutex* mutex) : mutex_(mutex) {
    mutex_->ReadLock();
}

ReadLock::~ReadLock() {
    mutex_->Unlock();
}

WriteLock::WriteLock(SharedMutex* mutex) : mutex_(mutex) {
    mutex_->WriteLock();
}

WriteLock::~WriteLock() {
    mutex_->Unlock();
}

Condition::Condition() {
    CHECK(0 == pthread_cond_init(&cv_, NULL));
}

Condition::~Condition() {
    CHECK(0 == pthread_cond_destroy(&cv_));
}

void Condition::Wait(Mutex *mu) {
    CHECK(0 == pthread_cond_wait(&cv_, &mu->mutex_));
}

bool Condition::WaitWithTimeout(Mutex *mu, int millis) {
    struct timeval now;
    struct timespec timeout;
    gettimeofday(&now, NULL);
    timeval2timespec(&now, &timeout, millis);
    return 0 != pthread_cond_timedwait(&cv_, &mu->mutex_, &timeout);
}

void Condition::Broadcast() {
    pthread_cond_broadcast(&cv_);
}

void Condition::Signal() {
    CHECK(0 == pthread_cond_signal(&cv_));
}

void Condition::SignalAll() {
    CHECK(0 == pthread_cond_broadcast(&cv_));
}
