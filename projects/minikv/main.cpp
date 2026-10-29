// minikv 的命令行界面（已经写好了）：从标准输入逐行读命令
//   put <key> <value>   get <key>   del <key>   range <lo> <hi>   size   quit
// 编译：tools/test.sh 会顺带编出 build/debug/projects/minikv/minikv；
// 运行：build/debug/projects/minikv/minikv，然后输入命令；也可以 minikv < 命令文件

#include <iostream>
#include <sstream>
#include <string>

#include "dsa/common.h"
#include "kvstore.h"

int main() try {
    minikv::KVStore db;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream in(line);
        std::string cmd, a, b;
        in >> cmd >> a >> b;
        try {
            if (cmd == "put" && !a.empty()) {
                db.put(a, b);
                std::cout << "OK\n";
            } else if (cmd == "get" && !a.empty()) {
                std::string v;
                std::cout << (db.get(a, v) ? v : "(nil)") << "\n";
            } else if (cmd == "del" && !a.empty()) {
                std::cout << (db.del(a) ? "1" : "0") << "\n";
            } else if (cmd == "range" && !a.empty() && !b.empty()) {
                for (auto& [k, v] : db.range(a, b)) std::cout << k << " " << v << "\n";
                std::cout << "END\n";
            } else if (cmd == "size") {
                std::cout << db.size() << "\n";
            } else if (cmd == "quit") {
                break;
            } else if (!cmd.empty()) {
                std::cout << "ERR 不认识的命令\n";
            }
        } catch (const dsa::NotImplemented& e) {
            std::cout << "ERR " << e.what() << "\n";
        }
    }
} catch (const dsa::NotImplemented& e) {
    std::cout << "ERR " << e.what() << "（先完成 B-树和 kvstore.h）\n";
    return 1;
}
