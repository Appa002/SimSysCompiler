#pragma once

#include <string>

namespace ACC{
    struct LineCountingPosition{
    private:
        size_t internal;
        std::string& document;

    public:
        size_t lineNum = 1;

        LineCountingPosition() = delete;
        explicit LineCountingPosition(std::string & document) : document(document), internal(0) {}

        operator size_t (){ return internal; };

        void doLineCheck(){
            if(document[internal] == '\n' ||document[internal] == '\r'){
                lineNum++;
            }
        }

        const LineCountingPosition operator++ (int){
            LineCountingPosition const copy = *this;
            internal++;
            doLineCheck();
            return copy;
        }
        const LineCountingPosition operator-- (int){
            LineCountingPosition const copy = *this;
            internal--;
            doLineCheck();
            return copy;
        }

        LineCountingPosition &operator++(){
            ++internal;
            doLineCheck();
            return *this;
        }

        LineCountingPosition &operator--(){
            ++internal;
            doLineCheck();
            return *this;
        }

    };
}