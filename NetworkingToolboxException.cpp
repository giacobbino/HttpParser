#include "NetworkingToolboxException.h"

namespace NetworkingToolbox {

    NetworkingToolboxException::NetworkingToolboxException(std::string message) {
        this->message = message;
    }

    NetworkingToolboxException::NetworkingToolboxException(const NetworkingToolboxException &ex) {
        message = ex.message;
    }

    NetworkingToolboxException::NetworkingToolboxException(NetworkingToolboxException &&ex) :
        std::exception(std::move(ex)) {
        std::swap(message, ex.message);
    }

    NetworkingToolboxException & NetworkingToolboxException::operator =(const NetworkingToolboxException &ex) {
        if (this != &ex) {
            NetworkingToolboxException(ex).swap(*this);
        }
        return *this;
    }

    NetworkingToolboxException & NetworkingToolboxException::operator =(NetworkingToolboxException &&ex) {
        if (this != &ex) {
            NetworkingToolboxException().swap(*this);
            swap(ex);
        }
        return *this;
    }

    void NetworkingToolboxException::swap(NetworkingToolboxException &ex) {
        std::swap(message, ex.message);
    }

    const char * NetworkingToolboxException::what() const throw() {
        return message.c_str();
    }

    NetworkingToolboxException::~NetworkingToolboxException() {

    }

}
