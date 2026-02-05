// Nombre del alumno: DANIEL ROLDAN SERRANO
// Usuario del Juez: DG26

#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <queue>
#include <stack>
#include <utility>

using namespace std;

template <class T> class BinTree {

private:
    struct TreeNode;
    using NodePointer = std::shared_ptr<TreeNode>;

public:
    BinTree() : root_node(nullptr) {}

    BinTree(const T& elem)
        : root_node(std::make_shared<TreeNode>(nullptr, elem, nullptr)) {}

    BinTree(const BinTree& left, const T& elem, const BinTree& right)
        : root_node(std::make_shared<TreeNode>(left.root_node, elem,
            right.root_node)) {}

    bool empty() const { return root_node == nullptr; }

    const T& root() const {
        assert(root_node != nullptr);
        return root_node->elem;
    }

    BinTree left() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->left;
        return result;
    }

    BinTree right() const {
        assert(root_node != nullptr);
        BinTree result;
        result.root_node = root_node->right;
        return result;
    }

    void display(std::ostream& out) const { display_node(root_node, out); }

    template <typename U> void preorder(U func) const {
        preorder(root_node, func);
    }

    template <typename U> void inorder(U func) const { inorder(root_node, func); }

    template <typename U> void postorder(U func) const {
        postorder(root_node, func);
    }

    template <typename U> void levelorder(U func) const;

private:
    struct TreeNode {
        TreeNode(const NodePointer& left, const T& elem, const NodePointer& right)
            : elem(elem), left(left), right(right) {}

        T elem;
        NodePointer left, right;
    };

    NodePointer root_node;

    static void display_node(const NodePointer& root, std::ostream& out) {
        if (root == nullptr) {
            out << ".";
        }
        else {
            out << "(";
            display_node(root->left, out);
            out << " " << root->elem << " ";
            display_node(root->right, out);
            out << ")";
        }
    }

    template <typename U> static void preorder(const NodePointer& node, U func);

    template <typename U> static void inorder(const NodePointer& node, U func);

    template <typename U> static void postorder(const NodePointer& node, U func);
};

template <typename T>
template <typename U>
void BinTree<T>::preorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        func(node->elem);
        preorder(node->left, func);
        preorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::inorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        inorder(node->left, func);
        func(node->elem);
        inorder(node->right, func);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::postorder(const NodePointer& node, U func) {
    if (node != nullptr) {
        postorder(node->left, func);
        postorder(node->right, func);
        func(node->elem);
    }
}

template <typename T>
template <typename U>
void BinTree<T>::levelorder(U func) const {
    std::queue<NodePointer> pending;
    if (root_node != nullptr) {
        pending.push(root_node);
    }
    while (!pending.empty()) {
        NodePointer current = pending.front();
        pending.pop();
        func(current->elem);
        if (current->left != nullptr) {
            pending.push(current->left);
        }
        if (current->right != nullptr) {
            pending.push(current->right);
        }
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const BinTree<T>& tree) {
    tree.display(out);
    return out;
}

template <typename T> BinTree<T> read_tree(std::istream& in) {
    char c;
    in >> c;
    if (c == '.') {
        return BinTree<T>();
    }
    else {
        assert(c == '(');
        BinTree<T> left = read_tree<T>(in);
        T elem;
        in >> elem;
        BinTree<T> right = read_tree<T>(in);
        in >> c;
        assert(c == ')');
        BinTree<T> result(left, elem, right);
        return result;
    }
}

template <typename T> struct tSol{
    bool sol;
    T max;
    T min;
    int altura;
};

template <typename T>
tSol<T> resolver(const BinTree<T>& tree) {
    if (tree.empty()) {
        return { true, T(), T(), 0 };
    }
    else {
        tSol<T> sol_izq = resolver(tree.left());
        tSol<T> sol_dcha = resolver(tree.right());
        tSol<T> sol; sol.sol = true;
        sol.altura = max(sol_izq.altura, sol_dcha.altura) + 1;
        if (abs(sol_izq.altura - sol_dcha.altura) > 1) sol.sol = false;
        if (tree.left().empty() && !tree.right().empty()) {
            sol.min = min(tree.root(), sol_dcha.min);
            sol.max = max(tree.root(), sol_dcha.max);
            if(sol_dcha.min <= tree.root()) sol.sol = false;
        }
        else if (!tree.left().empty() && tree.right().empty()) {
            sol.min = min(tree.root(), sol_izq.min);
            sol.max = max(tree.root(), sol_izq.max);
            if (sol_izq.max >= tree.root()) sol.sol = false;
        }
        else if (tree.left().empty() && tree.right().empty()) {
            sol.min = tree.root();
            sol.max = tree.root();
        }
        else {
            sol.min = min(tree.root(), min(sol_izq.min, sol_dcha.min));
            sol.max = max(tree.root(), max(sol_izq.max, sol_dcha.max));
            if (sol_izq.max >= tree.root()) sol.sol = false;
            if (sol_dcha.min <= tree.root()) sol.sol = false;
        }
        sol.sol = sol.sol && sol_izq.sol && sol_dcha.sol;
        return sol;
    }
}

bool resuelveCaso() {
    char c; cin >> c;

    if (!std::cin)
        return false;

    if (c == 'N') {
        BinTree<int> tree = read_tree<int>(cin);
        tSol<int> soluc = resolver(tree);
        if (soluc.sol) cout << "SI\n";
        else cout << "NO\n";
    }

    else if (c == 'P') {
        BinTree<string> tree = read_tree<string>(cin);
        tSol<string> soluc = resolver(tree);
        if (soluc.sol) cout << "SI\n";
        else cout << "NO\n";
    }

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}