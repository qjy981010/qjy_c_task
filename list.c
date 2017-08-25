#include "list.h"

org_node* org_list_head = 0;

void trimncpy(char* target, char* from, int n)
{
    char* it = from;
    char* targetit = target;
    char* end = target + n - 1;
    for (; (*it == ' ' || *it == '\n' || *it == '\t') && *it != '\0'; ++it);
    for (; *it != '\0' && targetit < end; ++targetit)
    {
        if (*it == ' ' || *it == '\n' || *it == '\t')
        {
            for (; (*it == ' ' || *it == '\n' || *it == '\t') && *it != '\0'; ++it);
            if (*it) *targetit = ' ';
            else break;
        }
        else
        {
            *targetit = *it;
            ++it;
        }
    }
    *targetit = '\0';
}

org_node* insert_org(char* id, char* name, char* chairman, char* phone_num)
{
    org_node* it = org_list_head;
    if (org_list_head)
    {
        for (; ; )
        {
            if (!strcmp(name, it->info.org_name))
            {
                fprintf(stderr, "Organization named %s has existed!\n", name);
                return 0;
            }
            if (it->next) it = it->next;
            else break;
        }
    }
    org_node* new_node = (org_node*)malloc(sizeof(org_node));
    trimncpy(new_node->info.org_id, id, 9);
    trimncpy(new_node->info.org_name, name, 31);
    trimncpy(new_node->info.chairman, chairman, 21);
    trimncpy(new_node->info.phone_num, phone_num, 21);
    new_node->achievements = 0;
    new_node->next = 0;
    new_node->info.achi_num = 0;
    new_node->info.national_achi_num = 0;
    new_node->info.provincial_achi_num = 0;
    new_node->info.municipal_achi_num = 0;
    if (org_list_head) it->next = new_node;
    else org_list_head = new_node;
    return new_node;
}

achi_node* insert_achi(org_node* org_ptr, char* id, char* name, char* field,  char* org,
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
                return 0;
            }
            if (it->next) it = it->next;
            else break;
        }
    }
    achi_node* new_node = (achi_node*)malloc(sizeof(achi_node));
    trimncpy(new_node->info.result_id, id, 13);
    trimncpy(new_node->info.result_name, name, 41);
    trimncpy(new_node->info.field, field, 21);
    trimncpy(new_node->info.org, org, 31);
    trimncpy(new_node->info.mvp, mvp, 21);
    trimncpy(new_node->info.price_name, price_name, 31);
    trimncpy(new_node->info.price_class, price_class, 11);
    new_node->info.price_ranking = price_ranking;
    new_node->contributors = 0;
    new_node->next = 0;
    new_node->info.contr_num = 0;
    if (org_ptr->achievements) it->next = new_node;
    else org_ptr->achievements = new_node;
    if (*price_class == 'N') ++org_ptr->info.national_achi_num;
    else if (*price_class == 'P') ++org_ptr->info.provincial_achi_num;
    else if (*price_class == 'M') ++org_ptr->info.municipal_achi_num;
    ++org_ptr->info.achi_num;
    return new_node;
}

contr_node* insert_contr(achi_node* achi_ptr, char* name, char* id, char* org,
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
                return 0;
            }
            if (it->next) it = it->next;
            else break;
        }
    }
    contr_node* new_node = (contr_node*)malloc(sizeof(contr_node));
    trimncpy(new_node->info.name, name, 21);
    trimncpy(new_node->info.id_num, id, 19);
    trimncpy(new_node->info.org, org, 31);
    trimncpy(new_node->info.result_name, result_name, 41);
    new_node->info.gender = gender;
    new_node->info.age = age;
    trimncpy(new_node->info.job_title, job_title, 16);
    new_node->info.ranking = ranking;
    new_node->next = 0;
    if (achi_ptr->contributors) it->next = new_node;
    else achi_ptr->contributors = new_node;
    ++achi_ptr->info.contr_num;
    return new_node;
}

char modify_org(org_node* org_ptr, char key, char* new_val)
{
    switch (key)
    {
        case 0: trimncpy(org_ptr->info.org_id, new_val, 9); return 1;
        case 1:
        {
                trimncpy(org_ptr->info.org_name, new_val, 31);
                achi_node* achi_ptr = org_ptr->achievements;
                for (; achi_ptr; achi_ptr = achi_ptr->next)
                {
                    trimncpy(achi_ptr->info.org, new_val, 31);
                    contr_node* contr_ptr = achi_ptr->contributors;
                    for (; contr_ptr; contr_ptr = contr_ptr->next)
                    {
                        trimncpy(contr_ptr->info.org, new_val, 31);
                    }
                }
                return 1;
        }
        case 2: trimncpy(org_ptr->info.chairman, new_val, 21); return 1;
        case 3: trimncpy(org_ptr->info.phone_num, new_val, 21); return 1;
        case 4: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        case 5: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        case 6: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        case 7: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        default: fprintf(stderr, "Modify: Key Error!\n"); return 0;
    }
}

