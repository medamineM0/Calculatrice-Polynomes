#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

void let(char *cmd) {
  char nom = *cmd;

  int nmonome = 0;
  int nbPlus = 0;
  int nbMoins = 0;
  if (find_poly(nom) != NULL) {
    puts("This poly already exist.");

  } else {
    poly *npoly = malloc(sizeof(npoly));
    npoly->next = NULL;
    ft_lstadd_back(&head, npoly);
    npoly->nom = *cmd;
    compterSignes(cmd + 4, &nbPlus, &nbMoins);
    npoly->monome = create_mon(cmd + 4, &nmonome);
    if ((nbPlus + nbMoins) + 1 != nmonome) {
      free(npoly);
    } else {
      monome *temp = npoly->monome;
      nmonome--;
      while (temp && nmonome != 0) {
        temp = temp->next;
        nmonome--;
        if (temp == NULL) {
          free(npoly);
        }
      }
    }
    simplifyPolynomial(&npoly->monome);
  }
}

void set(char *nom) {
  char c = nom[0];
  int nmonome = 0;
  int nbPlus = 0;
  int nbMoins = 0;
  poly *polyn = head;
  while (polyn) {
    if (polyn->nom == c) {
      poly *npoly = malloc(sizeof(npoly));
      npoly->next = NULL;
      compterSignes(nom + 4, &nbPlus, &nbMoins);
      npoly->monome = create_mon(nom + 4, &nmonome);
      if ((nbPlus + nbMoins) + 1 != nmonome) {
        free(npoly);
      } else {
        monome *temp = npoly->monome;
        nmonome--;
        while (temp && nmonome != 0) {
          temp = temp->next;
          nmonome--;
          if (temp == NULL) {
            free(npoly);
          }
        }
        if (temp) {
          polyn->monome = npoly->monome;
        }
      }
      simplifyPolynomial(&polyn->monome);
      break;
    }
    polyn = polyn->next;
  }
}

void affect(char *cmd) {
  char c1 = cmd[0];
  char c2 = cmd[2];

  find_poly(c2)->monome = find_poly(c1)->monome;
}

void display(char *cmd) {
  char nom = *cmd;
  poly *poly = head;
  int nbr = 0;
  while (poly) {
    if (poly->nom == nom) {
      break;
    }
    poly = poly->next;
  }
  if (poly == NULL) {
    printf("Le polynome %c inexistant.", nom);
    puts("");
    return;
  }
  monome *monome = poly->monome;
  int k = lenlist(monome);
  printf("%c = ", nom);
  while (monome != NULL && monome->coef.num == 0) {
    nbr++;
    monome = monome->next;
  }
  if (nbr == k) {
    printf("%d", 0);
    puts("");
  } else {
    printm(monome, 1);
    puts("");
  }
}

void mul(char *cmd) {
  char nomp = *cmd;
  char nomq = *(cmd + 2);

  if (find_poly(nomp) != NULL && find_poly(nomq) != NULL) {
    poly *polyp = head;
    poly *polyq = head;

    while (polyp) {
      if (polyp->nom == nomp) {
        break;
      }
      polyp = polyp->next;
    }
    while (polyq) {
      if (polyq->nom == nomq) {
        break;
      }
      polyq = polyq->next;
    }
    poly *result = (poly *)malloc(sizeof(poly));

    result->next = NULL;
    result->monome = NULL;
    monome *monomeP = polyp->monome;

    while (monomeP != NULL) {
      monome *monomeQ = polyq->monome;

      while (monomeQ != NULL) {
        int degResult = monomeP->deg + monomeQ->deg;
        coeff coefResult;

        coefResult.num = monomeP->coef.num * monomeQ->coef.num;
        coefResult.denum = monomeP->coef.denum * monomeQ->coef.denum;
        insertMonome(&result, degResult, coefResult);
        monomeQ = monomeQ->next;
      }
      monomeP = monomeP->next;
    }
    if (result == NULL) {
      printf("Le polynome inexistant.");
      puts("");
      return;
    }
    monome *monome = result->monome;
    printf("MulResult = ");
    while (monome->coef.num == 0) {
      monome = monome->next;
    }
    printm(monome, 1);
    puts("");
    free(result);
  }
}

