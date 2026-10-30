// huffzip 的测试（D39）

#include <string>

#include "dsa_test.h"
#include "huffzip.h"

using dsa_test::randInt;

TEST("D39 huffzip：空文件、单一字节、含 '\\0' 的数据，压缩再解压都要还原") {
    for (std::string s : {std::string(), std::string(1000, 'x'), std::string("a\0b\0\0c", 6), std::string(1, '\xff')}) {
        REQUIRE(huffzip::decompress(huffzip::compress(s)) == s);
    }
}

TEST("D39 huffzip：随机数据压缩再解压都要还原；分布不均匀时确实变小") {
    for (int round = 0; round < 200; ++round) {
        std::string s(randInt(0, 5000), '\0');
        int alphabet = (int)randInt(1, 256);
        for (auto& c : s) c = (char)randInt(0, randInt(0, alphabet - 1));  // 越小的字节越常见
        std::string packed = huffzip::compress(s);
        REQUIRE(huffzip::decompress(packed) == s);
    }
    std::string text;
    for (int i = 0; i < 20000; ++i) text += "aaaaaaab"[randInt(0, 7)];  // 只有两种字节，a 占 7/8
    CHECK(huffzip::compress(text).size() < text.size() / 4);
}
