#ifndef UTILS_H
#define UTILS_H

#include <string>


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

#endif