#include <iostream>
#include "bitree.h"
#include <assert.h>

using namespace std;

int main()
{
    // Test 1 - default constructor
    BiTree<int, int> tree;
    assert(tree.size()==0);

    // Test 2 - clear() and operator== test
    tree[1] = 5;
    tree[2] = 7;
    tree[3] = 8;
    tree.clearAll();
    BiTree<int, int> tree2;
    assert(tree == tree2);

    // Test 3 - file test
    string filename = "D:/Documents/TestLaba2.txt";
    tree.write(filename);
    tree2.read(filename);
    assert(tree==tree2);

    // Test 4 - insertion
    tree.clearAll();
    tree.paste(7,1);
    tree.paste(7,4);
    assert(tree.size()==1);

    // Test 5 - check if key is present in a tree
    assert(tree.contains(7)==1);

    // Test 6 - operator[]
    assert(tree[7]==4);

    // Test 7 - deletion
    tree.remove(20); // 20 is not in the tree rn
    assert(tree.size()==1);
    tree.remove(7);
    assert(tree.size()==0);

    // Test 8 - same as test 3
    assert(tree.contains(7)==0);

    // Test 9 - copy constructor test
    tree[1] = 1;
    tree[2] = 4;
    tree[3] = 9;
    BiTree<int, int> treecopy(tree);
    assert(tree==treecopy);
    treecopy[2]++;
    assert((tree==treecopy)==0);

    cout << "All tests passed!" << endl;
    return 0;
}

// Test 1: Размер коллекции, созданной конструктором по умолчанию, равен нулю
// Test 2: Непустая коллекция после удаления всех объектов равна коллекции, созданной при помощи конструктора по умолчанию)
// Test 3: Непустая коллекция, сохранённая в файл, равна новой коллекции, загруженной из того же файла
// Test 4: При добавлении новой пары ключ-значение K, V размер коллекции увеличивается на единицу, а при добавлении имеющейся пары ключ-значение K, V размер не изменяется
// Test 5: Метод, проверяющий наличие ключа принимает добавленный ключ K и возвращает истину
// Test 6: Оператор [] принимает добавленный ключ K и возвращает его значение V
// Test 7: При удалении существующего ключа K размер коллекции уменьшается на единицу, а при удалении отсутствующего ключа K размер не изменяется
// Test 8: Метод, проверяющий наличие ключа принимает удалённый ключ K и возвращает ложь
// Test 9: Копия непустой коллекции равна оригиналу, после изменения одного из значений V равенство нарушается
