#include <iostream>

struct subforwardlist {
    int data;
    subforwardlist* next;
};


bool init(subforwardlist **sfl);
bool push_back(subforwardlist **sfl, int d);
int pop_back(subforwardlist **sfl); 	//удаление элемента с конца недосписка, если пустой - возвращать 0
bool push_forward(subforwardlist **sfl, int d); 	//добавление элемента в начало недосписка
int pop_forward(subforwardlist **sfl); 	//удаление элемента из начала недосписка, если пустой - возвращать 0
bool push_where(subforwardlist **sfl, unsigned int where, int d); //добавление элемента с порядковым номером where
int erase_where(subforwardlist **sfl, unsigned int where);	//удаление элемента с порядковым номером where
void clear(subforwardlist  **sfl);	//очистить содержимое недосписка
unsigned int size(subforwardlist  **sfl);	//определить размер недосписка

bool init(subforwardlist **sfl) {
    *sfl = nullptr;
    return 1;
}
bool push_back(subforwardlist **sfl, int d) {
    while (*sfl) {
        sfl = &((*sfl)->next);
    }
    *sfl = new subforwardlist;
    (*sfl)->data = d;
    (*sfl)->next = nullptr;
    return 1;
}
int pop_back(subforwardlist **sfl) {
    if (!*sfl) return 0;
    while ((*sfl)->next) {
        sfl = &((*sfl)->next);
    }
    int temp = (*sfl)->data;
    delete (*sfl);
    *sfl = nullptr;
    return temp;
}
bool push_forward(subforwardlist **sfl, int d) {
    subforwardlist *new_list = new subforwardlist;
    new_list->data = d;
    new_list->next = *sfl;
    *sfl = new_list;
    return 1;
}
int pop_forward(subforwardlist **sfl) {
    if (!*sfl) return 0;
    int temp = (*sfl)->data;
    subforwardlist *temp2 = (*sfl)->next;
    delete *sfl;
    *sfl = temp2;
    return temp;
}

bool push_where(subforwardlist **sfl, unsigned int where, int d) {
    if (where == 0) {
        push_forward(sfl, d);
        return 1;
    }
    for (unsigned int i = 0; i < where - 1; i++) {
        sfl = &((*sfl)->next);
    }
    subforwardlist *new_el = new subforwardlist;
    new_el->data = d;
    new_el->next = (*sfl)->next;
    (*sfl)->next = new_el;
    return 1;
}
int erase_where(subforwardlist **sfl, unsigned int where) {
    if (!*sfl) return 0;
    if (where == 0) {
        return pop_forward(sfl);
    }
    for (unsigned int i = 0; i < where - 1; i++) {
        sfl = &((*sfl)->next);
    }
    subforwardlist *temp = (*sfl)->next;
    int ans = temp->data;
    (*sfl)->next = temp->next;
    delete temp;
    return ans;
}
void clear(subforwardlist **sfl) {
    while (*sfl) {
        pop_forward(sfl);
    }
}
unsigned int size(subforwardlist  *sfl) {
    unsigned int cnt = 0;
    while (sfl) {
        sfl = sfl->next;
        cnt++;
    }
    return cnt;
}

// ваш код сюда идет
#include <random>
#include <chrono>
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
    int *test_sequence = new int[n], sum_for_O3 = 0, test_sequence_sum = 0, ongoing_sum = 0,
        *push_sequence = new int[n],
        *pop_sequence = new int[n],
        *pop_push_sequence_eq = new int[n],
        *pop_push_sequence_push = new int[n],
        *pop_push_sequence_pushpush = new int[n],
        *four_ways_test = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);
//----------- Initialization
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        test_sequence[i] = rand_uns(0, n - 1);
        test_sequence_sum += test_sequence[i];
        push_sequence[i] = rand_uns(0, n - 1);
        pop_sequence[i] = rand_uns(0, n - 1);
        pop_push_sequence_eq[i] = rand_uns(0, 1);
        pop_push_sequence_push[i] = rand_uns(0, 5);
        pop_push_sequence_pushpush[i] = rand_uns(0, 10);
        four_ways_test[i] = rand_uns(0, 3);
    }

    finish = get_time();
    cout << "Test sequence initialization: \t\t\t\t" << finish - start << endl;
    subforwardlist *sv;
    init(&sv);
