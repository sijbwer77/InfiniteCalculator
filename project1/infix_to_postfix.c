#include <stdio.h>

#define MAX 100

struct CharStack {
    char data[MAX];  // 문자 배열
    int top;         // 스택 가장 위쪽
};

void initStack(struct CharStack *s) {
    s->top = -1;
}

int isEmpty(struct CharStack *s) {
    return s->top == -1;
}

// 문자 data에 추가
void push(struct CharStack *s, char value) {
    (s->top)++;
    s->data[s->top]=value;
}

// 문자 꺼내기
char pop(struct CharStack *s) {
    return s->data[(s->top)--];
}

//가장 위의 데이터 확인
char topChar(struct CharStack *s) {
    return s->data[s->top];
}

// 연산자 우선순위
int precedence(char op) {
    if (op == '(') return 0;
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

// 아스키코드로 숫자인지 연산자인지 판단하는 함수
int isDigit(char c) {
    return '9' >= c && c >= '0'; //0보다 크고 9보다 작아야 숫자임
}

void infixToPostfix(char *infix, char *postfix) {
    struct CharStack s;
    initStack(&s);
    int j = 0; //postfix 인덱스

    for (int i = 0; infix[i] != '\0'; i++) {  // infix[] 길이동안 반복함.
        char c = infix[i];

        if (isDigit(c)) {  // 피연산자 처리 (숫자)
            while (isDigit(infix[i])) {
                postfix[j] = infix[i]; //숫자면 바로출력함
                j++;
                i++;
            }
            i--;  // 숫자 끝까지 읽었으니 인덱스를 하나 줄임
        } else if (c == '(') {
            push(&s, c);
        } else if (c == ')') {
            // '('를 만날 때까지 스택에서 꺼내기
            while (topChar(&s) != '(') {
                postfix[j] = pop(&s);
                j++;
            }
            pop(&s);  // '(' 제거
        } else {
            while (!isEmpty(&s) && precedence(topChar(&s)) >= precedence(c)) {
                postfix[j] = pop(&s);
                j++;
            }
            push(&s, c);
        }
    }

    // 남은 연산자 모두 추가
    while (!isEmpty(&s)) {
        postfix[j] = pop(&s);
        j++;
    }
    postfix[j] = '\0';  // 문자열 끝
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("수식을 입력하세요: ");
    scanf("%s", infix);  // 예: 3+4*(2+13)

    infixToPostfix(infix, postfix);
    printf("후위 표기식: %s\n", postfix);

    return 0;
}
