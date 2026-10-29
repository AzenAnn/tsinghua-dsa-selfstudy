// minikv 的测试（D38）：随机命令和 std::map 对拍

#include <map>
#include <string>

#include "dsa_test.h"
#include "kvstore.h"

using dsa_test::randInt;

namespace {
std::string randKey() {
    std::string s(randInt(1, 3), 'a');
    for (auto& c : s) c = (char)randInt('a', 'f');
    return s;
}
}  // namespace

TEST("D38 minikv：put / get / del / range 和 std::map 对拍") {
    for (int round = 0; round < 30; ++round) {
        minikv::KVStore db((dsa::Rank)randInt(3, 8));
        std::map<std::string, std::string> ref;
        for (int op = 0; op < 3000; ++op) {
            std::string k = randKey();
            int kind = (int)randInt(0, 3);
            if (kind == 0) {
                std::string v = std::to_string(randInt(0, 999));
                db.put(k, v);
                ref[k] = v;
            } else if (kind == 1) {
                std::string v;
                bool ok = db.get(k, v);
                REQUIRE_EQ(ok, ref.count(k) == 1);
                if (ok) REQUIRE_EQ(v, ref[k]);
            } else if (kind == 2) {
                REQUIRE_EQ(db.del(k), ref.erase(k) == 1);
            } else {
                std::string lo = randKey(), hi = randKey();
                if (hi < lo) std::swap(lo, hi);
                std::vector<std::pair<std::string, std::string>> expect;
                for (auto it = ref.lower_bound(lo); it != ref.end() && it->first < hi; ++it) expect.push_back(*it);
                REQUIRE(db.range(lo, hi) == expect);
            }
            REQUIRE_EQ((std::size_t)db.size(), ref.size());
        }
    }
}
