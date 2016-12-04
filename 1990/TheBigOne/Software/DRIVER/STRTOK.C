#define     NULL    0
char *savstrtok;

char *strtok(ptr,separator)
char *ptr,*separator;
{
if(!ptr) ptr=savstrtok;                         /* Se ptr NULLO riprendo quello salvato */
while(*ptr==*separator&&*ptr){
 ++ptr;
 }
if(!*ptr) return(NULL);                         /* Trovato fine stringa */
savstrtok=ptr;
while(*savstrtok!=*separator&&*savstrtok) ++savstrtok;
if(*savstrtok){
               *savstrtok='\0';
               ++savstrtok;
               }
               return(ptr);
}














