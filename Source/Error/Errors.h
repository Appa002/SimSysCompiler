//
// Created by a_mod on 17.08.2019.
//

#pragma once

#include <AbstractSyntaxTree/ASTNode.h>
#include "ASTError.h"

namespace ACC::errors {

    struct MissingOverload : public ASTError {
        explicit MissingOverload(const ASTNode *node, std::string const &funcName) :
                ASTError("No fitting overload for function call to `" + funcName + "`") {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };

    };

    struct UnknownType : public ASTError {
        explicit UnknownType(const ASTNode *node, std::string const &typeName) :
                ASTError("Unknown type `" + typeName + "`") {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };

    };

    struct InvalidType : public ASTError {
        explicit InvalidType(const ASTNode *node, std::string const &typeName, std::string const &operationName) :
                ASTError("Invalid type `" + typeName + "` for operation " + operationName) {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };

        explicit InvalidType(const ASTNode *node, std::string const &msg) :
                ASTError(msg) {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };
    };

    struct TypeConversion : public ASTError {
        explicit TypeConversion(const ASTNode *node, std::string const &firstTypeName,
                                std::string const &secondTypeName) :
                ASTError("Can't convert type `" + firstTypeName + "` to type `" + secondTypeName + "`") {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };

        explicit TypeConversion(const ASTNode *node, std::string const &msg) :
                ASTError(msg) {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };
    };

    struct UnimplementedFunction : public ASTError {
        explicit UnimplementedFunction(const ASTNode *node, std::string const & type, std::string const &functionName) :
                ASTError("Type `"+type+"` doesn't implement function `"+functionName+"`.") {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };

    };

    struct Unique : public ASTError {
        explicit Unique(const ASTNode *node, std::string const &msg) :
                ASTError(msg) {
            if (node != nullptr) {
                lineNum = node->lineNum;
                lineContent = node->lineContent;
            }
        };
    };

}

