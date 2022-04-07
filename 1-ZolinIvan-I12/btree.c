#include "btree.h"

BTreeNode* _nodeAllocate(const int T) {
    BTreeNode* res = (BTreeNode*)malloc(sizeof(BTreeNode));
    if (!res)
        return NULL;
    res->keys = (int*)malloc((2 * T - 1) * sizeof(int));// allocate space for the array of keys
    if (!res->keys) {
        free(res);
        return NULL;
    }
    res->children = (BTreeNode**)malloc(2 * T * sizeof(BTreeNode*));// allocate space for the array of keys
    if (!res->children) {
        free(res);
        free(res->keys);
        return NULL;
    }
    for (int i = 0; i < 2 * T; ++i)
        res->children[i] = NULL;
    res->numKeys = 0;// set n of keys to 0
    res->isLeaf = false;
    return res;
}

void _nodeDestroy(BTreeNode* node) {
    free(node->children);
    free(node->keys);
    free(node);
}

int _findKeyInArr(const int* arr, const int size, const int key) {
    for (int i = 0; i < size; ++i)
        if (arr[i] == key)
            return i;
    return ERROR;
}

bool btCreate(BTree* tree) {
    BTreeNode* root = _nodeAllocate(tree->T);
    if (!root)
        return false;
    root->numKeys = 0;
    root->isLeaf = true;
    tree->root = root;
    return true;
}

bool btSearch(const BTree* tree, const int key) {
    int index = ERROR;
    BTreeNode* found = _findNodeContainsKey(tree, key, &index);
    return found;
}

bool btInsert(BTree* tree, const int key) {
    if (btSearch(tree, key))
        return false;

    BTreeNode* oldRoot = tree->root;
    // if the root is full -> need node split
    if (oldRoot->numKeys == 2 * tree->T - 1) {
        BTreeNode* newRoot = _nodeAllocate(tree->T); // create a new root node
        if (!newRoot)
            return false;
        tree->root = newRoot;// make it the new root 
        newRoot->isLeaf = false;
        newRoot->numKeys = 0;
        newRoot->children[0] = oldRoot;
        if (!_splitChild(newRoot, tree->T, 0)) {//if it failed to split -> delete the node
            _nodeDestroy(newRoot);
            return false;
        }
        return _insertNonfull(newRoot, key, tree->T);// now insert the new element
    }
    // simple nonfull insert
    return _insertNonfull(oldRoot, key, tree->T);
}

bool _insertNonfull(BTreeNode* node, const int key, const int t) {
    // node should not be full
    assert(node->numKeys < 2 * t - 1);

    int i = node->numKeys - 1;
    if (node->isLeaf) {// if in a leaf insert the new element
        // shifting bigger-than-key part to the right 
        while (i >= 0 && key < node->keys[i]) {// find the correct position
            node->keys[i + 1] = node->keys[i];
            --i;
        }
        // and inserting key
        node->keys[i + 1] = key;
        ++node->numKeys;
        return true;
    }
    else {// otherwise, descend to the appropriate child
        // looking for the appropriate child
        while (i >= 0 && key < node->keys[i]) {// get the correct child of the node
            --i;
        }
        ++i;
        // if appropriate child is full we need to split it
        if (node->children[i]->numKeys == 2 * t - 1) {
            if (!_splitChild(node, t, i))
                return false;
            if (key > node->keys[i])
                ++i;
        }
        // now insert in the appropriate child
        return _insertNonfull(node->children[i], key, t);
    }
}

bool _splitChild(BTreeNode* node, const int T, const int i) {
    assert(node->children[i]->numKeys == 2 * T - 1);

    BTreeNode* newNode = _nodeAllocate(T);
    if (!newNode)
        return false;

    BTreeNode* child = node->children[i];
    newNode->isLeaf = child->isLeaf; // they will be the same status
    newNode->numKeys = T - 1;
    for (int j = 0; j < T - 1; ++j)
        newNode->keys[j] = child->keys[j + T];

    if (!child->isLeaf) // need to copy childrens only if not leaf
        for (int j = 0; j < T; ++j)
            newNode->children[j] = child->children[j + T];
    child->numKeys = T - 1;
    // now newNode and child are prepared to be attached to the node
    for (int j = node->numKeys + 1; j > i + 1; --j)
        node->children[j] = node->children[j - 1];
    node->children[i + 1] = newNode;
    for (int j = node->numKeys; j > i; --j)
        node->keys[j] = node->keys[j - 1];
    node->keys[i] = child->keys[T - 1];
    ++node->numKeys;
    node->isLeaf = false;
    return true;
}

