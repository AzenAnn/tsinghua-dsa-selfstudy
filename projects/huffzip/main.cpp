// huffzip 的命令行界面（已经写好了）
//   huffzip c <输入文件> <输出文件>   压缩
//   huffzip d <输入文件> <输出文件>   解压
// 编译后在 build/debug/projects/huffzip/huffzip

#include <fstream>
#include <iostream>
#include <iterator>
#include <string>

#include "dsa/common.h"
#include "huffzip.h"

int main(int argc, char** argv) {
    if (argc != 4 || (std::string(argv[1]) != "c" && std::string(argv[1]) != "d")) {
        std::cerr << "用法：huffzip c|d <输入文件> <输出文件>\n";
        return 1;
    }
    std::ifstream in(argv[2], std::ios::binary);
    if (!in) {
        std::cerr << "打不开 " << argv[2] << "\n";
        return 1;
    }
    std::string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    try {
        std::string result = std::string(argv[1]) == "c" ? huffzip::compress(data) : huffzip::decompress(data);
        std::ofstream(argv[3], std::ios::binary) << result;
        std::cout << data.size() << " 字节 → " << result.size() << " 字节\n";
    } catch (const dsa::NotImplemented& e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
