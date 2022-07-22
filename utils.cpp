#include <string>

#include "utils.h"


ret_st ret_st::failure(const std::string &msg) {
    return ret_st(false, msg);
}

ret_st ret_st::success(const std::string &msg) {
    return ret_st(true, msg);
}