#include <iostream>
struct subset_node {
    int key;
    subset_node *left;
    subset_node *right;
};

bool init(subset_node **sn); // инициализация пустого дерева (аналогично списку, пустое дерево это указатель на NULL)
bool insert(subset_node **sn, int k); // добавление элемента в дерево, дубли игнорировать (ничего не добавлять в дерево, если там уже есть элемент с таким же key) и возвращать false
bool remove(subset_node **sn, int k); // удаление элемента из дерева (если элемента не нашлось, то ничего не удалять и вернуть false)
subset_node* find(subset_node **sn, int k); // поиск элемента в дереве, нужно вернуть указатель на элемент с тем же key или, если такого элемента не нашлось, то NULL
unsigned int size(subset_node *sn); // количество элементов в дереве
unsigned int height(subset_node *sn); // высота дерева
void destructor(subset_node *sn); // очистить всю используемую память
int* DFS (subset_node *sn); //обход в глубину, возвращает указатель на массив из динамической памяти (кучи)

bool init(subset_node **sn) {
    *sn = nullptr;
    return true;
}
bool insert(subset_node **sn, int k) {
    while (*sn) {
        if ((*sn)->key == k) return false;
        if ((*sn)->key > k) {
           sn = &((*sn)->left);
        }
        else {
            sn = &((*sn)->right);
        }
    }
    *sn = new subset_node;
    (*sn)->key = k;
    (*sn)->right = nullptr;
    (*sn)->left = nullptr;
    return true;
}
bool remove(subset_node **sn, int k) {
    while (*sn) {
        if ((*sn)->key == k) {
            subset_node *to_del = *sn;
            if ((*sn)->left == nullptr) {
                *sn = (*sn)->right;
                delete to_del;
            }
            else if ((*sn)->right == nullptr) {
                *sn = (*sn)->left;
                delete to_del;
            }
            // у узла оба ребенка
            else {   // находим минимальный узел в правом поддереве
                subset_node **min_right = &((*sn)->right);
                while ((*min_right)->left != nullptr) {
                    min_right = &((*min_right)->left);
                }
                (*sn)->key = (*min_right)->key;
                to_del = *min_right;
                *min_right = (*min_right)->right;  // у минимального узла нет левого ребенка
                delete to_del;
            }
            return true;
        }
        if ((*sn)->key > k) {
            sn = &((*sn)->left);
        }
        else {
            sn = &((*sn)->right);
        }
    }
    return false;
}
subset_node* find(subset_node *sn, int k) {
    while (sn) {
        if (sn->key == k) {
            return sn;
        }
        if (sn->key > k) {
            sn = sn->left;
        }
        else {
            sn = sn->right;
        }
    }
    return nullptr;
}
// size написан гениально. Я помнил как это пишется прост :)
unsigned int size(subset_node *sn) {
    if (!sn) return 0;
    return (1 + size(sn->left) + size(sn->right));
}

unsigned int height(subset_node *sn) {
    if (!sn) return 0;
    unsigned int height_l = height(sn->left);
    unsigned int height_r = height(sn->right);
    if (height_l > height_r) {
        return height_l + 1;
    }
        return height_r + 1;

}

void destructor(subset_node *sn) {
    if (!sn) return;
    destructor(sn->left);
    destructor(sn->right);
    delete sn;
}

void dop_DFS(subset_node *sn, int* mas, int* i) {
    if (!sn) return;
    dop_DFS(sn->left, mas, i);
    mas[*i] = sn->key;
    (*i)++;
    dop_DFS(sn->right, mas, i);
}

int* DFS(subset_node *sn) {
    unsigned int sz = size(sn);
    if (sz == 0) return nullptr;
    int *ms = new int[sz];
    int j = 0;
    dop_DFS(sn, ms, &j);
    return ms;
}

#include <random>
#include <chrono>
#include <climits>
using std::cout;
using std::endl;
double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}
int rand_uns(int min, int max)
{
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        static std::default_random_engine e(seed);
        std::uniform_int_distribution<int> d(min, max);
        return d(e);
}
int main()
{
    unsigned int n = 10000;
    int *sequent_sequence = new int[n],
        *rand_sequence_10 = new int[n],
        *rand_sequence_100 = new int[n],
        *rand_sequence_n = new int[n],
        *rand_sequence_unique = new int[n],
        *sorted_sequence_unique = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);
