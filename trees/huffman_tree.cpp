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

int main() {
    string sequence = "BABABBAACADBABAB";
    Node* root = huffman_tree(sequence);
    return 1;
}