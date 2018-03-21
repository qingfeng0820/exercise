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

/**
 * Parameters substitution for input patten
 * 
 * @param patten the input message patten
 * @param parameters  the values for substitution, which is joined by a splitter.
 * @param param_delim the spliter for parameters
 * @return the completed message with parameters substituted
 */
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
    
    // calculate the output length
    long output_len = pattern_len;
    long current_replace_index = -1;
    long current_replace_len = 0;
    bool is_param = false;
    for (i = 0; i <= pattern_len; i++) // cstring is null-terminated
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
                    output_len += param_len[current_replace_index] - current_replace_len - 1;
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
        }
    }

    char *output;
    output = (char*) malloc(sizeof(char) * (output_len + 1));

    // do replacement
    is_param = false;
    current_replace_index = -1;
    current_replace_len = 0;
    int j = 0;
	bool logged_missing_param_value_warning = false;
    bool logged_single_percent_sign_waring = false;
	int replaced_placeholder_count = 0;
    for (i = 0; i <= pattern_len; i++) // include null at end of string
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
                    // e.g. xxx%0xxx replace '%0' with parameter[0]
                    strncpy(output + j, param_pt[current_replace_index], param_len[current_replace_index]);
                    j += param_len[current_replace_index];
					replaced_placeholder_count++;
                }
                else
                {
                    // e.g. xxx%999xxx keep the '%999', log warning
                    strncpy(output + j, pattern + i - current_replace_len - 1, current_replace_len + 1);
                    j += current_replace_len + 1;
                    if (!logged_missing_param_value_warning)
                    {
                        logged_missing_param_value_warning = true;
                    }
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
                output[j++] = '%';
            }
            is_param = !is_param;
        }
        else if (is_param)
        {
            // e.g. xxx%xxx keep the '%', log warning
            is_param = !is_param;
            output[j++] = '%';
            output[j++] = pattern[i];
			if (!logged_single_percent_sign_waring)
            {
				printf("WARNING: Cannot replace single % | Message: %s\n", pattern);
                logged_single_percent_sign_waring = true;
            }
        }
        else
        {
            output[j++] = pattern[i];
        }
    }
	if (logged_missing_param_value_warning)
	{
		printf("WARNING: No values for parameters from index %d | Message: %s | Args: %s\n", params_size, pattern, parameters);
	}
    if (replaced_placeholder_count < params_size)
    {
        printf("WARNING: %d parameter values but only replaced %d placeholders | Message: %s | Args: %s\n", params_size, replaced_placeholder_count, pattern, parameters);
    }	
    return output;
}
