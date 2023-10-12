#include "parse.h"

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
queue* create_queue() {
    queue* q = (queue*)malloc(sizeof(queue));
    q->back = NULL;
    q->front = NULL;
    return q;
}

// Function to enqueue a node
void enqueue(queue* q, node* n) {
    n->next = NULL; // Initialize the next pointer of the new node
    if (q->back == NULL) {
        // If the queue is empty, set both back and front pointers to the new node
        q->back = n;
        q->front = n;
    } else {
        // If the queue is not empty, update the next pointer of the current last element
        q->back->next = n;
        // Update the back pointer of the queue to point to the new node
        q->back = n;
    }
}

node* dequeue(queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    // Get the front node
    node* node = q->front;
    // Update the front pointer to the next node
    q->front = node->next;
    // If the queue becomes empty, update the back pointer as well
    if (q->front == NULL) {
        q->back = NULL;
    }
    // Return the dequeued node
    return node;
}

void delete_queue(queue* q) {
    if (q == NULL) {
        return;
    }

    while (q->front != NULL) {
        node* temp = q->front;   // Get the front node
        q->front = q->front->next; // Move front to the next node
        free(temp); // Free the memory of the deleted node
    }

    // After deleting all nodes, make sure to set back to NULL
    q->back = NULL;
}
// ==========================================

// Функция, которая парсит строку выражения
// и переводит в очередь обратной польской записи (!)
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
            // Continue reading characters until a non-digit character is encountered
            while (i < l && isdigit(str[i])) {
                num = num * 10 + (str[i] - '0');
                i++;
            }
            i--; // Уменьшаем итератор чтобы не пропустить символ после числа

            // Есть ли унарный минус?
            if (t_idx > 0 && tokens[t_idx - 1] == '-') {
                if (t_idx - 2 == -1 || tokens[t_idx - 2] == '(') {
                    s_top--; // Убираем унарный минус из стека
                    unary_minus = true;
                }
            }

            node* node = create_node(NUMBER, ' ', num, ' ', unary_minus);
            enqueue(q, node);

            tokens[t_idx++] = 'v'; // 'v' - значит value (число или переменная)
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

            tokens[t_idx++] = 'v'; // 'v' - значит value (число или переменная)
        }
        else { // ЕСЛИ ОПЕРАТОР
            char op = str[i];
            if (op == '+' || op == '-' || op == '*' || op == '/' || op == '(' || op == ')') {
                tokens[t_idx++] = op; // Добавляем оператор в токены
            }
            switch (op) {
                case '+':
                case '-':
                    // Process + and - operators
                    while (s_top >= 0 &&
                          (s[s_top] == '+' || s[s_top] == '-' 
                           || s[s_top] == '*' || s[s_top] == '/')) 
                    {
                        // Pop operators from the s and enqueue them
                        node* op_node = create_node(OPERATOR, s[s_top], 0, ' ', unary_minus);
                        enqueue(q, op_node);
                        s_top--;
                    }
                    // Push the current operator onto the s
                    s_top++;
                    s[s_top] = op;
                    break;
                case '*':
                case '/':
                    // Process * and / operators
                    while (s_top >= 0 
                          && (s[s_top] == '*' || s[s_top] == '/')) 
                    {
                        // Pop operators from the s and enqueue them
                        node* op_node = create_node(OPERATOR, s[s_top], 0, ' ', unary_minus);
                        enqueue(q, op_node);
                        s_top--;
                    }
                    // Push the current operator onto the s
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
                    s_top--; // Убираем открывающуюся скобку
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


// Function to add nodes to the tree
node* add_to_tree(node* n, queue* q) {
    if (n == NULL) {
        return NULL;
    }
    if (n->type == NUMBER || n->type == VARIABLE) {
        return n;
    }
    node* temp = n;
    temp->r_ch = add_to_tree(dequeue(q), q);
    temp->l_ch = add_to_tree(dequeue(q), q);
    return temp;
}

// Function to build the syntax tree
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
    t->root->r_ch = add_to_tree(dequeue(reverse_q), reverse_q);
    t->root->l_ch = add_to_tree(dequeue(reverse_q), reverse_q);
free(reverse_q);
    return t;
}

// Function to print the tree in a formatted manner
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
        // Handle other types if needed
        default:
            // Handle invalid type or provide appropriate error handling
            break;
    }
}

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

// Function to free a node and its children
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

// Function to free the tree
void delete_tree(tree* t) {
    free_node(t->root);
    t->root = NULL;
    free(t);
}
