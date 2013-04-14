#ifndef ROBUSTNESSCHECKER_H
#define ROBUSTNESSCHECKER_H

#include <abstractcode.h>

typedef struct RobustCheckingResult
{
    double errorDetected;
    double errorFixed;
    double per_success;
} RobustCheckingResult;

class RobustnessChecker
{
public:
    RobustnessChecker(int n, ...);
    ~RobustnessChecker();
    int check(int64_t num, int codec_num);
    RobustCheckingResult*  check(int64_t from, int64_t to, int64_t times);
private:
    AbstractCodec** codecs;
    int ncodecs;
private:
    int invertOneBit(std::string &str);
};

#endif // ROBUSTNESSCHECKER_H
