#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*contributor information*/
typedef struct contributor_info{
	char name[21];
	char id_num[19];
    char org[31];
	char result_name[41];
	char gender;
	int age;
	char job_title[16];
	int ranking;
} contr_info;

typedef struct contributor_node {
	contr_info info;
	struct contributor_node* next;
} contr_node;


/*achievement information*/
typedef struct achievement_info{
	char result_id[13];
	char result_name[41];
	char field[21];
	char org[31];
	char mvp[21];
	char price_name[31];
	char price_class[11];
	int price_ranking;
	int contr_num;
} achi_info;

typedef struct achievement_node {
	achi_info info;
	contr_node* contributors;
	struct achievement_node* next;
} achi_node;


/*organization information*/
typedef struct organization_info {
	char org_id[9];
	char org_name[31];
	char chairman[21];
	char phone_num[21];
	int achi_num;
} org_info;

typedef struct organization_node {
	org_info info;
	achi_node* achievements;
	struct organization_node* next;
} org_node;

extern org_node* org_list_head;

char insert_org(char* id, char* name, char* chairman, char* phone_num);
char insert_achi(org_node* org_ptr, char* id, char* name, char* field, char* org,
		char* mvp, char* price_name, char* price_class, int price_ranking);
char insert_contr(achi_node* achi_ptr, char* name, char* id, char* org,
		char* result_name, char gender, int age, char* job_title, int ranking);
char insert_achi_node(achi_node* new_node, char* new_val);
char insert_contr_node(contr_node* new_node, org_node* org, char* new_val);;
void modify_org(org_node* org_ptr, char key, char* new_val);
void modify_achi(achi_node* achi_ptr, char key, char* new_val, int new_int);
void modify_contr(contr_node* contr_ptr, char key, char* new_val, int new_int);
void delete_org(org_node* org_ptr, org_node* pre_org_ptr);
void delete_achi(achi_node* achi_ptr, achi_node* pre_achi_ptr, org_node* org_ptr);
void delete_contr(contr_node* contr_ptr, contr_node* pre_contr_ptr, achi_node* achi_ptr);
void write_data(char* org_file, char* achi_file, char* contr_file);
void load_data(char* org_file, char* achi_file, char* contr_file);
org_node* get_org_by_name(char* org_name, org_node** pre_node);
achi_node* get_achi_by_name(char* org_name, char* achi_name, achi_node** pre_node, org_node** cur_org);
contr_node* get_contr_by_name(char* org_name, char* achi_name, char* contr_name, contr_node** pre_node, achi_node** cur_achi);
int min(int a, int b);
int dl_distance(char* p_string1, char* p_string2);

#endif
