// Copyright (c) 2019 Internetstiftelsen
// Written by Göran Andersson <initgoran@gmail.com>

// This class is meant to be used only _outside_ the event loop, i.e. from some
// other thread or process. It is used together with a UnixDomainBridge, which
// runs in the event loop. After creating the UnixDomainBridge object, call
// getClientSocket() on it to get a file descriptor which should be used as
// an argument to the constructor of this class. Then make sure the
// UnixDomainBridge object runs in an event loop, but not in the same thread or
// process as this class.

#pragma once

#include <string>

class UnixDomainClient {
public:
    UnixDomainClient(int peer_fd) :
        client_socket(peer_fd) {
    }
    // popFromAgent will return an empty string if no message
    // is available. Poll regularly or monitor the socket descriptor.
    std::string pollAgent();

    // As above, but blocks until a message is available or until timeout_us
    // microseconds have passed (or forever, if timeout_us is 0).
    std::string waitForMsgFromAgent(unsigned long timeout_us = 0);

    void pushToAgent(const std::string &msg);

private:
    std::string to_agent;
    std::string to_client;
    int client_socket;
};
