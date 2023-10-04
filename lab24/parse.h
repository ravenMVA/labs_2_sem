#include "parse.h"

// Функция для создания узла дерева
node* create_node(token type, char op, int val, char var, bool minus) {
    node* n = (node*)malloc(sizeof(node));
    n->type = type;
    n->oper = op;
    n->minus = minus;
    n->val = val;
    n->var = var;
    n->l_ch = NULL;
    n->r_ch = NULL;
    n->next = NULL;
    return n;
}

// =============== ОЧЕРЕДЬ =================
// Функция для создания очереди
queue* create_queue() {
    queue* q = (queue*)malloc(sizeof(queue));
    q->back = NULL;
    q->front = NULL;
    return q;
}

// Функция для добавления узла в очередь
void enqueue(queue* q, node* n) {
    n->next = NULL; // Инициализируем указатель на следующий узел нового узла
    if (q->back == NULL) {
        // Если очередь пуста, устанавливаем и back, и front на новый узел
        q->back = n;
        q->front = n;
    } else {
        // Если очередь не пуста, обновляем указатель на следующий узел текущего последнего элемента
        q->back->next = n;
        // Обновляем указатель back на новый узел
        q->back = n;
    }
}

// Функция для извлечения узла из очереди
node* dequeue(queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    // Получаем узел из начала очереди
    node* node = q->front;
    // Обновляем указатель front на следующий узел
    q->front = node->next;
    // Если очередь становится пустой, также обновляем указатель back
    if (q->front == NULL) {
        q->back = NULL;
    }
    // Возвращаем извлеченный узел
    return node;
}

// Функция для удаления очереди
void delete_queue(queue* q) {
    if (q == NULL) {
        return;
    }

    while (q->front != NULL) {
        node* temp = q->front;   // Получаем узел из начала очереди
        q->front = q->front->next; // Перемещаем указатель front к следующему узлу
        free(temp); // Освобождаем память удаляемого узла
    }

    // После удаления всех узлов обязательно устанавливаем back в NULL
    q->back = NULL;
}
// ==========================================

