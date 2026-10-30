#pragma once
// 第8章 kd-树（教材 §8.4）—— 第 25 天
//
// 这里只有声明；实现写在 src/kdtree.cpp 里，那边现在都是 DSA_TODO();。
// 这里的 2d-树把点存在每个节点上（书上把点存在叶子上，内部节点只存划分线，两种做法都可以）：
// 按深度交替用 x、y 坐标的中位数划分，每个节点记录它子树所有点的包围盒，查询时用来剪枝。
// 下面私有部分的设计可以按自己的想法改。

#include <vector>

#include "dsa/common.h"

namespace dsa {

struct Point2 {
    int x = 0, y = 0;
    bool operator==(const Point2& o) const { return x == o.x && y == o.y; }
    bool operator<(const Point2& o) const { return x < o.x || (x == o.x && y < o.y); }
};

class KdTree {
public:
    explicit KdTree(std::vector<Point2> pts);  // 构造平衡的 2d-树（点可以重复）
    ~KdTree();
    KdTree(const KdTree&) = delete;
    KdTree& operator=(const KdTree&) = delete;

    // 落在闭矩形 [x1, x2] × [y1, y2] 内的所有点（顺序任意，重复的点都要报告）
    std::vector<Point2> rangeQuery(int x1, int x2, int y1, int y2) const;
    int height() const;  // 树高（空树为 -1）；中位数划分时应为 ⌊log2 n⌋

private:
    struct Node {
        Point2 p;
        bool splitX = true;                   // 这一层按 x 还是按 y 划分
        int minX = 0, maxX = 0, minY = 0, maxY = 0;  // 子树所有点的包围盒
        Node* lc = nullptr;
        Node* rc = nullptr;
    };
    Node* root_ = nullptr;
};

}  // namespace dsa