//----------- Initialization
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sequent_sequence[i] = i;
        rand_sequence_10[i] = rand_uns(0, 10);
        rand_sequence_100[i] = rand_uns(0, 100);
        rand_sequence_n[i] = rand_uns(0, n);
    }
    for (unsigned int i = 0; i < n; i++)
    {
        rand_sequence_unique[i] = rand_uns(0, INT_MAX);
        for (unsigned int j = 0; j < i; j++)
            if (rand_sequence_unique[i] == rand_sequence_unique[j])
            {
                i--;
                break;
            }
    }
    for (unsigned int i = 0; i < n; i++)
        sorted_sequence_unique[i] = rand_sequence_unique[i];
    for (unsigned int i = 0; i < n; i++)
        for (unsigned int j = 0; j < n - i - 1; j++)
            if (sorted_sequence_unique[j] > sorted_sequence_unique[j + 1])
            {
                int tmp = sorted_sequence_unique[j];
                sorted_sequence_unique[j] = sorted_sequence_unique[j + 1];
                sorted_sequence_unique[j + 1] = tmp;
            }

    finish = get_time();
    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
    subset_node *sn;
    init(&sn);
//----------- Test 000 Insert of a sequent sequence
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, sequent_sequence[i]);
    }
    finish = get_time();
    if (size(sn) != n)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, wrong number of elements !!! ---" << endl;
        return 0;
    }
    if (height(sn) != n)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, wrong height !!! ---" << endl;
        return 0;
    }
    cout << "000 Insert of a sequent sequence: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 001 Finding of a sequent sequence
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, sequent_sequence[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "001 Finding of a sequent sequence: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 002 Remove of a sequent sequence
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, sequent_sequence[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "002 Remove of a sequent sequence: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 003 Insert of a random sequence (0 - 10)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_10[i]);
    }
    finish = get_time();
    auto content = DFS(sn);
    auto size_content = size(sn);
    for (unsigned int i = 0; i < size_content - 1; i++)
        if (content[i] >= content[i + 1])
        {
            cout <<endl <<"--- !!! Failed content order, the left is larger than the right !!! ---" << endl;
            return 0;
        }
    delete[] content;
    cout << "003 Insert of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 004 Finding of a random sequence (0 - 10)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_10[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "004 Finding of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 005 Remove of a random sequence (0 - 10)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, rand_sequence_10[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "005 Remove of a random sequence (0 - 10): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 006 Insert of a random sequence (0 - 100)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_100[i]);
    }
    finish = get_time();
    content = DFS(sn);
    size_content = size(sn);
    for (unsigned int i = 0; i < size_content - 1; i++)
        if (content[i] >= content[i + 1])
        {
            cout <<endl <<"--- !!! Failed content order, the left is larger than the right !!! ---" << endl;
            return 0;
        }
    delete[] content;
    cout << "006 Insert of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 007 Finding of a random sequence (0 - 100)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_100[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "007 Finding of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 008 Remove of a random sequence (0 - 100)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, rand_sequence_100[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "008 Remove of a random sequence (0 - 100): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 009 Insert of a random sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_n[i]);
    }
    finish = get_time();
    cout << "009 Insert of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 010 Finding of a random sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_n[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "010 Finding of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 011 Remove of a random sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, rand_sequence_n[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "011 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 012 Insert of an unique sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        insert(&sn, rand_sequence_unique[i]);
    }
    finish = get_time();
    cout << "012 Insert of an unique sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 013 Finding of an unique sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (!find(sn, rand_sequence_unique[i]))
        {
            cout <<endl <<"--- !!! Failed insert consistency or find, an element was not found !!! ---" << endl;
            return 0;
        }
    }
    if (find(sn, n + 1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    if (find(sn, -1))
    {
        cout <<endl <<"--- !!! Failed find, an extra element was found !!! ---" << endl;
        return 0;
    }
    finish = get_time();
    cout << "013 Finding of an unique sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 014 Checking the searchiness of the tree
    content = DFS(sn);
    size_content = size(sn);
    if (size_content != n)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, wrong number of elements !!! ---" << endl;
        return 0;
    }
    for (unsigned int i = 0; i < size_content; i++)
    {
        if (content[i] != sorted_sequence_unique[i])
        {
            cout <<endl <<"--- !!! Failed order, DFS is supposed to sort the data !!! ---" << endl;
            return 0;
        }
    }
    delete[] content;
    cout << "014 Checking the searchiness of the tree: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 015 Remove of an unique sequence (0 - n)
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        remove(&sn, sorted_sequence_unique[i]);
    }
    finish = get_time();
    if (size(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or size measurement, elements stuck !!! ---" << endl;
        return 0;
    }
    if (height(sn) != 0)
    {
        cout <<endl <<"--- !!! Failed insert consistency or height measurement, too high for an empty tree !!! ---" << endl;
        return 0;
    }
    cout << "015 Remove of a random sequence (0 - n): \t\t\t\t" << finish - start << endl;
    total += finish - start;

//----------- End of tests
//
    cout << "-----------" << endl <<"Alltests finished, total time: \t" << total << endl;
    delete[] sequent_sequence;
    delete[] rand_sequence_10;
    delete[] rand_sequence_100;
    delete[] rand_sequence_n;
    delete[] rand_sequence_unique;
    delete[] sorted_sequence_unique;
    return 0;
}