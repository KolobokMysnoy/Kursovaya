#include "search.h"
#include <algorithm>
#include <list>

void write_results(size_t from, size_t to, short* parents, std::vector <size_t>* result);
bool bfs(short* graph, short size, short to, short* visited, std::list<short>& buffer, short* parents) {
    if (buffer.empty()) return false;

    short from = buffer.front();
    buffer.pop_front();

    visited[from] = 1;
    if (from == to) {
        return true;
    }

    for (size_t i = 0; i < size; ++i) {
        if (graph[from*size + i] == 0) continue;
        if (visited[i] == 1) continue;
        if (std::find(buffer.begin(), buffer.end(), i) != buffer.end()) continue;

        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(graph, size, to, visited, buffer, parents);
}

std::vector <size_t> search_graph(short* graph, size_t size, size_t from, size_t to) {
    short* visited = new short[size];
    short* parents = new short[size];
    std::vector <size_t> results;

    // don't visit
    for (size_t i = 0; i < size; ++i) {
        visited[i] = 0;
    }

    std::list<short> buffer;
    buffer.push_back(from - 1);
    bfs(graph, size, to, visited, buffer, parents);

    write_results(from - 1, to - 1, parents, &results);

    // free memory
    delete[] visited;
    delete[] parents;
    return results;
}

void write_results(size_t from, size_t to, short* parents, std::vector <size_t> * result) {
    if (to == from) {
        result->push_back(to + 1);
        return;
    }
    size_t prefrom = parents[to];
    write_results(from, prefrom, parents, result);
    result->push_back(to + 1);
}



//std::vector <size_t> search_function(size_t from, size_t to, size_t size_of_array, short ** matrix) {
//    short ** matrix_to_work = &( *matrix);
//    short min_len[size_of_array];
//    short visited_nodes[size_of_array];
//    size_t temp, min_ind, min;

//    // get min values to all nodes
//    for(short i = 0; i< size_of_array; i++) {
//        min_len[i] = SHRT_MAX;
//        visited_nodes[i] = 1;
//    }

//    size_t begin_index = 0;
//    min_len[begin_index] = 0;

//    do {
//        min_ind = SHRT_MAX;
//        min = SHRT_MAX;

//        for (int i = 0; i < size_of_array; i++) {

//            if((visited_nodes[i] == 1) && (min_len[i] < min)){
//                min = min_len[i];
//                min_ind = i;
//            }
//        }

//        if(min_ind != SHRT_MAX) {
//                for (int i = 0; i < size_of_array; i++) {
//                    if (matrix_to_work[min_ind][i] > 0) {
//                        temp = min + matrix_to_work[min_ind][i];
//                        if(temp < min_len[i]) {
//                            min_len[i] = temp;
//                        }
//                    }
//                }
//        }
//        visited_nodes[min_ind] = 0;

//    } while (min_ind < SHRT_MAX);

//    // restore our way
//    short visited[size_of_array];
//    size_t end = to, start = from;

//    visited[0] = end;
//    size_t last_node = 1;
//    size_t weight = min_len[end];

//    while (end != begin_index) {
//        for (size_t i = 0; i < size_of_array; i++) {
//            if (matrix_to_work[i][end] != 0) {
//                size_t temp = weight - matrix_to_work[i][end];
//                if (temp == min_len[i]) {
//                    weight = temp;
//                    end = i;
//                    visited[last_node] = i + 1;
//                    last_node++;
//                }
//            }
//        }
//    }

//    std::vector <size_t> return_vec;

//    return_vec.reserve(last_node);

//    for ( size_t i = last_node - 1; i >= 0; i--) {
//        return_vec.push_back(visited[i]);
//    }

//    return return_vec;
//}

////int main()
////{
//  int a[SIZE][SIZE]; // матрица связей
//  int d[SIZE]; // минимальное расстояние
//  int v[SIZE]; // посещенные вершины
//  int temp, minindex, min;
//  int begin_index = 0;
////  system("chcp 1251");
////  system("cls");
////  // Инициализация матрицы связей
////  for (int i = 0; i<SIZE; i++)
////  {
////    a[i][i] = 0;
////    for (int j = i + 1; j<SIZE; j++) {
////      printf("Введите расстояние %d - %d: ", i + 1, j + 1);
////      scanf("%d", &temp);
////      a[i][j] = temp;
////      a[j][i] = temp;
////    }
////  }
////  // Вывод матрицы связей
////  for (int i = 0; i<SIZE; i++)
////  {
////    for (int j = 0; j<SIZE; j++)
////      printf("%5d ", a[i][j]);
////    printf("\n");
////  }
//  //Инициализация вершин и расстояний
//  for (int i = 0; i<SIZE; i++)
//  {
//    d[i] = 10000;
//    v[i] = 1;
//  }
//  d[begin_index] = 0;
//  // Шаг алгоритма
//  do {
//    minindex = 10000;
//    min = 10000;
//    for (int i = 0; i<SIZE; i++)
//    { // Если вершину ещё не обошли и вес меньше min
//      if ((v[i] == 1) && (d[i]<min))
//      { // Переприсваиваем значения
//        min = d[i];
//        minindex = i;
//      }
//    }
//    // Добавляем найденный минимальный вес
//    // к текущему весу вершины
//    // и сравниваем с текущим минимальным весом вершины
//    if (minindex != 10000)
//    {
//      for (int i = 0; i<SIZE; i++)
//      {
//        if (a[minindex][i] > 0)
//        {
//          temp = min + a[minindex][i];
//          if (temp < d[i])
//          {
//            d[i] = temp;
//          }
//        }
//      }
//      v[minindex] = 0;
//    }
//  } while (minindex < 10000);
//  // Вывод кратчайших расстояний до вершин
//  printf("\nКратчайшие расстояния до вершин: \n");
//  for (int i = 0; i<SIZE; i++)
//    printf("%5d ", d[i]);

//  // Восстановление пути
//  int ver[SIZE]; // массив посещенных вершин
//  int end = 4; // индекс конечной вершины = 5 - 1
//  ver[0] = end + 1; // начальный элемент - конечная вершина
//  int k = 1; // индекс предыдущей вершины
//  int weight = d[end]; // вес конечной вершины

//  while (end != begin_index) // пока не дошли до начальной вершины
//  {
//    for (int i = 0; i<SIZE; i++) // просматриваем все вершины
//      if (a[i][end] != 0)   // если связь есть
//      {
//        int temp = weight - a[i][end]; // определяем вес пути из предыдущей вершины
//        if (temp == d[i]) // если вес совпал с рассчитанным
//        {                 // значит из этой вершины и был переход
//          weight = temp; // сохраняем новый вес
//          end = i;       // сохраняем предыдущую вершину
//          ver[k] = i + 1; // и записываем ее в массив
//          k++;
//        }
//      }
//  }
//  // Вывод пути (начальная вершина оказалась в конце массива из k элементов)
//  printf("\nВывод кратчайшего пути\n");
//  for (int i = k - 1; i >= 0; i--)
//    printf("%3d ", ver[i]);
//  getchar(); getchar();
//  return 0;
//}

  /*
Блог программиста
программирование и алгоритмы

Блог
Форумы
Литература
Обо мне
Профиль
Поиск в ширину на C++
Прикладное программирование › Программирование на С/С++ › Решение задач на С++ › Поиск в ширину на C++

Помечено: cplusplus, алгоритмы, графы, структуры данных

Просмотр 0 веток ответов
Автор
Сообщения
08.07.2020 в 07:51#7106
@admin
Алгоритм поиск в ширину описан в статье «Графы — поиск в ширину и глубину«. Реализуем поиск пути с помощью алгоритма «поиск в ширину» из вершины S в вершину F на графе, представленном:

матрицей смежности;
матрицей инцидентности;
связными списками;
Пусть во входном файле задается:

<количество вершин> <количество дуг>
<начальная вершина> <конечная вершина>
<список дуг>
При этом дуга задается парой вершин:

<начало> <конец>
Пример входных данных:

10 12
1 6
1 3
1 4
1 5
2 5
2 6
3 4
3 6
5 6
7 8
7 10
8 9
9 10
Эти входные данные задают поиск пути из вершины 1 в вершину 6 на графе, приведенном на рисунке:



BFS на матрице смежности
Исходный код программы, реализующей этот алгоритм:

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;
bool bfs(int **graph, int n, int to, int* visited, list<int> &buffer, int* parents);
void print_path(int from, int to, int* parents, ofstream& ofst);
int main() {
    setlocale(LC_ALL, "rus");
    char filenamein[] = "in.txt";
    char filenameout[] = "out.txt";
    ifstream fin(filenamein);
    ofstream fout(filenameout);
    if (!fin || !fout) {
        cout << "ошибка при открытие файла\n";
        system("pause");
        return 1;
    }
    int n, m;
    fin >> n >> m;
    int from, to;
    fin >> from >> to;
    from--; to--;
    int** graph = new int* [n];
    int* visited = new int[n];
    int* parents = new int[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        fin >> a >> b;
        graph[a - 1][b - 1] = graph[b - 1][a - 1] = 1;
    }
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    list<int> buffer;
    buffer.push_back(from);
    if (false == bfs(graph, n, to, visited, buffer, parents)) {
        fout << "path does not exist" << endl;
    }
    else {
        print_path(from, to, parents, fout);
    }
    for (int i = 0; i < n; i++)
        delete[] graph[i];
    delete[] graph;
    delete[] visited;
    delete[] parents;
    fin.close();
    fout.close();
}
bool bfs(int **graph, int n, int to, int* visited, list<int>& buffer, int* parents) {
    if (buffer.empty())
        return false;
    int from = buffer.front();
    buffer.pop_front();
    visited[from] = true;
    if (from == to) {
        return true;
    }
    for (int i = 0; i < n; ++i) {
        if (graph[from][i] == 0)
            continue;
        if (visited[i] == true)
            continue;
        if (find(buffer.begin(), buffer.end(), i) != buffer.end())
            continue;
        parents[i] = from;
        buffer.push_back(i);
    }
    return bfs(graph, n, to, visited, buffer, parents);
}
void print_path(int from, int to, int* parents, ofstream& ofst) {
    if (to == from) {
        ofst << to+1;
        return;
    }
    int prefrom = parents[to];
    print_path(from, prefrom, parents, ofst);
    ofst << " -> " << to+1;
}
Видно, что функция bfs принимает также массив parents – он нужен для восстановления пути. В этот массив помещаются номера вершин, из которых осуществлен переход, так — если в ячейке с номером X находится число Y – значит в ячейку X можно попасть из вершины Y.

В строках:

77-78 выполняется извлечение первой (текущей) вершины из буфера;
86-95 происходит наполнение буфера вершинами, смежными с текущей вершиной, при этом:
пропускаются вершины, не смежные с текущей (строки 87-88);
пропускаются вершины, уже посещенные ранее (89-90);
пропускаются вершины, уже добавленные в буфер (91-92), при этом используется стандартный алгоритм find, который при неудачном поиске возвращает итератор end().
Функция print_path печатает найденный путь, при этом она использует массив parents.
При запуске этой программы для поиска пути

из узла 1 в узел 6 получим: 1 -> 3 -> 6
из узла 1 в узел 5: 1 -> 5
из узла 9 в узел 3: path does not exist
Поиск в ширину на матрице инцидентности
Отличие этой программы от предыдущей лишь в формате хранения графа. Изменился исходный код считывания графа из файла – матрица теперь имеет размер NxM. Функция bfs изменилась не очень сильно – но для получения вершины, смежной с X теперь перебираются все элементы столбца X. Исходный код программы целиком:

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;
bool bfs(int **graph, int n, int m, int to, int* visited, list<int> &buffer, int* parents);
void print_path(int from, int to, int* parents, ofstream& ofst);
int main() {
    setlocale(LC_ALL, "rus");
    char filenamein[] = "in.txt";
    char filenameout[] = "out.txt";
    ifstream fin(filenamein);
    ofstream fout(filenameout);
    if (!fin || !fout) {
        cout << "ошибка при открытие файла\n";
        system("pause");
        return 1;
    }
    int n, m;
    fin >> n >> m;
    int from, to;
    fin >> from >> to;
    from--; to--;
    int** graph = new int* [n];
    int* visited = new int[n];
    int* parents = new int[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[m];
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            graph[i][j] = 0;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        fin >> a >> b;
        graph[a - 1][i] = graph[b - 1][i] = 1;
    }
    for (int i = 0; i < n; i++)
        visited[i] = 0;
    list<int> buffer;
    buffer.push_back(from);
    if (false == bfs(graph, n, m, to, visited, buffer, parents)) {
        fout << "path does not exist" << endl;
    }
    else {
        print_path(from, to, parents, fout);
    }
    for (int i = 0; i < n; i++)
        delete[] graph[i];
    delete[] graph;
    delete[] visited;
    delete[] parents;
    fin.close();
    fout.close();
}
bool bfs(int **graph, int n, int m, int to, int* visited, list<int>& buffer, int* parents) {
    if (buffer.empty())
        return false;
    int from = buffer.front();
    buffer.pop_front();
    visited[from] = true;
    if (from == to) {
        return true;
    }
    for (int i = 0; i < m; ++i) {
        if (graph[from][i] == 0)
            continue;
        // i-тая дуга инцидентна вершине,
        // надо найти вторую вершину инцидентную I-той дуге
        int node;
        for (node = 0; node < n; ++node) {
            if (node != from && graph[node][i] != 0)
                break;
        }
        if (visited[node] == true)
            continue;
        if (find(buffer.begin(), buffer.end(), node) != buffer.end())
            continue;
        parents[node] = from;
        buffer.push_back(node);
    }
    return bfs(graph, n, m, to, visited, buffer, parents);
}
void print_path(int from, int to, int* parents, ofstream& ofst) {
    if (to == from) {
        ofst << to+1;
        return;
    }
    int prefrom = parents[to];
    print_path(from, prefrom, parents, ofst);
    ofst << " -> " << to+1;
}
Входные и выходные данные совпадают с данными для предыдущего примера.

BFS на связных списках
Будем хранить граф в виде связных списков, при этом узел графа опишем структурой:

struct Node {
    int number;
    Node* parent;
    list<Node*> nodes;
    bool is_visited;
    Node(int number_) :
        number(number_),
        is_visited(false) {
    }
};
Между собой узлы связаны через указатели, которые хранятся внутри связного списка. Все узлы графа будем хранить в еще одном связном списка – это необходимо, хотя бы для того, чтобы по окончанию работы программы освободить память (для этого надо перебрать все узлы).

Видно, что помимо своего номера и списка смежных вершин, каждый узел хранит флаг is_visited и узел parent – это сделано чтобы исключить из функции bfs дополнительные параметры – список уже посещенных вершин и список parents, используемый для восстановления пути.

Такая структура очень медленна во многих операциях – поиск узла по номеру требует O(N) операций, поиск смежной с ним вершины – тоже O(N). Однако, в такой граф можно более эффективно добавлять дуги (узлы в список nodes) и новые вершины, что очень сложно сделать для представления графа в виде матриц.

В функции main теперь кроме графа остался только список – буфер, используемый внутри алгоритма поиска в ширину. В программе несколько раз необходимо выполнять поиск узла по номеру – например при вводе графа, т.к. во входном файле находятся номера, а внутри программы узлы связаны через указатели. Поэтому для этой операции была написана функция node_by_number.

Исходный код программы целиком:

#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>
using namespace std;
struct Node {
    int number;
    Node* parent;
    list<Node*> nodes;
    bool is_visited;
    Node(int number_) :
        number(number_),
        is_visited(false) {
    }
};
Node* node_by_number(list<Node*>& graph, int number);
bool bfs(list<Node*>& graph, Node* to, list<Node *>& buffer);
void print_path(Node* from, Node* to, ofstream& ofst);
int main() {
    setlocale(LC_ALL, "rus");
    char filenamein[] = "in.txt";
    char filenameout[] = "out.txt";
    ifstream fin(filenamein);
    ofstream fout(filenameout);
    if (!fin || !fout) {
        cout << "ошибка при открытие файла\n";
        system("pause");
        return 1;
    }
    int n, m, from, to;
    fin >> n >> m >>
           from >> to;
    list<Node*> graph, buffer;
    // добавляю в граф узлы
    for (int i = 0; i < n; i++) {
        graph.push_back(new Node(i+1));
    }
    // ввод графа
    for (int i = 0; i < m; i++) {
        int edge_from_number, edge_to_number;
        fin >> edge_from_number >> edge_to_number;
        Node* edge_from = node_by_number(graph, edge_from_number);
        Node* edge_to = node_by_number(graph, edge_to_number);
        edge_from->nodes.push_back(edge_to);
        edge_to->nodes.push_back(edge_from);
    }
    // добавляю стартовую вершину в буфер
    buffer.push_back(node_by_number(graph, from));
    if (false == bfs(graph, node_by_number(graph, to), buffer)) {
        fout << "path does not exist" << endl;
    }
    else {
        print_path(node_by_number(graph, from), node_by_number(graph, to), fout);
    }
    for (list<Node*>::iterator it = graph.begin(); it != graph.end(); ++it) {
        delete *it;
    }
    fin.close();
    fout.close();
}
Node* node_by_number(list<Node*>& graph, int number) {
    for (list<Node*>::iterator it = graph.begin(); it != graph.end(); ++it) {
        if ((*it)->number == number)
            return *it;
    }
    return 0;
}
bool bfs(list<Node*>& graph, Node* to, list<Node *>& buffer) {
    if (buffer.empty())
        return false;
    Node* from = buffer.front();
    buffer.pop_front();
    from->is_visited = true;
    if (from == to) {
        return true;
    }
    // перебираю смежные вершины
    for (list<Node*>::iterator it = from->nodes.begin(); it != from->nodes.end(); ++it) {
        Node* node = *it;
        if (node->is_visited == true)
            continue;
        if (find(buffer.begin(), buffer.end(), node) != buffer.end())
            continue;
        node->parent = from;
        buffer.push_back(node);
    }
    return bfs(graph, to, buffer);
}
void print_path(Node* from, Node* to, ofstream& ofst) {
    if (to == from) {
        ofst << to->number;
        return;
    }
    print_path(from, to->parent, ofst);
    ofst << " -> " << to->number;
}
Результаты работы программы аналогичны результатам предыдущих программ.

Автор
Сообщения
Просмотр 0 веток ответов
Для ответа в этой теме необходимо авторизоваться.

Имя пользователя:
Пароль:
 Запомнить меня

Войти
ПОИСК

Наша группа ВКонтакте.

ПОСЛЕДНИЕ ТЕМЫ

Beamer: презентация средствами LaTeX опубликовано Васильев Владимир Сергеевич
1 месяц назад
Запись и выполнение макросов в VIM опубликовано Васильев Владимир Сергеевич
1 месяц, 1 неделя назад
Исполнение Пролог-программ на Android опубликовано Васильев Владимир Сергеевич
5 месяцев, 2 недели назад
БД книг на Prolog опубликовано Васильев Владимир Сергеевич
5 месяцев, 2 недели назад
Изоморфность деревьев (Prolog) опубликовано Васильев Владимир Сергеевич
5 месяцев, 2 недели назад
Блог программиста © 2022

Политика конфиденциальности

Тема от WP Puzzle
?


   */
