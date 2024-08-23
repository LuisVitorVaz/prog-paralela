#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, m, token = 0, ch = 0, flag = 0;

    printf("Digite o número de nós: ");
    scanf("%d", &n);

    m = n - 1;

    for (int i = 0; i < n; i++) {
        printf(" %d", i);
    }
    printf(" %d\n", 0);

    do {
        printf("Digite o remetente: ");
        int s;
        scanf("%d", &s);

        printf("Digite o destinatário: ");
        int r;
        scanf("%d", &r);

        printf("Digite os dados: ");
        int a;
        scanf("%d", &a);

        printf("Passagem de token:");
        for (int i = token, j = token; (i % n) != s; i++, j = (j + 1) % n) {
            printf(" %d->", j);
        }
        printf(" %d\n", s);

        printf("Remetente %d enviando dados: %d\n", s, a);

        for (int i = s + 1; i != r; i = (i + 1) % n) {
            printf("dados %d encaminhados por %d\n", a, i);
        }

        printf("Destinatário %d recebeu dados: %d\n\n", r, a);

        token = s;

        do {
            try {
                if (flag == 1)
                    printf("Entrada inválida!!...");
                printf("Você quer enviar novamente? Digite 1 para Sim e 0 para Não: ");
                scanf("%d", &ch);
                if (ch != 1 && ch != 0)
                    flag = 1;
                else
                    flag = 0;
            } catch (int e) {
                printf("Entrada inválida");
            }
        } while (ch != 1 && ch != 0);

    } while (ch == 1);

    return 0;
}
