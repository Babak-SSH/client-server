#include <cstdint>
#include <sys/select.h>

#include "../include/file_descriptor.h"

#define SELECT_FAILED -1
#define SELECT_TIMEOUT 0


namespace FileDesc {
    /**
     * monitor file descriptor and wait for I/O operation
     */
    Result waitFor(const FileDescriptor &fileDescriptor, uint32_t timeoutSeconds) {
        struct timeval tv;
        tv.tv_sec = timeoutSeconds;
        tv.tv_usec = 0;
        fd_set fds;

        FD_ZERO(&fds);
        FD_SET(fileDescriptor.get(), &fds);
        const int selectRet = select(fileDescriptor.get() + 1, &fds, nullptr, nullptr, &tv);

        if (selectRet == SELECT_FAILED) {
            return Result::FAILURE;
        } else if (selectRet == SELECT_TIMEOUT) {
            return Result::TIMEOUT;
        }
        return Result::SUCCESS;
    }

    int FileDescriptor::get() const { return FileDescriptor::_sockfd; }
    
    void FileDescriptor::set(int fd) { FileDescriptor::_sockfd = fd; }

} // namespace FileDesc