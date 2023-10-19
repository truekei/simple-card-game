#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

struct card{
    char type[7];
    unsigned int attack;
    struct card *next, *prev;
}drawDeck[16];

int drawIndex = 0;

void printDeck(struct card *head){
    struct card *ptr = head;
    int pos = 1;
    while(ptr != NULL){
        puts("=================");
        printf("%d  %-7s\n\n", pos, ptr->type);
        printf("Attack Power: %u\n", ptr->attack);
        puts("=================\n");
        ptr = ptr->next;
        pos++;
    }
}
void shuffle(struct card *deck){
    struct card temp;
    int ranNum, i;
    for(i = 0; i < 16; i++){
        ranNum = rand() % 16;
        temp = deck[i];
        deck[i] = deck[ranNum];
        deck[ranNum] = temp;
    }
}
void drawCard(struct card **head, struct card **tail){
    struct card *ptr;
    int i;
    for(i = 1; i <= 5; i++){
        if(i == 1){
            *tail = (struct card*) malloc(sizeof(struct card));
            *head = *tail;
            (*tail)->next = NULL;
            (*tail)->prev = NULL;
        } else{
            ptr = (struct card*) malloc(sizeof(struct card));
            (*tail)->next = ptr;
            ptr->prev = *tail;
            *tail = ptr;
            (*tail)->next = NULL;
        }
        strcpy((*tail)->type, drawDeck[drawIndex].type);
        (*tail)->attack = drawDeck[drawIndex].attack;
        drawIndex = (drawIndex+1) % 16;
    }

}
struct card *placeCard(struct card **head, struct card **tail, char pos){
    struct card *ptr = *head;
    char c = '1';
    while(ptr != NULL){
        if(c == pos){ // jika sudah di posisi kartu yang ingin ditaruh
            if(ptr->prev == NULL && ptr->next == NULL){ // jika hanya ada satu kartu
                *head = *tail = NULL;
            } else if(ptr->prev == NULL){               // jika kartu berada paling kiri
                *head = ptr->next;
                (*head)->prev = NULL;
            } else if(ptr->next == NULL){               // jika kartu berada paling kanan
                *tail = ptr->prev;
                (*tail)->next = NULL;
            } else{                                     // jika kartu berada di tengah2
                ptr->prev->next = ptr->next;
                ptr->next->prev = ptr->prev;
            }
            ptr->next = ptr->prev = NULL;
            return ptr;
        }
        c++;
        ptr = ptr->next;
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    struct card *head_1 = NULL, *tail_1, *head_2 = NULL, *tail_2, *card_1, *card_2, *ptr, *del;
    int damage, i, j, n, pil;
    int round = 1, hp_default = 25, hp_1 = hp_default, hp_2 = hp_default;
    char pick;
    unsigned int attack[] = {1,2,3,4};
    char type[][7] = {"Fire", "Nature", "Earth", "Water"};
    n = 0;

    // menyiapkan kartu di draw deck
    for(i = 0; i < 4; i++){
        for(j = 0; j < 4; j++){
            drawDeck[n].attack = attack[j];
            strcpy(drawDeck[n].type, type[i]);
            n++;
        }
    }

    // menu awal
    while(1){
        puts(" |||CARD GAME|||");
        puts("||||MAIN MENU||||\n\n1.Mulai Game\n2.Opsi\n3.Keluar");
        printf("Masukkan Input: ")	;
        scanf ("%d",&pil);
        fflush(stdin);
        switch(pil){
            case 1:
                // shuffle draw deck
                shuffle(drawDeck);

                // draw awal
                drawCard(&head_1, &tail_1);
                drawCard(&head_2, &tail_2);

                while(1){
                    system("cls");
                    printf("------------ RONDE %d ------------\n\n", round);
                    if(head_1 == NULL || head_2 == NULL){
                        drawCard(&head_1, &tail_1);
                        drawCard(&head_2, &tail_2);
                        puts("5 kartu telah dibagikan kepada kedua PLAYER dari Draw Deck\n");
                    }
                    puts("Tekan [ENTER] jika PLAYER 1 sudah siap bermain.");
                    getchar();

                    // pick kartu player 1
                    system("cls");
                    puts("DECK PLAYER 1:\n");
                    printDeck(head_1);
                    printf("HP: ");
                    for(i = 1; i <= hp_1; i++) printf("|");
                    printf(" (%d)\n\n\n", hp_1);
                    puts("Pilih kartu yang ingin dimainkan sesuai urutan dengan menekan angka 1-5 pada keyboard.");
                    while(1){
                        pick = getch();
                        card_1 = placeCard(&head_1, &tail_1, pick);
                        if(card_1 == NULL) puts("Kartu tidak ditemukan, mohon input ulang");
                        else break;
                    }
                    system("cls");
                    puts("Tekan [ENTER] jika PLAYER 2 sudah siap bermain.");
                    getchar();

                    // pick kartu player 2
                    system("cls");
                    puts("DECK PLAYER 2:\n");
                    printDeck(head_2);
                    printf("HP: ");
                    for(i = 1; i <= hp_2; i++) printf("|");
                    printf(" (%d)\n\n\n", hp_2);
                    puts("Pilih kartu yang ingin dimainkan sesuai urutan dengan menekan angka 1-5 pada keyboard.");
                    while(1){
                        pick = getch();
                        card_2 = placeCard(&head_2, &tail_2, pick);
                        if(card_2 == NULL) puts("Kartu tidak ditemukan, mohon input ulang");
                        else break;
                    }
                    system("cls");
                    printDeck(card_1);
                    puts("\tVS\n");
                    printDeck(card_2);

                    // PENGHITUNGAN ATTACK POWER
                    if((!strcmp(card_1->type, "Fire")) && (!strcmp(card_2->type, "Nature"))){           // fire -> nature
                        card_1->attack = card_1->attack * 2;
                    } else if((!strcmp(card_1->type, "Nature")) && (!strcmp(card_2->type, "Earth"))){   // nature -> earth
                        card_1->attack = card_1->attack * 2;
                    } else if((!strcmp(card_1->type, "Earth")) && (!strcmp(card_2->type, "Water"))){    // earth -> water
                        card_1->attack = card_1->attack * 2;
                    } else if((!strcmp(card_1->type, "Water")) && (!strcmp(card_2->type, "Fire"))){     // water -> fire
                        card_1->attack = card_1->attack * 2;
                    } else if((!strcmp(card_1->type, "Nature")) && (!strcmp(card_2->type, "Fire"))){    // nature -> fire
                        card_2->attack = card_2->attack * 2;
                    } else if((!strcmp(card_1->type, "Fire")) && (!strcmp(card_2->type, "Water"))){     // fire -> water
                        card_2->attack = card_2->attack * 2;
                    } else if((!strcmp(card_1->type, "Water")) && (!strcmp(card_2->type, "Earth"))){    // water -> earth
                        card_2->attack = card_2->attack * 2;
                    } else if((!strcmp(card_1->type, "Earth")) && (!strcmp(card_2->type, "Nature"))){   // earth -> nature
                        card_2->attack = card_2->attack * 2;
                    }

                    if(card_1->attack > card_2->attack){ // pengurangan HP player 2
                        damage = card_1->attack - card_2->attack;
                        printf("Kartu PLAYER 1 menyerang PLAYER 2 dengan total damage: %d\n", damage);
                        hp_2 -= damage;
                        printf("Sisa HP PLAYER 2: ");
                        if(hp_2 > 0){
                            for(i = 1; i <= hp_2; i++) printf("|");
                            printf(" (%d)\n", hp_2);
                            puts("\nTekan [ENTER] untuk melanjutkan.");
                            getchar();
                        } else{
                            puts("0");
                        }
                    } else if(card_1->attack < card_2->attack){ // pengurangan HP player 1
                        damage = card_2->attack - card_1->attack;
                        printf("Kartu PLAYER 2 menyerang PLAYER 1 dengan total damage: %d\n", damage);
                        hp_1 -= damage;
                        printf("Sisa HP PLAYER 1: ");
                        if(hp_1 > 0){
                            for(i = 1; i <= hp_1; i++) printf("|");
                            printf(" (%d)\n", hp_1);
                            puts("\nTekan [ENTER] untuk melanjutkan.");
                            getchar();
                        } else{
                            puts("0");
                        }
                    } else{
                        printf("Ronde Seri. Tidak ada HP PLAYER yang berkurang\n");
                        puts("\nTekan [ENTER] untuk melanjutkan.");
                        getchar();
                    }
                    free(card_1);
                    free(card_2);
                    if(hp_1 <= 0){
                        puts("\nPLAYER 2 berhasil mengalahkan PLAYER 1!\n");
                        break;
                    } else if(hp_2 <= 0){
                        puts("\nPLAYER 1 berhasil mengalahkan PLAYER 2!\n");
                        break;
                    }
                    round++;
                }

                // RESET GAME
                // pembersihan deck player 1
                del = head_1;
                do{
                    ptr = del->next;
                    free(del);
                    del = ptr;

                } while(del != NULL);
                head_1 = NULL;

                // pembersihan deck player 2
                del = head_2;
                do{
                    ptr = del->next;
                    free(del);
                    del = ptr;

                } while(del != NULL);
                head_2 = NULL;

                // reset hp dan round
                hp_1 = hp_2 = hp_default;
                round = 1;

                puts("\nTekan [ENTER] untuk melanjutkan.");
                getchar();
                system("cls");
                break;
            case 2:
                printf("Masukan HP yang akan digunakan: ");
			    scanf("%d", &hp_default);
			    fflush(stdin);
                hp_1 = hp_2 = hp_default;
			    puts("HP berhasil diubah.");

                puts("\nTekan [ENTER] untuk melanjutkan.");
                getchar();
                system("cls");
                break;
            case 3: return 0;
            default: puts("Pilihan Tidak Ada");
        }
    }
    return 0;
}

/*
    FINAL PROJECT STRUKTUR DATA
    PROGRAM PERMAINAN KARTU (MENGGUNAKAN KONSEP DOUBLE LINKED LIST)
    OLEH:
    1. I WAYAN ADHI SURYA GEMILANG  (2108561039)
    2. KADEK DWITYA ADHI PRADYTO    (2108561082)
*/
