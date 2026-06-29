#include <iostream>
#include <vector>
#include <string>

// forward declaration 
template <typename Key, typename Val>
class UnorderedMap;

template <typename Key, typename Val>
struct Node {
    Key key;
    Val val;
    Node* next;
    Node(const Key& k, const Val& v) : key(k), val(v), next(nullptr) {}
};

// custom forward iterator
template <typename Key, typename Val>
class Iterator {
private:
    const UnorderedMap<Key, Val>* mapRef;
    size_t bucketIdx;
    Node<Key, Val>* nodePtr;
public:
    Iterator(const UnorderedMap<Key, Val>* map, size_t idx, Node<Key, Val>* node) : mapRef(map), bucketIdx(idx), nodePtr(node) {}

    std::pair<const Key, Val&> operator*() { return { nodePtr->key, nodePtr->val }; }

    // prefix increment (++it)
    Iterator& operator++() {
        if (nodePtr && nodePtr->next) {
            nodePtr = nodePtr->next;
        }
        else {
            nodePtr = nullptr;
            while (++bucketIdx < mapRef->tableSize) {
                if (mapRef->buckets[bucketIdx] != nullptr) {
                    nodePtr = mapRef->buckets[bucketIdx];
                    break;
                }
            }
        }
        return *this;
    }

    bool operator!=(const Iterator& other) const {
        return nodePtr != other.nodePtr;
    }
};

template <typename Key, typename Val>
class UnorderedMap {
private:
    vector<Node<Key, Val>*> buckets;
    size_t numElements;
    size_t tableSize;
    const float maxLoadFactor = 0.75f;

    // Grant Iterator access to private members
    friend class Iterator<Key, Val>;

    size_t getHash(const Key& key) const {
        return hash<Key>{}(key) % tableSize;
    }

    void rehash() {
        size_t oldSize = tableSize;
        tableSize *= 2;
        vector<Node<Key, Val>*> newBuckets(tableSize, nullptr);

        for (size_t i = 0; i < oldSize; ++i) {
            Node<Key, Val>* current = buckets[i];
            while (current != nullptr) {
                Node<Key, Val>* nextNode = current->next;
                size_t newIdx = hash<Key>{}(current->key) % tableSize;

                // Head insert into the new bucket
                current->next = newBuckets[newIdx];
                newBuckets[newIdx] = current;

                current = nextNode;
            }
        }
        buckets = move(newBuckets);
    }
public:
    UnorderedMap(size_t initialCapacity = 7) : numElements(0), tableSize(initialCapacity) {
        buckets.resize(tableSize, nullptr);
    }

    ~UnorderedMap() { clear(); }

    // Disable copy semantics to prevent accidental pointer aliasing crashes
    UnorderedMap(const UnorderedMap&) = delete;
    UnorderedMap& operator=(const UnorderedMap&) = delete;

    void clear() {
        for (size_t i = 0; i < tableSize; ++i) {
            Node<Key, Val>* current = buckets[i];
            while (current != nullptr) {
                Node<Key, Val>* temp = current;
                current = current->next;
                delete temp;
            }
            buckets[i] = nullptr;
        }
        numElements = 0;
    }

    Val& operator[](const Key& key) {
        size_t index = getHash(key);
        Node<Key, Val>* current = buckets[index];

        while (current != nullptr) {
            if (current->key == key) {
                return current->val;
            }
            current = current->next;
        }

        // Check load factor before adding a new item
        if ((float)(numElements + 1) / tableSize > maxLoadFactor) {
            rehash();
            index = getHash(key);
        }

        Node<Key, Val>* newNode = new Node<Key, Val>(key, Val());
        newNode->next = buckets[index];
        buckets[index] = newNode;
        numElements++;

        return newNode->val;
    }

    size_t size() const { return numElements; }
    bool empty() const { return numElements == 0; }

    Iterator<Key, Val> begin() const {
        for (size_t i = 0; i < tableSize; ++i) {
            if (buckets[i] != nullptr) {
                return Iterator<Key, Val>(this, i, buckets[i]);
            }
        }
        return end();
    }

    Iterator<Key, Val> end() const {
        return Iterator<Key, Val>(this, tableSize, nullptr);
    }
};