/** ��� �ֹ� Ű����ũ */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#define MAX 20 // �ִ� ���� ����

struct RAMEN_INFO {
    char r_menu[10];    // ��� �޴�
    char t_menu[10];    // ���� �޴�
    char w_amt[10];     // ���� ����
    int no;             // ��ǰ��ȣ
    int price;          // �ݾ�
};

typedef struct RAMEN_INFO ram;
const int basic=3000;                               // �⺻�ݾ�
const int ki=500, eg=500, go=500, ch=500;           // ��ġ, ���, ��, ġ�� ���� �ݾ�

int total_cnt=MAX;                                  // ���� ����
int total_ki=5, total_eg=5, total_go=5, total_ch=3; // ���� ����
int r_cnt=0;                                        // ��� �ֹ���
int total=0;                                        // �ֹ� �Ѿ�
int sold=0;                                         // ǰ�� ����
int balance=0;                                      // �ܾ�

void order(ram *ramen, int count);                                        // �ֹ� �Է� �Լ� ����
void soldout(char title[10], int cnt);                                   // ǰ�� �ȳ� �Լ�  ����
void sub_order (ram *ramen, char title[10], char topping[10], int tp);   // ���� �޴� �Է� �Լ� ����
void water_amt(ram *ramen);                                               // ���� �Է� �Լ� ����
void print_menu(ram *ramen);                                              // �ֹ� �޴� Ȯ�� �Լ� ����
void delete_menu(ram *ramen);                                             // �޴� ���� �Լ� ����
void add_menu(ram *ramen);                                                // �޴� �߰� �Լ� ����
void pay(ram *ramen);                                                     // ���� �Լ� ����

int main()
{
    ram ramen[total_cnt]; // ��� ����ü ����
    int menu=0, flag=0;

    printf("-------------------------------------------------------\n");
    printf("\t�������! ���ִ� ��� ���Ǳ��Դϴ�!! :) \n");
    printf("-------------------------------------------------------\n");
    printf("\t�ֹ��Ͻ� ��� ������ �Է����ּ���! \n");
    printf("\t>> ");
    scanf("%d", &r_cnt);

    //�ִ� ���� �̻� �Է½� �ֹ����� �ִ밪���� ����
    if(r_cnt>MAX){
        printf("\t���� �ֹ� ������ ����� %d�� �Դϴ�. \n", MAX);
        printf("\t��� %d���� �ֹ��մϴ�. \n", MAX);
        r_cnt = MAX;
    }

    while(!flag){
        system("cls");
        printf("-------------------------------------------------------\n");
        printf("\t�����Ͻ� �׸��� �������ּ��� \n");
        printf("-------------------------------------------------------\n");
        printf("\t1. �ֹ��ϱ� \n");
        printf("\t2. �ֹ��� �޴� Ȯ���ϱ� \n");
        printf("\t3. �޴� �����ϱ� \n");
        printf("\t4. �޴� �߰��ϱ� \n");
        printf("\t5. �����ϱ� \n");
        printf("\t6. �����ϱ� \n");
        printf("\t>> ");
        scanf("%d", &menu);

        switch(menu){
        case 1 : //�ֹ�
            order(ramen, r_cnt);
            system("cls");
            print_menu(ramen);
            getchar();
            getchar();
            break;
        case 2 : //�޴� Ȯ��
            system("cls");
            print_menu(ramen);
            getchar();
            getchar();
            break;
        case 3 : // �޴�����
            delete_menu(ramen);
            getchar();
            getchar();
            break;
        case 4 : // �޴� �߰�
            add_menu(ramen);
            getchar();
            getchar();
            break;
        case 5 : // ����
            pay(ramen);
            flag=1;
            break;
        case 6 :
            if(balance!=0){
                system("cls");
                printf("\t���� �Ϸ� �� ���� �����մϴ�. \n");
                pay(ramen);
                flag = 1;
            }else{
            printf("\t��� �ֹ��� �����մϴ�. \n");
            flag = 1;
            }
            break;
        default :
            printf("\t�ٽ� �Է����ּ��� :(");
            getchar();
            getchar();
        }
    }//end of while

    puts("\n\t\t�̿����ּż� �����մϴ�");
    return 0;
}

