#include <iostream>
#include <vector>
#include <algorithm>

// 定義m-way搜尋樹的節點結構
struct MWayNode {
    std::vector<int> keys; // 節點中的鍵值
    std::vector<MWayNode*> children; // 子節點
    bool isLeaf; // 是否為葉節點

    MWayNode(int m, bool leaf) : isLeaf(leaf) {
        keys.reserve(m - 1); // 預留空間給鍵值
        children.reserve(m); // 預留空間給子節點
    }
};

// 定義B-tree的節點結構
struct BTreeNode {
    std::vector<int> keys; // 節點中的鍵值
    std::vector<BTreeNode*> children; // 子節點
    bool isLeaf; // 是否為葉節點

    BTreeNode(int t, bool leaf) : isLeaf(leaf) {
        keys.reserve(2 * t - 1); // 預留空間給鍵值
        children.reserve(2 * t); // 預留空間給子節點
    }
};

// 插入和刪除功能的實現（簡化版）
void insertMWay(MWayNode* root, int key, int m) {
    if (root->isLeaf) {
        root->keys.push_back(key); // 插入鍵值
        std::sort(root->keys.begin(), root->keys.end()); // 排序鍵值
        if (root->keys.size() == m - 1) {
            // 分裂節點邏輯
        }
    }
    else {
        // 找到適當的子節點進行遞迴插入
    }
}

void deleteMWay(MWayNode* root, int key) {
    // 刪除邏輯
    auto it = std::find(root->keys.begin(), root->keys.end(), key);
    if (it != root->keys.end()) {
        // 如果在當前節點找到鍵值，則刪除
        root->keys.erase(it);
    }
    else if (!root->isLeaf) {
        // 如果不是葉節點，則遞迴刪除
        for (auto child : root->children) {
            deleteMWay(child, key);
        }
    }
}

void insertBTree(BTreeNode* root, int key, int t) {
    if (root->isLeaf) {
        root->keys.push_back(key); // 插入鍵值
        std::sort(root->keys.begin(), root->keys.end()); // 排序鍵值
        if (root->keys.size() == 2 * t - 1) {
            // 分裂節點邏輯
            // 這裡假設有一個分裂節點的函數 splitChild
            // splitChild(parent, index, t)
        }
    }
    else {
        // 找到適當的子節點進行遞迴插入
        int i = 0;
        while (i < root->keys.size() && key > root->keys[i]) {
            i++;
        }
        if (root->children[i]->keys.size() == 2 * t - 1) {
            // 如果子節點已滿，先分裂
            // 這裡假設有一個分裂節點的函數 splitChild
            // splitChild(root, i, t)
            if (key > root->keys[i]) {
                i++;
            }
        }
        insertBTree(root->children[i], key, t);
    }
}

// 分裂節點的輔助函數
void splitChild(BTreeNode* parent, int index, int t) {
    BTreeNode* child = parent->children[index];
    BTreeNode* newChild = new BTreeNode(t, child->isLeaf);
    parent->children.insert(parent->children.begin() + index + 1, newChild);
    parent->keys.insert(parent->keys.begin() + index, child->keys[t - 1]);

    newChild->keys.assign(child->keys.begin() + t, child->keys.end());
    child->keys.resize(t - 1);

    if (!child->isLeaf) {
        newChild->children.assign(child->children.begin() + t, child->children.end());
        child->children.resize(t);
    }
}

void deleteBTree(BTreeNode* root, int key) {
    // 刪除邏輯
    auto it = std::find(root->keys.begin(), root->keys.end(), key);
    if (it != root->keys.end()) {
        // 如果在當前節點找到鍵值，則刪除
        root->keys.erase(it);
    }
    else if (!root->isLeaf) {
        // 如果不是葉節點，則遞迴刪除
        for (auto child : root->children) {
            deleteBTree(child, key);
        }
    }
}

// 樹狀圖顯示功能
void printMWayTree(MWayNode* root, int level = 0) {
    if (root == nullptr) return;
    for (int i = 0; i < level; ++i) std::cout << "  "; // 縮排
    for (int key : root->keys) std::cout << key << " "; // 顯示鍵值
    std::cout << std::endl;
    for (MWayNode* child : root->children) printMWayTree(child, level + 1); // 遞迴顯示子節點
}

void printBTree(BTreeNode* root, int level = 0) {
    if (root == nullptr) return;
    for (int i = 0; i < level; ++i) std::cout << "  "; // 縮排
    for (int key : root->keys) std::cout << key << " "; // 顯示鍵值
    std::cout << std::endl;
    for (BTreeNode* child : root->children) printBTree(child, level + 1); // 遞迴顯示子節點
}

int main() {
    int m = 3; // m-way搜尋樹的m值
    int t = 2; // B-tree的t值

    MWayNode* mwayRoot = new MWayNode(m, true); // 建立m-way搜尋樹的根節點
    BTreeNode* btreeRoot = new BTreeNode(t, true); // 建立B-tree的根節點

    int choice, value;
    while (true) {
        // 顯示操作選單
        std::cout << "選擇操作: 1. 插入到m-way搜尋樹 2. 刪除從m-way搜尋樹 3. 插入到B-tree 4. 刪除從B-tree 5. 顯示樹狀圖 6. 退出\n";
        std::cin >> choice;
        switch (choice) {
        case 1:
            std::cout << "輸入要插入的值: ";
            std::cin >> value;
            insertMWay(mwayRoot, value, m); // 插入到m-way搜尋樹
            break;
        case 2:
            std::cout << "輸入要刪除的值: ";
            std::cin >> value;
            deleteMWay(mwayRoot, value); // 從m-way搜尋樹刪除
            break;
        case 3:
            std::cout << "輸入要插入的值: ";
            std::cin >> value;
            insertBTree(btreeRoot, value, t); // 插入到B-tree
            break;
        case 4:
            std::cout << "輸入要刪除的值: ";
            std::cin >> value;
            deleteBTree(btreeRoot, value); // 從B-tree刪除
            break;
        case 5:
            std::cout << "MWay Tree:" << std::endl;
            printMWayTree(mwayRoot); // 顯示m-way搜尋樹
            std::cout << "BTree:" << std::endl;
            printBTree(btreeRoot); // 顯示B-tree
            break;
        case 6:
            return 0; // 退出程式
        default:
            std::cout << "無效的選擇，請重新輸入。\n"; // 無效選擇提示
        }
    }

    return 0;
}
