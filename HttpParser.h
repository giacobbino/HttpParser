#ifndef HttpParserH
#define HttpParserH

#include "Utils.h"

namespace NetworkingToolbox {

    class HttpParser final {

        private:
            std::string headersSeparator;
            std::string bodySeparator;
            std::string headerValueSeparator;
            std::string method;
            std::string requestTarget;
            std::string httpVersion;
            std::string status;
            std::string reasonPhrase;
            std::map<std::string, std::string> httpHeaders;
            std::string body;
            std::regex methodRegex;
            std::regex requestTargetRegex;
            std::regex httpVersionRegex;
            std::regex statusRegex;
            bool request;
            bool response;
            virtual void clear();
            virtual void parseFirstLine(const std::string &);

        public:
            HttpParser();
            HttpParser(const std::string &);
            HttpParser(const HttpParser &);
            HttpParser(HttpParser &&);
            virtual HttpParser & operator =(const HttpParser &) final;
            virtual HttpParser & operator =(HttpParser &&) final;
            virtual void swap(HttpParser &);
            HttpParser & parseString(const std::string &);
            virtual std::string getMethod() const;
            virtual HttpParser & setMethod(const std::string &);
            virtual std::string getRequestTarget() const;
            virtual HttpParser & setRequestTarget(const std::string &);
            virtual std::string getHttpVersion() const;
            virtual HttpParser & setHttpVersion(const std::string &);
            virtual std::string getHeader(const std::string &);
            virtual HttpParser & setHeader(const std::string &, const std::string &);
            virtual std::string getBody() const;
            virtual HttpParser &setBody(const std::string &);
            virtual std::string getStatus() const;
            virtual HttpParser & setStatus(const std::string &);
            virtual std::string getReasonPhrase() const;
            virtual HttpParser & setReasonPhrase(const std::string &);
            virtual bool isResponse() const;
            virtual bool isRequest() const;

    };

}
#endif // HttpParserH
