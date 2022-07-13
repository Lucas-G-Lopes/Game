#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int shuff(int cards[]) {

  int t;
  int i;
  int desk[52];
  for (i = 0; i < 52; i++)
    desk[i] = (i / 13 + 3) * 100 + i % 13 + 1;

  srand(time(NULL));
  for (i = 0; i < 52; i++) {
    do {
      t = rand() % 52;
    } while (desk[t] == 0);
    cards[i] = desk[t];
    desk[t] = 0;
  }

  return 0;
}

int convert_jkq(int a) {
  if ((a % 100 == 11) || (a % 100 == 12) || (a % 100 == 13))
    return (a / 100) * 100 + 10;
  else
    return a;
}

void pic(int num) {
  char fl;
  int po_num;

  fl = num / 100;
  po_num = num % 100;
  switch (po_num) {
  case 1: {
    printf("*******\n");
    printf("*     *\n");
    printf("* %c   *\n", fl);
    printf("*   A *\n");
    printf("*     *\n");
    printf("*******\n");
    break;
  }
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10: {
    printf("*******\n");
    printf("*     *\n");
    printf("* %c   *\n", fl);
    printf("*  %2d *\n", po_num);
    printf("*     *\n");
    printf("*******\n");
    break;
  }
  case 11: {
    printf("*******\n");
    printf("*     *\n");
    printf("* %c   *\n", fl);
    printf("*   J *\n");
    printf("*     *\n");
    printf("*******\n");
    break;
  }
  case 12: {
    printf("*******\n");
    printf("*     *\n");
    printf("* %c   *\n", fl);
    printf("*   Q *\n");
    printf("*     *\n");
    printf("*******\n");
    break;
  }
  case 13: {
    printf("*******\n");
    printf("*     *\n");
    printf("* %c   *\n", fl);
    printf("*   K *\n");
    printf("*     *\n");
    printf("*******\n");
    break;
  }
  }
}

