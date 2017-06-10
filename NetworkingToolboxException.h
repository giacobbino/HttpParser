#ifndef NetworkingToolboxExceptionH
#define NetworkingToolboxExceptionH

#include <string>
#include <stdexcept>

namespace NetworkingToolbox {

    class NetworkingToolboxException : public std::exception {

        private:
            std::string message;

        public:
            NetworkingToolboxException(std::string message = "");
            NetworkingToolboxException(const NetworkingToolboxException &);
            NetworkingToolboxException(NetworkingToolboxException &&);
            virtual NetworkingToolboxException & operator =(const NetworkingToolboxException &) final;
            virtual NetworkingToolboxException & operator =(NetworkingToolboxException &&) final;
            virtual void swap(NetworkingToolboxException &);
            virtual const char* what() const throw();
            virtual ~NetworkingToolboxException();
    };

}

#endif // NetworkingToolboxExceptionH
