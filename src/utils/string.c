#include "utils.h"
#include <stdlib.h>
#include <stdio.h>

int ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void *ft_memset(void *s, int c, size_t n)
{
	size_t i;
	char *str;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (s);
}

int ft_isalnum(char c)
{
	return ('a' <= c && c <= 'z') ||
		   ('A' <= c && c <= 'Z') ||
		   ('0' <= c && c <= '9');
}

int ft_tolower(char c)
{
	if ('A' <= c && c <= 'Z')
		return c + 32;
	return c;
}

static char *strdup_alpha(char *s)
{
	size_t len = ft_strlen(s);
	char *str = malloc(len * sizeof(char));
	size_t j = 0;

	if (!str)
		return s;
	for (size_t i = 0; i < len; i++)
		if (ft_isalnum(s[i]))
			str[j++] = ft_tolower(s[i]);
	str[j] = 0;
	return str;
}

int ft_strcmp_alpha(char *s1, char *s2)
{
	char *sa1 = strdup_alpha(s1);
	char *sa2 = strdup_alpha(s2);
	int ret = ft_strcmp(sa1, sa2);
	free(sa1);
	free(sa2);
	return ret;
}

int ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
	{
		if (i == n - 1)
			return (0);
		i++;
	}
	return (s1[i] - s2[i]);
}

size_t ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char *ft_strstr(char *str, char *to_find)
{
	size_t i;
	size_t j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] && to_find[j] && str[i + j] == to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

void print_strs(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
	{
		printf(" - %s\n", strs[i]);
		i++;
	}
}
