#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

struct Node {
    int symbol;  // Index/symbol number
    int freq;
    Node *left, *right;
    
    Node(int s, int f) : symbol(s), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;  // Min heap
    }
};

class HuffmanCoding {
private:
    vector<string> huffmanCodes;
    Node* root;

    void generateCodes(Node* root, string str) {
        if (!root) return;
        
        // Found a leaf node
        if (!root->left && !root->right) {
            huffmanCodes[root->symbol] = str;
        }
        
        generateCodes(root->left, str + "0");
        generateCodes(root->right, str + "1");
    }

public:
    void buildHuffmanTree(const vector<int>& freq) {
        huffmanCodes.resize(freq.size());
        priority_queue<Node*, vector<Node*>, Compare> pq;
        
        // Create leaf nodes
        for (int i = 0; i < freq.size(); i++) {
            pq.push(new Node(i, freq[i]));
        }
        
        // Build Huffman Tree
        while (pq.size() > 1) {
            Node* left = pq.top(); pq.pop();
            Node* right = pq.top(); pq.pop();
            
            // Internal nodes use -1 as symbol
            Node* parent = new Node(-1, left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            
            pq.push(parent);
        }
        
        root = pq.top();
        generateCodes(root, "");
    }
    
    void printCodes() {
        for (int i = 0; i < huffmanCodes.size(); i++) {
            if(i == huffmanCodes.size()-1){
                cout << huffmanCodes[i];
            } else {
                cout << huffmanCodes[i] << ' ';
            }
        }
        cout << endl;
    }
};

int main() {
    int n;
    cin >> n;  // Number of symbols
    
    vector<int> freq(n);
    for (int i = 0; i < n; i++) {
        cin >> freq[i];  // Read frequencies
    }
    
    HuffmanCoding huffman;
    huffman.buildHuffmanTree(freq);
    cout << n << endl;
    huffman.printCodes();
    
    return 0;
}
