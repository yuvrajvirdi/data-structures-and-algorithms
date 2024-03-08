#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

class HuffmanTree {
private:
    struct Node {
        char c;             // character
        int freq;           // frequency of character
        Node *left, *right; // left and right child
        Node(char c, int freq) : c(c), freq(freq), left(nullptr), right(nullptr) {}
    };

    Node* root;
    string sequence;  

    // builds huffman trees
    void build_tree() {
        if (sequence.empty()) return;

        // store frequencies in map
        unordered_map<char, int> freq;
        for (char c : sequence)
            freq[c]++;

        // create min heap
        auto compare = [](Node* l, Node* r) { return l->freq > r->freq; };
        priority_queue<Node*, vector<Node*>, decltype(compare)> minHeap(compare);

        // add nodes of characters and frequencies to heap
        for (auto pair : freq)
            minHeap.push(new Node(pair.first, pair.second));

        while (minHeap.size() > 1) {
            // find minimum element in heap
            Node* left = minHeap.top();
            minHeap.pop();
            // find next min elem
            Node* right = minHeap.top();
            minHeap.pop();
            // make new parent node whose children are left and right
            Node* parent = new Node('$', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            // add new parent to heap
            minHeap.push(parent);
        }

        root = minHeap.top();
    }

    // prints all huffman codes
    void print_huffman_codes(Node* node, const string &cur) {
        if (!node) return;
        if (node->c != '$')
            cout << node->c << " has a code of " << cur << "\n";
        else {
            // left paths append 0
            print_huffman_codes(node->left, cur + "0");
            // right paths append 1
            print_huffman_codes(node->right, cur + "1");
        }
    }

    // deconstructor method
    void free_tree(Node* node) {
        if (!node) return;
        else {
            free_tree(node->left);
            free_tree(node->right);
            delete node;
        }
    }

public:
    HuffmanTree(const string &sequence) : sequence(sequence) {
        build_tree();
    }

    ~HuffmanTree() {
        free_tree(root);
    }

    void print_all_codes() {
        print_huffman_codes(root, "");
    }
};

int main() {
    string sequence = "BABABBAACADBABAB";
    HuffmanTree huffman_tree(sequence);
    huffman_tree.print_all_codes();
    return 0;
}
