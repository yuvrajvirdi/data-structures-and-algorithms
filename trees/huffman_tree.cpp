#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std; 

struct Node {
    char c;             // character
    int freq;           // frequency of character 
    Node *left, *right; // left and right child
    Node(char data, int freq) : 
    c(c), freq(freq), left(nullptr), right(nullptr) {}
};

Node* huffman_tree(const string &sequence) {
    unordered_map<char, int> freq;
    for (char c : sequence) 
        freq[c]++;

    auto compare = [](Node* l, Node* r) { return l->freq > r->freq; };
    priority_queue<Node*, vector<Node*>, decltype(compare)> min_heap(compare);

    for (auto pair : freq) 
        min_heap.push(new Node(pair.first, pair.second));

    while (min_heap.size() > 1) {
        Node* left = min_heap.top();
        min_heap.pop();
        Node *right = min_heap.top();
        min_heap.pop();
        Node *top = new Node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        min_heap.push(top);
    }

    return min_heap.top();
}

void print_huffman_codes(Node* root, const string &cur) {
    if (!root) return;
    else if (root->c != '$') {
        cout << root->c << ": " << cur << "\n";
        return;
    }
    else {
        print_huffman_codes(root->left, cur + "0");
        print_huffman_codes(root->right, cur + "1");
    }
}

int main() {
    string sequence = "BABABBAACADBABAB";
    Node* root = huffman_tree(sequence);
    print_huffman_codes(root, "");
    return 1;
}