#include <stdio.h>
#include <stdlib.h>
typedef struct result {
  int position;
  struct result *next;
} result;

result* create(int position) {
    result *r = malloc(sizeof(result));
    r->position = position;
    r->next = NULL;
    return r;
}

void release(result *r) {
  if(r){
    if (r->next)
      release(r->next);
    free(r);
  }
}
int main() {
  char *text = "bbabaxababayababa";
  char *p = "aba";
  printf("searching for \"%s\" in \"%s\"\n", p, text);
  result *results = create(-1);
  result *current = results;
  char letter;
  int i;
  int j;
  for(i=0; text[i]!='\0'; i++){
    printf("%i. %c: ", i, text[i]);
    for(j=0; p[j]!='\0'; j++) {
      if(p[j]==text[i+j])
	printf("%c ", p[j]);
      else {
        printf("\n");
	break;
      }
      if(p[j+1]=='\0'){
        printf("match found at positing %i\n", i);
        current->next = create(i);
        current = current->next;
      }
    }
  }
  printf("Results: ");
  current = results;
  while(current->next) {
    current = current->next;
    printf("%i ", current->position);
  };
  printf("\n");
  release(results);
}
