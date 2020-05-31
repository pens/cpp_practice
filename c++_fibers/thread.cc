/*
    Thread vs Fiber comparison
*/
#include <functional>
#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <boost/fiber/all.hpp>
using namespace std;
using namespace boost;

mutex work_mut;
mutex cout_mut;
queue<function<void()>> work;
bool stayAlive = true;

void thread_work(int i) {
    unique_lock<mutex> lock(cout_mut);
    cout << "Thread: " << this_thread::get_id() << " Num: " << i << endl;
}

void thread_fn() {
    while (stayAlive) {
        function<void()> to_do;
        bool ready = false;
        if (work_mut.try_lock()) {
            if (!work.empty()) {
                to_do = work.front();
                ready = true;
                work.pop();
            }
            work_mut.unlock();
            if (ready) {
                to_do();
                ready = false;
            }
        }
        else
            this_thread::yield();
    }
}

void fiber_work(int i) {
    unique_lock<mutex> lock(cout_mut);
    cout << "Fiber: " << this_fiber::get_id() << " Num: " << i << endl;
}

void fiber_fn() {
    while (stayAlive) {
        function<void()> to_do;
        bool ready = false;
        if (work_mut.try_lock()) {
            if (!work.empty()) {
                to_do = work.front();
                ready = true;
                work.pop();
            }
            else {
                work_mut.unlock();
                return;
            }
            work_mut.unlock();
            if (ready) {
                to_do();
                ready = false;
            }
        }
        else
            this_fiber::yield();
    }
}

int main()
{
    //Threads
    auto start = chrono::high_resolution_clock::now();

    thread threads[8];

    for (auto i = 0; i < 8; ++i) {
        threads[i] = thread{ thread_fn };
    }

    for (auto i = 0; i < 1000; ++i) {
        work_mut.lock();
        work.push([i]() { thread_work(i); });
        work_mut.unlock();
    }

    while (!work.empty());

    stayAlive = false;
    for (auto i = 0; i < 8; ++i) {
        threads[i].join();
    }

    auto threadStop = chrono::high_resolution_clock::now() - start;

    //Fibers
    //TODO add 8 threads to run fibers
    stayAlive = true;

    start = chrono::high_resolution_clock::now();

    fibers::use_scheduling_algorithm<fibers::algo::shared_work>();

    fibers::fiber fibers[8];
    for (auto i = 0; i < 8; ++i) {
        fibers[i] = fibers::fiber{ fiber_fn };
    }

    for (auto i = 0; i < 1000; ++i) {
        work_mut.lock();
        work.push([i]() { fiber_work(i); });
        work_mut.unlock();
    }

    while (!work.empty())
        this_fiber::yield();

    stayAlive = false;
    for (auto i = 0; i < 8; ++i) {
        fibers[i].join();
    }

    auto fiberStop = chrono::high_resolution_clock::now() - start;
    cout << "Threads: " << ((chrono::duration<double, milli>)threadStop).count() << "ms Fibers: " << ((chrono::duration<double, milli>)fiberStop).count() << "ms" << endl;

    return 0;
}

