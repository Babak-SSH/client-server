#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H


#include <cstdint>

namespace TCP {

    enum Result {
        FAILURE,
        TIMEOUT,
        SUCCESS
    };

    Result waitFor(const FileDescriptor &fileDescriptor, uint32_t timeoutSeconds = 1);

    class FileDescriptor {
        private:
            int _sockfd = 0;

        public:
            void set(int fd) { _sockfd = fd; }
            int get() const { return _sockfd; }
    };

} // namespace TCP

#endif