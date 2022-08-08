#ifndef SEND_IMP_H
#define SEND_IMP_H

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/any.pb.h>


using namespace google::protobuf::io;

namespace TCP {

    template <typename T> ret_st TcpClient::sendMsg(T payload) {
        google::protobuf::Any any;
        any.PackFrom(payload);

        int pktSize = any.ByteSizeLong()+4;
        char *pkt = new char [pktSize];
        google::protobuf::io::ArrayOutputStream aos(pkt,pktSize);
        CodedOutputStream *coded_output = new CodedOutputStream(&aos);
        coded_output->WriteVarint32(any.ByteSizeLong());
        any.SerializeToCodedStream(coded_output);

        const size_t numBytesSent = send(_sockfd.get(), pkt, pktSize, 0);

        if (numBytesSent < 0 ) { // send failed
            return ret_st::failure(strerror(errno));
        }
        if (numBytesSent < pktSize) { // not all bytes were sent
            char errorMsg[100];
            sprintf(errorMsg, "Only %lu bytes out of %lu was sent to client", numBytesSent, pktSize);
            return ret_st::failure(errorMsg);
        }

        return ret_st::success();
    }
} // namespace TCP

#endif