// Функция, которая анализирует строку выражения
// и преобразует ее в очередь обратной польской записи (!)
queue* parse(char* str, int l) {
    char tokens[MAX_SIZE];
    int t_idx = 0;
    queue* q = create_queue();
    char s[MAX_SIZE]; // СТЕК
    int s_top = -1;

    for (int i = 0; i < l; i++) {
        char c = str[i];
        bool unary_minus = false;

        if (isdigit(c)) { // ЕСЛИ ЧИСЛО
            int num = 0;
            // Продолжаем считывать символы, пока не встретится нецифровой символ
            while (i < l && isdigit(str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            i--; // Уменьшаем итератор, чтобы не пропустить символ после числа

            // Есть ли унарный минус?
            if (t_idx > 0 && tokens[t_idx - 1] == '-') {
                if (t_idx - 2 == -1 || tokens[t_idx - 2] == '(') {
                    s_top--; // Убираем унарный минус из стека
                    unary_minus = true;
                }
            }

            node* node = create_node(NUMBER, ' ', num, ' ', unary_minus);
            enqueue(q, node);

            tokens[t_idx++] = 'v'; // 'v' - значит значение (число или переменная)
        }
        else if (isalpha(c)) { // ЕСЛИ ПЕРЕМЕННАЯ
            // Есть ли унарный минус?
            if (t_idx > 0 && tokens[t_idx - 1] == '-') {
                if (t_idx - 2 == -1 || tokens[t_idx - 2] == '(' ) {
                    s_top--; // Убираем унарный минус из стека
                    unary_minus = true;
                }
            }

            node* node = create_node(VARIABLE, ' ', 0, c, unary_minus);
            enqueue(q, node);

            tokens[t_idx++] = 'v'; // 'v' - значит значение (число или переменная)
        }
        else { // ЕСЛИ ОПЕРАТОР
            char op = str[i];
            if (op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')') {
                tokens[t_idx++] = op; // Добавляем оператор в токены
            }
            switch (op) {
                case '+':
                case '-':
                    // Обрабатываем операторы + и -
                    while (s_top >= 0 &&
                          (s[s_top] == '+' || s[s_top] == '-' 
                           || s[s_top] == '*' || s[s_top] == '/')) 
                    {
                        // Извлекаем операторы из стека и добавляем их в очередь
                        node* op_node = create_node(OPERATOR, s[s_top], 0, ' ', unary_minus);
                        enqueue(q, op_node);
                        s_top--;
                    }
                    // Помещаем текущий оператор в стек
                    s_top++;
                    s[s_top] = op;
                    break;
                case '*':
                case '/':
                    // Обрабатываем операторы * и /
                    while (s_top >= 0 
                          && (s[s_top] == '*' || s[s_top] == '/')) 
                    {
                        // Извлекаем операторы из стека и добавляем их в очередь
                        node* op_node = create_node(OPERATOR, s[s_top], 0, ' ', unary_minus);
                        enqueue(q, op_node);
                        s_top--;
                    }
                    // Помещаем текущий оператор в стек
                    s_top++;
                    s[s_top] = op;
                    break;
                case '(':
                    s_top++;
                    s[s_top] = op;
                    break;
                case ')':
                    while (s_top >= 0 && (s[s_top] != '(')) {
                        node* op_node = create_node(OPERATOR, s[s_top], 0, ' ', unary_minus);
                        enqueue(q, op_node);
                        s_top--;
                    }
                    s_top--; // Убираем открывающую скобку
                    break;
                default:
                    
                    break;
            }
        }
    }
    // Перекладываем остальные операторы
    while (s_top >= 0) {
        if (s[s_top] != '(') {
            node* op_node = create_node(OPERATOR, s[s_top], 0, ' ', false);
            enqueue(q, op_node);
        }
        s_top--;
    }
    return q;
}

// Функция для добавления узлов в дерево
node* add_to_tree(node* n, queue* q) {
    if (n == NULL) {
        return NULL;
    }
    if (n->type == NUMBER || n->type == VARIABLE) {
        return n;
    }
    node* temp = n;
    temp->l_ch = add_to_tree(dequeue(q), q);
    temp->r_ch = add_to_tree(dequeue(q), q);
    return temp;
}

// Функция для создания синтаксического дерева
tree* create_tree(queue* q) {
    // РАЗВОРАЧИВАЕМ ОЧЕРЕДЬ
    queue* reverse_q = create_queue();
    node* stack[MAX_SIZE];
    int top = -1;
    while (q->front != NULL) {
        top++;
        stack[top] = dequeue(q);
    }
    while (top >= 0) {
        enqueue(reverse_q, stack[top]);
        top--;
    }
    // ======================
    tree* t = (tree*)malloc(sizeof(tree));
    t->root = dequeue(reverse_q);
    t->root->l_ch = add_to_tree(dequeue(reverse_q), reverse_q);
    t->root->r_ch = add_to_tree(dequeue(reverse_q), reverse_q);

    return t;
}

// Функция для печати дерева в отформатированном виде
void print_tree(node* root, int n) {
    if (root == NULL) {
        return;
    }
    print_tree(root->r_ch, n + 1);
    for (int i = 0; i < n; i++) printf("    ");
    print_node(root);
    printf("\n");
    print_tree(root->l_ch, n + 1);
}

// функция для вывода дерева в форматированном виде
void print_node(node* n) {
    char minus;
    if (n->minus) {
        minus = '-';
    } else {
        minus = ' ';
    }
    switch (n->type) {
        case NUMBER:
            printf("%c%d ", minus, n->val);
            break;
        case VARIABLE:
            printf("%c%c ", minus, n->var);
            break;
        case OPERATOR:
            if (n->minus) {
                printf("-(%c) ", n->oper);
            } else {
                printf("%c ", n->oper);
            }
            break;
        // Обрабатываем другие типы, если необходимо
        default:
            // Обрабатываем недопустимый тип или предоставляем соответствующую обработку ошибок
            break;
    }
}

// Функция для сокращения минусов в дереве
bool reduce_minuses(node* root) {
    if (root->type == NUMBER || root->type == VARIABLE) {
        return root->minus;
    }
    if (root->oper == '*') {
        bool unary = (reduce_minuses(root->l_ch) + reduce_minuses(root->r_ch)) % 2;
        root->minus = unary;
        root->l_ch->minus = false;
        root->r_ch->minus = false;
        return unary;
    }
    reduce_minuses(root->l_ch);
    reduce_minuses(root->r_ch);
    return false;
}

// Функция для инфиксного представления дерева
char* infix(node* root) {
    char* str = (char*)malloc(MAX_SIZE);

    if (root->type == NUMBER) {
        if (root->minus) {
            sprintf(str, "(-%d)", root->val);
            return str;
        }
        sprintf(str, "%d", root->val);
        return str;
    }
    if (root->type == VARIABLE) {
        if (root->minus) {
            sprintf(str, "(-%d)", root->val);
            return str;
        }
        sprintf(str, "%c", root->var);
        return str;
    }

    char* left = infix(root->l_ch);
    char* right = infix(root->r_ch);
    char op = root->oper;

    if (root->minus) {
        sprintf(str, "-(%s %c %s)", left, op, right);
    } else if (op == '-' || op == '+') {
        sprintf(str, "(%s %c %s)", left, op, right);
    } else {
        sprintf(str, "%s %c %s", left, op, right);
    }
    
    free(left);
    free(right);

    return str;
}

// Функция для освобождения узла и его детей
void free_node(node* n) {
    if (n == NULL) {
        return;
    }
    if (n->l_ch != NULL)
        free_node(n->l_ch);
    if (n->r_ch != NULL)
        free_node(n->r_ch);
    free(n);
}

// Функция для освобождения дерева
void delete_tree(tree* t) {
    free_node(t->root);
    t->root = NULL;
}
