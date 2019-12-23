#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "factory.h"
#include "subscriber.h"

int main(int argc, char** argv){
    if (argc != 2) {
        std::cout << "Wrong. Try ./oop_exercise_08 size\n";
        return 0;
    }
    int Vecsize = std::atoi(argv[1]);
    std::vector<std::shared_ptr<figures::Figure>> Vec;
    factory::Factory Factory;
    std::condition_variable cv;
    std::condition_variable cv2;
    std::mutex mutex;
    bool done = false;
    char cmd = 'd';
    int in = 1;
    std::vector<std::shared_ptr<Sub>> subs;
    subs.push_back(std::make_shared<Print>());
    subs.push_back(std::make_shared<Log>());
    std::thread subscriber([&]() {
        std::unique_lock<std::mutex> subscriber_lock(mutex);
        while(!done) {
            cv.wait(subscriber_lock);
            if (done) {
                cv2.notify_all();
                break;
            }
            for (unsigned int i = 0; i < subs.size(); ++i) {
                subs[i]->output(Vec);
            }
            in++;
            Vec.resize(0);
            cv2.notify_all();
        }
    });
    while(cmd != 'q') {
        std::cout << "Input 'q' for quit, or 'r' to continue" << std::endl;
        std::cin >> cmd;
        if (cmd != 'q') {
            std::unique_lock<std::mutex> main_lock(mutex);
            for (int i = 0; i < Vecsize; i++) {
                Vec.push_back(Factory.FigureCreate(std::cin));
                std::cout << "Added" << std::endl;
            }
            cv.notify_all();
            cv2.wait(main_lock);
        }
    }
    done = true;
    cv.notify_all();
    subscriber.join();
    return 0;
}