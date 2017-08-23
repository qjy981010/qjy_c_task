#include "list.h"

org_node* org_list_head = 0;

char insert_org(char* id, char* name, char* chairman, char* phone_num)
{
    org_node* it = org_list_head;
    if (org_list_head)
    {
        for (; ; )
        {
            if (!strcmp(name, it->info.org_name))
            {
                fprintf(stderr, "Organization named %s has existed!\n", name);
                return 1;
            }
            if (it->next) it = it->next;
            else break;
        }
    }
    org_node* new_node = (org_node*)malloc(sizeof(org_node));
    strncpy(new_node->info.org_id, id, 8);
    strncpy(new_node->info.org_name, name, 30);
    strncpy(new_node->info.chairman, chairman, 20);
    strncpy(new_node->info.phone_num, phone_num, 20);
    new_node->info.org_id[8] = '\0';
    new_node->info.org_name[30] = '\0';
    new_node->info.chairman[20] = '\0';
    new_node->info.phone_num[20] = '\0';
    new_node->achievements = 0;
    new_node->next = 0;
    new_node->info.achi_num = 0;
    if (org_list_head) it->next = new_node;
    else org_list_head = new_node;
    return 0;
}

char insert_achi(org_node* org_ptr, char* id, char* name, char* field,	char* org,
        char* mvp, char* price_name, char* price_class, int price_ranking)
{
    achi_node* it = org_ptr->achievements;
    if (it)
    {
        for (; ; )
        {
            if (!strcmp(name, it->info.result_name))
            {
                fprintf(stderr, "Achievement named %s has existed in %s!\n", name, org);
                return 1;
            }
            if (it->next) it = it->next;
            else break;
        }
    }
    achi_node* new_node = (achi_node*)malloc(sizeof(achi_node));
    strncpy(new_node->info.result_id, id, 12);
    strncpy(new_node->info.result_name, name, 40);
    strncpy(new_node->info.field, field, 20);
    strncpy(new_node->info.org, org, 30);
    strncpy(new_node->info.mvp, mvp, 20);
    strncpy(new_node->info.price_name, price_name, 30);
    strncpy(new_node->info.price_class, price_class, 10);
    new_node->info.result_id[12] = '\0';
    new_node->info.result_name[40] = '\0';
    new_node->info.field[20] = '\0';
    new_node->info.org[30] = '\0';
    new_node->info.mvp[20] = '\0';
    new_node->info.price_name[30] = '\0';
    new_node->info.price_class[10] = '\0';
    new_node->info.price_ranking = price_ranking;
    new_node->contributors = 0;
    new_node->next = 0;
    new_node->info.contr_num = 0;
    if (org_ptr->achievements) it->next = new_node;
    else org_ptr->achievements = new_node;
    ++org_ptr->info.achi_num;
    return 0;
}

char insert_contr(achi_node* achi_ptr, char* name, char* id, char* org,
    char* result_name, char gender, int age, char* job_title, int ranking)
{
    contr_node* it = achi_ptr->contributors;
    if (it)
    {
        for (; ; )
        {
            if (!strcmp(name, it->info.name))
            {
                fprintf(stderr, "Contributor named %s has existed in %s!\n", name, result_name);
                return 1;
            }
            if (it->next) it = it->next;
            else break;
        }
    }
    contr_node* new_node = (contr_node*)malloc(sizeof(contr_node));
    strncpy(new_node->info.name, name, 20);
    strncpy(new_node->info.id_num, id, 18);
    strncpy(new_node->info.org, org, 30);
    strncpy(new_node->info.result_name, result_name, 40);
    new_node->info.gender = gender;
    new_node->info.age = age;
    new_node->next = 0;
    strncpy(new_node->info.job_title, job_title, 15);
    new_node->info.name[20] = '\0';
    new_node->info.id_num[18] = '\0';
    new_node->info.org[30] = '\0';
    new_node->info.result_name[40] = '\0';
    new_node->info.job_title[15] = '\0';
    new_node->info.ranking = ranking;
    if (achi_ptr->contributors) it->next = new_node;
    else achi_ptr->contributors = new_node;
    ++achi_ptr->info.contr_num;
    return 0;
}

void modify_org(org_node* org_ptr, char key, char* new_val)
{
    switch (key)
    {
        case 0: strncpy(org_ptr->info.org_id, new_val, 8); break;
        case 1:
        {
                strncpy(org_ptr->info.org_name, new_val, 30);
                achi_node* achi_ptr = org_ptr->achievements;
                for (; achi_ptr; achi_ptr = achi_ptr->next)
                {
                    strncpy(achi_ptr->info.org, new_val, 30);
                    contr_node* contr_ptr = achi_ptr->contributors;
                    for (; contr_ptr; contr_ptr = contr_ptr->next)
                    {
                        strncpy(contr_ptr->info.org, new_val, 30);
                    }
                }
                break;
        }
        case 2: strncpy(org_ptr->info.chairman, new_val, 20); break;
        case 3: strncpy(org_ptr->info.phone_num, new_val, 20); break;
        default: fprintf(stderr, "Modify: Key Error!\n");
    }
}