BTreeNode* _findNodeContainsKey(const BTree* tree, const int key, int* index) {
    BTreeNode* iter = tree->root;
    while (!iter->isLeaf) {
        *index = _findKeyInArr(iter->keys, iter->numKeys, key);
        if (*index != ERROR)
            return iter;
        // if greater than every child
        // proceed to the last child
        if (key >= iter->keys[iter->numKeys - 1]) {
            iter = iter->children[iter->numKeys];
            continue;
        }
        // or we find next node manually
        for (int i = 0; i < iter->numKeys; ++i)
            if (key < iter->keys[i]) {
                iter = iter->children[i];
                break;
            }
    }
    // here we have iter as a leaf so key is here or nowhere
    *index = _findKeyInArr(iter->keys, iter->numKeys, key);
    return *index != ERROR ? iter : NULL;
}

int _getPredecessor(BTreeNode* node, const int index) {
    node = node->children[index];
    while (!node->isLeaf)
        node = node->children[node->numKeys];
    return node->keys[node->numKeys - 1];
}

int _getSuccessor(BTreeNode* node, const int index) {
    node = node->children[index + 1];
    while (!node->isLeaf)
        node = node->children[0];
    return node->keys[0];
}

void _removeFromArrI(int* arr, const int size, const int index) {
    for (int i = index; i + 1 < size; ++i)
        arr[i] = arr[i + 1];
}

void _removeFromArrNP(BTreeNode** arr, const int size, const int idx) {
    for (int i = idx; i + 1 < size; ++i)
        arr[i] = arr[i + 1];
}

void _leftRotate(BTreeNode* node, const int keyIdx) {
    BTreeNode* left = node->children[keyIdx];
    BTreeNode* right = node->children[keyIdx + 1];
    ++left->numKeys;
    left->keys[left->numKeys - 1] = node->keys[keyIdx];
    left->children[left->numKeys] = right->children[0];
    node->keys[keyIdx] = right->keys[0];
    for (int i = 0; i + 1 < right->numKeys; ++i)
        right->keys[i] = right->keys[i + 1];
    for (int i = 0; i + 1 < right->numKeys + 1; ++i)
        right->children[i] = right->children[i + 1];
    --right->numKeys;
}

void _rightRotate(BTreeNode* node, const int keyIdx) {
    BTreeNode* lNeighbour = node->children[keyIdx];
    BTreeNode* rNeighbour = node->children[keyIdx + 1];
    ++rNeighbour->numKeys;
    for (int i = rNeighbour->numKeys - 1; i - 1 >= 0; --i)
        rNeighbour->keys[i] = rNeighbour->keys[i - 1];
    rNeighbour->keys[0] = node->keys[keyIdx];
    for (int i = rNeighbour->numKeys; i - 1 >= 0; --i)
        rNeighbour->children[i] = rNeighbour->children[i - 1];
    rNeighbour->children[0] = lNeighbour->children[lNeighbour->numKeys];
    node->keys[keyIdx] = lNeighbour->keys[lNeighbour->numKeys - 1];
    --lNeighbour->numKeys;
}

void _mergeChild(BTreeNode* node, const int keyIndex) {
    BTreeNode* left_child = node->children[keyIndex];
    BTreeNode* right_child = node->children[keyIndex + 1];
    //collecting new node (lchild merged with node[keyIdx] + rChild)
    left_child->keys[left_child->numKeys] = node->keys[keyIndex];
    for (int i = 0; i < right_child->numKeys; ++i)
        left_child->keys[left_child->numKeys + 1 + i] = right_child->keys[i];
    for (int i = 0; i < right_child->numKeys + 1; ++i)
        left_child->children[left_child->numKeys + 1 + i] = right_child->children[i];
    left_child->numKeys += 1 + right_child->numKeys;
    _removeFromArrI(node->keys, node->numKeys, keyIndex);
    _removeFromArrNP(node->children, node->numKeys + 1, keyIndex + 1);
    --node->numKeys;
    _nodeDestroy(right_child);
}

