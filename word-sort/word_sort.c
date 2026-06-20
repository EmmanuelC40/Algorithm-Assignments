#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void word_sort(char *s);

int main()
{  char test1[] = "pea carrot bean cabbage mushroom artichoke lentil onion leek ";
   char test2[] = "raccoon chipmunk deer opossum coyote skunk rabbit bear groundhog ";
   char test3[100001];
   int i,j,k,l,n;

   printf("Test1: \n\nunsorted:\n %s\n", test1);
   word_sort(test1);
   printf("sorted:\n %s\n", test1);

   printf("\nTest2: \n\nunsorted:\n %s\n", test2);
   word_sort(test2);
   printf("sorted:\n %s\n", test2);

   printf("\nTest3\n");
   n=0; srand(time(NULL));
   for(i=0; i< 10; i++)
      for(j=0; j< 10; j++)
         for(k=0; k< 10; k++)
            for(l=0; l< 10; l++)
	      {  test3[n] = (char) ( (int) 'a' + (9 - l));
         	 test3[n+1] = (char) ( (int) 'a' + ((3*(k+2))%10));
		 test3[n+2] = 'x';
		 test3[n+3] = (char) ( (int) 'a' + ((9*(i+1))%10));
		 test3[n+4] = 'x';
		 test3[n+5] = (char) ( (int) 'a' + ((7*(9-j))%10));
		 test3[n+6] = 'x'; 
		 test3[n+7] = 'y';
		 test3[n+8] = 'z';
		 test3[n+9] = ' ';
		   n = n+10;
	      }
	      
   test3[n] = '\0';
   printf("\nTest3 starts: ");
   for(i=0; i<60; i++) printf("%c", test3[i]);
   word_sort(test3);
   printf("\nTest3 after sorting: random fragment, starting at %d\n", i = 10*(rand() %9990));
   for(j=0; j<60; j++) printf("%c", test3[i+j]);
   printf("\n\n");
   exit(0);
}

// ---------- helper functions ----------

// Compare two null-terminated words lexicographically
int compare_words(const char *a, const char *b) 
{
    while (*a && (*a == *b)) 
    {  
        a++; 
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

// Mergesort adapted for words
void mergesort(char **a, char **aux, int length) 
{
    if (length <= 1) return;

    int mid = length / 2;
    mergesort(a, aux, mid);
    mergesort(a + mid, aux, length - mid);

    // Merge sorted halves into aux
    int i = 0, j1 = 0, j2 = mid;
    while (i < length) 
    {
        if (j1 < mid && (j2 == length || compare_words(a[j1], a[j2]) <= 0)) 
        {
            aux[i++] = a[j1++]; 
        } 
        else 
        {
            aux[i++] = a[j2++];
        }
    }

    // Copy merged result back
    for (i = 0; i < length; i++)
        a[i] = aux[i];
}

// Split the input string s into words by replacing spaces with '\0'
int split_words(char *s, char ***words_out, char ***aux_out, int len) 
{
    int word_count = 0;
    for (int i = 0; i < len; ++i)
        if (s[i] == ' ') 
            word_count++; 

    // Allocate and instantly verify memory safety
    char **words = (char **) malloc(sizeof(char*) * (word_count > 0 ? word_count : 1));
    char **aux   = (char **) malloc(sizeof(char*) * (word_count > 0 ? word_count : 1));
    if (words == NULL || aux == NULL) 
    {
        fprintf(stderr, "Fatal error: Memory allocation failed in split_words.\n");
        exit(EXIT_FAILURE);
    }

    int idx = 0;
    char *p = s;
    for (int i = 0; i < len; ++i) 
    {
        if (s[i] == ' ') 
        {
            s[i] = '\0';    
            words[idx++] = p;   
            p = s + i + 1;  
        }
    }

    *words_out = words;
    *aux_out   = aux;
    return word_count;
}

// ---------- word_sort function ----------
void word_sort(char *s) 
{
    // compute string length
    int len = 0;
    while (s[len] != '\0') 
        ++len;

    if (len == 0) 
        return;  // nothing to sort

    char **words = NULL;
    char **ptr_aux = NULL;
    int word_count = split_words(s, &words, &ptr_aux, len);

    // temporary buffer for rebuilt string
    char *sorted = (char *) malloc(len + 1);
    if (sorted == NULL) 
    {
        fprintf(stderr, "Fatal error: Memory allocation failed in word_sort.\n");
        exit(EXIT_FAILURE);
    }
    
    char *out = sorted;

    if (word_count > 1)
        mergesort(words, ptr_aux, word_count);

    // rebuild sorted string with spaces
    for (int i = 0; i < word_count; i++) 
    {
        char *w = words[i];
        while (*w) 
            *out++ = *w++;
        *out++ = ' ';
    }
    *out = '\0';

    // copy result back to original buffer
    for (int i = 0; i <= len; i++)
        s[i] = sorted[i];

    // free dynamic memory
    free(words);
    free(ptr_aux);
    free(sorted);
}
