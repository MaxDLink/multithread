#ifndef CUSTOMERRORLISTENER_H
#define CUSTOMERRORLISTENER_H

#include "antlr4-runtime.h"
#include "./lib/json.hpp"

using json = nlohmann::json;

class CustomErrorListener : public antlr4::BaseErrorListener {
private:
    json errorDetails;

public:
    void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                     size_t line, size_t charPositionInLine, const std::string &msg,
                     std::exception_ptr e) override;

    void writeErrorsToFile(const std::string &filename);

     std::vector<json> getErrors() const {
        if(!errorDetails.empty()){
          return errorDetails;
        }
        else{
            //TODO - logic to handle case with no errors 
            // Create a JSON object with a "no errors" message
            json noError = {
                {"type", "No Error"},
                {"message", "No lexical or syntax errors found in flowscript file."}
            };

            // Return a vector containing this single JSON object
            return std::vector<json>{noError};

        }
    }
};

#endif // CUSTOMERRORLISTENER_H
