#ifndef LIST_H_
#define LIST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*contributor information*/
typedef struct contributor_info{
	char name[21]; // 姓名
	char id_num[19]; // 身份证号
    char org[31]; // 工作单位
	char result_name[41]; // 成果名
	char gender; // 性别
	int age; // 年龄
	char job_title[16]; // 职称
	int ranking; // 成果排名
} contr_info;

typedef struct contributor_node {
	contr_info info; // 基本信息
	struct contributor_node* next; // 指向下一结点的指针
} contr_node;


/*achievement information*/
typedef struct achievement_info{
	char result_id[13]; // 成果编号
	char result_name[41]; // 成果名称
	char field[21]; // 所属技术领域
	char org[31]; // 第一完成单位
	char mvp[21]; // 第一完成人
	char price_name[31]; // 获奖名称
	char price_class[11]; // 获奖档次
	int price_ranking; // 获奖等级
	int contr_num; // 完成人员数
} achi_info;

typedef struct achievement_node {
	achi_info info; // 基本信息
	contr_node* contributors; // 完成人员链
	struct achievement_node* next; // 指向下一结点的指针
} achi_node;


/*organization information*/
typedef struct organization_info {
	char org_id[9]; // 单位名称
	char org_name[31]; // 单位编号
	char chairman[21]; // 负责人
	char phone_num[21]; // 联系电话
	int achi_num; // 成果数
	int national_achi_num; // 国家级成果数
	int provincial_achi_num; // 省级成果数
	int municipal_achi_num; // 市级成果数
} org_info;

typedef struct organization_node {
	org_info info; // 基本信息
	achi_node* achievements; // 成果链
	struct organization_node* next; // 指向下一结点的指针
} org_node;

extern org_node* org_list_head; // 一级链表头

void trimncpy(char* from, char* target, int n); // 能去除多余空格的strncpy
org_node* insert_org(char* id, char* name, char* chairman, char* phone_num); // 插入研发单位
achi_node* insert_achi(org_node* org_ptr, char* id, char* name, char* field, char* org, // 在指定单位插入成果
		char* mvp, char* price_name, char* price_class, int price_ranking);
contr_node* insert_contr(achi_node* achi_ptr, char* name, char* id, char* org, // 在指定成果插入完成人
		char* result_name, char gender, int age, char* job_title, int ranking);
char modify_org(org_node* org_ptr, char key, char* new_val); // 修改单位信息
char modify_achi(achi_node* achi_ptr, char key, char* new_val, int new_int); // 修改成果信息
char modify_contr(contr_node* contr_ptr, char key, char* new_val, int new_int); // 修改完成人信息
void delete_org(org_node* org_ptr, org_node* pre_org_ptr); // 删除指定单位
void delete_achi(achi_node* achi_ptr, achi_node* pre_achi_ptr, org_node* org_ptr); // 删除指定成果
void delete_contr(contr_node* contr_ptr, contr_node* pre_contr_ptr, achi_node* achi_ptr); // 删除指定完成人
char write_data(char* org_file, char* achi_file, char* contr_file); // 写入数据
char load_data(char* org_file, char* achi_file, char* contr_file); // 读取数据
org_node* get_org_by_name(char* org_name, org_node** pre_node); // 根据名字获取单位结点
achi_node* get_achi_by_name(char* org_name, char* achi_name, achi_node** pre_node, org_node** cur_org); // 根据名字获取成果结点
contr_node* get_contr_by_name(char* org_name, char* achi_name, // 根据名字获取完成人结点
	char* contr_name, contr_node** pre_node, achi_node** cur_achi);
int min(int a, int b); // 取最小值
int dl_distance(char* p_string1, char* p_string2); // 计算Damerau–Levenshtein distance
void sort_orgs_if_needed(org_node* cur_org, org_node* pre_org); // 需要排序时进行排序
contr_node* filter_by_age(int from, int to); // 根据年龄段过滤完成人
contr_node* filter_by_age_MVC(int from, int to); // 根据年龄段过滤第一完成人
void delete_contr_list(contr_node* head); // 删除完成人链
void delall(); // 删除整个十字交叉链表

#endif // LIST_H_