void _removeFromLeaf(BTreeNode* node, const int T, const int key) {
    // find appropriate child
    int i = node->numKeys - 1;
    while (i >= 0 && key < node->keys[i]) {
        --i;
    }
    ++i;
    BTreeNode* child = node->children[i];
    int idx = _findKeyInArr(child->keys, child->numKeys, key);
    if (idx != ERROR) {
        assert(child->isLeaf);
        _removeFromArrI(child->keys, child->numKeys, idx);
        --child->numKeys;
    }
    else {
        if (child->isLeaf)
            return;
        _removeFromLeaf(child, T, key);
    }
    // fixing antioverflows from bottom to top
    // with the recursion reverse stroke
    if (child->numKeys < T - 1) {
        // we have antioverflow
        if (i < node->numKeys) {
            // we have right neighbour of child
            BTreeNode* rNeighbour = node->children[i + 1];
            if (child->numKeys + rNeighbour->numKeys + 1 <= 2 * T - 1) {
                // we can merge them which is priority case because
                // one Node will be destroyed after this operation
                _mergeChild(node, i);
            }
            else
                // we can rotate to the left to remanage values in Nodes
                _leftRotate(node, i);
        }
        else {
            // only left neighbour of child 
            BTreeNode* lNeighbour = node->children[i - 1];
            if (child->numKeys + lNeighbour->numKeys + 1 <= 2 * T - 1) {
                // we can merge them which is priority case because
                // one Node will be destroyed after this operation
                _mergeChild(node, i - 1);
            }
            else
                // we can rotate to the right to remanage values in Nodes
                _rightRotate(node, i - 1);
        }
    }
}

void _remove(BTreeNode* node, BTreeNode* nodeContainsKey, const int index, const int T, const int key) {
    if (!nodeContainsKey)
        // do nothing if no such key
        return;
    if (nodeContainsKey->isLeaf)
        // _RemoveFromLeaf is fine
        _removeFromLeaf(node, T, key);
    else {
        if (nodeContainsKey->children[index]->numKeys >= T) {
            int pred = _getPredecessor(nodeContainsKey, index);
            _removeFromLeaf(node, T, pred);
            nodeContainsKey->keys[index] = pred;
        }
        else if (nodeContainsKey->children[index + 1]->numKeys >= T) {
            int succ = _getSuccessor(nodeContainsKey, index);
            _removeFromLeaf(node, T, succ);
            nodeContainsKey->keys[index] = succ;
        }
        else {
            _mergeChild(nodeContainsKey, index);
            _remove(node, nodeContainsKey->children[index], (2 * T - 1) / 2, T, key);
        }
    }
}

void btDelete(BTree* tree, const int key) {
    if (tree->root->isLeaf) {
        int index = _findKeyInArr(tree->root->keys, tree->root->numKeys, key);
        if (index != ERROR) {
            _removeFromArrI(tree->root->keys, tree->root->numKeys, index);
            --tree->root->numKeys;
            // do nothing if root->numKeys is 0 as its the whole tree
            // if btDestroy here user will need to re-init tree
            // which is anomaly
        }
        // do nothing if no such key
    }
    else {
        int index = ERROR;
        BTreeNode* neededNode = _findNodeContainsKey(tree, key, &index);
        _remove(tree->root, neededNode, index, tree->T, key);
        if (tree->root->numKeys == 0) {
            // after recursion reverse stroke root could become empty
            BTreeNode* root = tree->root;
            tree->root = tree->root->children[0];
            _nodeDestroy(root);
        }
    }
}

void _destroy(BTreeNode* node, const int t) {
    if (!node->isLeaf)
        for (int i = 0; i < node->numKeys + 1; ++i)
            _destroy(node->children[i], t);
    _nodeDestroy(node);
}

void btDestroy(BTree* tree) {
    _destroy(tree->root, tree->T);
    tree->root = NULL;
}
