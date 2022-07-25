#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <functional>


namespace TCP {

class ret_st {

private:

    bool _successFlag = false;
    std::string _msg = "";

public:

    ret_st() = default;
    ret_st(bool successFlag, const std::string &msg) :
        _successFlag{successFlag},
        _msg{msg}
    {}

    std::string message() const { return _msg; }
    bool isSuccessful() const { return _successFlag; }

    static ret_st failure(const std::string & msg);
    static ret_st success(const std::string &msg = "");
};

struct server_observer_t {
	std::string wantedIP = "";
	std::function<void(const std::string &clientIP, const char * msg, size_t size)> incomingPacketHandler;
	std::function<void(const std::string &ip, const std::string &msg)> disconnectionHandler;
};

} // namespace TCP
#endif