char modify_achi(achi_node* achi_ptr, char key, char* new_val, int new_int)
{
    switch (key)
    {
        case 0: trimncpy(achi_ptr->info.result_id, new_val, 13); return 1;
        case 1:
        {
                trimncpy(achi_ptr->info.result_name, new_val, 41);
                contr_node* contr_ptr = achi_ptr->contributors;
                for (; contr_ptr; contr_ptr = contr_ptr->next)
                {
                    trimncpy(contr_ptr->info.result_name, new_val, 41);
                }
                return 1;
        }
        case 2: trimncpy(achi_ptr->info.field, new_val, 21); return 1;
        case 3: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        case 4: trimncpy(achi_ptr->info.mvp, new_val, 21); return 1;
        case 5: trimncpy(achi_ptr->info.price_name, new_val, 31); return 1;
        case 6: trimncpy(achi_ptr->info.price_class, new_val, 11); return 1;
        case 7: achi_ptr->info.price_ranking = new_int; return 2;
        case 8: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        default: fprintf(stderr, "Modify: Key Error!\n"); return 0;
    }
}

char modify_contr(contr_node* contr_ptr, char key, char* new_val, int new_int)
{
    switch (key)
    {
        case 0: trimncpy(contr_ptr->info.name, new_val, 21); return 1;
        case 1: trimncpy(contr_ptr->info.id_num, new_val, 19); return 1;
        case 2: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        case 3: fprintf(stderr, "Modify: Invalid modify!\n"); return 0;
        case 4: contr_ptr->info.gender = *new_val; return 1;
        case 5: contr_ptr->info.age = new_int; return 2;
        case 6: trimncpy(contr_ptr->info.job_title, new_val, 16); return 1;
        case 7: contr_ptr->info.ranking = new_int; return 2;
        default: fprintf(stderr, "Modify: Key Error!\n"); return 0;
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
    if (*achi_ptr->info.price_class == 'N') --org_ptr->info.national_achi_num;
    else if (*achi_ptr->info.price_class == 'P') --org_ptr->info.provincial_achi_num;
    else if (*achi_ptr->info.price_class == 'M') --org_ptr->info.municipal_achi_num;
    free(achi_ptr);
    --org_ptr->info.achi_num;
}

void delete_contr(contr_node* contr_ptr, contr_node* pre_contr_ptr, achi_node* achi_ptr)
{
    if (pre_contr_ptr) pre_contr_ptr->next = contr_ptr->next;
    else achi_ptr->contributors = contr_ptr->next;
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
    org_node* last_org = 0;
    if (fp_org && fp_achi && fp_contr)
    {
        for (; ; )
        {
            org_node* new_org = (org_node*)malloc(sizeof(org_node));
            if (fread(&new_org->info, sizeof(org_info), 1, fp_org) != 1) break;
            if (last_org)
            {
                last_org->next = new_org;
                last_org = new_org;
            }
            else
            {
                last_org = org_list_head = new_org;
            }
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

void sort_orgs_if_needed(org_node* cur_org, org_node* pre_org)
{
    if (!cur_org) return;
    int num = cur_org->info.achi_num;
    if (!pre_org || num <= pre_org->info.achi_num)
    {
        return;
    }
    else
    {
        pre_org->next = cur_org->next;
        if (org_list_head->info.achi_num <= num)
        {
            cur_org->next = org_list_head;
            org_list_head = cur_org;
            return;
        }
        org_node* larger_node = org_list_head;
        for (; larger_node->next->info.achi_num > num; larger_node = larger_node->next);
        cur_org->next = larger_node->next;
        larger_node->next = cur_org;
    }
}

contr_node* filter_by_age_MVC(int from, int to)
{
    if (from > to || !to) return 0;
    contr_node* result = 0;
    org_node* it_org_ptr = org_list_head;
    for (; it_org_ptr; it_org_ptr = it_org_ptr->next)
    {
        achi_node* it_achi_ptr = it_org_ptr->achievements;
        for (; it_achi_ptr; it_achi_ptr = it_achi_ptr->next)
        {
            contr_node* it_contr_ptr = it_achi_ptr->contributors;
            for (; it_contr_ptr; it_contr_ptr = it_contr_ptr->next)
            {
                if (!strcmp(it_achi_ptr->info.mvp, it_contr_ptr->info.name) &&
                    it_contr_ptr->info.age >= from && it_contr_ptr->info.age <= to)
                {
                    contr_node* new_node = (contr_node*)malloc(sizeof(contr_node));
                    new_node->info = it_contr_ptr->info;
                    new_node->next = result;
                    result = new_node;
                }
            }
        }
    }
    return result;
}

contr_node* filter_by_age(int from, int to)
{
    if (from > to || !to) return 0;
    contr_node* result = 0;
    org_node* it_org_ptr = org_list_head;
    for (; it_org_ptr; it_org_ptr = it_org_ptr->next)
    {
        achi_node* it_achi_ptr = it_org_ptr->achievements;
        for (; it_achi_ptr; it_achi_ptr = it_achi_ptr->next)
        {
            contr_node* it_contr_ptr = it_achi_ptr->contributors;
            for (; it_contr_ptr; it_contr_ptr = it_contr_ptr->next)
            {
                if (it_contr_ptr->info.age >= from && it_contr_ptr->info.age <= to)
                {
                    contr_node* new_node = (contr_node*)malloc(sizeof(contr_node));
                    new_node->info = it_contr_ptr->info;
                    new_node->next = result;
                    result = new_node;
                }
            }
        }
    }
    return result;
}

void delete_contr_list(contr_node* head)
{
    contr_node* it = head, *temp;
    for (; it; it = temp)
    {
        temp = it->next;
        free(it);
    }
}

