#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "polynome.h"

poly	*ft_lstlast(poly *lst)
{
    while (lst && lst->next) {
        lst = lst->next;
    }
    return lst;
}

void	ft_lstadd_back(poly **alst, poly *new)
{
	poly	*last;

	if (alst)
	{
		if (*alst)
		{
			last = ft_lstlast(*alst);
			last->next = new;
		}
		else
			*alst = new;
	}
}

int	ft_atoi1(const char *str, int *count)
{
	int	num=0;
	int	i=0;
	int	sign=1;
    int nbr = 0;


	if (str[i] == '+' || str[i] == '-')
    {
		if (str[i++] == '-')
			sign = -1;
        nbr++;
    }
    while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
        nbr++;
	}
    *count = nbr;
	return (sign * num);
}

int	ft_atoi(const char *str, int *count, int *stop)
{
	int	num;
	int	i;
	int	sign;
    int nbr = 0;

	sign = 1;
	i = 0;
	num = 0;

	if (str[i] == '+' || str[i] == '-')
    {
		if (str[i++] == '-')
			sign = -1;
        nbr++;
    }
    if (!(str[i] >= '0' && str[i] <= '9'))
    {
        *stop = 1;
    }
    while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
        nbr++;
	}
    if (str[i] != '\n' && (str[i] != 'X' && str[i] != '/' && str[i] != '+' && str[i] != '-'))
    {
        *stop = 1;
    }
    *count = nbr;
	return (sign * num);
}

monome *create_mon(char *cmd, int *nmonome)
{
    if (*cmd == '\n')
        return NULL;
    if (*cmd == '\f' || *cmd == '\r' || *cmd == '\t' || *cmd == ' ')
        return NULL;
    int count = 0;
    int stop = 0;
    monome *mon = malloc(sizeof(monome));
    (*nmonome)++;
    mon->coef.num = 1;
    mon->coef.denum = 1;
    mon->deg = 0;
    if (*cmd == '-' && *(cmd + 1) == 'X')
    {
        mon->coef.num = -1;
        cmd++;
    }
    if (*cmd == '+' && *(cmd + 1) == 'X')
    {
        mon->coef.num = +1;
        cmd++;
    }
    if (*cmd != 'X')
    {

        // mon->coef.num = 1;
        mon->coef.num = ft_atoi(cmd, &count, &stop);
        if (stop == 1)
            return NULL;
        cmd += count;
        if (*cmd == '\f' || *cmd == '\r' || *cmd == '\t' || *cmd == ' ')
            return NULL;
        if (*cmd == '/')
        {
            cmd++;
            if (*cmd == '\f' || *cmd == '\r' || *cmd == '\t' || *cmd == ' ')
                return NULL;
            mon->coef.denum = ft_atoi(cmd, &count, &stop);
            if (stop == 1)
                return NULL;
            cmd += count;
        }
    }
    if (*cmd == 'X')
    {
        mon->deg = 1;
        cmd++;
        if (*cmd == '\f' || *cmd == '\r' || *cmd == '\t' || *cmd == ' ')
            return NULL;
        if (*cmd == '^')
        {
            cmd++;
            if (*cmd == '\f' || *cmd == '\r' || *cmd == '\t' || *cmd == ' ')
                return NULL;
            mon->deg = ft_atoi(cmd, &count, &stop);
            if (stop == 1)
                return NULL;
            cmd += count;
            if (*cmd == '\f' || *cmd == '\r' || *cmd == '\t' || *cmd == ' ')
                return NULL;
        }
    }
    mon->next = create_mon(cmd, nmonome);
    return mon;
}

poly *find_poly(char nom)
{
    poly *poly = head;
    while(poly)
    {
        if (poly->nom == nom)
        {
            break;
        }
        poly = poly->next;
    }
    return poly;
}

// void print_monome(monome *m, int flag)
// {
//     if (m->coef.num == 1 || m->coef.num == -1)
//     {
//         if (m->deg == 0)
//             printf("%d",m->coef.num);
//         else
//         {
//             if (flag)
//                 printf("+");
//             else
//                 printf("-");
//         }
//     }
//     else
//     {
//         if (flag)
//             printf("%d",m->coef.num);
//         else
//             printf("%+d",m->coef.num);
//     }
//     if (m->coef.denum != 1)
//         printf("%d",m->coef.denum);
//     if (m->deg != 0)
//     {
//         if (m->deg == 1)
//             printf("X");
//         else
//             printf("X^%d",m->deg);
//     }
//     print_monome(m->next, 0);
// }