// �ֹ� �Է� �Լ� ����
void order(ram *ramen, int count){
    int menu=0;
    int i=0;

    //��ü ��� ��� ������ ǰ�� �ȳ�
    soldout("���", total_cnt);

    for(i=0; i<count; i++){
        system("cls");
        printf("-------------------------------------------------------\n");
        printf("\t���� �����༭ �� ���ִ� ����� �Ұ��մϴ�! \n");
        printf("-------------------------------------------------------\n");
        printf("\t1) �⺻��� (�������: %2d) : 3,000��\n", total_cnt);
        printf("\t2) ��ġ��� (�������: %2d) : 3,500��\n", total_ki);
        printf("\t3) ������ (�������: %2d) : 3,500��\n", total_eg);
        printf("\t4) �ĸ���� (�������: %2d) : 3,500��\n", total_go);
        printf("\t5) ġ���� (�������: %2d) : 3,500��\n", total_ch);
        printf("\t�ֹ��Ͻ� ����� �������ּ���: ");
        scanf("%d", &menu);
        printf("\n");

        switch(menu){
        case 1 :
            soldout("�⺻���", total_cnt);
            sub_order (&ramen[i], "�⺻���", "����", 0);
            break;
        case 2 :
            soldout("��ġ���", total_ki);
            sub_order (&ramen[i], "��ġ���", "��ġ", ki);
            break;
        case 3 :
            soldout("������", total_eg);
            sub_order (&ramen[i], "������", "���", eg);
            break;
        case 4 :
            soldout("�ĸ����", total_go);
            sub_order (&ramen[i], "�ĸ����", "��", go);
            break;
        case 5 :
            soldout("ġ����", total_ch);
            sub_order (&ramen[i], "ġ����", "ġ��", ch);
            break;
        default :
            printf("\t�ٽ� �Է����ּ��� :( \n");
            getchar(); getchar();
        }//end of switch

        // ǰ���� for�� Ƚ�� ȸ��
        if(sold){
            i--;
            sold=0;
        }
    }//end of for

    return;
}

// ���� �޴� �Է� �Լ� ����
void sub_order (ram *ramen, char title[10], char topping[10], int tp){
    if(sold) return; // �ش� �޴� ǰ���� �Լ� ���� ���

    strcpy(ramen->r_menu, title);
    strcpy(ramen->t_menu, topping);

    // ��ü ��� ���� ���̱�
    total_cnt--;
    // ���� ������ 0���� Ŭ ���� �ش� ���� ��� ���̱�
    if(!strncmp(ramen->t_menu,"��ġ",2) && (total_ki>0)){
        total_ki--;
    }else if(!strncmp(ramen->t_menu,"���",2) && (total_eg>0)){
        total_eg--;
    }else if(!strncmp(ramen->t_menu,"��",1) && (total_go>0)){
        total_go--;
    }else if(!strncmp(ramen->t_menu,"ġ��",2) && (total_ch>0)){
        total_ch--;
    }
    //��ǰ��ȣ �� �ڸ��� ��������(�˻���)
    srand(time(NULL));
    ramen->no = rand()%99+1;

    ramen->price = basic + tp;
    total += ramen->price;
    balance = total;
    printf("\n");

    water_amt(ramen);

    return;
}

//ǰ�� �ȳ� �Լ� ����
void soldout(char title[10], int cnt){
    if(!cnt){
        printf("\t�ƽ��Ե� ���� %s��(��) ǰ���Ǿ����!�Ф�\n\n", title);
        sold = 1;
        getchar();
    }
    getchar();
    return;
}

// ���� �Է� �Լ� ����
void water_amt(ram *ramen){
    int menu=0, flag=0;

    while(!flag){
        system("cls");
        printf("-------------------------------------------------------\n");
        printf("\t\t������ �������ּ���! \n");
        printf("-------------------------------------------------------\n");
        printf("\t1) ����(400ml) 2) ����(500ml) 3)����(600ml) \n");
        printf("\t>> ");
        scanf("%d", &menu);

        switch(menu){
        case 1:
            strcpy(ramen->w_amt, "����");
            return;
        case 2:
            strcpy(ramen->w_amt, "����");
            return;
        case 3:
            strcpy(ramen->w_amt, "����");
            return;
        default:
            printf("\t�ٽ� �Է����ּ��� :( \n");
            getchar(); getchar();
        }
    }
    return;
}

//�ֹ� �޴� Ȯ�� �Լ� ����
void print_menu(ram *ramen){
    int i=0;

    printf("-------------------------------------------------------\n");
    printf("\t�ֹ��Ͻ� �޴��� �Ʒ��� �����ϴ� \n");
    printf("-------------------------------------------------------\n");

    for(i=0; i<r_cnt; i++){
        if(ramen[i].price==0) continue; // ������ �޴� ��� ����

        printf("\tNO.%02d %9s (����: %5s) %5d�� \n",
               ramen[i].no, ramen[i].r_menu, ramen[i].w_amt, ramen[i].price);
    }

    printf("------------------------------------------------------\n");
    printf("\t\t�Ѿ� : %d�� \n", total);
    return;
}