void ft_pow(char *cmd) {
  char nomp = *cmd;
  int count = 0;
  int n = ft_atoi1(cmd + 2, &count);

  poly *p = find_poly(nomp);

  if (p != NULL) {
    poly *result = (poly *)malloc(sizeof(poly));
    result->next = NULL;
    result->monome = NULL;

    insertMonome(&result, 0, (coeff){1, 1});

    for (int i = 0; i < n; ++i) {
      poly *temp_result = (poly *)malloc(sizeof(poly));
      temp_result->next = NULL;
      temp_result->monome = NULL;

      monome *monomeResult = result->monome;

      while (monomeResult != NULL) {
        monome *monomeP = p->monome;

        while (monomeP != NULL) {
          int degResult = monomeResult->deg + monomeP->deg;
          coeff coefResult;

          coefResult.num = monomeResult->coef.num * monomeP->coef.num;
          coefResult.denum = monomeResult->coef.denum * monomeP->coef.denum;
          insertMonome(&temp_result, degResult, coefResult);
          monomeP = monomeP->next;
        }

        monomeResult = monomeResult->next;
      }

      free(result);

      result = temp_result;
    }

    if (result->monome == NULL) {
      printf("Le polynôme résultant est inexistant.\n");
    } else {
      monome *monome = result->monome;
      printf("PowResult = ");
      while (monome->coef.num == 0) {
        monome = monome->next;
      }
      printm(monome, 1);
      puts("");
    }

    free(result);
  } else {
    printf("Le polynôme %c est inexistant.\n", nomp);
  }
}

void derivate(char *cmd) {

  char nom = *cmd;
  poly *poly = head;
  while (poly) {
    if (poly->nom == nom) {
      break;
    }
    poly = poly->next;
  }
  if (poly == NULL) {
    printf("Le polynome %c inexistant.", nom);
    puts("");
    return;
  }
  monome *tmp = poly->monome;
  while (tmp) {
    tmp->coef.num *= tmp->deg;
    tmp->deg--;
    tmp = tmp->next;
  }
}

void eval(char *cmd) {
  float s = 0;
  char nom = *cmd;
  poly *poly = head;

  while (poly) {
    if (poly->nom == nom) {
      break;
    }
    poly = poly->next;
  }
  if (poly == NULL) {
    printf("Le polynome %c inexistant.", nom);
    puts("");
    return;
  }
  monome *tmp = poly->monome;
  while (tmp != NULL) {

    s +=
        evalcoeff(tmp->coef) * power(evalcoeff(strtocoeff(cmd + 10)), tmp->deg);
    tmp = tmp->next;
  }
  printf("%f", s);
  puts("");
}

void ft_add(char *cmd) {
  char nomp = *cmd;
  char nomq = *(cmd + 2);

  int count = 0;

  poly *polyp = find_poly(nomp);
  poly *polyq = find_poly(nomq);

  if (polyp != NULL && polyq != NULL) {
    poly *result = (poly *)malloc(sizeof(poly));
    result->next = NULL;
    result->monome = NULL;

    monome *monomeP = polyp->monome;
    monome *monomeQ = polyq->monome;

    while (monomeP != NULL && monomeQ != NULL) {
      if (monomeP->deg == monomeQ->deg) {
        int degResult = monomeP->deg;
        coeff coefResult;
        if (monomeP->coef.denum == monomeQ->coef.denum) {
          coefResult.num = monomeP->coef.num + monomeQ->coef.num;
          coefResult.denum = monomeP->coef.denum;
        } else {
          coefResult.num = monomeP->coef.num * monomeQ->coef.denum +
                           monomeQ->coef.num * monomeP->coef.denum;
          coefResult.denum = monomeP->coef.denum * monomeQ->coef.denum;
        }

        insertMonome(&result, degResult, coefResult);

        monomeP = monomeP->next;
        monomeQ = monomeQ->next;
      } else if (monomeP->deg < monomeQ->deg) {
        insertMonome(&result, monomeP->deg, monomeP->coef);
        monomeP = monomeP->next;
      } else {
        insertMonome(&result, monomeQ->deg, monomeQ->coef);
        monomeQ = monomeQ->next;
      }
    }

    while (monomeP != NULL) {
      insertMonome(&result, monomeP->deg, monomeP->coef);
      monomeP = monomeP->next;
    }

    while (monomeQ != NULL) {
      insertMonome(&result, monomeQ->deg, monomeQ->coef);
      monomeQ = monomeQ->next;
    }

    if (result->monome == NULL) {
      printf("Le polynôme résultant est inexistant.\n");
    } else {
      monome *monome = result->monome;
      printf("SumResult = ");
      while (monome && monome->coef.num == 0) {
        count++;
        monome = monome->next;
      }
      if (count == lenlist(result->monome))
        printf("0");
      else
        printm(monome, 1);
      puts("");
    }

    free(result);
  } else {
    printf("Les polynômes %c et %c sont inexistants.\n", nomp, nomq);
  }
}

