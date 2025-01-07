#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2324_P1/ListLinked.h"

using namespace std;

template <typename V>
class HashTable: public Dict<V> {

private:
	int n;
	int max;
	ListLinked<TableEntry<V>>* table;

	int h(string key){
		int n = key.length();
		int sum = 0;
		char c;

		for(int i=0; i<n; i++){
			c = key.at(i);
			sum += int(c);
		}

		return sum % max;
	};

public:
    HashTable(int size) : n(0), max(size) {
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    void insert(string key, V value) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket.get(i).key == key) {
                throw runtime_error("La clave ya existe en el diccionario.");
            }
        }
        bucket.insert(bucket.size(), TableEntry<V>(key, value));
        ++n;
    }

    V search(string key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket.get(i).key == key) {
                return bucket.get(i).value;
            }
        }
        throw runtime_error("Clave no encontrada en el diccionario.");
    }

    V remove(string key) override {
        int index = h(key);
        ListLinked<TableEntry<V>>& bucket = table[index];
        for (int i = 0; i < bucket.size(); ++i) {
            if (bucket.get(i).key == key) {
                V value = bucket.get(i).value;
                bucket.remove(i);
                --n;
                return value;
            }
        }
        throw runtime_error("Clave no encontrada en el diccionario.");
    }

    int entries() override {
        return n;
    }

    int capacity() {
        return max;
    }

    friend ostream& operator<<(ostream &out, const HashTable<V> &ht) {
        for (int i = 0; i < ht.max; ++i) {
            out << "Cubeta " << i << ": ";
            const ListLinked<TableEntry<V>>& bucket = ht.table[i];
            if (bucket.size() == 0) {
                out << "(vacía)";
            } else {
                for (int j = 0; j < bucket.size(); ++j) {
                    out << "[" << bucket.get(j).key << " -> " << bucket.get(j).value << "] ";
                }
            }
            out << endl;
        }
        return out;
    }

    V operator[](string key) {
        return search(key);
    }


};

#endif
