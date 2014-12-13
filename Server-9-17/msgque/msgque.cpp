#include "msgque.h"

msgque::msgque() {
    thread_stop = false;
    queCount = 0;
    string err = "cannot start the accpet thread";
    try {
        if (pthread_create(&thread_ID, NULL, queDealer, this) != 0)
            throw err;
    } catch (string _err) {
        cout << "thread create\t[FAILD]" << endl;
        cout << _err << endl;
    }
}

msgque::~msgque() {
    thread_stop = true;
    while (thread_stop)
        sleep(1);
}

void* msgque::queDealer(void* param) {
    msgque *THIS = (msgque*) param;
    while (!THIS->thread_stop) {
        if (!THIS->msgQueue.empty()) {
            THIS->msgDealer(THIS->msgQueue.front());
            THIS->msgQueue.pop_front();
            THIS->queCount --;
        }
        usleep(1000);
    }
    THIS->thread_stop = false;
    return nullptr;
}

void msgque::addMsg(protocol _pkg) {
    msgQueue.push_back(_pkg);
    queCount ++;
}