//�޴� ���� �Լ� ����
void delete_menu(ram *ramen){
    int num=0;
    int i=0, flag=0;

    system("cls");
    print_menu(ramen);

    printf("\t����Ͻ� �޴���ȣ�� �Է����ּ��� \n");
    printf("\t>> ");
    scanf("%d",&num);

    for(i=0; i<r_cnt; i++){
        if(ramen[i].no==num){
            // �޴� ���� �� ��� ȸ��
            total_cnt++;
            if(!strncmp(ramen[i].t_menu,"��ġ",2)){
                total_ki++;
            }else if(!strncmp(ramen[i].t_menu,"���",2)){
                total_eg++;
            }else if(!strncmp(ramen[i].t_menu,"��",1)){
                total_go++;
            }if(!strncmp(ramen[i].t_menu,"ġ��",2)){
                total_ch++;
            }
            // �Ѿ� ����
            total -= ramen[i].price;

            //����ü �ʱ�ȭ
            strcpy(ramen[i].r_menu,"");
            strcpy(ramen[i].t_menu,"");
            strcpy(ramen[i].w_amt,"");
            ramen[i].no = 0;
            ramen[i].price = 0;
            flag = 1;
        }
    }
    if(!flag){
        printf("\t��ġ�ϴ� �޴��� �����ϴ�.\n");
    }
    printf("\t�޴� ��Ұ� �Ϸ�Ǿ����ϴ�. \n");

    return;
}

// �޴� �߰� �Լ� ����
void add_menu(ram *ramen){
    //��ü ��� ��� ǰ���� �޴� �߰� �Ұ� �ȳ�
    if(total_cnt<=0){
        printf("\t�޴��� �߰��� �� �����ϴ�. \n\t������ �̿����ּ��� \n");
        return;
    }
    //��� �ֹ��� �߰�
    r_cnt++;

    printf("\t�߰��� �޴��� �������ּ��� \n");
    order(&ramen[r_cnt-1], 1);

    system("cls");
    print_menu(ramen);
    printf("\t�޴� �߰��� �Ϸ�Ǿ����ϴ�. \n");

    return;
}

// ���� �Լ� ����
void pay(ram *ramen){
    int payment=0;      // �������� ����
    int money=0;        // ����
    int total_money=0;  // ������
    int flag=0;

    print_menu(ramen);

    AAA:
    printf("\n\t���������� �������ּ��� \n");
    printf("\t1) ���ݰ���  2) ī�����\n");
    printf("\t>> ");
    scanf("%d", &payment);

    if(!(payment-1)){
        //���ݰ���
        while(!flag){
            printf("\t������ �Է����ּ��� \n");
            printf("\t>> ");
            scanf("%d", &money);
            total_money += money;
            //�ݾ� ������ �߰� �Է� ��û
            if(total_money<total){
                balance = total - total_money; // ������ �ݾ� Ȯ��
                printf("\t�ݾ��� %d�� �����մϴ�. \n", balance);
            }else{
                flag=1;
            }
        }

        balance = total_money - total; // �Ž����� Ȯ��
        printf("\n\t������ �Ϸ�Ǿ����ϴ�. \n\t%d���� ��ȯ�մϴ�. \n", balance);
        balance = 0;
    }else if(!(payment-2)){
        //ī�� ����
        printf("\tī�� �޾ҽ��ϴ�. \n");
        printf("\t���� �������Դϴ�. ��ø� ��ٷ��ּ���. \n");
        Sleep(1000); // ���� ���� �� ���
        balance=0;
        printf("\n\t������ �Ϸ�Ǿ����ϴ�. \n");
    }else{
        puts("\t�ٽ� �Է����ּ���.");
        goto AAA;
    }

    printf("\t������ ������ ������ Ȯ�����ּ���! \n");

    getchar();
    getchar();
    system("cls");
    printf("\n\t����� ���� ���Դϴ�. ��ø� ��ٷ� �ּ���� \n");
    Sleep(500); printf("\t\t ��"); // �����ð� �� �Ͻ�����
    Sleep(500); printf("\t ��");
    Sleep(500); printf("\t ��\n");
    Sleep(500);
    printf("\n\t\t����� �ϼ��Ǿ����ϴ�! \n ");
    printf("\t�ұ� ���� �� �弼��! ���� �Ϸ� �Ǽ���~:) \n ");

    return;
}

