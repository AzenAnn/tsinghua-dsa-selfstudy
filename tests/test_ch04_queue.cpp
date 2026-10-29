// 第4章 队列与试探回溯的测试（D10）

#include <cstdlib>
#include <queue>
#include <string>
#include <vector>

#include "dsa/queue.h"
#include "dsa/stack_apps.h"
#include "dsa_test.h"

using namespace dsa;
using dsa_test::randInt;

namespace {

// 参考：BFS 判断 s 能否到达 t
bool reachable(const std::vector<std::string>& g, std::pair<int, int> s, std::pair<int, int> t) {
    int R = (int)g.size(), C = (int)g[0].size();
    if (g[s.first][s.second] != '.' || g[t.first][t.second] != '.') return false;
    std::vector<std::vector<bool>> seen(R, std::vector<bool>(C));
    std::queue<std::pair<int, int>> q;
    q.push(s);
    seen[s.first][s.second] = true;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (r == t.first && c == t.second) return true;
        const int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
        for (int d = 0; d < 4; ++d) {
            int nr = r + dr[d], nc = c + dc[d];
            if (0 <= nr && nr < R && 0 <= nc && nc < C && g[nr][nc] == '.' && !seen[nr][nc]) {
                seen[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
    return false;
}

std::vector<int> bankRef(int nWin, const std::vector<int>& serv) {
    int n = (int)serv.size();
    std::vector<std::queue<int>> w(nWin);
    std::vector<int> rem = serv, fin(n);
    int done = 0;
    for (int t = 0; done < n; ++t) {
        if (t < n) {
            int best = 0;
            for (int i = 1; i < nWin; ++i)
                if (w[i].size() < w[best].size()) best = i;
            w[best].push(t);
        }
        for (int i = 0; i < nWin; ++i)
            if (!w[i].empty() && --rem[w[i].front()] == 0) {
                fin[w[i].front()] = t + 1;
                w[i].pop();
                ++done;
            }
    }
    return fin;
}

}  // namespace

TEST("D10 Queue：enqueue / dequeue / front 和 std::queue 对拍") {
    Queue<int> Q;
    std::queue<int> ref;
    for (int op = 0; op < 20000; ++op) {
        if (ref.empty() || randInt(0, 2)) {
            int e = (int)randInt(0, 1000);
            Q.enqueue(e);
            ref.push(e);
        } else {
            REQUIRE_EQ(Q.front(), ref.front());
            REQUIRE_EQ(Q.dequeue(), ref.front());
            ref.pop();
        }
        REQUIRE_EQ(Q.size(), (Rank)ref.size());
    }
}

TEST("D10 placeQueens：n 皇后解的个数（OEIS A000170）") {
    const long long expect[] = {0, 1, 0, 0, 2, 10, 4, 40, 92, 352, 724, 2680};
    for (int n = 1; n <= 11; ++n) REQUIRE_EQ(placeQueens(n), expect[n]);
}

TEST("D10 labyrinth：固定的迷宫") {
    std::vector<std::string> g = {
        ".#...",
        ".#.#.",
        "...#.",
        "##.#.",
        "....#",
    };
    auto path = labyrinth(g, {0, 0}, {0, 4});
    CHECK(!path.empty());
    CHECK(path.front() == std::make_pair(0, 0));
    CHECK(path.back() == std::make_pair(0, 4));
    CHECK(labyrinth(g, {0, 0}, {4, 4}).empty());  // (4,4) 是墙
    CHECK(labyrinth(g, {0, 0}, {0, 0}).size() == 1u);
}

TEST("D10 labyrinth：随机迷宫，路径合法，有路时一定能找到") {
    for (int round = 0; round < 500; ++round) {
        int R = (int)randInt(1, 12), C = (int)randInt(1, 12);
        std::vector<std::string> g(R, std::string(C, '.'));
        for (auto& row : g)
            for (auto& ch : row)
                if (randInt(0, 99) < 30) ch = '#';
        std::pair<int, int> s{(int)randInt(0, R - 1), (int)randInt(0, C - 1)};
        std::pair<int, int> t{(int)randInt(0, R - 1), (int)randInt(0, C - 1)};
        auto path = labyrinth(g, s, t);
        bool can = reachable(g, s, t);
        REQUIRE_EQ(!path.empty(), can);
        if (!can) continue;
        REQUIRE(path.front() == s);
        REQUIRE(path.back() == t);
        for (std::size_t i = 0; i < path.size(); ++i) {
            auto [r, c] = path[i];
            REQUIRE(0 <= r && r < R && 0 <= c && c < C && g[r][c] == '.');
            if (i) REQUIRE(std::abs(r - path[i - 1].first) + std::abs(c - path[i - 1].second) == 1);
        }
    }
}

TEST("D10 bankSimulate：手算的例子") {
    CHECK_EQ(bankSimulate(2, {3, 1, 2}), (std::vector<int>{3, 2, 4}));
    CHECK_EQ(bankSimulate(1, {2, 2}), (std::vector<int>{2, 4}));
    CHECK_EQ(bankSimulate(3, {}), (std::vector<int>{}));
}

TEST("D10 bankSimulate：随机数据和参考模拟对拍") {
    for (int round = 0; round < 500; ++round) {
        int nWin = (int)randInt(1, 6);
        std::vector<int> serv(randInt(0, 80));
        for (auto& x : serv) x = (int)randInt(1, 10);
        REQUIRE_EQ(bankSimulate(nWin, serv), bankRef(nWin, serv));
    }
}