//----------- Test 000 Straight push_back
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        push_back(&sv, test_sequence[i]);
    }
    finish = get_time();
    cout << "000 Straight push_back: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 001 Straight pop_forward
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_forward(&sv) != test_sequence[i])
        {
            cout <<endl <<"--- !!! Failed push/pop consistency !!! ---" << endl;
            return 0;
        }
    }
    finish = get_time();
    if (size(sv))
    {
        cout <<endl <<"--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }
    cout << "001 Straight pop_forward: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 002 Straight push_forward
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        push_forward(&sv, test_sequence[i]);
    }
    finish = get_time();
    cout << "002 Straight push_forward: \t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 003 Straight pop_back
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_back(&sv) != test_sequence[i])
        {
            cout <<endl <<"--- !!! Failed push/pop consistency !!! ---" << endl;
            return 0;
        }
    }
    finish = get_time();
    if (size(sv))
    {
        cout <<endl <<"--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }
    cout << "003 Straight pop_back: \t\t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 004 Random push_where
    for (unsigned int i = 0; i < n; i++)
    {
        push_back(&sv, test_sequence[i]);
    }
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        push_where(&sv, push_sequence[i], test_sequence[i]);
    }
    finish = get_time();
    if (size(sv) != 2 * n)
    {
        cout <<endl <<"--- !!! Failed push/pop consistency, wrong elements number !!! ---" << endl;
        return 0;
    }
    ongoing_sum = 0;
    for (unsigned int i = 0; i < 2 * n; i++)
    {
        ongoing_sum += pop_back(&sv);
    }
    if (size(sv))
    {
        cout <<endl <<"--- !!! Failed push/pop consistency, some elememts stuck !!! ---" << endl;
        return 0;
    }
    if (ongoing_sum != 2 * test_sequence_sum)
    {
        cout <<endl <<"--- !!! Failed push/pop consistency, sum incoherent !!! ---" << endl;
        return 0;
    }
    cout << "004 Random push_where: \t\t\t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 005 Random erase_where
    for (unsigned int i = 0; i < 2 * n; i++)
    {
        push_back(&sv, test_sequence[i % n]);
    }
    sum_for_O3 = 0;
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        sum_for_O3 += erase_where(&sv, pop_sequence[i]);
    }
    finish = get_time();
    if (size(sv) != n)
    {
        cout <<endl <<"--- !!! Failed push/pop consistency, wrong elements number !!! ---" << endl;
        return 0;
    }
    clear(&sv);
    if (size(sv))
    {
        cout <<endl <<"--- !!! Clear works wrongly !!! ---" << endl;
        return 0;
    }
    cout << "005 Random erase_where: \t\t\t\t" << finish - start << " \t\t" << sum_for_O3 << endl;
    total += finish - start;

//----------- Test 006 Random pop/push back equal amount
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            push_back(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_back(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "006 Random pop/push back equal amount: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 007 Random pop/push back more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            push_back(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_back(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "007 Random pop/push back more push: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 008 Random pop/push back much more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            push_back(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_back(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "008 Random pop/push back much more push: \t\t" << finish - start <<"\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 009 Random pop/push forward equal amount
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            push_forward(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_forward(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "009 Random pop/push forward equal amount: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 010 Random pop/push forward more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            push_forward(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_forward(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "010 Random pop/push forward more push: \t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 011 Random pop/push forward much more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            push_forward(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_forward(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "011 Random pop/push forward much more push: \t\t" << finish - start <<"\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 012 Random pop/push four ways
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (unsigned int i = 0; i < n; i++)
    {
        if (four_ways_test[i] == 0)
            push_back(&sv, test_sequence[i]);
        else if (four_ways_test[i] == 1)
            sum_for_O3 += pop_back(&sv);
        else if (four_ways_test[i] == 2)
            push_forward(&sv, test_sequence[i]);
        else
            sum_for_O3 += pop_forward(&sv);
    }
    finish = get_time();
    clear(&sv);
    cout << "012 Random pop/push four ways: \t\t\t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- End of tests
//
    cout << "-----------" << endl <<"Alltests finished, total time: \t" << total << endl;
    delete[] test_sequence;
    delete[] pop_push_sequence_eq;
    delete[] pop_push_sequence_push;
    delete[] pop_push_sequence_pushpush;
    delete[] push_sequence,
    delete[] pop_sequence,
    delete[] four_ways_test;

    return 0;
}