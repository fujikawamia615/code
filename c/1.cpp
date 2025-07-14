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
        printf("\n通讯录管理系统\n");
        printf("1. 添加联系人\n");
        printf("2. 删除联系人\n");
        printf("3. 修改联系人\n");
        printf("4. 按姓名查询\n");
        printf("5. 按城市查询\n");
        printf("6. 显示所有联系人\n");
        printf("7. 保存到文件\n");
        printf("8. 从文件读取\n");
        printf("0. 退出\n");
        printf("请选择操作: ");
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
            default: printf("无效选择!\n");
        }
    }
    return 0;
}
Contact* createContact(int id, const char *name, const char *phone, const char *city) {
    Contact *newContact = (Contact*)malloc(sizeof(Contact));
    if (newContact == NULL) {
        printf("内存分配失败!\n");
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
    printf("输入联系人信息:\n");
    printf("编号: "); scanf("%d", &id);
    if (isIdExist(id)) {
        printf("错误: 编号 %d 已存在!\n", id);
        return;
    }
    printf("姓名: "); scanf("%s", name);
    while (1) {
        printf("手机号(11位): "); scanf("%s", phone);
        if (!isPhoneValid(phone)) {
            printf("错误: 手机号格式无效!\n");
        } else if (isPhoneExist(phone, -1)) {
            printf("错误: 手机号已存在!\n");
        } else {
            break;
        }
    }
    printf("城市: "); scanf("%s", city);
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
    printf("联系人添加成功!\n");
}
void deleteContact() {
    if (head == NULL) {
        printf("通讯录为空!\n");
        return;
    }
    int id;
    printf("输入要删除的联系人编号: ");
    scanf("%d", &id);
    Contact *temp = head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("错误: 找不到编号为 %d 的联系人!\n", id);
        return;
    }
    if (prev == NULL) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("联系人删除成功!\n");
}
void changeContact() {
    if (head == NULL) {
        printf("通讯录为空!\n");
        return;
    }
    int id;
    printf("输入要修改的联系人编号: ");
    scanf("%d", &id);
    Contact *current = head;
    while (current != NULL && current->id != id) {
        current = current->next;
    }
    if (current == NULL) {
        printf("错误: 找不到编号为 %d 的联系人!\n", id);
        return;
    }
    printf("当前信息:\n");
    printf("编号: %d, 姓名: %s, 手机号: %s, 城市: %s\n",
           current->id, current->name, current->phone, current->city);
    int choice;
    printf("修改选项:\n1. 手机号\n2. 城市\n选择: ");
    scanf("%d", &choice);
    if (choice == 1) {
        char newPhone[12];
        while (1) {
            printf("输入新手机号: ");
            scanf("%s", newPhone);
            if (!isPhoneValid(newPhone)) {
                printf("错误: 手机号格式无效!\n");
            } else if (isPhoneExist(newPhone, id)) {
                printf("错误: 手机号已存在!\n");
            } else {
                strcpy(current->phone, newPhone);
                printf("手机号修改成功!\n");
                break;
            }
        }
    } else if (choice == 2) {
        printf("输入新城市: ");
        scanf("%s", current->city);
        printf("城市修改成功!\n");
    } else {
        printf("无效选择!\n");
    }
}
void searchByName() {
    if (head == NULL) {
        printf("通讯录为空!\n");
        return;
    }
    char name[50];
    printf("输入要查询的姓名: ");
    scanf("%s", name);
    Contact *current = head;
    int found = 0; 
    printf("查询结果:\n");
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("编号: %d, 姓名: %s, 手机号: %s, 城市: %s\n",
                   current->id, current->name, current->phone, current->city);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("未找到匹配的联系人!\n");
    }
}
void searchByCity() {
    if (head == NULL) {
        printf("通讯录为空!\n");
        return;
    }
    char city[50];
    printf("输入要查询的城市关键字: ");
    scanf("%s", city);
    Contact *current = head;
    int found = 0;
    printf("查询结果:\n");
    while (current != NULL) {
        if (strstr(current->city, city) != NULL) {
            printf("编号: %d, 姓名: %s, 手机号: %s, 城市: %s\n",
                   current->id, current->name, current->phone, current->city);
            found = 1;
        }
        current = current->next;
    }   
    if (!found) {
        printf("未找到匹配的联系人!\n");
    }
}
void showContacts() {
    if (head == NULL) {
        printf("通讯录为空!\n");
        return;
    }
    printf("\n通讯录列表:\n");
    Contact *current = head;
    while (current != NULL) {
        printf("编号: %d, 姓名: %s, 手机号: %s, 城市: %s\n",
               current->id, current->name, current->phone, current->city);
        current = current->next;
    }
}
void save() {
    FILE *file = fopen("address_book.txt", "w");
    if (file == NULL) {
        printf("无法打开文件!\n");
        return;
    }
    
    Contact *current = head;
    while (current != NULL) {
        fprintf(file, "%d %s %s %s\n",
                current->id, current->name, current->phone, current->city);
        current = current->next;
    }
    
    fclose(file);
    printf("通讯录已保存到文件!\n");
}
void load() {
    FILE *file = fopen("address_book.txt", "r");
    if (file == NULL) {
        printf("文件不存在或无法打开!\n");
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
    printf("通讯录已从文件加载!\n");
}

// 验证手机号格式
int isPhoneValid(const char *phone) {
    
    for (int i = 0; i < 11; i++) {
        if (!isdigit(phone[i])) return 0;
    }
    
    return (phone[0] == '1');
}

// 检查手机号是否存在（excludeId用于修改时排除自身）
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

// 检查编号是否存在
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

// 释放链表内存
void freeList() {
    Contact *current = head;
    while (current != NULL) {
        Contact *next = current->next;
        free(current);
        current = next;
    }
    head = NULL;
}
