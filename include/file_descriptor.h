#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <cstdint>

#define MAX_PACKET_SIZE 4096


namespace FileDesc {

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
            void set(int fd);
            int get() const;
    };

} // namespace TCP

#endif