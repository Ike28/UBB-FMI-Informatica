#include <vector>
#include <iostream>

static constexpr float EPSILON = 10e-3f;

bool equalFloats(float f1, float f2)
{
    return std::abs(f1 - f2) < EPSILON;
}

struct Tree {
    float value;
    std::vector<Tree> children;
};

float countTreeRecursive(const Tree& t, bool countOnlyEvenLevels, bool currentIsEven = true)
{
    float treeSum = 0.0f;
    if (countOnlyEvenLevels && currentIsEven)
        treeSum = t.value;

    if (t.children.size() == 0)
        return treeSum;

    float curr;
    for (int i = 0; i < t.children.size(); i++)
    {
        curr = countTreeRecursive(t.children[i], countOnlyEvenLevels, !currentIsEven);
        treeSum += curr;
    }

    return treeSum;
}

float countTree(const Tree& t, bool countOnlyEvenLevels)
{
    float result = countTreeRecursive(t, countOnlyEvenLevels);
    return result;
}

void fillTree(Tree& tree, int level)
{
    tree.value = 2.0f * static_cast<float>(level);
    if (level >= 4)
        return;

    Tree child;
    fillTree(child, level + 1);

    for (int i = 0; i < level + 2; ++i) {
        tree.children.push_back(child);
    }
}

int main()
{
    Tree root;
    fillTree(root, 0);
    float visitAnswer1 = countTree(root, false);
    float visitAnswer2 = countTree(root, true);

    if (equalFloats(visitAnswer1, 1132.0f) && equalFloats(visitAnswer2, 984.0f))
    {
        std::cout << "Exercise 2: Correct for this specific test case" << std::endl;
    }
    else {
        std::cout << "Exercise 2: Incorrect for this specific test case" << std::endl;
    }
}
