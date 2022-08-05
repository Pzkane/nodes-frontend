// DEMO
#include <atomic>
#include <thread>
#include <string>
#include <chrono>

#include "NodeFrontEnd.hpp"

void launchWindow(nf::NodeFrontEnd &api, std::atomic<bool> &isDone)
{
    api.init();
    api.launch();
    isDone = true;
}

int main()
{
    std::atomic<bool> done(false);
    nf::NodeFrontEnd api;
    std::thread mainLoop(launchWindow, std::ref(api), std::ref(done));

    while (!api.isInit())
    {
    }

    api.setWindowColor(sf::Color(219, 189, 189));
    for (int i = 0; i < 1; ++i)
    {
        nf::Node *node = api.addNode("w");
        node->setPosition(100, 100);
    }

    std::string txt;
    std::chrono::system_clock::time_point begin;
    std::chrono::system_clock::time_point end;
    nf::Node *node = api.addNode("ss");
    node->setFillColor(sf::Color::Green); // overlap test
    for (int i = 0; i < 1; ++i)
    {
        begin = std::chrono::system_clock::now();

        do {
            end = std::chrono::system_clock::now();
            /* do nothing */
        } while (std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() < 1);
        std::cout << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << std::endl;

        txt += std::to_string(i);
        node->setText(txt);
    }
    while (!done)
    {
    };

    mainLoop.join();

    return 0;
}
