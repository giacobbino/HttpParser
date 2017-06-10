#include "HttpParser.h"

namespace NetworkingToolbox {

    HttpParser::HttpParser() {
        clear();
    }

    HttpParser::HttpParser(const std::string &packet)
    try : HttpParser() {
        parseString(packet);
    } catch (const NetworkingToolboxException &ex) {
        throw ex;
    }

    HttpParser::HttpParser(const HttpParser &httpParser) {
        clear();
        httpHeaders = httpParser.httpHeaders;
        method = httpParser.method;
        requestTarget = httpParser.requestTarget;
        httpVersion = httpParser.httpVersion;
        status = httpParser.status;
        reasonPhrase = httpParser.reasonPhrase;
        body = httpParser.body;
        request = httpParser.request;
        response = httpParser.response;
    }

    HttpParser::HttpParser(HttpParser &&httpParser) {
        swap(httpParser);
    }

    HttpParser & HttpParser::operator =(const HttpParser &httpParser) {
        if (this != &httpParser) {
            HttpParser(httpParser).swap(*this);
        }
        return *this;
    }

    HttpParser & HttpParser::operator =(HttpParser &&httpParser) {
        if (this != &httpParser) {
            HttpParser().swap(*this);
            swap(httpParser);
        }
        return *this;
    }

    void HttpParser::swap(HttpParser &httpParser) {
        std::swap(httpHeaders, httpParser.httpHeaders);
        std::swap(method, httpParser.method);
        std::swap(requestTarget, httpParser.requestTarget);
        std::swap(httpVersion, httpParser.httpVersion);
        std::swap(status, httpParser.status);
        std::swap(reasonPhrase, httpParser.reasonPhrase);
        std::swap(body, httpParser.body);
        std::swap(request, httpParser.request);
        std::swap(response, httpParser.response);
    }

    void HttpParser::clear() {
        httpHeaders.clear();
        method = "";
        requestTarget = "";
        httpVersion = "";
        status = "";
        reasonPhrase = "";
        body = "";
        request = false;
        response = false;
        headersSeparator = "\r\n";
        bodySeparator = "\r\n\r\n";
        headerValueSeparator = ":";
        methodRegex = std::regex("^(GET|POST)$");
        requestTargetRegex = std::regex("^\\/(([A-z0-9\\-\\%]+\\/)*[A-z0-9\\-\\%]+)?(\\?([A-z0-9\\-\\%]+=[A-z0-9\\-\\%]+&{0,1})*){0,1}$", std::regex_constants::icase);
        httpVersionRegex = std::regex("^HTTP\\/[0-9].[0-9]$");
        statusRegex = std::regex("^[0-9]{3}$");
    }

    void HttpParser::parseFirstLine(const std::string &firstLine) {
        std::string temp = firstLine;
        std::string firstToken = trimmed(temp.substr(0, temp.find(" ")));
        temp = trimmed(temp.substr(temp.find(" ") + 1));
        std::string secondToken = trimmed(temp.substr(0, temp.find(" ")));
        temp = trimmed(temp.substr(temp.find(" ") + 1));
        std::string thirdToken = trimmed(temp);
        if (std::regex_match(firstToken, methodRegex) && std::regex_match(secondToken, requestTargetRegex) && std::regex_match(thirdToken, httpVersionRegex)) {
            method = firstToken;
            requestTarget = secondToken;
            httpVersion = thirdToken;
            request = true;
        } else if (std::regex_match(firstToken, httpVersionRegex) && std::regex_match(secondToken, statusRegex)) {
            httpVersion = firstToken;
            status = secondToken;
            reasonPhrase = thirdToken;
            response = true;
        } else {
            throw NetworkingToolboxException("Invalid HTTP.");
        }
    }

    HttpParser & HttpParser::parseString(const std::string &http) {
        clear();
        body = http.substr(http.find(bodySeparator) + bodySeparator.length());
        std::string headers = trimmed(http.substr(0, http.find(bodySeparator))) + headersSeparator;
        parseFirstLine(trimmed(headers.substr(0, headers.find(headersSeparator))));
        headers = headers.substr(headers.find(headersSeparator) + headersSeparator.length());
        while (headers != "") {
            if (headers.find(headerValueSeparator) == std::string::npos) {
                clear();
                throw NetworkingToolboxException("Invalid HTTP header field.");
            }
            headers += headersSeparator;
            std::string key = trimmed(headers.substr(0, headers.find(headersSeparator)));
            std::string value = trimmed(key.substr(key.find(headerValueSeparator) + headerValueSeparator.length()));
            key = trimmed(key.substr(0, key.find(headerValueSeparator)));
            httpHeaders[key] = value;
            headers = trimmed(headers.substr(headers.find(headersSeparator) + headersSeparator.length()));
        }
        return *this;
    }

    HttpParser & HttpParser::setMethod(const std::string &method) {
        this->method = method;
        return *this;
    }

    std::string HttpParser::getMethod() const {
        return method;
    }

    HttpParser & HttpParser::setRequestTarget(const std::string &requestTarget) {
        this->requestTarget = requestTarget;
        return *this;
    }

    std::string HttpParser::getRequestTarget() const {
        return requestTarget;
    }

    HttpParser & HttpParser::setHttpVersion(const std::string &httpVersion) {
        this->httpVersion = httpVersion;
        return *this;
    }

    std::string HttpParser::getHttpVersion() const {
        return httpVersion;
    }

    HttpParser & HttpParser::setHeader(const std::string &header, const std::string &value) {
        httpHeaders[header] = value;
        return *this;
    }

    std::string HttpParser::getHeader(const std::string &header) {
        if (httpHeaders.count(header) == 0)
            return "";
        return httpHeaders[header];
    }

    HttpParser & HttpParser::setBody(const std::string &body) {
        this->body = body;
        return *this;
    }

    std::string HttpParser::getBody() const {
        return body;
    }

    HttpParser &HttpParser::setStatus(const std::string &status) {
        this->status = status;
        return *this;
    }

    std::string HttpParser::getStatus() const {
        return status;
    }

    HttpParser & HttpParser::setReasonPhrase(const std::string &reasonPhrase) {
        this->reasonPhrase = reasonPhrase;
        return *this;
    }

    std::string HttpParser::getReasonPhrase() const {
        return reasonPhrase;
    }

    bool HttpParser::isRequest() const {
        return true;
    }

    bool HttpParser::isResponse() const {
        return true;
    }

}

