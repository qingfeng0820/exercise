#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { false, true } bool;

char * strtok_single (char *str, char const *delim)
{
    static char  *src = NULL;
    char  *p,  *ret = 0;

    if (str != NULL)
    {
        src = str;
    }
    if (src == NULL)
    {
        return NULL;
    }

    if ((p = strpbrk (src, delim)) != NULL)
    {
        *p  = 0;
        ret = src;
        src = ++p;
    }
    else if (*src)
    {
        ret = src;
        src = NULL;
    }

    return ret;
}

char ** str_split(const char *a_str, const char *a_delim)
{
    int str_len = strlen(a_str);
    char *tmp_str = malloc(sizeof(char) * (str_len + 1));
    strcpy (tmp_str, a_str);
    char **result = 0;
    int count = 0;
    char *p = tmp_str;
    int delim_len = strlen(a_delim);

    /* Count how many elements will be extracted. */
    while(p = strstr(p, a_delim))
    {
        count++;
        p = p + delim_len;
    }
    /* Splitting. */
    p = tmp_str;
    result = malloc(sizeof(char*) * (count + 2));
    int idx  = 0;
    char *token = strtok_single(tmp_str, a_delim);
    while (token)
    {
        *(result + idx++) = token;
        token = strtok_single(0, a_delim);
    }
    *(result + idx) = 0;
    free(tmp_str);
    return result;
}

char * params_substitution (const char *pattern, const char *parameters, const char *param_delim)
{
    long pattern_len = strlen(pattern);
    // Splitting parameters 
    const char *p = parameters;
    int delim_len = strlen(param_delim);
    int params_size = 1;
    
    // Get parameter count
    while(p = strstr(p, param_delim))
    {
      params_size++;
      p = p + delim_len;
    }
    
    // Do Splitting
    p = parameters;
    const char *pre_p = p;
    const char *param_pt[params_size];
    int param_len[params_size];
    int i = 0;
    while(p = strstr(p, param_delim))
    {
        param_pt[i] = pre_p;
        param_len[i] = p - pre_p;
        
        p = p + delim_len;
        pre_p = p;
        i++;
    }
    param_pt[i] = pre_p;
    param_len[i] = strlen(pre_p);
    
    // get the amount of placeholder
    int replace_size = 0;
    long current_replace_index = -1;
    bool is_param = false;
    for (i = 0; i <= pattern_len; i++)
    {
        if (is_param)
        {
            if (pattern[i] >= '0' && pattern[i] <= '9') 
            {
                // calculate placeholder index. Like index of %0 is 0, index of %2 is 2
                current_replace_index = (current_replace_index == -1 ? 0 : current_replace_index) * 10 + (pattern[i]-'0');
                continue;
            }
            else if (current_replace_index >= 0)
            {
                if (current_replace_index < params_size)
                {
                    replace_size++;
                }
                
                 // reset state
                is_param = false;
                current_replace_index = -1;
            }
        }
        if (pattern[i] == '%')
        {
            is_param = !is_param;
        }
        else if (is_param)
        {
            is_param = !is_param;
        }
    }
   
    // Get replace positions in pattern
    long replace_pos[replace_size];
    int replace_index[replace_size];
    int replace_len[replace_size];
    int pos = 0;
    is_param = false;
    current_replace_index = -1;
    long current_replace_len = 0;
    long output_len = pattern_len;
    for (i = 0; i <= pattern_len; i++)
    {
        
        if (is_param)
        {
            if (pattern[i] >= '0' && pattern[i] <= '9') 
            {
                // calculate placeholder index. Like index of %0 is 0, index of %2 is 2
                current_replace_index = (current_replace_index == -1 ? 0 : current_replace_index) * 10 + (pattern[i]-'0');
                current_replace_len++;
                continue;
            }
            else if (current_replace_index >= 0)
            {
                if (current_replace_index < params_size)
                {
                    replace_index[pos] = current_replace_index;
                    replace_len[pos] = current_replace_len + 1;
                    replace_pos[pos] = i - replace_len[pos];
                    output_len += param_len[current_replace_index] - current_replace_len;
                    pos++;
                }
                else
                {
                    printf("Error: no value for parameter index %d | %s\n", current_replace_index, pattern);
                }

                // reset state
                is_param = false;
                current_replace_index = -1;
                current_replace_len = 0;
            }
        }
        if (pattern[i] == '%')
        {
            if (is_param)
            {
                // %% is %
                output_len--;
            }
            is_param = !is_param;
        }
        else if (is_param)
        {
            is_param = !is_param;
            printf("Error: cannot replace single % | %s\n", pattern);
        }
    }

    char *output;
    output = (char*) malloc(sizeof(char) * (output_len + 1));
    pos = 0;
    int j = 0;
    // do replacement
    for (i = 0; i < pattern_len; i++)
    {
        if (pos < replace_size && i == replace_pos[pos])
        {
            if (replace_index[pos] < params_size)
            {
                strncpy(output + j, param_pt[replace_index[pos]], param_len[replace_index[pos]]);
                i += replace_len[pos] - 1;
                j += param_len[replace_index[pos]];
                pos++;
            }
            else
            {
                output[j++] = pattern[i];
            }
        }
        else if (pattern[i] == '%' && pattern[i+1] == '%')
        {
            output[j++] = '%';
            i++;
        }
        else
        {
            output[j++] = pattern[i];
        }
    }
    output[j] = 0;
    return output;
}
