
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFOR 64


//  Napisz program, który:
// utworzy potok (funkcją pipe),
// uruchomi podproces, z którym proces nadrzędny będzie komunikował się przez ten potok (funkcja fork),
// proces nadrzędny otworzy plik tekstowy podany w argumencie wywołania programu, 
// a następnie wyśle procesowi potomnemu zawartość tego pliku przez potok,
// proces potomny odczyta dane z potoku, a następnie wyświetli je na standardowym wyjściu dodając znak '#' na początku i 
// końcu każdej odebranej paczki danych. Wielkość paczek jest dowolna.



int main(int argc , char* argv[])
{

int pid_numb;
int file_desc_numb[2];

pipe(file_desc_numb);

pid_numb = fork();

if (pid_numb)
{
    //child
   char bufor[MAX_BUFFOR];
   while (read(file_desc_numb[0],bufor,MAX_BUFFOR))
   {
       if (bufor[MAX_BUFFOR - 1] == 0)
       {
           break;
       }
        bufor[MAX_BUFFOR - 1] = '\0';
        printf("#%s#\n", bufor);
   }
   
}
else
{
    //parent
    FILE *f = fopen(argv[1],"r");
    char buffor[MAX_BUFFOR];

    while (fgets(buffor,MAX_BUFFOR,f))
    {
        buffor[MAX_BUFFOR-1] = 1;
        write(file_desc_numb[1],buffor,MAX_BUFFOR);
    }

    buffor[MAX_BUFFOR-1]=0;
    write(file_desc_numb[1],buffor,MAX_BUFFOR);

    fclose(f);
        
}



}