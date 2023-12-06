#include "customerrorlistener.h"
#include <fstream>

void CustomErrorListener::syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol,
                                      size_t line, size_t charPositionInLine, const std::string &msg,
                                      std::exception_ptr e) {
    // Construct an error object and add it to the errorDetails array.
    json error = {
        {"line", line},
        {"charPositionInLine", charPositionInLine},
        {"offendingSymbol", offendingSymbol ? offendingSymbol->getText() : "null"},
        {"message", msg}
    };

    errorDetails.push_back(error);
}

void CustomErrorListener::writeErrorsToFile(const std::string &filename) {
    // Write the JSON array of errors to a file.
    std::ofstream file(filename);
    if (file.is_open()) {
        file << errorDetails.dump(4);  // Dump the JSON with an indentation of 4 spaces
        file.close();
    } else {
        std::cerr << "Unable to open file for writing JSON errors: " << filename << std::endl;
    }
}
