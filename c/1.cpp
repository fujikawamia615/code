#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Contact {
    int id;
    char name[50];
    char phone[12];
    char city[50];
    struct Contact *next;
} Contact;
Contact *head = NULL;

void addContact();
void deleteContact();
void changeContact();
void searchByName();
void searchByCity();
void save();
void load();
void sort();
void showContacts();
int isPhoneValid(const char *phone);
int isPhoneExist(const char *phone, int excludeId);
int isIdExist(int id);
Contact* createContact(int id, const char *name, const char *phone, const char *city);
void freeList();
int main() {
    int i;
    while (1) {
        printf("\nͨѶ¼����ϵͳ\n");
        printf("1. �����ϵ��\n");
        printf("2. ɾ����ϵ��\n");
        printf("3. �޸���ϵ��\n");
        printf("4. ��������ѯ\n");
        printf("5. �����в�ѯ\n");
        printf("6. ��ʾ������ϵ��\n");
        printf("7. ���浽�ļ�\n");
        printf("8. ���ļ���ȡ\n");
        printf("0. �˳�\n");
        printf("��ѡ�����: ");
        scanf("%d", &i);
        switch (i) {
            case 1: addContact(); break;
            case 2: deleteContact(); break;
            case 3: changeContact(); break;
            case 4: searchByName(); break;
            case 5: searchByCity(); break;
            case 6: showContacts(); break;
            case 7: save(); break;
            case 8: load(); break;
            case 0: freeList(); exit(0);
            default: printf("��Чѡ��!\n");
        }
    }
    return 0;
}
Contact* createContact(int id, const char *name, const char *phone, const char *city) {
    Contact *newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact == NULL) {
        printf("�ڴ����ʧ��!\n");
        return NULL;
    }
    newContact->id = id;
    strcpy(newContact->name, name);
    strcpy(newContact->phone, phone);
    strcpy(newContact->city, city);
    newContact->next = NULL;
    return newContact;
}
void addContact() {
    int id;
    char name[50], phone[12], city[50];
    printf("������ϵ����Ϣ:\n");
    printf("���: "); scanf("%d", &id);
    if (isIdExist(id)) {
        printf("����: ��� %d �Ѵ���!\n", id);
        return;
    }
    printf("����: "); scanf("%s", name);
    while (1) {
        printf("�ֻ���(11λ): "); scanf("%s", phone);
        if (!isPhoneValid(phone)) {
            printf("����: �ֻ��Ÿ�ʽ��Ч!\n");
        } else if (isPhoneExist(phone, -1)) {
            printf("����: �ֻ����Ѵ���!\n");
        } else {
            break;
        }
    }
    printf("����: "); scanf("%s", city);
    Contact *newContact = createContact(id, name, phone, city);
    if (newContact == NULL) return;
    if (head == NULL || head->id > id) {
        newContact->next = head;
        head = newContact;
    } else {
        Contact *current = head;
        while (current->next != NULL && current->next->id < id) {
            current = current->next;
        }
        newContact->next = current->next;
        current->next = newContact;
    }
    printf("��ϵ����ӳɹ�!\n");
}
void deleteContact() {
    if (head == NULL) {
        printf("ͨѶ¼Ϊ��!\n");
        return;
    }
    int id;
    printf("����Ҫɾ������ϵ�˱��: ");
    scanf("%d", &id);
    Contact *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("����: �Ҳ������Ϊ %d ����ϵ��!\n", id);
        return;
    }
    if (prev == NULL) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("��ϵ��ɾ���ɹ�!\n");
}
void changeContact() {
    if (head == NULL) {
        printf("ͨѶ¼Ϊ��!\n");
        return;
    }
    int id;
    printf("����Ҫ�޸ĵ���ϵ�˱��: ");
    scanf("%d", &id);
    Contact *current = head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("����: �Ҳ������Ϊ %d ����ϵ��!\n", id);
        return;
    }
    printf("��ǰ��Ϣ:\n");
    printf("���: %d, ����: %s, �ֻ���: %s, ����: %s\n",
           current->id, current->name, current->phone, current->city);
    int choice;
    printf("�޸�ѡ��:\n1. �ֻ���\n2. ����\nѡ��: ");
    scanf("%d", &choice);
    if (choice == 1) {
        char newPhone[12];
        while (1) {
            printf("�������ֻ���: ");
            scanf("%s", newPhone);
            if (!isPhoneValid(newPhone)) {
                printf("����: �ֻ��Ÿ�ʽ��Ч!\n");
            } else if (isPhoneExist(newPhone, id)) {
                printf("����: �ֻ����Ѵ���!\n");
            } else {
                strcpy(current->phone, newPhone);
                printf("�ֻ����޸ĳɹ�!\n");
                break;
            }
        }
    } else if (choice == 2) {
        printf("�����³���: ");
        scanf("%s", current->city);
        printf("�����޸ĳɹ�!\n");
    } else {
        printf("��Чѡ��!\n");
    }
}
void searchByName() {
    if (head == NULL) {
        printf("ͨѶ¼Ϊ��!\n");
        return;
    }
    char name[50];
    printf("����Ҫ��ѯ������: ");
    scanf("%s", name);
    Contact *current = head;
    int found = 0; 
    printf("��ѯ���:\n");
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("���: %d, ����: %s, �ֻ���: %s, ����: %s\n",
                   current->id, current->name, current->phone, current->city);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("δ�ҵ�ƥ�����ϵ��!\n");
    }
}
void searchByCity() {
    if (head == NULL) {
        printf("ͨѶ¼Ϊ��!\n");
        return;
    }
    char city[50];
    printf("����Ҫ��ѯ�ĳ��йؼ���: ");
    scanf("%s", city);
    Contact *current = head;
    int found = 0;
    printf("��ѯ���:\n");
    while (current != NULL) {
        if (strstr(current->city, city) != NULL) {
            printf("���: %d, ����: %s, �ֻ���: %s, ����: %s\n",
                   current->id, current->name, current->phone, current->city);
            found = 1;
        }
        current = current->next;
    }   
    if (!found) {
        printf("δ�ҵ�ƥ�����ϵ��!\n");
    }
}
void showContacts() {
    if (head == NULL) {
        printf("ͨѶ¼Ϊ��!\n");
        return;
    }
    printf("\nͨѶ¼�б�:\n");
    Contact *current = head;
    while (current != NULL) {
        printf("���: %d, ����: %s, �ֻ���: %s, ����: %s\n",
               current->id, current->name, current->phone, current->city);
        current = current->next;
    }
}
void save() {
    FILE *file = fopen("address_book.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ�!\n");
        return;
    }
    
    Contact *current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %s %s\n",
                current->id, current->name, current->phone, current->city);
        current = current->next;
    }
    
    fclose(file);
    printf("ͨѶ¼�ѱ��浽�ļ�!\n");
}
void load() {
    FILE *file = fopen("address_book.txt", "r");
    if (file == NULL) {
        printf("�ļ������ڻ��޷���!\n");
        return;
    }
    freeList();
    head = NULL;   
    int id;
    char name[50], phone[12], city[50];
    
    while (fscanf(file, "%d %s %s %s", &id, name, phone, city) != EOF) {
        Contact *newContact = createContact(id, name, phone, city);
        if (newContact == NULL) continue;
        if (head == NULL) {
            head = newContact;
        } else {
            Contact *current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newContact;
        }
    }
    
    fclose(file);
    printf("ͨѶ¼�Ѵ��ļ�����!\n");
}

// ��֤�ֻ��Ÿ�ʽ
int isPhoneValid(const char *phone) {
    
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    
    return (phone[0] == '1');
}

// ����ֻ����Ƿ���ڣ�excludeId�����޸�ʱ�ų�����
int isPhoneExist(const char *phone, int excludeId) {
    Contact *current = head;
    while (current != NULL) {
        if (strcmp(current->phone, phone) == 0 && current->id != excludeId) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// ������Ƿ����
int isIdExist(int id) {
    Contact *current = head;
    while (current != NULL) {
        if (current->id == id) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// �ͷ������ڴ�
void freeList() {
    Contact *current = head;
    while (current != NULL) {
        Contact *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
