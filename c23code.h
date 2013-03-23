#ifndef C23CODE_H
#define C23CODE_H
#include <vector>
#include "abstractcode.h"


typedef std::pair<uint64_t,uint64_t> _C23Block;
typedef std::vector<_C23Block> _C23;

class C23Codec : public AbstractCode
{
public:
    C23Codec();
    ~C23Codec();
    virtual std::string encode(const uint64_t num);
    virtual uint64_t decode(const std::string &code);

private:
    const char Ki_SYMBOl;
    const char Di_SYMBOl;
    const std::string BLOCK_DELIMITER;
std::string CODE_DELIMITER;

protected:
    virtual uint64_t fki(uint64_t ki);

private:
    /**
     * @brief Coverts number to (2,3)-represenation. List of (n_i,k_i),
     *  where x_i = 2^(n_i) + 3^(k_i)*x_{i+1}
     * @param num
     * @return
     */
    _C23 convertToC23(const uint64_t num);
    /**
     * @brief getNextBlock
     * @param code
     * @param resultBlock - result block
     * @param isDelimiter - seted to true if next block is Delimiter.
     * @return Block true if next block can be decoded.
     */
    bool getNextBlock(const char* code,_C23Block &block, bool *isDelimiter);
};

#endif // C23CODE_H
