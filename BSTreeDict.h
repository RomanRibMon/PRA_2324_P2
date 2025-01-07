#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <stdexcept>
#include <string>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"
using namespace std;

template <typename V>
class BSTreeDict : public Dict<V> {
private:
    BSTree<TableEntry<V>> tree;

public:
    BSTreeDict() {}

    ~BSTreeDict() {}

    void insert(string key, V value) override {
        tree.insert(TableEntry<V>(key, value));
    }

    V search(string key) override {
        return tree.search(TableEntry<V>(key, V())).value;
    }

    V remove(string key) override {
        TableEntry<V> entry(key, V());
        V value = tree.search(entry).value; // Obtenemos el valor antes de eliminar
        tree.remove(entry);
        return value;
    }

    int entries() override {
        return tree.size();
    }

    V operator[](string key) {
        return search(key);
    }

    friend ostream& operator<<(ostream &out, const BSTreeDict<V> &dict) {
        out << dict.tree;
        return out;
    }
};

#endif
