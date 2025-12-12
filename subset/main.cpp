

struct subset_node {
    int key;
    subset_node *left;
    subset_node *right;
};

bool init(subset_node @sn); // инициализация пустого дерева (аналогично списку, пустое дерево это указатель на NULL)
bool insert(subset_node @sn, int k); // добавление элемента в дерево, дубли игнорировать (ничего не добавлять в дерево, если там уже есть элемент с таким же key) и возвращать false
bool remove(subset_node @sn, int k); // удаление элемента из дерева (если элемента не нашлось, то ничего не удалять и вернуть false)
subset_node* find(subset_node @sn, int k); // поиск элемента в дереве, нужно вернуть указатель на элемент с тем же key или, если такого элемента не нашлось, то NULL
unsigned int size(subset_node @sn); // количество элементов в дереве
unsigned int height(subset_node @sn); // высота дерева
void destructor(subset_node @sn); // очистить всю используемую память
int* DFS (subset_node @sn); //обход в глубину, возвращает указатель на массив из динамической памяти (кучи)

bool init(subset_node *sn) {
    sn = nullptr;
    return 1;
}
bool insert{subset_node @sn}