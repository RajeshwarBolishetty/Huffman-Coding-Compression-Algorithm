#include <iostream>
#include <vector>
#include <queue>

// A Huffman tree node
struct HuffmanNode {
    char character;
    int frequency;
    HuffmanNode *left, *right;

    HuffmanNode(char character, int frequency)
        : character(character), frequency(frequency), left(NULL), right(NULL) {}
};

// For comparison of two heap nodes (needed in priority queue)
struct CompareNode {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return (l->frequency > r->frequency);
    }
};

// Prints huffman codes from the root of Huffman Tree.
void printCodes(HuffmanNode* root, std::string str) {
    if (!root) return;

    if (root->character != '$')
        std::cout << root->character << ": " << str << std::endl;

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size) {
    HuffmanNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new HuffmanNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies. 
        // Make the two extracted node as left and right children of this new node. Add this node to the min heap
        top = new HuffmanNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}

// Driver program to test above functions
int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(arr) / sizeof(arr[0]);

    HuffmanCodes(arr, freq, size);

    return 0;
}