void sub(char *cmd) {
  char nomp = *cmd;
  char nomq = *(cmd + 2);
  int count = 0;

  poly *polyp = find_poly(nomp);
  poly *polyq = find_poly(nomq);

  if (polyp != NULL && polyq != NULL) {
    poly *result = (poly *)malloc(sizeof(poly));
    result->next = NULL;
    result->monome = NULL;

    monome *monomeP = polyp->monome;
    monome *monomeQ = polyq->monome;

    while (monomeP != NULL && monomeQ != NULL) {
      if (monomeP->deg == monomeQ->deg) {
        int degResult = monomeP->deg;
        coeff coefResult;
        if (monomeP->coef.denum == monomeQ->coef.denum) {
          coefResult.num = monomeP->coef.num - monomeQ->coef.num;
          coefResult.denum = monomeP->coef.denum;
        } else {
          coefResult.num = monomeP->coef.num * monomeQ->coef.denum -
                           monomeQ->coef.num * monomeP->coef.denum;
          coefResult.denum = monomeP->coef.denum * monomeQ->coef.denum;
        }

        insertMonome(&result, degResult, coefResult);

        monomeP = monomeP->next;
        monomeQ = monomeQ->next;
      } else if (monomeP->deg < monomeQ->deg) {
        insertMonome(&result, monomeP->deg, monomeP->coef);
        monomeP = monomeP->next;
      } else {
        coeff coef;
        coef.denum = monomeQ->coef.denum;
        coef.num = monomeQ->coef.num * -1;

      insertMonome(&result, monomeQ->deg, coef);
        monomeQ = monomeQ->next;
      }
    }

    while (monomeP != NULL) {
      insertMonome(&result, monomeP->deg, monomeP->coef);
      monomeP = monomeP->next;
    }

    while (monomeQ != NULL) {
        coeff coef;
        coef.denum = monomeQ->coef.denum;
        coef.num = monomeQ->coef.num * -1;

      insertMonome(&result, monomeQ->deg, coef);
      monomeQ = monomeQ->next;
    }

    if (result->monome == NULL) {
      printf("Le polynôme résultant est inexistant.\n");
    } else {
      monome *monome = result->monome;
      printf("SubResult = ");
      while (monome && monome->coef.num == 0) {
        count++;
        monome = monome->next;
      }
      if (count == lenlist(result->monome))
        printf("0");
      else
        printm(monome, 1);
      puts("");
    }

    free(result);
  } else {
    printf("Les polynômes %c et %c sont inexistants.\n", nomp, nomq);
  }
}

void integrate(char*cmd){

    char nom = *cmd;
    poly *poly = head;
    while(poly)
    {
        if (poly->nom == nom)
        {
            break;
        }
        poly = poly->next;
    }
    if (poly == NULL)
    {
        printf("Le polynome %c inexistant.",nom);
        puts("");
        return;
    }
    monome*tmp=poly->monome;
    while(tmp){
            if(tmp->coef.num!=0){
            tmp->coef.denum*=(tmp->deg+1);
            tmp->coef=simplifier(tmp->coef);
            tmp->deg++;
            }
            else if(tmp->coef.num==0  && tmp->deg==0){
                tmp->deg++;
            }
            tmp=tmp->next;

    }

}

void help(){

       puts("\t\tLET :pour ajouter un polynome");
       puts("\t\tSET :pour modifier un polynome");
       puts("\t\tDISPLAY :pour afficher un polynome");
       puts("\t\tADD :pour additionner deux polynome");
       puts("\t\tSUB :pour effectuer la soustraction entre deux polynome");
       puts("\t\tPOW :pour avoir la puissance d'un polynome");
       puts("\t\tMUL :pour multiplier un polynome");
       puts("\t\tDER :pour deriver un polynome");
       puts("\t\tINT :pour integrer un polynome");
       puts("\t\tEVAL :pour evaluer un polynome a une valeur");
       puts("\t\tEXIT :pour quitter le programme\n");

}

int command(char *cmd) {
  if (strncmp(cmd, "LET ", 4) == 0)
    let(cmd + 4);
  else if (strncmp(cmd, "DISPLAY ", 8) == 0)
    display(cmd + 8);
  else if (strncmp(cmd, "SET ", 4) == 0)
    set(cmd + 4);
  else if (strncmp(cmd, "AFFECT ", 7) == 0)
    affect(cmd + 7);
  else if (strncmp(cmd, "MUL ", 4) == 0)
    mul(cmd + 4);
  else if (strncmp(cmd, "POW ", 4) == 0)
    ft_pow(cmd + 4);
  else if (strncmp(cmd, "ADD ", 4) == 0)
    ft_add(cmd + 4);
  else if (strncmp(cmd, "SUB ", 4) == 0)
    sub(cmd + 4);
  else if (strncmp(cmd, "DER ", 4) == 0)
    derivate(cmd + 4);
  else if (strncmp(cmd, "INT ", 4) == 0)
      integrate(cmd + 4);
  else if (strncmp(cmd, "EVAL ", 5) == 0)
    eval(cmd + 5);
  else if (strncmp(cmd, "EXIT", 4) == 0)
    exit(0);
  else if (strncmp(cmd, "HELP", 4) == 0)
    help();
  else
    puts("commande erronee !");
  return 0;
}

int main() {
  head = NULL;
  puts("-----------------------------CALCULATRICE DE POLYNOME--------------------------------");
  puts("");
  puts("                         POUR AVOIR UNE AIDE - SAISIR HELP ;");
  puts("");
  char cmd[1000];
  printf("> ");
  while (fgets(cmd, 1000, stdin)) {
    command(cmd);
    printf("> ");
  }
}