void modify_achi(achi_node* achi_ptr, char key, char* new_val, int new_int)
{
    switch (key)
    {
        case 0: strncpy(achi_ptr->info.result_id, new_val, 12); break;
        case 1:
        {
                strncpy(achi_ptr->info.result_name, new_val, 40);
                contr_node* contr_ptr = achi_ptr->contributors;
                for (; contr_ptr; contr_ptr = contr_ptr->next)
                {
                    strncpy(contr_ptr->info.result_name, new_val, 40);
                }
                break;
        }
        case 2: strncpy(achi_ptr->info.field, new_val, 20); break;
        case 3: fprintf(stderr, "Modify: Invalid modify!\n"); break;
        case 4: strncpy(achi_ptr->info.mvp, new_val, 20); break;
        case 5: strncpy(achi_ptr->info.price_name, new_val, 30); break;
        case 6: strncpy(achi_ptr->info.price_class, new_val, 10); break;
        case 7: achi_ptr->info.price_ranking = new_int; break;
        default: fprintf(stderr, "Modify: Key Error!\n");
    }
}

void modify_contr(contr_node* contr_ptr, char key, char* new_val, int new_int)
{
    switch (key)
    {
        case 0: strncpy(contr_ptr->info.name, new_val, 20); break;
        case 1: strncpy(contr_ptr->info.id_num, new_val, 18); break;
        case 2: fprintf(stderr, "Modify: Invalid modify!\n"); break;
        case 3: fprintf(stderr, "Modify: Invalid modify!\n"); break;
        case 4: contr_ptr->info.gender = *new_val; break;
        case 5: contr_ptr->info.age = new_int; break;
        case 6: strncpy(contr_ptr->info.job_title, new_val, 15); break;
        case 7: contr_ptr->info.ranking = new_int; break;
        default: fprintf(stderr, "Modify: Key Error!\n");
    }
}

void delete_org(org_node* org_ptr, org_node* pre_org_ptr)
{
    achi_node* achi_ptr = org_ptr->achievements;
    achi_node* t_achi_ptr;
    while (achi_ptr)
    {
        contr_node* contr_ptr = achi_ptr->contributors;
        contr_node* t_contr_ptr;
        while (contr_ptr)
        {
            t_contr_ptr = contr_ptr->next;
            free(contr_ptr);
            contr_ptr = t_contr_ptr->next;
        }
        t_achi_ptr = achi_ptr->next;
        free(achi_ptr);
        achi_ptr = t_achi_ptr->next;
    }
    if (pre_org_ptr) pre_org_ptr->next = org_ptr->next;
    else org_list_head = org_ptr->next;
    free(org_ptr);
}

void delete_achi(achi_node* achi_ptr, achi_node* pre_achi_ptr, org_node* org_ptr)
{
    contr_node* contr_ptr = achi_ptr->contributors;
    contr_node* t_contr_ptr;
    while (contr_ptr)
    {
        t_contr_ptr = contr_ptr->next;
        free(contr_ptr);
        contr_ptr = t_contr_ptr->next;
    }
    if (pre_achi_ptr) pre_achi_ptr->next = achi_ptr->next;
    else org_ptr->achievements = achi_ptr->next;
    free(achi_ptr);
    --org_ptr->info.achi_num;
}

void delete_contr(contr_node* contr_ptr, contr_node* pre_contr_ptr, achi_node* achi_ptr)
{
    printf("before delete\n");
    if (pre_contr_ptr) pre_contr_ptr->next = contr_ptr->next;
    else achi_ptr->contributors = contr_ptr->next;
    printf("after delete\n");
//    free(contr_ptr);
    printf("after free\n");
    --achi_ptr->info.contr_num;
}


void write_data(char* org_file, char* achi_file, char* contr_file)
{
    FILE* fp_org = fopen(org_file, "wb");
    FILE* fp_achi = fopen(achi_file, "wb");
    FILE* fp_contr = fopen(contr_file, "wb");
    if (fp_org && fp_achi && fp_contr)
    {
        org_node* it_org_ptr = org_list_head;
        for (; it_org_ptr; it_org_ptr = it_org_ptr->next)
        {
            fwrite(&it_org_ptr->info, sizeof(org_info), 1, fp_org);
            achi_node* it_achi_ptr = it_org_ptr->achievements;
            for (; it_achi_ptr; it_achi_ptr = it_achi_ptr->next)
            {
                fwrite(&it_achi_ptr->info, sizeof(achi_info), 1, fp_achi);
                contr_node* it_contr_ptr = it_achi_ptr->contributors;
                for (; it_contr_ptr; it_contr_ptr = it_contr_ptr->next)
                {
                    fwrite(&it_contr_ptr->info, sizeof(contr_info), 1, fp_contr);
                }
            }
        }
        fclose(fp_org);
        fclose(fp_achi);
        fclose(fp_contr);
    }
    else
    {
        fprintf(stderr, "fail to save the data!\n");
    }
}

