#include <string>

#include "../include/utils.h"


TCP::ret_st TCP::ret_st::failure(const std::string &msg) {
    return ret_st(false, msg);
}

TCP::ret_st TCP::ret_st::success(const std::string &msg) {
    return ret_st(true, msg);
}