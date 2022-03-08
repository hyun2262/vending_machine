/** 라면 주문 키오스크 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#define MAX 20 // 최대 개수 지정

struct RAMEN_INFO {
    char r_menu[10];    // 라면 메뉴
    char t_menu[10];    // 토핑 메뉴
    char w_amt[10];     // 물양 선택
    int no;             // 상품번호
    int price;          // 금액
};

typedef struct RAMEN_INFO ram;
const int basic=3000;                               // 기본금액
const int ki=500, eg=500, go=500, ch=500;           // 김치, 계란, 파, 치즈 토핑 금액

int total_cnt=MAX;                                  // 전제 재고수
int total_ki=5, total_eg=5, total_go=5, total_ch=3; // 토핑 재고수
int r_cnt=0;                                        // 라면 주문수
int total=0;                                        // 주문 총액
int sold=0;                                         // 품절 여부
int balance=0;                                      // 잔액

void order(ram *ramen, int count);                                        // 주문 입력 함수 선언
void soldout(char title[10], int cnt);                                   // 품절 안내 함수  선언
void sub_order (ram *ramen, char title[10], char topping[10], int tp);   // 메인 메뉴 입력 함수 선언
void water_amt(ram *ramen);                                               // 물양 입력 함수 선언
void print_menu(ram *ramen);                                              // 주문 메뉴 확인 함수 선언
void delete_menu(ram *ramen);                                             // 메뉴 삭제 함수 선언
void add_menu(ram *ramen);                                                // 메뉴 추가 함수 선언
void pay(ram *ramen);                                                     // 결제 함수 선언

int main()
{
    ram ramen[total_cnt]; // 라면 구조체 변수
    int menu=0, flag=0;

    printf("-------------------------------------------------------\n");
    printf("\t어서오세요! 맛있는 라면 자판기입니다!! :) \n");
    printf("-------------------------------------------------------\n");
    printf("\t주문하실 라면 개수를 입력해주세요! \n");
    printf("\t>> ");
    scanf("%d", &r_cnt);

    //최대 재고수 이상 입력시 주문개수 최대값으로 수정
    if(r_cnt>MAX){
        printf("\t현재 주문 가능한 라면은 %d개 입니다. \n", MAX);
        printf("\t라면 %d개를 주문합니다. \n", MAX);
        r_cnt = MAX;
    }

    while(!flag){
        system("cls");
        printf("-------------------------------------------------------\n");
        printf("\t실행하실 항목을 선택해주세요 \n");
        printf("-------------------------------------------------------\n");
        printf("\t1. 주문하기 \n");
        printf("\t2. 주문한 메뉴 확인하기 \n");
        printf("\t3. 메뉴 삭제하기 \n");
        printf("\t4. 메뉴 추가하기 \n");
        printf("\t5. 결제하기 \n");
        printf("\t6. 종료하기 \n");
        printf("\t>> ");
        scanf("%d", &menu);

        switch(menu){
        case 1 : //주문
            order(ramen, r_cnt);
            system("cls");
            print_menu(ramen);
            getchar();
            getchar();
            break;
        case 2 : //메뉴 확인
            system("cls");
            print_menu(ramen);
            getchar();
            getchar();
            break;
        case 3 : // 메뉴삭제
            delete_menu(ramen);
            getchar();
            getchar();
            break;
        case 4 : // 메뉴 추가
            add_menu(ramen);
            getchar();
            getchar();
            break;
        case 5 : // 결제
            pay(ramen);
            flag=1;
            break;
        case 6 :
            if(balance!=0){
                system("cls");
                printf("\t결제 완료 후 종료 가능합니다. \n");
                pay(ramen);
                flag = 1;
            }else{
            printf("\t라면 주문을 종료합니다. \n");
            flag = 1;
            }
            break;
        default :
            printf("\t다시 입력해주세요 :(");
            getchar();
            getchar();
        }
    }//end of while

    puts("\n\t\t이용해주셔서 감사합니다");
    return 0;
}

// 주문 입력 함수 정의
void order(ram *ramen, int count){
    int menu=0;
    int i=0;

    //전체 라면 재고 소진시 품절 안내
    soldout("라면", total_cnt);

    for(i=0; i<count; i++){
        system("cls");
        printf("-------------------------------------------------------\n");
        printf("\t남이 끓여줘서 더 맛있는 라면을 소개합니다! \n");
        printf("-------------------------------------------------------\n");
        printf("\t1) 기본라면 (남은재고: %2d) : 3,000원\n", total_cnt);
        printf("\t2) 김치라면 (남은재고: %2d) : 3,500원\n", total_ki);
        printf("\t3) 계란라면 (남은재고: %2d) : 3,500원\n", total_eg);
        printf("\t4) 파맛라면 (남은재고: %2d) : 3,500원\n", total_go);
        printf("\t5) 치즈라면 (남은재고: %2d) : 3,500원\n", total_ch);
        printf("\t주문하실 라면을 선택해주세요: ");
        scanf("%d", &menu);
        printf("\n");

        switch(menu){
        case 1 :
            soldout("기본라면", total_cnt);
            sub_order (&ramen[i], "기본라면", "없음", 0);
            break;
        case 2 :
            soldout("김치라면", total_ki);
            sub_order (&ramen[i], "김치라면", "김치", ki);
            break;
        case 3 :
            soldout("계란라면", total_eg);
            sub_order (&ramen[i], "계란라면", "계란", eg);
            break;
        case 4 :
            soldout("파맛라면", total_go);
            sub_order (&ramen[i], "파맛라면", "파", go);
            break;
        case 5 :
            soldout("치즈라면", total_ch);
            sub_order (&ramen[i], "치즈라면", "치즈", ch);
            break;
        default :
            printf("\t다시 입력해주세요 :( \n");
            getchar(); getchar();
        }//end of switch

        // 품절시 for문 횟수 회복
        if(sold){
            i--;
            sold=0;
        }
    }//end of for

    return;
}

// 메인 메뉴 입력 함수 정의
void sub_order (ram *ramen, char title[10], char topping[10], int tp){
    if(sold) return; // 해당 메뉴 품절시 함수 실행 취소

    strcpy(ramen->r_menu, title);
    strcpy(ramen->t_menu, topping);

    // 전체 라면 재고수 줄이기
    total_cnt--;
    // 토핑 개수가 0보다 클 때만 해당 토핑 재고 줄이기
    if(!strncmp(ramen->t_menu,"김치",2) && (total_ki>0)){
        total_ki--;
    }else if(!strncmp(ramen->t_menu,"계란",2) && (total_eg>0)){
        total_eg--;
    }else if(!strncmp(ramen->t_menu,"파",1) && (total_go>0)){
        total_go--;
    }else if(!strncmp(ramen->t_menu,"치즈",2) && (total_ch>0)){
        total_ch--;
    }
    //상품번호 두 자릿수 랜덤지정(검색용)
    srand(time(NULL));
    ramen->no = rand()%99+1;

    ramen->price = basic + tp;
    total += ramen->price;
    balance = total;
    printf("\n");

    water_amt(ramen);

    return;
}

//품절 안내 함수 정의
void soldout(char title[10], int cnt){
    if(!cnt){
        printf("\t아쉽게도 오늘 %s은(는) 품절되었어요!ㅠㅠ\n\n", title);
        sold = 1;
        getchar();
    }
    getchar();
    return;
}

// 물양 입력 함수 정의
void water_amt(ram *ramen){
    int menu=0, flag=0;

    while(!flag){
        system("cls");
        printf("-------------------------------------------------------\n");
        printf("\t\t물양을 선택해주세요! \n");
        printf("-------------------------------------------------------\n");
        printf("\t1) 조금(400ml) 2) 보통(500ml) 3)많이(600ml) \n");
        printf("\t>> ");
        scanf("%d", &menu);

        switch(menu){
        case 1:
            strcpy(ramen->w_amt, "조금");
            return;
        case 2:
            strcpy(ramen->w_amt, "보통");
            return;
        case 3:
            strcpy(ramen->w_amt, "많이");
            return;
        default:
            printf("\t다시 입력해주세요 :( \n");
            getchar(); getchar();
        }
    }
    return;
}

//주문 메뉴 확인 함수 정의
void print_menu(ram *ramen){
    int i=0;

    printf("-------------------------------------------------------\n");
    printf("\t주문하신 메뉴는 아래와 같습니다 \n");
    printf("-------------------------------------------------------\n");

    for(i=0; i<r_cnt; i++){
        if(ramen[i].price==0) continue; // 삭제된 메뉴 출력 제외

        printf("\tNO.%02d %9s (물양: %5s) %5d원 \n",
               ramen[i].no, ramen[i].r_menu, ramen[i].w_amt, ramen[i].price);
    }

    printf("------------------------------------------------------\n");
    printf("\t\t총액 : %d원 \n", total);
    return;
}

//메뉴 삭제 함수 정의
void delete_menu(ram *ramen){
    int num=0;
    int i=0, flag=0;

    system("cls");
    print_menu(ramen);

    printf("\t취소하실 메뉴번호를 입력해주세요 \n");
    printf("\t>> ");
    scanf("%d",&num);

    for(i=0; i<r_cnt; i++){
        if(ramen[i].no==num){
            // 메뉴 삭제 후 재고 회복
            total_cnt++;
            if(!strncmp(ramen[i].t_menu,"김치",2)){
                total_ki++;
            }else if(!strncmp(ramen[i].t_menu,"계란",2)){
                total_eg++;
            }else if(!strncmp(ramen[i].t_menu,"파",1)){
                total_go++;
            }if(!strncmp(ramen[i].t_menu,"치즈",2)){
                total_ch++;
            }
            // 총액 수정
            total -= ramen[i].price;

            //구조체 초기화
            strcpy(ramen[i].r_menu,"");
            strcpy(ramen[i].t_menu,"");
            strcpy(ramen[i].w_amt,"");
            ramen[i].no = 0;
            ramen[i].price = 0;
            flag = 1;
        }
    }
    if(!flag){
        printf("\t일치하는 메뉴가 없습니다.\n");
    }
    printf("\t메뉴 취소가 완료되었습니다. \n");

    return;
}

// 메뉴 추가 함수 정의
void add_menu(ram *ramen){
    //전체 라면 재고 품절시 메뉴 추가 불가 안내
    if(total_cnt<=0){
        printf("\t메뉴를 추가할 수 없습니다. \n\t다음에 이용해주세요 \n");
        return;
    }
    //라면 주문수 추가
    r_cnt++;

    printf("\t추가할 메뉴를 선택해주세요 \n");
    order(&ramen[r_cnt-1], 1);

    system("cls");
    print_menu(ramen);
    printf("\t메뉴 추가가 완료되었습니다. \n");

    return;
}

// 결제 함수 정의
void pay(ram *ramen){
    int payment=0;      // 결제수단 선택
    int money=0;        // 현금
    int total_money=0;  // 총현금
    int flag=0;

    print_menu(ramen);

    AAA:
    printf("\n\t결제수단을 선택해주세요 \n");
    printf("\t1) 현금결제  2) 카드결제\n");
    printf("\t>> ");
    scanf("%d", &payment);

    if(!(payment-1)){
        //현금결제
        while(!flag){
            printf("\t현금을 입력해주세요 \n");
            printf("\t>> ");
            scanf("%d", &money);
            total_money += money;
            //금액 부족시 추가 입력 요청
            if(total_money<total){
                balance = total - total_money; // 부족한 금액 확인
                printf("\t금액이 %d원 부족합니다. \n", balance);
            }else{
                flag=1;
            }
        }

        balance = total_money - total; // 거스름돈 확인
        printf("\n\t결제가 완료되었습니다. \n\t%d원을 반환합니다. \n", balance);
        balance = 0;
    }else if(!(payment-2)){
        //카드 결제
        printf("\t카드 받았습니다. \n");
        printf("\t결제 진행중입니다. 잠시만 기다려주세요. \n");
        Sleep(1000); // 결제 진행 중 대기
        balance=0;
        printf("\n\t결제가 완료되었습니다. \n");
    }else{
        puts("\t다시 입력해주세요.");
        goto AAA;
    }

    printf("\t잊으신 물건이 없는지 확인해주세요! \n");

    getchar();
    getchar();
    system("cls");
    printf("\n\t라면을 조리 중입니다. 잠시만 기다려 주세요★ \n");
    Sleep(500); printf("\t\t 조"); // 조리시간 중 일시정지
    Sleep(500); printf("\t 리");
    Sleep(500); printf("\t 중\n");
    Sleep(500);
    printf("\n\t\t라면이 완성되었습니다! \n ");
    printf("\t불기 전에 얼른 드세요! 좋은 하루 되세요~:) \n ");

    return;
}