void load_data(char* org_file, char* achi_file, char* contr_file)
{
    FILE* fp_org = fopen(org_file, "rb");
    FILE* fp_achi = fopen(achi_file, "rb");
    FILE* fp_contr = fopen(contr_file, "rb");
    if (fp_org && fp_achi && fp_contr)
    {
        for (; ; )
        {
            org_node* new_org = (org_node*)malloc(sizeof(org_node));
            if (fread(&new_org->info, sizeof(org_info), 1, fp_org) != 1) break;
            new_org->next = org_list_head;
            org_list_head = new_org;
            int i = 0;
            for (; i != new_org->info.achi_num; ++i)
            {
                achi_node* new_achi = (achi_node*)malloc(sizeof(achi_node));
                fread(&new_achi->info, sizeof(achi_info), 1, fp_achi);
                new_achi->next = new_org->achievements;
                new_org->achievements = new_achi;
                int j = 0;
                for (; j != new_achi->info.contr_num; ++j)
                {
                    contr_node* new_contr = (contr_node*)malloc(sizeof(contr_node));
                    fread(&new_contr->info, sizeof(contr_info), 1, fp_contr);
                    new_contr->next = new_achi->contributors;
                    new_achi->contributors = new_contr;
                }
            }
        }
        fclose(fp_org);
        fclose(fp_achi);
        fclose(fp_contr);
    }
    else
    {
        fprintf(stderr, "fail to load the data!\n");
    }
}

org_node* get_org_by_name(char* org_name, org_node** pre_node)
{
    org_node* org_ptr = org_list_head;
    org_node* pre_org_ptr = 0;
    for (; org_ptr; pre_org_ptr = org_ptr, org_ptr = org_ptr->next)
    {
        if (!strcmp(org_name, org_ptr->info.org_name))
        {
            *pre_node = pre_org_ptr;
            return org_ptr;
        }
    }
    fprintf(stderr, "No organization named %s!\n", org_name);
    return 0;
}

achi_node* get_achi_by_name(char* org_name, char* achi_name, achi_node** pre_node, org_node** cur_org)
{
    org_node* org_ptr = org_list_head;
    for (; org_ptr; org_ptr = org_ptr->next)
    {
        if (!strcmp(org_name, org_ptr->info.org_name))
        {
            achi_node* achi_ptr = org_ptr->achievements;
            achi_node* pre_achi = 0;
            for (; achi_ptr; pre_achi = achi_ptr, achi_ptr = achi_ptr->next)
            {
                if (!strcmp(achi_name, achi_ptr->info.result_name))
                {
                    *pre_node = pre_achi;
                    *cur_org = org_ptr;
                    return achi_ptr;
                }
            }
            fprintf(stderr, "No achievement named %s in %s!\n", achi_name, org_name);
            return 0;
        }
    }
    fprintf(stderr, "No organization named %s!\n", org_name);
    return 0;
}

contr_node* get_contr_by_name(char* org_name, char* achi_name, char* contr_name, contr_node** pre_node, achi_node** cur_achi)
{
    org_node* org_ptr = org_list_head;
    for (; org_ptr; org_ptr = org_ptr->next)
    {
        if (!strcmp(org_name, org_ptr->info.org_name))
        {
            achi_node* achi_ptr = org_ptr->achievements;
            for (; achi_ptr; achi_ptr = achi_ptr->next)
            {
                if (!strcmp(achi_name, achi_ptr->info.result_name))
                {
                    contr_node* contr_ptr = achi_ptr->contributors;
                    contr_node* pre_contr = 0;
                    for (; contr_ptr; pre_contr = contr_ptr, contr_ptr = contr_ptr->next)
                    {
                        if (!strcmp(contr_name, contr_ptr->info.name))
                        {
                            *pre_node = pre_contr;
                            *cur_achi = achi_ptr;
                            return contr_ptr;
                        }
                    }
                    fprintf(stderr, "No contributor named %s in %s!\n", contr_name, achi_name);
                    return 0;
                }
            }
            fprintf(stderr, "No achievement named %s in %s!\n", achi_name, org_name);
            return 0;
        }
    }
    fprintf(stderr, "No organization named %s!\n", org_name);
    return 0;
}

int min(int a, int b)
{
    return a > b ? b : a;
}

int dl_distance(char* p_string1, char* p_string2)
{
    int l_string_length1 = strlen(p_string1);
    int l_string_length2 = strlen(p_string2);
    int d[l_string_length1+1][l_string_length2+1];

    int i, j, l_cost;

    for (i = 0; i <= l_string_length1; i++)
    {
        d[i][0] = i;
    }
    for(j = 0; j <= l_string_length2; j++)
    {
        d[0][j] = j;
    }
    for (i = 1; i <= l_string_length1; i++)
    {
        for(j = 1; j <= l_string_length2; j++)
        {
            l_cost = p_string1[i-1] == p_string2[j-1] ? 0 : 1;
            d[i][j] = min(d[i-1][j] + 1, min(d[i][j-1] + 1, d[i-1][j-1] + l_cost));
            if( i > 1 && j > 1 &&
                (p_string1[i-1] == p_string2[j-2]) &&
                (p_string1[i-2] == p_string2[j-1]))
            {
                d[i][j] = min(d[i][j], d[i-2][j-2] + l_cost);
            }
        }
    }
    return d[l_string_length1][l_string_length2];
}