int play(void) {
  int i;
  int psum = 0;
  int bsum = 0;
  int pcards[5] = {0};
  int bcards[5] = {0};
  int cards[52];
  char go_on;
  char d;

  printf("----------BLACKJACK----------\n\n"
         "Pressione Enter para comecar.\n\n\n"
         "Pressione Ctrl + C para sair.\n\n");
  do {
    go_on = getchar();
  } while (go_on != '\n');
  printf("\n");

  // shuff the cards
  shuff(cards);

  // Distribuiçao das cartas
  pcards[0] = cards[0];
  pcards[1] = cards[1];
  bcards[0] = cards[2];
  bcards[1] = cards[3];

  // 2 cartas do jogador
  printf("Uma das cartas que a banca recebeu:\n");
  pic(bcards[0]);
  printf("\n");
  printf("As duas cartas que voce recebeu:\n");
  pic(pcards[0]);
  // printf("\n");
  pic(pcards[1]);
  // printf("\n");

  i = 0;
  for (i = 0; i < 2; i++) {
    if (pcards[i] % 100 == 1) {
      printf("Decida o valor de A para sua carta de numero %d, insira 'y' para 11 ou 'n' para 1:\n",
             i + 1);
      do {
        d = getchar();
      } while (d != 'y' && d != 'n');

      if (d == 'y') {
        printf("Voce escolheu 11 para o valor de A.\n");
        psum = psum + 11;
      } else if (d == 'n') {
        printf("Voce escolheu 1 para o valor de A.\n");
        psum = psum + 1;
      }
    } else if (convert_jkq(pcards[i]) % 100 == 10)
      psum = psum + 10;
    else
      psum = psum + pcards[i] % 100;

    if (psum > 21) {
      printf("Soma do valor das suas cartas: %d\n\n", psum);
      printf("A banca venceu!\n");
      return 1;
    } else if (psum == 21) {
      printf("Soma do valor das suas cartas: %d\n\n", psum);
      printf("Voce venceu!\n");
      return 0;
    }
  }
  printf("Soma do valor das suas cartas: %d\n\n", psum);

  // Quando o jogador recebe mais uma carta
  i = 0;
  for (i = 0; i < 3; i++) {
    char j = 'n';

    printf("Deseja receber mais uma carta? Insira 'y' para SIM ou 'n' para NAO:\n");
    do {
      j = getchar();
    } while (j != 'y' && j != 'n');

    if (j == 'y') {
      printf("Voce decidiu receber outra carta.\n");
      pcards[i + 2] = cards[i + 4];
      printf("Aqui esta ela, sua carta de numero %d:\n", i + 3);
      pic(pcards[i + 2]);

      if (pcards[i + 2] % 100 == 1) {
        printf(
            "Decida o valor de A para sua carta de numero %d, insira 'y' para 11 ou 'n' para 1:\n",
            i + 3);
        do {
          d = getchar();
        } while (d != 'y' && d != 'n');
        if (d == 'y') {
          printf("Voce escolheu 11 para o valor de A.\n");
          psum = psum + 11;
        } else if (d == 'n') {
          printf("Voce escolheu 1 para o valor de A.\n");
          psum = psum + 1;
        }
      } else if (convert_jkq(pcards[i + 2]) % 100 == 10)
        psum = psum + 10;
      else
        psum = psum + pcards[i + 2] % 100;

      if (psum > 21) {
        printf("Soma do valor das suas cartas: %d\n\n", psum);
        printf("A banca venceu!\n");
        return 1;
      } else if (psum == 21) {
        printf("Soma do valor das suas cartas: %d\n\n", psum);
        printf("Voce venceu!\n");
        return 0;
      } else
        printf("Soma do valor das suas cartas: %d\n\n", psum);
    } else {
      printf("Soma do valor das suas cartas: %d\n\n", psum);
      break;
    }
  }
  if (i == 3) {
    printf("Voce venceu! Pois o valor da soma das suas 5 cartas e menor que 21!"
           "Que sorte hein!\n");
    return 0;
  }

  // As duas cartas da banca
  // i = 0;
  printf("As cartas da banca:\n");
  pic(bcards[0]);
  pic(bcards[1]);

  if (bcards[0] % 100 + bcards[1] % 100 == 2) {
    bsum = 12; // As duas cartas A
    printf("Soma do valor das cartas da banca: %d\n\n", bsum);
  } else if ((convert_jkq(bcards[0])) % 100 + (convert_jkq(bcards[1])) % 100 ==
             1) {
    bsum = 21;
    printf("Soma do valor das cartas da banca: %d\n\n", bsum);
    printf("A banca venceu!\n");
    return 1;
  } else if (bcards[0] % 100 == 1 || bcards[1] % 100 == 1) {
    bsum = (bcards[0] + bcards[1]) % 100 + (rand() % 2) * 10;
    printf("Soma do valor das cartas da banca: %d\n\n", bsum);
  } else {
    bsum = (convert_jkq(bcards[0])) % 100 + (convert_jkq(bcards[1])) % 100;
    printf("Soma do valor das cartas da banca: %d\n\n", bsum);
  }

  // Se a banca decidira receber outra carta ate que bsum > 16
  // i = 0;
  for (i = 0; i < 3 && bsum < 17; i++) {
    bcards[i + 2] = cards[i + 7];
    printf("A carta da banca de numero %d e:\n", i + 3);
    pic(bcards[i + 2]);

    if (bcards[i + 2] % 100 == 1) {
      if (bsum + 11 <= 21) {
        printf("A banca escolheu A como 11\n");
        bsum = bsum + 11;
        printf("Soma do valor das cartas da banca: %d\n\n", bsum);
      } else {
        printf("A banca escolheu A como 1\n");
        bsum = bsum + 1;
        printf("Soma do valor das cartas da banca: %d\n\n", bsum);
      }
    } else {
      bsum = bsum + convert_jkq(bcards[i + 2]) % 100;
      printf("Soma do valor das cartas da banca: %d\n\n", bsum);
    }
  }
  if (i == 3) {
    printf("A banca venceu! Pois o valor da soma das 5 cartas dela e menor que 21!"
           "Que azar hein!\n");
    return 1;
  }

  // Decisao
  if (bsum > 21 || psum > bsum) {
    printf("Voce venceu!\n");
    return 0;
  } else if (psum == bsum) {
    printf("Empate!\n");
    return 3;
  } else if (psum < bsum) {
    printf("A banca venceu!\n");
    return 1;
  }

  return 3;
}

int main(void) {
  char again;

  play();

  //Replay
  printf("\nJogar novamente? Insira 'y' para SIM ou 'n' para NAO:\n");
  do {
    again = getchar();
  } while (again != 'y' && again != 'n');

  if (again == 'y') {
    printf("\nVamos la!\n\n");
    main();
  }

  return 0;
}