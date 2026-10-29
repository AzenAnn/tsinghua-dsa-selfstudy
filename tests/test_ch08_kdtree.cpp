// 第8章 kd-树的测试（D25）

#include <algorithm>
#include <cmath>
#include <vector>

#include "dsa/kdtree.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

TEST("D25 KdTree：树高是 ⌊log2 n⌋") {
    for (int n : {0, 1, 2, 3, 7, 8, 100, 1000}) {
        std::vector<Point2> pts(n);
        for (auto& p : pts) p = {(int)randInt(0, 100), (int)randInt(0, 100)};
        KdTree t(pts);
        int expect = n == 0 ? -1 : (int)std::floor(std::log2(n));
        REQUIRE_EQ(t.height(), expect);
    }
}

TEST("D25 KdTree::rangeQuery：和暴力扫描对拍（含重复点、退化的矩形）") {
    for (int round = 0; round < 300; ++round) {
        int n = (int)randInt(0, 300), range = (int)randInt(1, 50);
        std::vector<Point2> pts(n);
        for (auto& p : pts) p = {(int)randInt(0, range), (int)randInt(0, range)};
        KdTree t(pts);
        for (int q = 0; q < 20; ++q) {
            int x1 = (int)randInt(-5, range + 5), x2 = (int)randInt(x1, range + 5);
            int y1 = (int)randInt(-5, range + 5), y2 = (int)randInt(y1, range + 5);
            if (q == 0) x2 = x1;  // 竖线
            std::vector<Point2> expect;
            for (auto& p : pts)
                if (x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2) expect.push_back(p);
            auto got = t.rangeQuery(x1, x2, y1, y2);
            std::sort(expect.begin(), expect.end());
            std::sort(got.begin(), got.end());
            REQUIRE(got == expect);
        }
    }
}
