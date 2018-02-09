#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum { false, true } bool;

char ** str_split(const char *a_str, const char *a_delim)
{
    int str_len = strlen(a_str);
    char *tmp_str = malloc(sizeof(char) * str_len);
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
    result = malloc(sizeof(char*) * (count + 1));
    int idx  = 0;
    char *token = strtok(tmp_str, a_delim);
    while (token)
    {
        *(result + idx++) = strdup(token);
        token = strtok(0, a_delim);
    }
    *(result + idx) = 0;
    return result;
}

char * params_substitution (const char *pattern, const char *parameters)
{
    long pattern_len = strlen(pattern);
    char **params = str_split(parameters, ",");
    int param_size = 0;
    char **r = params;
    while (*r != 0)
    {
        param_size++;
        r++;
    }
    long replace_pos[param_size];
    int replace_index[param_size];
    int replace_len[param_size];
    int pos = 0;
    bool is_param = false;
    long current_replace_index = -1;
    long current_replace_len = 0;
    long output_len = pattern_len;
    int start_index = param_size;
    int i = 0;
    for (i = 0; i<pattern_len; i++)
    {
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
            if (pattern[i] >= '0' && pattern[i] <= '9') {
                current_replace_index = (current_replace_index == -1 ? 0 : current_replace_index) * 10 + (pattern[i]-'0');
                current_replace_len++;
                continue;
            }
            else if (current_replace_index >= 0)
            {
                if (current_replace_index < param_size)
                {
                  replace_index[pos] = current_replace_index;
                  replace_len[pos] = current_replace_len + 1;
                  replace_pos[pos] = i - replace_len[pos];
                  pos++;

                  if (current_replace_index < start_index) 
                  {
                     start_index = current_replace_index;
                  }
                }
            }
            
            // reset state
            is_param = false;
            current_replace_index = -1;
            current_replace_len = 0;
        }
    }

  int replace_size = pos;
  for (pos=0; pos < replace_size; pos++)
  {
      output_len += strlen(*(params + replace_index[pos] - start_index)) - replace_len[pos];
  }
  char *output;
  output = (char*) malloc(sizeof(char) * output_len);
  pos = 0;
  int j = 0;
  for (i = 0; i < pattern_len; i++)
  {
    if (pos < replace_size && i == replace_pos[pos])
    {
          
      strcat(output, *(params + replace_index[pos] - start_index));
      i += replace_len[pos] - 1;
      j += strlen(*(params + replace_index[pos] - start_index));
      pos++;
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