#include "project.h"

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int main()
{
	char*	test = ft_calloc(10, sizeof(char)), *test2;
	test[5] = 'c';
	free(test);

	test = ft_itoa(1230123);
	
	char** tab = ft_split(test, '0');
	free(test);
	char *test3 = ft_strdup(tab[1]);

	test = ft_strjoin(test3, "yep   ");
	free(test3);
	test2 = ft_strtrim(test, " ");
	free(test);
	test = ft_substr(test2, 3, 3);

	write(1, test, 3);
	free(tab[0]);
	free(tab[1]);
	free(tab);
	free(test);
	free(test2);
}