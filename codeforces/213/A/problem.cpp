#include <cstdio>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

// we will use this class, it is able to do everything
// simple map<int, int> can do, and as we can see, much more!
typedef tree<int, int, less<int>, rb_tree_tag> Tree;
// another choice is to use splay_tree_tag for splay tree implementation

void print_tree(Tree::node_iterator it, Tree::node_iterator null, int indent = 0)
{
    if (it == null)
        return;
    // that's how we can access left child and right child
    // as I understand, there is no way to access parent node
    print_tree(it.get_l_child(), null, indent + 1);
    for (int i = 0; i < indent; i++)
        printf("    ");
    printf("(%d %d)\n", (**it).first, (**it).second);
    // of course this is equal to:
    // printf("(%d %d)\n", (*it)->first, (*it)->second);
    print_tree(it.get_r_child(), null, indent + 1);
}

int main()
{
    Tree X;
    // we can use X like usual map container
    for (int i = 0; i < 15; i++)
        X[i * i] = i ^ (i + 1);
    // we can iterate over it using iterators, begin() and end()
    for (Tree::iterator it = X.begin(); it != X.end(); it++)
        printf("%d %d\n", it->first, it->second);
    for (auto it = X.node_begin(); it != X.node_end(); it = it.get_l_child()) {
         printf("%d %d\n", (*it)->first, (*it)->second);
    }
    /* output:
     * 0 1
     * 1 3
     * 4 1
     * 9 7
     * 16 1
     * 25 3
     * 36 1
     * 49 15
     * 64 1
     * 81 3
     * 100 1
     * 121 7
     * 144 1
     * 169 3
     * 196 1
     */
    // but implementation gives us cool interface to access nodes of the tree!
    Tree::node_iterator root = X.node_begin();
    // for example we can print value at the root of the tree
    // root has type node_iterator
    // *root has type point_iterator == iterator (these two types are synonimic for trees)
    // **root has containing type (pair<int, int> in our case)
    printf("%d %d\n", (**root).first, (**root).second);
    // output: 9 7
    // let's traverse the tree using methods get_l_node() and get_r_node()
    print_tree(root, X.node_end()); // X.node_end() defines null (leaf terminator) for this tree
    /* output:
     *         (0 1)
     *     (1 3)
     *         (4 1)
     * (9 7)
     *            (16 1)
     *         (25 3)
     *             (36 1)
     *     (49 15)
     *             (64 1)
     *         (81 3)
     *                 (100 1)
     *             (121 7)
     *                     (144 1)
     *                 (169 3)
     *                     (196 1)
     */
    Tree Y;
    // Now we are going to split by the key 42
    // (42 and greater are moving to the right operand Y, other keys remain in X tree)
    X.split(42, Y);
    print_tree(X.node_begin(), X.node_end());
    /* output:
     *         (0 1)
     *     (1 3)
     *         (4 1)
     * (9 7)
     *         (16 1)
     *     (25 3)
     *         (36 1)
     */
    print_tree(X.node_begin(), X.node_end());
    /* output:
     *         (0 1)
     *     (1 3)
     *         (4 1)
     * (9 7)
     *         (16 1)
     *     (25 3)
     *         (36 1)
     */
    // notice that both parts are absolutely balanced!
    // we can merge them back
    X.join(Y);
    printf("%d\n", (int)X.size());
    // output: 15
    // we can find lower bound for a key in this tree
    Tree::iterator it = (X.lower_bound(42));
    // it returns a usual iterator, not a node_iterator
    // it's easy to understand that it is more formally correct: one can possibly
    // use this tree as usual map, and it will be a big surprise, that lower_bound
    // returns some strange node_iterator type instead of usual iterator
    printf("%d %d\n", it->first, it->second);
    // output: 49 15
    // but now some strange effect: we can simply cast node_iterator to iterator
    // with dereferensing (*node_iterator = iterator), but I didn't found
    // any other way to do the reverse cast (from iterator to node_iterator) except this:
    Tree::node_iterator n_it = it.m_p_nd;
    printf("%d %d\n", (*n_it)->first, (*n_it)->second);
    // output: 49 15
    // .m_p_nd field is left public, that is strange for c++-library style, but
    // I don't know other ways to convert iterator to node_iterator. Any ideas?

    return 0;
}

