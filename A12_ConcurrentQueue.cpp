/*
 * ============================================================
 *  Atharva Jadhao | SEDA B | Roll No. 21
 *  Assignment 12: Concurrent Data Structures – Thread-Safe Queue
 * ============================================================
 *
 * HOW TO COMPILE & RUN:
 *   g++ A12_ConcurrentQueue.cpp -o a12 -lpthread && ./a12
 *
 * INPUT  : No input needed.
 *
 * EXPECTED OUTPUT (order may vary slightly due to threading):
 *   [Producer] Enqueued: 10
 *   [Consumer] Dequeued: 10
 *   [Producer] Enqueued: 20
 *   [Consumer] Dequeued: 20
 *   [Producer] Enqueued: 30
 *   [Consumer] Dequeued: 30
 *   [Producer] Enqueued: 40
 *   [Consumer] Dequeued: 40
 *   [Producer] Enqueued: 50
 *   [Consumer] Dequeued: 50
 *   All tasks processed safely.
 * ============================================================
 */
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;

class ConcurrentQueue {
    queue<int> q;
    mutex mtx;
    condition_variable cv;
    bool done=false;
public:
    void push(int val){
        unique_lock<mutex> lk(mtx);
        q.push(val);
        cout<<"[Producer] Enqueued: "<<val<<endl;
        cv.notify_one();
    }
    bool pop(int& val){
        unique_lock<mutex> lk(mtx);
        cv.wait(lk,[&]{ return !q.empty()||done; });
        if(q.empty()) return false;
        val=q.front(); q.pop();
        return true;
    }
    void setDone(){ unique_lock<mutex> lk(mtx); done=true; cv.notify_all(); }
};

int main(){
    ConcurrentQueue cq;
    thread producer([&](){
        for(int i=1;i<=5;i++){
            this_thread::sleep_for(chrono::milliseconds(150));
            cq.push(i*10);
        }
        cq.setDone();
    });
    thread consumer([&](){
        int val;
        while(cq.pop(val))
            cout<<"[Consumer] Dequeued: "<<val<<endl;
    });
    producer.join(); consumer.join();
    cout<<"All tasks processed safely."<<endl;
    return 0;
}