void printm(monome*m,int debut){
        if(m==NULL)
        {
            return;
        }
        else{
            if(m->coef.num!=0){

                if(m->deg==0){

                afficher(m->coef,debut,m->deg);


                }else if(m->deg==1){

                    afficher(m->coef,debut,m->deg);

                    printf("X");

                }else{

                    afficher(m->coef,debut,m->deg);

                    printf("X^%d",m->deg);

                    }
                             }
            }
                printm(m->next,0);

}

void print_monome(monome *monome, int flag)
{
    if (monome == NULL)
        return ;
    if (monome->coef.num == -1 && monome->coef.denum == 1 && monome->deg == 1)
        printf("-");
    if (monome->coef.num == 1 && monome->coef.denum == 1 && monome->deg == 1 && flag == 0)
        printf("+");
    if (monome->coef.num == -1 && monome->coef.denum == 1 && monome->deg == 0)
        printf("%d",monome->coef.num);
    if (monome->coef.num == 1 && monome->coef.denum == 1 && monome->deg == 0)
    {
        if (flag)
            printf("%d",monome->coef.num);
        else
            printf("%+d",monome->coef.num);
    }
    if((monome->coef.num != 1 && monome->coef.num != -1) || monome->coef.denum != 1)
    {
        if (flag)
            printf("%d", monome->coef.num);
        else
            printf("%+d", monome->coef.num);
    }
    if(monome->coef.denum != 1)
    {
        printf("/%d", monome->coef.denum);
    }
    if(monome->deg != 0)
    {
        printf("X");
        if (monome->deg != 1)
        {
            printf("^%d", monome->deg);
        }

    }
    print_monome(monome->next, 0);
}

void insertMonome(poly **polyr, int deg, coeff coef) {
    monome *newMonome = (monome *)malloc(sizeof(monome));
    newMonome->deg = deg;
    newMonome->coef = coef;
    newMonome->next = NULL;

    if ((*polyr)->monome == NULL) {
        (*polyr)->monome = newMonome;
    } else {
        monome *current = (*polyr)->monome;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = newMonome;
    }
}

int lenlist(monome*m){
    if(m==NULL){
        return 0;
    }
    return 1+lenlist(m->next);

}

coeff strtocoeff(char*cmd){
    coeff res;
    res.num=1;
    res.denum=1;
    int count=0;
    res.num = ft_atoi1(cmd, &count);
    cmd += count;
    if (*cmd == '/')
    {
        cmd++;
        res.denum = ft_atoi1(cmd, &count);
    }
    return res;
}

float power(float a,int n)
{   float pow=1.00000;
    for(int i=0;i<n;i++)
    {
        pow=pow*a;
    }
    return pow;
}

float evalcoeff(coeff a){
    return ((float)a.num/(float)a.denum);
}

void simplifyPolynomial(monome **head) {
    if (*head == NULL || (*head)->next == NULL) {
        return;
    }

    monome *result = NULL;
    monome *current = *head;
    int *processedDegrees = NULL;
    int processedDegreesCount = 0;

    while (current != NULL) {
        int degreeProcessed = 0;
        for (int i = 0; i < processedDegreesCount; ++i) {
            if (processedDegrees[i] == current->deg) {
                degreeProcessed = 1;
                break;
            }
        }

        if (!degreeProcessed) {
            processedDegrees = realloc(processedDegrees, (processedDegreesCount + 1) * sizeof(int));
            processedDegrees[processedDegreesCount] = current->deg;
            processedDegreesCount++;

            monome *next = current->next;

            while (next != NULL) {
                if (next->deg == current->deg) {
                    current->coef.num += next->coef.num;
                    monome *temp = next;
                    next = next->next;
                    free(temp);
                } else {
                    next = next->next;
                }
            }

            monome *newMonome = (monome *)malloc(sizeof(monome));
            newMonome->deg = current->deg;
            newMonome->coef = current->coef;
            newMonome->next = NULL;

            if (result == NULL) {
                result = newMonome;
            } else {
                monome *merged = result;
                while (merged->next != NULL) {
                    merged = merged->next;
                }
                merged->next = newMonome;
            }
        }

        current = current->next;
    }

    free(processedDegrees);
    free(*head);
    *head = result;
}
