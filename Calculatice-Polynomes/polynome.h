#include <stdlib.h>

typedef struct coef {
  int num;
  int denum;
} coeff;

typedef struct monome {
  int deg;
  coeff coef;
  struct monome *next;
} monome;

typedef struct poly {
  char nom;
  monome *monome;
  struct poly *next;
} poly;

poly *head;

poly *ft_lstlast(poly *lst);
void ft_lstadd_back(poly **alst, poly *new);
void ft_lstadd_front(poly **alst, poly *new);
int	ft_atoi1(const char *str, int *count);
int ft_atoi(const char *str, int *count, int *stop);
monome *create_mon(char *cmd, int *nmonome);
poly *find_poly(char nom);
void print_monome(monome *m, int flag);
void compterSignes(char *polynome, int *nbPlus, int *nbMoins);
void add(poly *p1, poly *p2);
void insertMonome(poly **polyr, int deg, coeff coef);

int pgcd(int a, int b) {
  if (a % b == 0)
    return b;
  return pgcd(b, a % b);
}

coeff simplifier(coeff a) {
  int n = pgcd(a.num, a.denum);
  a.denum = a.denum / n;
  a.num = a.num / n;
  if (a.denum < 0 || (a.denum < 0 && a.num < 0)) {
    a.denum = -a.denum;
    a.num = -a.num;
  }
  return a;
}

void afficher(coeff a,int debut,int deg){
    coeff tmp=simplifier(a);
    if(debut==0){

                if(tmp.denum==1){
                        if (tmp.num==-1){
                            if(deg==0)
                                printf("-1");
                            else
                                printf("-");
                            }
                        else if (tmp.num==1){
                            if(deg==0)
                                printf("+1");
                            else
                                printf("+");
                            }
                        else
                            printf("%+d",tmp.num);
                }else{
                    printf("%+d/%d",tmp.num,tmp.denum);
                }
    }else if(debut==1){
                    if(tmp.denum==1){
                            if (tmp.num==-1){
                                if(deg==0)
                                    printf("-1");
                                else
                                    printf("-");}
                            else if (tmp.num==1){
                                if(deg==0)
                                    printf("1");
                                }
                            else if(tmp.num!=-1&&tmp.num!=1)
                                printf("%d",tmp.num);
                    }else{
                        printf("%d/%d",tmp.num,tmp.denum);
                    }

                            }
}

void compterSignes(char *polynome, int *nbPlus, int *nbMoins) {
  *nbPlus = 0;
  *nbMoins = 0;
  int j = 0;

  while (polynome[j] == '+' || polynome[j] == '-') {
    j++;
  }
  for (int k = j; polynome[k] != '\0'; k++) {
    if (polynome[k] == '+') {
      (*nbPlus)++;
    } else if (polynome[k] == '-') {
      (*nbMoins)++;
    }
  }
}
