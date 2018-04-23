#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


struct natural { //Натуральное число
  int len;     // Длина
  int *num;    // Массив цифр
};

struct integer { //Целое число
  int sign;    // Знак
  int len;     // Длина
  int *num;    // Массив цифр
};

struct rational { //Рациональное число
    int sign;          // Знак числителя
    int lenNum;        // Длина числителя
    int *numerator;    // Массив числителя
    int lenDen;        // Длина знаменателя
    int *denominator;  // Массив знаменателя
};

struct polynomial { //Многочлен с рациональными коэффициентами
    struct rational* coeff;     // Массив коэффициентов
    int *deg;                   // Массив степеней
    int len;                    // Кол-во членов
};

char* line2(char *s) //функция ввода строки
{
    int c, i;
	for (i = 0;((c=getchar()) != '\n') && (i<60); ++i){
        s=(char*)realloc(s,(i+1)*sizeof(char));
		s[i] = c;
	}

	s=(char*)realloc(s,(i+1)*sizeof(char));
	s[i] = '\0';

	return s;
}


//!Парсер натурального
struct natural inputnat(char *s)
{
    int i,j=0;
    struct natural a;
    char *s2=(char*)malloc(2*sizeof(char));

    while (s[j]==' ')
        j++;
    while((s[j]=='0')&&(s[j+1]!='\0'))
        j++;
    a.len=strlen(s)-j;
    a.num=(int*)malloc(a.len*sizeof(int));
    for (i=0;i<a.len;i++){
        s2=strncpy(s2,s+i+j,1);
        s2[1]='\0';
        a.num[i]=atoi(s2);
    }

    return a;
}

//!Парсер целого

struct integer inputint (char* s)
{
    int i,j=0;
    struct integer d;
    char *s2=(char*)malloc(2*sizeof(char));

    while (s[j]==' ')
        j++;
    if (s[j]=='-'){
        d.sign=1;
    }
    else
        d.sign=0;
    j+=d.sign;
            while ((s[j]=='0') && (s[j+1]!='\0'))
                j++;
    d.len=strlen(s)-j;
    d.num=(int*)malloc(d.len*sizeof(int));
    for (i=0;i<d.len;i++){
        s2=strncpy(s2,s+i+j,1);
        s2[1]='\0';
        d.num[i]=atoi(s2);
    }

    return d;
};

//!Парсер рациональных

struct rational inputratio(char* s)
{
    int i,j;
    char *s1;
    char *s2=(char*)malloc(2*sizeof(char));
    struct rational m;
    s1=(char*)malloc(strlen(s)*sizeof(char));
    s1=strcpy(s1,s);
    s1=strtok(s1,"/");


    if (s1[0]=='-'){
        m.sign=1;
    }
    else
        m.sign=0;
    j=m.sign;
    if (s1[0]=='+')
        j++;
    while (s1[j]==' ')
        j++;
    while ((s1[j]=='0') && (s1[j+1]!='\0'))
        j++;
    m.lenNum=strlen(s1)-j;
    m.numerator=(int*)malloc(m.lenNum*sizeof(int));
    for (i=0;i<m.lenNum;i++){
        s2=strncpy(s2,s1+i+j,1);
        s2[1]='\0';
        m.numerator[i]=atoi(s2);
    }
    if (m.lenNum==0){
        m.lenNum=1;
        m.numerator=(int*)realloc(m.numerator,sizeof(int));
        m.numerator[0]=1;
    }

    s1=strtok(NULL,"/");
    if (s1==NULL){
        m.lenDen=1;
        m.denominator=(int*)malloc(sizeof(int));
        m.denominator[0]=1;
    }
    else {
        j=0;
        while((s1[j]=='0')&&(s1[j+1]!='\0'))
            j++;

        m.lenDen=strlen(s1)-j;
        m.denominator=(int*)malloc(m.lenDen*sizeof(int));
        for (i=0;i<m.lenDen;i++){
            s2=strncpy(s2,s1+i+j,1);
            s2[1]='\0';
            m.denominator[i]=atoi(s2);
        }
    }
    return m;
}

//!Парсер многочленов

struct polynomial inputpol(char* s)
{
    int i,j=0,h;
    struct polynomial x;
    char *s2=(char*)malloc(2*sizeof(char));
    char **s3;

    x.len=1;
    s2=(char*)realloc(s2,strlen(s)*sizeof(char));
    s3=(char**)malloc(sizeof(char*));
    *s3=s;
    i=1;
    j=1;
    while (i<strlen(s)){
        if ((s[i]=='+') || (s[i]=='-')){
            s3=(char**)realloc(s3,(j+1)*sizeof(char*));
            *(s3+j)=s+i;
            j++;
            x.len++;
        }
        i++;
    }
    i=0;
    x.coeff=(struct rational*)malloc(x.len*sizeof(struct rational));
    x.deg=(int*)malloc(x.len*sizeof(int));
    while(i<x.len){
        j=0;
        while((s3[i][j]!='x')&&(s3[i][j]!='\0')){
            j++;
        }
        if (j==0)
            x.coeff[i]=inputratio("1");
        else {
        s2=strncpy(s2,s3[i],j);
        s2[j]='\0';
        x.coeff[i]=inputratio(s2);
        }
        if (s3[i][j]=='\0'){
            x.deg[i]=0;
        }
        else {
            j=j+1;
            h=0;
            while ((s3[i][j+h]!='+')&&(s3[i][j+h]!='-')&&(s3[i][j+h]!='\0')&&(s3[i][j+h]!=' ')){
                h++;
            }
            if (h==0)
                x.deg[i]=1;
            else {
            j++;
            s2=strncpy(s2,s3[i]+j,h-1);
            s2[h-1]='\0';
            x.deg[i]=atoi(s2);
            }
        }
        i++;
    }

    return x;
};


//!вывод
void natprint(struct natural a)
{
    int i;
    for (i=0;i<a.len;i++){
        printf("%d",a.num[i]);
    }
    printf("\n");
    printf("\n");
}

void intprint(struct integer d)
{
    int i;
    if (d.sign==1)
        printf("-");
    for (i=0;i<d.len;i++){
        printf("%d",d.num[i]);
    }
    printf("\n");
    printf("\n");
}

void ratprint(struct rational m)
{
    int i;
    if (m.sign==1)
        printf("-");
    for (i=0;i<m.lenNum;i++){
        printf("%d",m.numerator[i]);
    }
    printf("/");

    for (i=0;i<m.lenDen;i++){
        printf("%d",m.denominator[i]);
    }
    printf("\n");
    printf("\n");
}

void polprint(struct polynomial y)
{
    int i,j;
        j=0;
    while(j<y.len){
        if (y.coeff[j].sign==1)
            printf("-");
        else if (j!=0)
            printf("+");
    for (i=0;i<y.coeff[j].lenNum;i++)
        printf("%d",y.coeff[j].numerator[i]);
    printf("/");
    for (i=0;i<y.coeff[j].lenDen;i++)
        printf("%d",y.coeff[j].denominator[i]);
    printf("x^%d",y.deg[j]);
    j++;
    }
    printf("\n");
    printf("\n");
}



//!Прототипы
struct rational ADD_QQ_Q(struct rational, struct rational);
struct rational SUB_QQ_Q(struct rational, struct rational);

//!Модули натуральных чисел

//!N-1
//!Сравнение натуральных чисел: 2 - если первое больше второго, 0, если равно, 1 иначе. (COM_NN_D)
//!Патрухина

int COM_NN_D(struct natural a, struct natural b)
{
    int i =0, flag = 0;
    if (a.len > b.len) //Первый по длине больше второго
        flag = 2;
    else
        if(a.len < b.len) //Второй по длине больше первого
            flag = 1;
    else //Если равны по длине
        for (i = 0; i < a.len; i++)
            if (a.num[i] != b.num[i])
                if (a.num[i] > b.num[i]) //Цифра первого больше цифры второго
                {
                    flag = 2;
                    i = a.len;
                }
            else
                if (a.num[i] < b.num[i]) //Цифра второго больше цифры первого
                {
                    flag = 1;
                    i = a.len;
                }
    return flag; //Если числа равны, то flag остался 0. Первое больше второго - 2, второе больше первого - 1
}

//!Функция для проверки числа на 0, если оно 0, функция вернет 0, если нет то 1
//!Владислав Пиков
//!N-2
int NZER_N_B(struct natural u)  // передача в функцию и массив цифр
{
    int flag=1;
    if(u.len==1)    // сколько цифр в числе
       {
         if (u.num[0]==0)  // сравнение на 0/1
         {
             flag=0;
             return flag;   // если ноль тогда возращает 0
         }
       }
     else
     return flag;  // если не 0 возращает 1
}

//!Мамаева Е.А.
//!N-3
//!Прибавление 1 к натуральному числу
struct natural ADD_1N_N(struct natural a)
{
    //int i = a.len - 1;
    int i = a.len - 1;

    while ((a.num[i] == 9) && (i != (-1)))
        {
            a.num[i] = 0;
            i--;
        }

    if (i != (-1))
    {
        a.num[i] += 1;
    }
    else
    {
        a.num = (int*)realloc(a.num, (a.len++)*sizeof(int));
        a.num[0] = 1;
        for (i = 1; i < a.len; i++ )
        {
            a.num[i] = 0;
        }
    }

    return a;
}

//! Модуль N-4
//!Сумма натуральных чисел
//! Разработчики: Кадыров Т., Резников Д., Пиков В.

struct natural ADD_NN_N(struct natural c, struct natural b)  //!На вход получает 2 числа в виде структур
{
    struct natural swap, a; //!структура для перестановки
    int i,j,k;     //!операторы цикла
    a.len=c.len;
    a.num=(int*)malloc(a.len*sizeof(int));
    for(i=0;i<a.len;i++)                            //!поскольку у нас num*, то есть указатель, то чтобы его значения не менялись, мы переноси входную с в внутреннюю а
    {
        a.num[i]=c.num[i];
    }
    //!если второе больше первого, то меняем их местами
    if(COM_NN_D(a,b)==1)
    {
        swap=a;
        a=b;
        b=swap;
    }
    //!сложение
    for (i=a.len-1,j=b.len-1;i>-1,j>-1;i--,j--) //! i, j - номера элементов большего и меньшего числа соответсвенно
    {
        a.num[i]=a.num[i]+b.num[j];    //!Поэлементное(поразрядное) сложение
        if (a.num[i]>9)  //!Если сумма больше 9
        {
            if (i==0) //!Если мы дошли до старшего разряда
            {
               a.len++;  //!Увеличиваем длину результата
               a.num=(int*)realloc(a.num, (a.len)*sizeof(int));
               for(k=a.len-1;k>0;k--) //!цикл сдвига элементов массива вправо на 1, из-за увеличения длины увеличилось количесво разрядов
               {
                   a.num[k]=a.num[k-1]; //!сам сдвиг
               }
               a.num[1]=a.num[1]-10; //!перенос 2-х старших разрядов
               a.num[0]=1;
            }
            else
                if (j==0)  //!Если второе число по длине меньше первого, это условие сработает
                {
                    k=i;
                    while ((a.num[k]>9) && (k>0)){
                        a.num[k]=a.num[k]-10;       //!уменьшение значения разряда на 10
                        a.num[k-1]=a.num[k-1]+1;   //!добавление единицы к старшему относительно k разряду
                        k--;
                    }
                }
            else
            {
                a.num[i]=a.num[i]-10;      //!уменьшение значения разряда на 10
                a.num[i-1]=a.num[i-1]+1;  //!добавление единицы к старшему относительно k разряду
            }
        }
    }
    return a;   //!Возвращаем структуру-результат сложения
}

//!N-5
//!Вычитание из первого большего натурального числа второго меньшего или равного
//!Корниенко А.

struct natural SUB_NN_N(struct natural a, struct natural b) //a и b структуры первого и второго числа
{
    int i, j, l;// i,j - операторы цикла
    struct natural c, d, swap,e; //c - структура разности
    c.num=(int*)malloc(a.len*sizeof(int));
    c.len = 0;
    d = a;// переписываем в отдельную структуру для дальнейшей работы
    e = b;
    //если второе больше первого, то меняем их местами
    if (COM_NN_D(d,e)==0){
        c.len=1;
        c.num=(int*)realloc(c.num,sizeof(int));
        c.num[0]=0;
    }
    else {
    if(COM_NN_D(d,e) == 1)
    {
        swap = d;
        d = e;
        e = swap;
    }
    l = e.len - 1;//конец второго числа
    for ( i = d.len-1; i > -1; i-- )//с конца
    {
        if ( l > -1 )//уменьшаем до тех пор пока второе число не кончится
        {
            if ( (d.num[i] > e.num[l]) || (d.num[i] == e.num[l]) )//элемент пеервого числа больше второго
            {
                c.num[i] = d.num[i] - e.num[l];//просто вычитаем первое из второго
            }
            if ( d.num[i] < e.num[l] )//вычитание из ме��ьшего элемента большего
            {
                if (d.num[i] == 0)
                {
                    j = i-1;
                    while ( d.num[j] == 0 )//пока он равен нулю отнимаем
                    {
                        d.num[j] = 9;//заменяем оставшуюся часть числа
                        j--;
                    }
                d.num[j] = d.num[j] - 1;//из-за увеличения последующих разрядов уменьшаем первый ненулевой
                d.num[i] = 10;
                c.num[i] = d.num[i] - e.num[l];
                }
                else
                {
                    d.num[i-1] = d.num[i-1] - 1;//тут крч все как столбиком - из предыдущего отнимаем единичку
                    d.num[i] = d.num[i] + 10;//к настоящему прибавляем десять
                    c.num[i] = d.num[i] - e.num[l];//по кайфу вычитаем
                }
            }
            l--;
        }
        else
            c.num[i] = d.num[i];//просто переписываем
            c.len++;//находим мнимую длинну разности
    }
        while ( c.num[0] == 0)//корректирование длины и удаление нулей в начале числа
        {
            c.len--;
            for ( i = 0; i < c.len; i++ )
            {
                c.num[i] = c.num[i+1];
            }
        }
        c.num = (int*) realloc(c.num, c.len * sizeof(int));
    }
        return c;//возвращаем структуру разности
}


//! Модуль N-6
//! Разработчики: Кадыров Т., Резников Д., Пиков В.

struct natural MUL_ND_N(struct natural c, int b)  //!На вход получает число в виде структуры и цифру на которую нужно умножить
{
    struct natural a;
    int i,j;     //!операторы циклов
    int counter=0;  //!счетчик прибавления
    a.len=c.len;
    a.num=(int*)malloc(a.len*sizeof(int));
    for(i=0;i<a.len;i++)                   //!так как у нас num* то мы преносим данные из входящей с во внутреннюю а чтобы они не изменялись
    {
        a.num[i]=c.num[i];
    }
    //!умножение
    for (i=a.len-1;i>-1;i--) //! i - номер элементов числа
    {
        a.num[i]=b*a.num[i];             //!Поэлементное(поразрядное) умножение
        a.num[i]=a.num[i]+counter;      //!добавление к разряду "излишков" из предыдущего разряда
        counter=0;                     //!обнуление счетчика добавления
        while(a.num[i]>9)             //!пока значение разряда больше 9
        {
            a.num[i]=a.num[i]-10;    //!мы вычитаем по 10
            counter++;              //!и увеличиваем счетчик на 1
            if (i==0)              //!если мы дошли при этом до старшего разряда числа
            {
                a.len++;              //!то увеличиваем длину
                a.num=(int*)realloc(a.num, a.len*sizeof(int));
                for(j=a.len-1;j>0;j--)  //!цикл сдвига массива вправо на 1 разряд
                {
                    a.num[j]=a.num[j-1]; //!сам сдвиг
                }
                while(a.num[1]>9)  //!аналогичное уменьшение значения разряда большего 9, но конкретно для данного(того что перед старшим, хз как назвать)
                {
                        a.num[1]=a.num[1]-10;   //!опять таки вычитание десятки
                        counter++;             //!и увеличение счетчика
                }
                a.num[0]=counter;  //!запись значения счетчика в старший разряд
            }
        }
    }
    return a;   //!Возвращаем структуру-результат умножения
}



//!N - 7
//!Умножение натурального числа на 10^k (MUL_NN_N)
//!Патрухина

struct natural MUL_Nk_N(struct natural a, int k) //a - структура числа. k - степень 10
{
    int i;
    a.num = (int*)realloc(a.num, (a.len + k) * sizeof(int));//Перераспределение памяти так, чтоб влезли все нули (их количество равно степени k)
    for (i = a.len; i < k + a.len; i++)
        a.num[i] = 0;
    a.len = k + a.len;
    return a;
}

//!N-8
//!Умножение натуральных чисел
//!Игумнова
struct natural MUL_NN_N(struct natural a, struct natural b)
{
    struct natural mul_1;
    struct natural mul_2;
    struct natural MUL;
    MUL.len=0;

    int i,k;
    k=0;

    for (i=(a.len-1); i>=0; i--)
    {
      mul_1=MUL_ND_N(b, a.num[i]);
      mul_2=MUL_Nk_N(mul_1, k);
      MUL=ADD_NN_N(mul_2, MUL);
      //natprint(MUL);
      k++;
    }
    return MUL;
}

//!Кочмарев Григорий
//!N_9 Вычитание из натурального другого натурального, умноженного на цифру для случая с неотрицательным результатом
struct natural SUB_NDN_N(struct natural c, int d, struct natural e)//c - уменьшаемое, d - множитель, e - вычитаемое, которое будет умножено
    {
        struct natural k, m;
        k=MUL_ND_N(e, d); //Умножение множителя на вычитаемое
        if(COM_NN_D(c, k)==1) printf ("ERROR in function SUB_NDN_N");
        m=SUB_NN_N(c, k);
        return m;
    }


//!N-10
//!Грацев Егор
/*!N-10: Вычисление первой цифры деления большего натурального на меньшее, домноженное на 10^k,
где k - номер позиции этой цифры (номер считается с нуля)*/
struct natural DIV_NN_Dk(struct natural number1,struct natural number2)
{
    int i,j,k,l;
    int counter=0;
    struct natural temple,array, array2;         //!Добавочные структуры для счёта и резервной копии
    array2.num=(int*)malloc(1*sizeof(int));
    if(COM_NN_D(number1,number2)==2)                    //!проверка, больше ли числитель знаменателя
        {

        //!деление
        temple.num=(int*)malloc(number2.len*sizeof(int)); //!создаём новый массив, равный по длине знаменателю
        array.num=(int*)malloc(number2.len*sizeof(int));
        for(i=0;i<number2.len;i++)
        {
            temple.num[i]=number1.num[i];   //!значения элементов массива берутся из числителя
            temple.len=i+1;
            array.num[i]=number2.num[i];
        }
        array.len=number2.len;                //!создаём новую структуру, чтобы не изменять входные значения
        if (COM_NN_D(temple,number2)!=2)    //!если число меньше, то добавляем ещё одну ячейку
        {
            temple.num=(int*)realloc(temple.num,(number2.len+1)*sizeof(int));
            temple.num[i]=number1.num[i];
            temple.len++;
        }
        k=number1.len-temple.len;           //!степень является оставшимся количеством элементов числителя
        while(COM_NN_D(temple,number2)!=1)
        {
            counter++;
            number2 = array;
            number2 = MUL_ND_N(number2,counter);    //!при помощи функции умножения находим множитель, являющися целой частью частного
        }
        counter=counter-1;
        if(counter>9)
        {
            k++;              //!если число делится нацело, то будет 10 или всё такое, и первая цифра будет 1
            counter=1;
        }

        array2.num[0]=counter;
        array2.len=1;
        array2=MUL_Nk_N(array2,k);
        }
    else if (COM_NN_D(number1,number2)==0){
            array2.num=(int*)realloc(array2.num,sizeof(int));
            array2.num[0]=1;
            array2.len=1;
        }
        else
    {
        array2.num=(int*)realloc(array2.num,sizeof(int));
        array2.num[0]=0;
        array2.len=1;
    }
    return array2;
}

//!N-11
//!Частное от деления большего натурального числа на меньшее или равное натуральное с остатком (делитель отличен от нуля)
//!Корниенко А.
struct natural DIV_NN_N (struct natural a, struct natural b) //a и b структуры чисел
{
    int i,j;// i - оператор цикла
    struct natural d, c, e, swap,m; // d - структура частного, c - вспомогательная структура
    c.num = (int*)malloc(a.len*sizeof(int));
    c.len = a.len;
    d.num=(int*)malloc(sizeof(int));
    d.num[0]=0;
    d.len = 1;
    e = a;
    m = b;// переписываем в отдельную структуру для дальнейшей работы
    //если второе больше первого, то меняем их местами
    if(COM_NN_D(e,m) == 1)
    {
        swap = e;
        e = m;
        m = swap;
    }
    i = 0;
    while ( COM_NN_D(e,m) != 1 )//пока делимое больше либо равно делителю
    {
        c = DIV_NN_Dk(e,m);//первая цифра деления умноженная на 10^k, где k новер позиции
        e = SUB_NN_N(e,MUL_NN_N(m,c));//вычитаем это из числа
        d = ADD_NN_N(d,c);
        i++;
    }
    d.num = (int*) realloc(d.num, d.len* sizeof(int));
    return d;//возвращаем частное
}

//!N-12
//!Остаток от деления большего натурального числа на меньшее или равное натуральное с остатком (делитель отличен от нуля)
//!Корниенко А.

struct natural MOD_NN_N(struct natural a, struct natural b)//a и b - структуры чисел
{
    struct natural c, d, swap, k,m;//c - вспомогательная структура, а также структура остатка
    int i;
    d = a;
    m = b;// переписываем в отдельную структуру для дальнейшей работы
    //если второе больше первого, то меняем их местами
    if(COM_NN_D(d,m) == 1)
    {
        swap = d;
        d = m;
        m = swap;
    }
    c = DIV_NN_N(d,m);//определим частное от деления посредством функций
    k = MUL_NN_N(c,m);
    c = SUB_NN_N(d,k);
    return c;//возвращаем структуру остатка
}

//!N-13
//!Поиск ��ОД'а двух натуральных чисел
//!Лалаев А.
struct natural GCF_NN_N(struct natural a, struct natural b)
{
    struct natural d,mod,c,e;
    d=b;
    e=a;
    if (COM_NN_D(a,b)==1){
        e=b;  // Результат сравнения чисел
        d=a;
    }
    else {
        e=a;
        d=b;
    }
        mod=MOD_NN_N(e,d);
    while(NZER_N_B(mod) != 0) // Проверка остатка на 0
    {
        c=d;
        d=mod;
        mod=MOD_NN_N(c,d);
    }
        return d; // Возвращаем НОД
}


//!N-14
//!НОК натуральных чисел
//!Лалаев А.
struct natural LCM_NN_N(struct natural a, struct natural b){
    struct natural LCM;                                     // НОК
    struct natural numerator;                               // Числитель, равный произведению a и b
    struct natural denominator;                             // Знаменатель, равный НОД'у a и b
    struct natural e=a,d=b;
    numerator = MUL_NN_N(e, d);
    denominator =  GCF_NN_N(e, d);
    LCM = DIV_NN_N(numerator, denominator);                 // Считаем НОК
    return LCM;                                             // Возвращаем НОК
}

//!Модули целых чисел

//!Мамаева Е.А.
//!Z-1
//!Абсолютная величина числа; mas-массив числа
struct integer ABS_Z_N(struct integer a)
{
 if(a.sign == 1)
    a.sign = 0;
 return a;
}

//!Мамаева Е.А.
//!Z-2
/*!Определение положительности числа (2 - положительное,
0 — равное нулю, 1 - отрицательное)*/
int POZ_Z_D(struct integer a)// mas - массив числа;n - количество цифр в числе
{
    int flag = 2;
    if(a.sign == 1)
        flag = 1;
    if(a.sign == 0)
        if((a.len == 1)&&(a.num[0] == 0))
            flag = 0;
    return flag;
}


//!Z - 3
//!Умножение целого на (-1) (MUL_ZM_Z)
//!Патрухина
struct integer MUL_ZM_Z(struct integer a)
{
  if (a.sign == 1)
    a.sign = 0;
  else
    a.sign = 1;
  return a;
}

//!Гарцев Е.А.
//!Z-4
//!Преобразование натурального в целое
struct integer TRANS_N_Z(struct natural c)
{
    struct integer k;
    int i;
    k.sign=0;                                 //добавление знака 0 перед массивом цифр
    k.len=c.len;
    k.num=(int*)malloc(k.len*sizeof(int));
    for (i=0;i<c.len;i++)                    //перенос массива цифр в структуру целого числа
    {
        k.num[i]=c.num[i];
    }
    return k;
}

//!Гарцев Е.А.
//!Z-5
//!Преобразование целого неотрицательного в натуральное
struct natural TRANS_Z_N(struct integer c)
{
    struct natural k;
    int i;
    k.len=c.len;
    k.num=(int*)malloc(k.len*sizeof(int));
    for (i=0;i<c.len;i++)                    //перенос массива цифр в структуру натурального числа
    {
        k.num[i]=c.num[i];
    }
    return k;
}

//!Z-6
//!Сложение целых чисел
//!Холопов И.
struct integer ADD_ZZ_Z (struct integer a, struct integer b)
{

    struct integer abs_1, abs_2, result;                //абсолютные величины чисел и результат
    struct natural nat_1, nat_2, nat_temp;              //вспомогательные структуры для хранения чисел как натуральных, а так же временная для сортировки
    int sign_1, sign_2;                                 //знаки чисел

    abs_1=ABS_Z_N(a);
    abs_2=ABS_Z_N(b);                                   //абсолютные величины чисел

    nat_1=TRANS_Z_N(abs_1);
    nat_2=TRANS_Z_N(abs_2);                             //преобразование в натуральные для сложения и вычитания в последствии

    if (COM_NN_D(nat_1, nat_2) == 1)                    //заведомо делаем первое число больше второго, чтобы избежать многократного испольования функции сравнения
    {
        nat_temp = nat_1;
        nat_1 = nat_2;
        nat_2 = nat_temp;
    }

    sign_1=POZ_Z_D(a);
    sign_2=POZ_Z_D(b);                                  //знаки чисел


    if (sign_1 == 1)                                    //если большее число отрицательно
    {
        if (sign_2 == 1)
        {
            result = (MUL_ZM_Z(TRANS_N_Z(ADD_NN_N(nat_1, nat_2))));
        }
        else
        {
            result = (MUL_ZM_Z(TRANS_N_Z(SUB_NN_N(nat_1, nat_2))));
        }
    }
    else                                                //если большее число положительно
    {
        if (sign_2 == 1)
        {
            result = (TRANS_N_Z(SUB_NN_N(nat_1, nat_2)));
        }
        else
        {
            result = (TRANS_N_Z(ADD_NN_N(nat_1, nat_2)));
        }
    }

    if(result.num[0]==0)
    {
        result=ABS_Z_N(result);
    }

    return result;
}

//!Z-7
//!Вычитание целых чисел
//!Филин Максим
struct integer SUB_ZZ_Z (struct integer a, struct integer b)
{

    struct integer abs_1, abs_2, result;                //абсолютные величины чисел и результат
    struct natural nat_1, nat_2, nat_temp;              //вспомогательные структуры для хранения чисел как натуральных, а так же временная для сортировки
    int sign_1, sign_2;                                 //знаки чисел

    abs_1=ABS_Z_N(a);
    abs_2=ABS_Z_N(b);                                   //абсолютные величины чисел

    nat_1=TRANS_Z_N(abs_1);
    nat_2=TRANS_Z_N(abs_2);                             //преобразование в натуральные для сложения и вычитания в последствии

    if (COM_NN_D(nat_1, nat_2) == 1)                    //заведомо делаем первое число больше второго, чтобы избежать многократного испольования функции сравнения
    {
        nat_temp = nat_1;
        nat_1 = nat_2;
        nat_2 = nat_temp;
    }

    sign_1=POZ_Z_D(a);
    sign_2=POZ_Z_D(b);                                  //знаки чисел

    if (sign_1 == 0)
    {
        return MUL_ZM_Z(b);
    }

    if (sign_2 == 0)
    {
        return a;
    }                                                   //в случае, если одно из чисел равно нулю, вывод может быть намного проще

    if (sign_1 == 1)                                    //если большее число отрицательно
    {
        if (sign_2 == 1)
        {
            if (COM_NN_D(TRANS_Z_N(abs_1),TRANS_Z_N(abs_2))==2)
                result = (MUL_ZM_Z(TRANS_N_Z(SUB_NN_N(nat_1, nat_2))));

            else
                result = (TRANS_N_Z(SUB_NN_N(nat_1, nat_2)));
        }
        else
        {
            result = (MUL_ZM_Z(TRANS_N_Z(ADD_NN_N(nat_1, nat_2))));
        }
    }
    else                                                //если большее число положительно
    {
        if (sign_2 == 1)
        {
            result = (TRANS_N_Z(ADD_NN_N(nat_1, nat_2)));
        }
        else
        {
            if (COM_NN_D(TRANS_Z_N(abs_1),TRANS_Z_N(abs_2))==2)
                result = (TRANS_N_Z(SUB_NN_N(nat_1, nat_2)));
            else
                result = (MUL_ZM_Z(TRANS_N_Z(SUB_NN_N(nat_1, nat_2))));
        }
    }

    if(result.num[0]==0)
    {
        result=ABS_Z_N(result);
    }

    return result;
}


//!Z-8
//!Умножение целых чисел
//!Игумнова А.
struct integer MUL_ZZ_Z(struct integer a, struct integer b)
{
    struct integer abs_1, abs_2;
    struct natural nat_1, nat_2;
    struct natural mul_nat;
    struct integer mul_int;
    int sign_1, sign_2;

    abs_1=ABS_Z_N(a);
    abs_2=ABS_Z_N(b);

    nat_1=TRANS_Z_N(abs_1);
    nat_2=TRANS_Z_N(abs_2);

    mul_nat=MUL_NN_N(nat_1,nat_2);

    mul_int=TRANS_N_Z(mul_nat);


    sign_1=POZ_Z_D(a);
    sign_2=POZ_Z_D(b);

    if (((sign_1==1)&&(sign_2==2))||((sign_1==2)&&(sign_2==1)))
        {
            mul_int=MUL_ZM_Z(mul_int);
        }
    return mul_int;
}

//!Z-9
//!Частное от деления большего целого числа на меньшее или равное натуральное с остатком(делитель отличен от нуля)
//!Филин Максим
struct integer DIV_ZZ_Z (struct integer a, struct natural b)
{
    struct natural result, abs_int;
    struct integer signed_result;
    struct integer one;
    int in_sign;
    one.num=(int*)malloc(sizeof(int));
    one.len=1;
    one.num[0]=1;
    one.sign=1;
    in_sign=a.sign;
    abs_int = TRANS_Z_N(ABS_Z_N(a));

    result = DIV_NN_N(abs_int, b);
    signed_result=TRANS_N_Z(result);
    signed_result.sign=in_sign;
    if (NZER_N_B(MOD_NN_N(abs_int,b))!=0){
    if (POZ_Z_D(signed_result)==1)
        signed_result=ADD_ZZ_Z(signed_result,one);
    }
    return signed_result;
}

//!Z-10
//!Остаток от деления большего целого числа на меньшее или равное натуральное с остатком(делитель отличен от нуля)
//!Филин Максим
struct integer MOD_ZZ_Z (struct integer a, struct natural b)
{
    struct integer result, support,c;
    int i;
    support=a;
    result=DIV_ZZ_Z(support,b);
    c=MUL_ZZ_Z(result,TRANS_N_Z(b));
    result = SUB_ZZ_Z(support,c);

    return result;
}

//!Модули рациональных чисел

//!Q-1
//!Сокращение дроби
//!Литвинов К.
struct rational RED_Q_Q (struct rational ft_f) {
    struct natural NOD; //Наибольший общий делитель
    struct natural numerator_n; //Натуральное значение числителя
    struct natural denominator_n; // Натуральное значение знаменателя
    struct rational new_ft; //Значения сокращённой дроби
    int compare;

    numerator_n.len=ft_f.lenNum;// Переводим числитель и знаменатель в натуральные числа
    denominator_n.len=ft_f.lenDen;
    numerator_n.num=ft_f.numerator;
    denominator_n.num=ft_f.denominator;

    compare=COM_NN_D(numerator_n, denominator_n);
    if (compare==1)
        NOD=GCF_NN_N(denominator_n, numerator_n);
    else
        NOD=GCF_NN_N(numerator_n, denominator_n); //Находим наибольший общий делитель числителя и знаменателя
    numerator_n=DIV_NN_N(numerator_n, NOD); //Сокращаем числитель
    denominator_n=DIV_NN_N(denominator_n, NOD); //Сокращаем знаминатель

    //natprint(numerator_n);
    //natprint(denominator_n);

    new_ft.sign=ft_f.sign; //Присваиваем новой дроби значения числителя и знаменателя
    new_ft.numerator=numerator_n.num;
    new_ft.lenNum=numerator_n.len;
    new_ft.denominator=denominator_n.num;
    new_ft.lenDen=denominator_n.len;

    return new_ft;
}

//!Q-2
//!Проверка на целое, 1 если цело, иначе 0
//!Литвинов К.
int INT_Q_B (struct rational fr_f) { //numerator — знаменатель, denominator — числитель
    if ((fr_f.denominator[fr_f.lenDen-1]==1) && (fr_f.lenDen==1) ) {
        return 1;
        //printf("Yes\n"); //Пишет "Yes", если число целое
    }
    else {
        return 0;
        //printf ("No\n"); //Пишет "No", если число не целое
    }
}

//!Q_3
//!Преобразование целого числа в дробное
//!Кочмарев Г.
struct rational TRANS_Z_Q(struct integer c)
{
    struct rational k;
    int i;
    k.sign=c.sign;
    k.lenNum=c.len;
    k.numerator=(int*)malloc(k.lenNum*sizeof(int));
    for (i=0;i<c.len;i++)
        k.numerator[i]=c.num[i];
    k.denominator=(int*)malloc(sizeof(int));
    k.denominator[0]=1;
    k.lenDen=1;
    return k;
}


//!Q_4
//!Преобразование дробного в целое (если знаменатель равен 1)
//!Кочмарев Г.
struct integer TRANS_Q_Z(struct rational d)
{
    struct integer s;
    int i;
    if((!(d.lenDen==1)&&(d.denominator[0]==1)))                         //Не уверен в необходимости этой проверки
        printf("Error in function TRANS_Q_Z. Denominator!=1.");   //И в том, что функция должна передавать, если проверка не пройдена
    s.sign=d.sign;
    s.len=d.lenNum;
    s.num=(int*)malloc(s.len*sizeof(int));
    for (i=0;i<d.lenNum;i++)
        s.num[i]=d.numerator[i];
    return s;
}

//!Q-5
//!Сложение дробей
//!Лалаев А.
struct rational ADD_QQ_Q(struct rational a, struct rational b){

    int sign = 0;                                       // Содержит информацию о знаках дробей. 0, если плюс. 1, если минус
    int Flag = 1;

    struct rational result;

    struct natural lcmDen;                              // Общий знаменатель
    struct natural firstNum;                            // Числитель первой дроби
    struct natural secondNum;                           // Числитель второй дроби

    struct natural firstDen;                            // Знаменатель первой дроби
    struct natural secondDen;                           // Знаменатель второй дроби

    struct natural thirdNum;

    struct natural multi1;                              // Частное от деления общего знаменателя на числитель для пе��вой дроби
    struct natural multi2;                              // Частное от деления общего знаменателя на числитель для второй дроби

    firstNum.num = a.numerator;                         // Числитель первой дроби
    firstNum.len = a.lenNum;                            // Длина числителя первой дроби
    firstDen.num = a.denominator;                       // Знаменатель первой дроби
    firstDen.len = a.lenDen;                            // Длина знаменателя первой дроби

    secondNum.num = b.numerator;                        // Числитель второй дроби
    secondNum.len = b.lenNum;                           // Длина числителя второй дроби
    secondDen.num = b.denominator;                      // Знаменатель второй дроби
    secondDen.len = b.lenDen;                           // Длина знаменателя второй дроби

    if (a.sign != b.sign){
        if (a.sign == 1){                               // Если у "а" знак - минус, то меняем его на плюс и вызываем вычитание дробей(ИЗ b вычитаем а)
            a.sign = 0;
            result = SUB_QQ_Q(b, a);
        }
        else if (b.sign == 1){                          // Если у "b" знак - минус, то меняем его на плюс и вызываем вычитание дробей(ИЗ a вычитаем b)
            b.sign = 0;
            result = SUB_QQ_Q(a, b);
        }
        Flag = 0;
    }
    else if ((a.sign == b.sign) && (a.sign == 1)){
        a.sign = 0;                                     // Делаем знак "+"
        b.sign = 0;
        sign = 1;                                       // Сохраняем предыдущий знак
    }
    if (Flag == 1){
        lcmDen = LCM_NN_N(firstDen, secondDen);         // Находим общий знаменатель
        multi1 = DIV_NN_N(lcmDen, firstDen);            // Находим на что нужно умножить первый числитель
        multi2 = DIV_NN_N(lcmDen, secondDen);           // Находим на что нужно умножить второй числитель
        firstNum = MUL_NN_N(firstNum, multi1);          // Домножаем числитель первой дроби
        secondNum = MUL_NN_N(secondNum, multi2);        // Домножаем числитель второй дроби
        thirdNum = ADD_NN_N(firstNum, secondNum);       // Складываем числители первых двух

        result.denominator = lcmDen.num;                // Знаменатель результирующей дроби
        result.lenNum = thirdNum.len;
        result.numerator = thirdNum.num;
        result.lenDen = lcmDen.len;
        result.sign = sign;
    }
    if (result.numerator[0]!=0)
        result=RED_Q_Q(result);
    return result;
}

//!Q-6
//!Вычитание дробей
//!Литвинов К.
struct rational SUB_QQ_Q(struct rational a, struct rational b){

    int sign = 0;                                       // Содержит информацию о знаках дробей. 0, если плюс. 1, если минус
    int Flag = 1;

    struct rational result;

    struct natural lcmDen;                              // Общий знаменатель
    struct natural firstNum;                            // Числитель первой дроби
    struct natural secondNum;                           // Числитель второй дроби

    struct natural firstDen;                            // Знаменатель первой дроби
    struct natural secondDen;                           // Знаменатель второй дроби

    struct natural thirdNum;

    struct natural multi1;                              // Частное от деления общего знаменателя на числитель для пе��вой дроби
    struct natural multi2;                              // Частное от деления общего знаменателя на числитель для второй дроби

    firstNum.num = a.numerator;                         // Числитель первой дроби
    firstNum.len = a.lenNum;                            // Длина числителя первой дроби
    firstDen.num = a.denominator;                       // Знаменатель первой дроби
    firstDen.len = a.lenDen;                            // Длина знаменателя первой дроби

    secondNum.num = b.numerator;                        // Числитель второй дроби
    secondNum.len = b.lenNum;                           // Длина числителя второй дроби
    secondDen.num = b.denominator;                      // Знаменатель второй дроби
    secondDen.len = b.lenDen;                           // Длина знаменателя второй дроби

    if (a.sign != b.sign){
        if (a.sign == 1){                               // Если у "а" знак - минус, то меняем его на плюс и вызываем вычитание дробей(ИЗ b вычитаем а)
            b.sign = 1;
            result = ADD_QQ_Q(b, a);
        }
        else if (b.sign == 1){                          // Если у "b" знак - минус, то меняем его на плюс и вызываем вычитание дробей(ИЗ a вычитаем b)
            b.sign = 0;
            result = ADD_QQ_Q(a, b);
        }
        Flag = 0;
    }
    else if ((a.sign == b.sign) && (a.sign == 1)){
        a.sign = 0;                                     // Делаем знак "+"
        b.sign = 0;
        sign = 1;                                       // Сохраняем предыдущий знак
    }
    if (Flag == 1){
        lcmDen = LCM_NN_N(firstDen, secondDen);         // Находим общий знаменатель
        multi1 = DIV_NN_N(lcmDen, firstDen);            // Находим на что нужно умножить первый числитель
        multi2 = DIV_NN_N(lcmDen, secondDen);           // Находим на что нужно умножить второй числитель
        firstNum = MUL_NN_N(firstNum, multi1);          // Домножаем числитель первой дроби
        secondNum = MUL_NN_N(secondNum, multi2);        // Домножаем числитель второй дроби
        thirdNum = SUB_NN_N(firstNum, secondNum);       // Складываем числители первых двух

        result.denominator = lcmDen.num;                // Знаменатель результирующей дроби
        result.lenNum = thirdNum.len;
        result.numerator = thirdNum.num;
        result.lenDen = lcmDen.len;
        if (COM_NN_D(firstNum,secondNum)==1)
            sign=1;
        result.sign = sign;
    }

    if (result.numerator[0]!=0)
        result=RED_Q_Q(result);
    return result;
}

//!Q-7
//!Умножение дробей
//!Холопов И.
struct rational MUL_QQ_Q(struct rational R1, struct rational R2 )
{
    struct rational R3;
    struct integer INT1;
    struct integer INT2;
    struct integer INT3;
    int i;

    INT1.sign=R1.sign;
    INT1.len=R1.lenNum;
    INT1.num=R1.numerator;

    INT2.sign=R2.sign;
    INT2.len=R2.lenNum;
    INT2.num=R2.numerator;

    INT3=MUL_ZZ_Z(INT1,INT2);
    R3.sign=INT3.sign;
    R3.lenNum=INT3.len;
    R3.numerator=INT3.num;

    INT1.len=R1.lenDen;
    INT1.num=R1.denominator;

    INT2.len=R2.lenDen;
    INT2.num=R2.denominator;

    INT3=MUL_ZZ_Z(INT1,INT2);
    R3.lenDen=INT3.len;
    R3.denominator=INT3.num;

   // if (GCF_NN_N())
   //     R3=RED_Q_Q(R3);
    return R3;
}

//!Q-8
//!Деление дробей
//!Холопов И.
struct rational DIV_QQ_Q(struct rational R1, struct rational R2 )
{
    struct rational R3;
    struct integer INT1;
    struct integer INT2;
    struct integer INT3;

    INT1.sign=R1.sign;
    INT1.len=R1.lenNum;
    INT1.num=R1.numerator;

    INT2.sign=R2.sign;
    INT2.len=R2.lenDen;
    INT2.num=R2.denominator;

    INT3=MUL_ZZ_Z(INT1,INT2);
    R3.sign=INT3.sign;
    R3.lenNum=INT3.len;
    R3.numerator=INT3.num;

    INT1.len=R1.lenDen;
    INT1.num=R1.denominator;

    INT2.len=R2.lenNum;
    INT2.num=R2.numerator;

    INT3=MUL_ZZ_Z(INT1,INT2);
    R3.lenDen=INT3.len;
    R3.denominator=INT3.num;

    R3=RED_Q_Q(R3);
    return R3;
}

//!Многочлены

//!P-1
//!Сложение многочленов
//!Колмакова
struct polynomial ADD_PP_P(struct polynomial p_1, struct polynomial p_2){
int flag=0, max=0; // max - максимальная степень многочлена
int i, j, k, j1, k1,t;
struct polynomial newp;// или так struct polynomial *newp=malloc(sizeof(struct polynomial));
struct polynomial p1=p_1,p2=p_2;
//(newp->deg)=(int*)malloc(sizeof(int));
for( i=0; i<p1.len; i++){ // находим максимальную степень многочлена
if( p1.deg[i]>max) max = p1.deg[i];
}
for( i=0; i<p2.len; i++){
if( p2.deg[i]>max) max = p2.deg[i];
}
//newp.len=(p_2.len>p_1.len)?p_2.len:p_1.len;
newp.len=0;
newp.deg=(int*)malloc(sizeof(int));
newp.coeff=(struct rational*)malloc(sizeof(struct rational));
for( i=max; i>-1; i--){
flag=0;
j1=0;
k1=0;
for( j=0; j<p1.len; j++){ // проверяем есть ли такая степень в первом полиноме
if( i == p1.deg[j]) {
flag=1;
j1=j;
}
}
for( k=0; k<p2.len; k++){ // проверяем есть ли такая степень во втором полиноме
if( i == p2.deg[k]) {
flag+=2; //+= или =
k1=k;
}
}
if( flag == 3) { // если такая степень есть в обоих полиномах складываем коэффициенты
newp.len++;
newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
newp.deg[newp.len-1]=i;
newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
newp.coeff[newp.len-1]=ADD_QQ_Q( p1.coeff[j1], p2.coeff[k1]);
}
if( flag == 2) { // если такая степень есть во втором полиноме записываем этот коэффициент в многочлен
newp.len++;
newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
newp.deg[newp.len-1]=i;
newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
newp.coeff[newp.len-1]=p2.coeff[k1];
}
if( flag == 1) { //если такая степень есть в первом полиноме записываем этот коэффициент в многочлен
newp.len++;
newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
newp.deg[newp.len-1]=i;
newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
newp.coeff[newp.len-1]=p1.coeff[j1];
}
}

if (newp.len>1){
    for (j=0;j<newp.len-1;j++)
            if ((newp.coeff[j].numerator[0]==0)){
                for (t=j;t<newp.len-1;t++){
                    newp.coeff[t]=newp.coeff[t+1];
                    newp.deg[t]=newp.deg[t+1];
                }
                    newp.len--;
                    j--;
                    newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
                    newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
            }
        if (newp.coeff[j].numerator[0]==0){
            newp.len--;
            newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
            newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
        }
    }
    if ((newp.len==1) && (newp.coeff[0].lenNum==1) && (newp.coeff[0].numerator[0]==0))
        newp.deg[0]=0;

return newp;
}

//!P-2
//!Вычитание многочленов
//!Колмакова
struct polynomial SUB_PP_P(struct polynomial p_1, struct polynomial p_2)
{
    int flag=0, max=0; // max - максимальная степень многочлена
    int i, j, k, j1, k1,t;
    struct polynomial newp;// или так struct polynomial *newp=malloc(sizeof(struct polynomial)); //новый многочлен
    struct polynomial p1,p2;
    //(newp->deg)=(int*)malloc(sizeof(int));
    p1=p_1;
    p2=p_2;
    for( i=0; i<p1.len; i++)
        { // находим максимальную степень многочлена
        if( p1.deg[i]>max) max = p1.deg[i];
        }
    for( i=0; i<p2.len; i++)
    {
        if( p2.deg[i]>max) max = p2.deg[i];
    }
    newp.len=0;
    newp.deg=(int*)malloc(sizeof(int));
    newp.coeff=(struct rational*)malloc(sizeof(struct rational));
    for( i=max; i>-1; i--)
    {
        flag=0;
        j1=0;
        k1=0;
        for( j=0; j<p1.len; j++)// проверяем есть ли такая степень в первом полиноме
        {
            if( i == p1.deg[j])
            {
                flag=1;
                j1=j;
            }
        }
        for( k=0; k<p2.len; k++)// проверяем есть ли такая степень во втором полиноме
        {
            if( i == p2.deg[k])
            {
                flag+=2;
                k1=k;
            }
        }
        if( flag == 3)// если такая степень есть в обоих полиномах, вычитаем коэффициенты
        {
            newp.len++;
            newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
            newp.deg[newp.len-1]=i;
            newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
            newp.coeff[newp.len-1]=SUB_QQ_Q( p1.coeff[j1], p2.coeff[k1]);
        }
        if( flag == 2) // если такая степень есть во втором полиноме записываем этот коэффициент в многочлен
        {
            newp.len++;
            newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
            newp.deg[newp.len-1]=i;
            newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
            newp.coeff[newp.len-1]=p2.coeff[k1];
            newp.coeff[newp.len-1].sign=(p2.coeff[k1].sign==1)?0:1;
        }
        if( flag == 1)//если такая степень есть в первом полиноме записываем этот коэффициент в многочлен
        {
            newp.len++;
            newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
            newp.deg[newp.len-1]=i;
            newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
            newp.coeff[newp.len-1]=p1.coeff[j1];
        }
    }

    if (newp.len>1){
    for (j=0;j<newp.len-1;j++)
            if ((newp.coeff[j].numerator[0]==0)){
                for (t=j;t<newp.len-1;t++){
                    newp.coeff[t]=newp.coeff[t+1];
                    newp.deg[t]=newp.deg[t+1];
                }
                    newp.len--;
                    j--;
                    newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
                    newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
            }
        if ((newp.coeff[j].numerator[0]==0) && (newp.len>1)){
            newp.len--;
            newp.coeff=(struct rational*)realloc(newp.coeff,newp.len*sizeof(struct rational));
            newp.deg=(int*)realloc(newp.deg,newp.len*sizeof(int));
        }
    }
    if ((newp.len==1) && (newp.coeff[0].lenNum==1) && (newp.coeff[0].numerator[0]==0))
        newp.deg[0]=0;

    return newp;
}

//!P-3
//!умножение многочлена на рациональное число
//!Щетинина Т.
struct polynomial MUL_PQ_P(struct polynomial strP, struct rational mnoz) //strP - многочлен исходный; mnoz - число-множитель
{
	int i, kol, j, t;
	struct polynomial newPol; //новый многочлен;
	newPol.len=strP.len; //количество слагаемых неизменно
	newPol.coeff=(struct rational*)malloc(newPol.len*sizeof(struct rational));
	kol=newPol.len; //присваиваем длину массива переменной kol
	(newPol.deg)=(int*)malloc((kol)*sizeof(int));
	for(i=0;i<kol;i++)
	{
		newPol.deg[i]=strP.deg[i]; //степени при переменных не меняются копируем их
		newPol.coeff[i]=MUL_QQ_Q(strP.coeff[i],mnoz); //коэффициенты меняем используя модуль MUL_QQ_Q
	}

if (newPol.len>1){
    for (j=0;j<newPol.len-1;j++)
            if ((newPol.coeff[j].numerator[0]==0)){
                for (t=j;t<newPol.len-1;t++){
                    newPol.coeff[t]=newPol.coeff[t+1];
                    newPol.deg[t]=newPol.deg[t+1];
                }
                    newPol.len--;
                    j--;
                    newPol.coeff=(struct rational*)realloc(newPol.coeff,newPol.len*sizeof(struct rational));
                    newPol.deg=(int*)realloc(newPol.deg,newPol.len*sizeof(int));
            }
        if (newPol.coeff[j].numerator[0]==0){
            newPol.len--;
            newPol.coeff=(struct rational*)realloc(newPol.coeff,newPol.len*sizeof(struct rational));
            newPol.deg=(int*)realloc(newPol.deg,newPol.len*sizeof(int));
        }
    }
    if ((newPol.len==1) && (newPol.coeff[0].lenNum==1) && (newPol.coeff[0].numerator[0]==0))
        newPol.deg[0]=0;


	return newPol; //возвращаем новый многочлен
}

//!P-4
//!Умножение многочлена на x^k
//!Лебедев
struct polynomial MUL_Pxk_P(struct polynomial Polynom, int k)//Передается вся исходная структура Polynom, k-степень x, на который мы умножаем
{
int j;
int length;//Длина массива
struct polynomial newPolynom; //новый многочлен
	newPolynom.len=Polynom.len;
	newPolynom.coeff=(struct rational*)malloc(newPolynom.len*sizeof(struct rational));
	newPolynom.deg=(int*)malloc(newPolynom.len*sizeof(int));
	length=newPolynom.len;
for (j=0;j<length;j++)
  {
    newPolynom.deg[j]=Polynom.deg[j]+k;//Ко всем степеням многочлена прибавляем k
    newPolynom.coeff[j]=Polynom.coeff[j];
  }

return newPolynom;
}

//!P-5
//!Старший коэффициент многочлена
//!Лебедев
struct rational LED_P_Q(struct polynomial Polynom){ //Передается вся структура
    int i,max;
    int c;//Адрес максимальной степени/старшего коэффициента
    c=0;
    max=-1; //Переменная, которая хранит максимальную степень
    for (i=0;i<Polynom.len;i++){    // Идем по массиву степеней, ищем максимальную
        if (Polynom.deg[i]>max){
            max=Polynom.deg[i];
            c=i;
            }
    }
    return Polynom.coeff[c];//Возвращаем коэффициент
}

//!P-6
//!вычисление старшей степени многочлена
//!Щетинина Т.
int DEG_P_N(struct polynomial strP) //передаётся весь многочлен
{
	int i, deg, lens;
	deg=strP.deg[0]; //первый элемент принимаем за максимум
	lens=strP.len;  //длина массива степеней для удобства присваивается переменной
	for(i=1;i<lens;i++) //с элемента [1] т.к. [0] уже максимум
	{
		if((strP.deg[i])>deg)
			deg=strP.deg[i];
	}

	return deg; //возвращается максимальная степень
}

///P-7
//    P-7
//    Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей
//    Щетинина Т.

struct polynomial FAC_P_Q(struct polynomial initPol)
{
	struct polynomial newPol;
	struct integer *numer, NOK_2, quot;
	struct natural *numNat, *denom, NOK, NOD;
	int i, n;

	n=initPol.len; //длина массива коэффициентов
	numer=(struct integer*)malloc(n*sizeof(struct integer)); //выделяеется память под массив структур для числителей
	denom=(struct natural*)malloc(n*sizeof(struct natural));  // для знаменателей
	numNat=(struct natural*)malloc(n*sizeof(struct natural));  //для числителей в натуральном виде

	for(i=0;i<n;i++) //разбиваем массив коэффициентов на два массива - массив числителей и массив знаменателей
	{
		numer[i].sign=initPol.coeff[i].sign;
		numer[i].len=initPol.coeff[i].lenNum;
		numer[i].num=initPol.coeff[i].numerator;

		denom[i].len=initPol.coeff[i].lenDen;
		denom[i].num=initPol.coeff[i].denominator;
	}


	NOK=LCM_NN_N(denom[0],denom[1]); //вычисление НОК знаменателей
	for(i=2;i<n;i++)
	{
		NOK=LCM_NN_N(NOK,denom[i]);
	}


	NOK_2=TRANS_N_Z(NOK); //преобразуем НОК из natural в integer

	for(i=0;i<n;i++)
	{
		quot=DIV_ZZ_Z(NOK_2,denom[i]);  //делим НОК на знаменатель т.к. НОК>=знаменателю
		numer[i]=MUL_ZZ_Z(numer[i],quot);  //домножаем соответствующй числитель на частное
	}



		for(i=0;i<n;i++)  //переводим массив числителей из integer в natural
	{
		numer[i]=ABS_Z_N(numer[i]); //получаем модуль числа
		numNat[i]=TRANS_Z_N(numer[i]);  //переводим в натуральное
	}


	NOD=GCF_NN_N(numNat[0],numNat[1]);

	for(i=2;i<n;i++)  //находим НОД числителей
	{
		NOD=GCF_NN_N(NOD, numNat[i]);
	}

	for(i=0;i<n;i++)  //делим каждый числитель на НОД
	{
		numer[i]=DIV_ZZ_Z(numer[i],NOD);
	}


		newPol.len=initPol.len;  //копирование коэффициентов и других данных в новый многочлен
		newPol.coeff=(struct rational*)malloc(newPol.len*sizeof(struct rational));
		newPol.deg=(int*)malloc(newPol.len*sizeof(int));
	for(i=0;i<n;i++)
	{
		newPol.coeff[i].sign=initPol.coeff[i].sign;  //знаки при слагаемых те, что в исходном многочлене
		newPol.coeff[i].lenNum=numer[i].len; //у числителей длина новых числителей
		newPol.coeff[i].lenDen=1; //длина знаменателя 1 т.к. при делении на НОК они все стали равны 1
		newPol.coeff[i].numerator=numer[i].num;  //новые числители
		newPol.coeff[i].denominator=(int*)malloc(sizeof(int));
		newPol.coeff[i].denominator[0]=1; //все знаменатели равны 1
		newPol.deg[i]=initPol.deg[i]; //степени не изменились
	}
	free(numNat);
	free(denom);
	free(numer);
	return newPol;
}

//!P-8
//!Умножение многочленов
//!Колмакова
struct polynomial MUL_PP_P(struct polynomial p_1, struct polynomial p_2)
{
    struct polynomial newp,temp;// или так struct polynomial newp=malloc(sizeof(struct polynomial));
    int flag=0, max=0,max1=0,max2=0;// max - максимальная степень многочлена
    int i, j, k, t, h;
    struct rational sum; // сумма нужных многочленов
    struct rational mult; // произведение нужных многочленов
    struct polynomial p1=p_1,p2=p_2;



    newp.len=1;
    newp.deg=(int*)malloc(sizeof(int));
    newp.coeff=(struct rational*)malloc(sizeof(struct rational));
    newp.deg[0]=0;
    newp.coeff[0]=inputratio("0");


    for (i=0;i<p2.len;i++){
        temp=MUL_Pxk_P(p1,p2.deg[i]);
        temp=MUL_PQ_P(temp,p2.coeff[i]);
        //polprint(temp);
        newp=ADD_PP_P(newp,temp);
    }

    return newp;
}
//!P-9
//!Деление
struct polynomial DIV_PP_P(struct polynomial p_1, struct polynomial p_2) { //p_1 p_2 — Первый и второй полином
    int degree1, degree2, mult, i=0,j,t; //degree1, degree2 — степени первого и второго числа, mult — степень, на которую надо умножить многочлен
    struct polynomial temp_p; //Умноженный на какой-то другой многочлен, многочлен, нужен чтобы вычитать из р_1 значения
    struct polynomial temp_pp; ///На что надо умножать многочлен, чтобы делить столбиком
    struct polynomial di_v; //Частное от деления на многочлен
    struct rational temp; //Коэффициент на котрый надо умножить многочлен
    struct polynomial p1,p2;
    p1=p_1;
    p2=p_2;
    di_v.len=1;
    di_v.deg=(int*)malloc(sizeof(int));
    di_v.deg[0]=0;
    di_v.coeff=(struct rational*)malloc(sizeof(struct rational));
    di_v.coeff[0]=inputratio("0");
    degree1=DEG_P_N(p1); //Находим степень первого числа
    degree2=DEG_P_N(p2); //Находим степень второго числа
    if (degree1>=degree2) {
        mult=degree1-degree2; //Находим разность степеней
        //printf("%d", degree1);
        temp=DIV_QQ_Q(p1.coeff[i], p2.coeff[i]); //Находим коэффициент, на который надо домнажать
        temp_p=p2; //Приравниваем многочлен, чтобы потом домножить его на нужныее коэфициенты
        temp_pp.coeff=(struct rational*)malloc(1*sizeof(struct rational));
        temp_pp.coeff[0]=temp;//Состовляем структуру для первого коэффициента
        temp_pp.deg=(int*)malloc(1*sizeof(int));
        temp_pp.deg[0]=mult;
        temp_pp.len=1;
        temp_p=MUL_Pxk_P(temp_p, mult);//Перемножаем временный полином на нужные коэффициенты
        temp_p=MUL_PQ_P(temp_p, temp);//Перемножаем временный полином на нужные коэффициенты
        p1=SUB_PP_P(p1, temp_p); //Вычитаем из оригинального полинома, полученный полином
        di_v=ADD_PP_P(di_v,temp_pp); //Приравниваем к частному от деления
        degree1=DEG_P_N(p1);
    }
    else {//КОГДА 0, ДОБАВТЕ СВОЙ ИНПУТ
        di_v.deg=(int*)malloc(1*sizeof(int));
        di_v.deg[0]=0;
        di_v.len=1;
        di_v.coeff=(struct rational*)malloc(sizeof(struct rational));
        di_v.coeff[0]=inputratio("0");
    }
    while (degree1>=degree2) { //Аналогично то, что выше
        mult=degree1-degree2;
        temp=DIV_QQ_Q(p1.coeff[0], p2.coeff[0]);
        //printf("%d ",degree1);
        temp_pp.coeff[0]=temp;
        temp_pp.deg[0]=mult;
        temp_p=p2;
        temp_p=MUL_Pxk_P(temp_p, mult);
        temp_p=MUL_PQ_P(temp_p, temp);
        p1=SUB_PP_P(p1, temp_p);
        di_v=ADD_PP_P(di_v,temp_pp); //Прибавляем коэффициент к нужному частному
        if ((degree2==0) && (degree1==0))
            break;
        degree1=DEG_P_N(p1);//Находим высшую степень, чтобы цикл не умер
    }
    return di_v;// Возвращаем частное
}

//!    P-10
//!    Остаток от деления многочлена на многочлен при делении с остатком
//!    Щетинина Т.
struct polynomial MOD_PP_P(struct polynomial P1, struct polynomial P2)  //P1 - делимое; P2 - делитель
{
    int j,t;
	struct polynomial newp, dopPol;
    struct polynomial p1=P1,p2=P2;

	dopPol=DIV_PP_P(p1, p2);  //получаем частное от деления первого на второй
	dopPol=MUL_PP_P(dopPol, p2); //умножаем частное на делитель
	newp=SUB_PP_P(p1, dopPol); //вычисляем разность полученного произведения и делимого

	return newp;
}


//!    P-11
//!    НОД многочленов
//!    Щетинина Т.
struct polynomial GCF_PP_P(struct polynomial P1, struct polynomial P2)
{
	struct polynomial GCF, delim, delit;


	if(DEG_P_N(P1)>DEG_P_N(P2))  //вычисляем у какого многочлена больше степень
	{
		delim=P1; //делимое
		delit=P2;  //делитель

		GCF=MOD_PP_P(delim,delit); //вычисляем первый остаток

		while(GCF.coeff[0].numerator[0]!=0)  //пока остаток не равен нулю
		{
		    //printf("%d\n",GCF.coeff[0].numerator[0]);
			delim=delit;  //делитель теперь делимое
			delit=GCF;  //делителем будет новый остаток
			GCF=MOD_PP_P(delim,delit);  //вычисляем остаток от их деления
		}
	}
	else
	{
		delim=P2;  //проделываем те же операции что и в if
		delit=P1;

		GCF=MOD_PP_P(delim,delit);

		while(GCF.coeff[0].numerator[0]!=0)
		{
			delim=delit;
			delit=GCF;
			GCF=MOD_PP_P(delim,delit);
		}
	}

	return delit;  //возвращаем последний делитель - он и будет НОД многочленов
}

//! P-12
//! Производная многочлена
//! Лебедев К.
struct polynomial DER_P_P(struct polynomial Polynom)
{
int i,j=0,t,k,n;
char* s=NULL;
struct rational numer;//Структура для создания из числителя натурального числа
struct polynomial newPolynom,p;//Новый многочлен
p=Polynom;

newPolynom.deg=(int*)malloc(p.len*sizeof(int));
newPolynom.coeff=(struct rational*)malloc(p.len*sizeof(struct rational));

for (i = 0; i < p.len; i++)
{
if (p.deg[i] != 0)
{

newPolynom.deg[j]=p.deg[i]-1;
n=p.deg[i];
t=0;
while (n>0){
    n=n/10;
    t++;
}
s=(char*)realloc(s,(t+1)*sizeof(char));
s=itoa(p.deg[i],s,10);
numer=inputratio(s);

newPolynom.coeff[j]=MUL_QQ_Q(numer,p.coeff[i]);
j++;

}
}
newPolynom.len=j;

free(s);
s=NULL;
return newPolynom;
}

//!P-13
//!Преобразование многочлена - кратные корни в простые
//!Абакарова Ю. и Литвинов К.

struct polynomial NMR_P_P(struct polynomial pol_f) {
    struct polynomial deg; //Производная полинома
    struct polynomial NOD; //НОД изначального исходного полинома и его производной
    struct polynomial newpol_f; //Полученный результат

    deg=DER_P_P(pol_f); //Находим производную
    NOD=GCF_PP_P(pol_f, deg); //Находим НОД  исходного полинома и его производной
    newpol_f=DIV_PP_P(pol_f, NOD); //Делим исходный полином на его производную

    newpol_f=FAC_P_Q(newpol_f);
    return newpol_f;
}

void natural_sector(int main_menu)
{
    char *num_1=NULL, *num_2=NULL, *num_3=NULL;
    struct natural nat_res, nat_1, nat_2, nat_3;
    int D, K, result;
    D=0; K=0; result=0;
    switch(main_menu)
    {
        case 1:
            printf("- N-1:  Comparison of natural numbers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            result=COM_NN_D(nat_1, nat_2);
            //printf("%d", result);
            if (result==1) {printf("The second number is bigger then the first\n");}
            else if (result == 2) {printf("The first number is bigger then the second\n");}
            else {printf("Numbers are equal\n");}
            break;
        case 2:
            printf("- N-2:  Verification by zero;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            nat_1=inputnat(num_1);
            result=NZER_N_B(nat_1);
            //printf("%d", result);
            if (result==0) {printf("Inputed number equals 0\n");}
            else {printf("Inputed number is not equals 0");}
            break;
        case 3:
            printf("- N-3:  Appendix 1 to the natural;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            nat_1=inputnat(num_1);
            nat_res=ADD_1N_N(nat_1);
            natprint(nat_res);
            break;
        case 4:
            printf("- N-4:  Addition of natural numbers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=ADD_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 5:
            printf("- N-5:  Subtraction from the first largest natural number\n        of the second smaller or equal;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=SUB_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 6:
            printf("- N-6:  Multiplication of a natural number by a digit;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in digit: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            D=nat_2.num[0];
            nat_res=MUL_ND_N(nat_1, D);
            natprint(nat_res);
            break;
        case 7:
            printf("- N-7:  Multiplication of a natural number by 10^k;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in digit: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            K=nat_2.num[0];
            nat_res=MUL_Nk_N(nat_1, K);
            natprint(nat_res);
            break;
        case 8:
            printf("- N-8:  Multiplication of natural numbers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=MUL_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 9:
            printf("- N-9:  Subtraction from natural other natural, multiplied\n        by a digit for the case with a non-negative result;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in digit: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            printf("Put in second number: ");
            num_3=line2(num_3);
            nat_3=inputnat(num_3);
            D=nat_3.num[0];
            nat_res=SUB_NDN_N(nat_1, D, nat_2);
            natprint(nat_res);
            break;
        case 10:
            printf("- N-10: The calculation of the first digit of the division\n        of a larger natural number into a smaller one, multiplied\n        by 10 ^ k, where k is the position number of this digit;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=DIV_NN_Dk(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 11:
            printf("- N-11: Private from dividing a larger natural number into\n        a smaller or equal natural number with a remainder;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=DIV_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 12:
            printf("- N-12: The remainder of dividing a larger natural number\n        by less or equal to the natural number with a remainder;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=MOD_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 13:
            printf("- N-13: GCD of natural numbers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=GCF_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        case 14:
            printf("- N-14: LCM of natural numbers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            nat_1=inputnat(num_1);
            nat_2=inputnat(num_2);
            nat_res=LCM_NN_N(nat_1, nat_2);
            natprint(nat_res);
            break;
        default:
            printf("Wrong menu value!\n");
    }
}

void integer_sector(int main_menu)
{
    char *num_1=NULL, *num_2=NULL;
    struct natural nat_res, nat_2;
    struct integer int_res, int_1, int_2;
    int result;
    result=0;
    switch(main_menu)
    {
        case 1:
            printf("- Z-1:  Absolute value of the number;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            int_1=inputint(num_1);
            int_res=ABS_Z_N(int_1);
            intprint(int_res);
            break;
        case 2:
            printf("- Z-2:  Determination of positivity of a number;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            int_1=inputint(num_1);
            result=POZ_Z_D(int_1);
            //printf("%d", result);
            if (result==1) {printf("Number is negative\n");}
            else if(result==0) {printf("Inputed number equals 0\n");}
            else {printf("Number is positive\n");}
            break;
        case 3:
            printf("- Z-3:  Multiplication of an integer by (-1);\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            int_1=inputint(num_1);
            int_res=MUL_ZM_Z(int_1);
            intprint(int_res);
            break;
        case 4:
            printf("- Z-4:  Converting a natural into an integer;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            nat_res=inputnat(num_1);
            int_res=TRANS_N_Z(nat_res);
            intprint(int_res);
            break;
        case 5:
            printf("- Z-5:  The transformation of a non-negative integer into a\n        natural;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            int_1=inputint(num_1);
            nat_res=TRANS_Z_N(int_1);
            natprint(nat_res);
            break;
        case 6:
            printf("- Z-6:  Adding integers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            int_1=inputint(num_1);
            int_2=inputint(num_2);
            int_res=ADD_ZZ_Z(int_1, int_2);
            intprint(int_res);
            break;
        case 7:
            printf("- Z-7:  Subtraction of integers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            int_1=inputint(num_1);
            int_2=inputint(num_2);
            int_res=SUB_ZZ_Z(int_1, int_2);
            intprint(int_res);
            break;
        case 8:
            printf("- Z-8:  Multiplication of integers;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            int_1=inputint(num_1);
            int_2=inputint(num_2);
            int_res=MUL_ZZ_Z(int_1, int_2);
            intprint(int_res);
            break;
        case 9:
            printf("- Z-9:  Private from dividing the larger integer by less\n        than or equal to the natural number with the remainder;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            int_1=inputint(num_1);
            nat_2=inputnat(num_2);
            int_res=DIV_ZZ_Z(int_1, nat_2);
            intprint(int_res);
            break;
        case 10:
            printf("- Z-10: The remainder of dividing the larger integer by\n        less than or equal to the natural number with the remainder;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            int_1=inputint(num_1);
            nat_2=inputnat(num_2);
            int_res=MOD_ZZ_Z(int_1, nat_2);
            intprint(int_res);
            break;
        default:
            printf("Wrong menu value!\n");
    }
}


void rational_sector(int main_menu)
{
    struct rational rat_1, rat_2, rat_res;
    struct integer int_res;
    char *num_1=NULL, *num_2=NULL;
    int result;
    result=0;
    switch(main_menu)
    {
        case 1:
            printf("- Q-1:  Reduction of fractions;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            rat_res=RED_Q_Q(rat_1);
            ratprint(rat_res);
            break;
        case 2:
            printf("- Q-2:  Checking for an integer, if the rational number is\n        an integer, then yes, otherwise no;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            result=INT_Q_B(rat_1);
            //printf("%d", result);
            if(result==1) {printf("Number is integer\n");}
            else {printf("Number is rational\n");}

            break;
        case 3:
            printf("- Q-3:  Convert integer to fractional;\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            int_res=inputint(num_1);
            rat_res=TRANS_Z_Q(int_res);
            ratprint(rat_res);
            break;
        case 4:
            printf("- Q-4:  The conversion of fractional into an integer\n        (if the denominator is 1);\n");
            printf("Put in number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            int_res=TRANS_Q_Z(rat_1);
            intprint(int_res);
            break;
        case 5:
            printf("- Q-5:  Addition of fractions;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            rat_2=inputratio(num_2);
            rat_res=ADD_QQ_Q(rat_1, rat_2);
            ratprint(rat_res);
            break;
        case 6:
            printf("- Q-6:  Subtraction of fractions;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            rat_2=inputratio(num_2);
            rat_res=SUB_QQ_Q(rat_1, rat_2);
            ratprint(rat_res);
            break;
        case 7:
            printf("- Q-7:  Multiplication of fractions;\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            rat_2=inputratio(num_2);
            rat_res=MUL_QQ_Q(rat_1, rat_2);
            ratprint(rat_res);
            break;
        case 8:
            printf("- Q-8:  The division of fractions (the divisor is\n        different from zero);\n");
            printf("Put in first number: ");
            num_1=line2(num_1);
            rat_1=inputratio(num_1);
            printf("Put in second number: ");
            num_2=line2(num_2);
            rat_2=inputratio(num_2);
            rat_res=DIV_QQ_Q(rat_1, rat_2);
            ratprint(rat_res);
            break;
        default:
            printf("Wrong menu value!\n");
    }
}


void polynomial_sector(int main_menu)
{
    char *num_1=NULL, *num_2=NULL;
    struct polynomial pol_1, pol_2, pol_res;
    struct rational rat_res, rat_2;
    struct natural nat_1;
    int result, K;
    result=0; K=0;
    switch(main_menu)
    {
        case 1:
            printf("- P-1:  Addition of polynomials;\n");
            printf("Put in first polynomial: ");
            num_1=line2(num_1);
            printf("Put in second polynomial: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            pol_2=inputpol(num_2);
            pol_res=ADD_PP_P(pol_1, pol_2);
            polprint(pol_res);
            break;
        case 2:
            printf("- P-2:  Subtraction of polynomials;\n");
            printf("Put in first polynomial: ");
            num_1=line2(num_1);
            printf("Put in second polynomial: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            pol_2=inputpol(num_2);
            pol_res=SUB_PP_P(pol_1, pol_2);
            polprint(pol_res);
            break;
        case 3:
            printf("- P-3:  Multiplication of a polynomial by a rational number;\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            printf("Put in rational number: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            rat_2=inputratio(num_2);
            pol_res=MUL_PQ_P(pol_1, rat_2);
            polprint(pol_res);
            break;
        case 4:
            printf("- P-4:  Multiplication of a polynomial by x^k;\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            printf("Put in natural number: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            nat_1=inputnat(num_2);
            K=nat_1.num[0];
            pol_res=MUL_Pxk_P(pol_1, K);
            polprint(pol_res);
            break;
        case 5:
            printf("- P-5:  The leading coefficient of the polynomial;\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            pol_1=inputpol(num_1);
            rat_res=LED_P_Q(pol_1);
            ratprint(rat_res);
            break;
        case 6:
            printf("- P-6:  The degree of a polynomial;\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            pol_1=inputpol(num_1);
            result=DEG_P_N(pol_1);
            printf("%d\n", result);
            break;
        case 7:
            printf("- P-7:  The derivation from the LCM polynomial of the\n        denominators of the coefficients and the GCD of\n        the numerators;\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            pol_1=inputpol(num_1);
            pol_res=FAC_P_Q(pol_1);
            polprint(pol_res);
            break;
        case 8:
            printf("- P-8:  Multiplication of polynomials;\n");
            printf("Put in first polynomial: ");
            num_1=line2(num_1);
            printf("Put in second polynomial: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            pol_2=inputpol(num_2);
            pol_res=MUL_PP_P(pol_1, pol_2);
            polprint(pol_res);
            break;
        case 9:
            printf("- P-9:  Partial from dividing a polynomial into a polynomial\n        in division with a remainder;\n");
            printf("Put in first polynomial: ");
            num_1=line2(num_1);
            printf("Put in second polynomial: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            pol_2=inputpol(num_2);
            pol_res=DIV_PP_P(pol_1, pol_2);
            polprint(pol_res);
            break;
        case 10:
            printf("- P-10: The remainder of dividing the polynomial into a\n        polynomial in the division with the remainder;\n");
            printf("Put in first polynomial: ");
            num_1=line2(num_1);
            printf("Put in second polynomial: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            pol_2=inputpol(num_2);
            pol_res=MOD_PP_P(pol_1, pol_2);
            polprint(pol_res);
            break;
        case 11:
            printf("- P-11: GCD of polynomials;\n");
            printf("Put in first polynomial: ");
            num_1=line2(num_1);
            printf("Put in second polynomial: ");
            num_2=line2(num_2);
            pol_1=inputpol(num_1);
            pol_2=inputpol(num_2);
            pol_res=GCF_PP_P(pol_1, pol_2);
            polprint(pol_res);
            break;
        case 12:
            printf("- P-12: The polynomial derivative;\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            pol_1=inputpol(num_1);
            pol_res=DER_P_P(pol_1);
            polprint(pol_res);
            break;
        case 13:
            printf("- P-13: Transformation of a polynomial - multiple roots\n        into simple;\n\n");
            printf("Put in polynomial: ");
            num_1=line2(num_1);
            pol_1=inputpol(num_1);
            pol_res=NMR_P_P(pol_1);
            polprint(pol_res);
            break;
        default:
            printf("Wrong menu value!\n");
    }
}


int main()
{
    system("color 1E");
    printf(" Welcome to the Computer Algebra System\n");
//!меню
char sector_menu;
int main_menu;
printf(" Choose group of modules\n n - for naturals\n z - for integers\n q - for rationals\n p - for polynomials \n or 0 to stop\n");
scanf("%c", &sector_menu);
getchar();
while(sector_menu!='0')
{
    switch(sector_menu)
    {
    case 'n':
        printf("Choose module\n 1-14\n");
        printf("- N-1:  Comparison of natural numbers;\n");
        printf("- N-2:  Verification by zero;\n");
        printf("- N-3:  Appendix 1 to the natural;\n");
        printf("- N-4:  Addition of natural numbers;\n");
        printf("- N-5:  Subtraction from the first largest natural number\n        of the second smaller or equal;\n");
        printf("- N-6:  Multiplication of a natural number by a digit;\n");
        printf("- N-7:  Multiplication of a natural number by 10^k;\n");
        printf("- N-8:  Multiplication of natural numbers;\n");
        printf("- N-9:  Subtraction from natural other natural, multiplied\n        by a digit for the case with a non-negative result;\n");
        printf("- N-10: The calculation of the first digit of the division\n        of a larger natural number into a smaller one, multiplied\n        by 10 ^ k, where k is the position number of this digit;\n");
        printf("- N-11: Private from dividing a larger natural number into\n        a smaller or equal natural number with a remainder;\n");
        printf("- N-12: The remainder of dividing a larger natural number\n        by less or equal to the natural number with a remainder;\n");
        printf("- N-13: GCD of natural numbers;\n");
        printf("- N-14: LCM of natural numbers;\n");
        scanf("%d", &main_menu);
        getchar();
        while(main_menu!=0)
        {
            natural_sector(main_menu);
            printf("Choose again or 0 to go back\n");
            scanf("%d", &main_menu);
            getchar();
        }
        break;
    case 'z':
        printf("Choose module\n 1-10\n");
        printf("- Z-1:  Absolute value of the number;\n");
        printf("- Z-2:  Determination of positivity of a number;\n");
        printf("- Z-3:  Multiplication of an integer by (-1);\n");
        printf("- Z-4:  Converting a natural into an integer;\n");
        printf("- Z-5:  The transformation of a non-negative integer into a\n        natural;\n");
        printf("- Z-6:  Adding integers;\n");
        printf("- Z-7:  Subtraction of integers;\n");
        printf("- Z-8:  Multiplication of integers;\n");
        printf("- Z-9:  Private from dividing the larger integer by less\n        than or equal to the natural number with the remainder;\n");
        printf("- Z-10: The remainder of dividing the larger integer by\n        less than or equal to the natural number with the remainder;\n");
        scanf("%d", &main_menu);
        getchar();
        while(main_menu!=0)
        {
            integer_sector(main_menu);
            printf("Choose again or 0 to go back\n");
            scanf("%d", &main_menu);
            getchar();
        }
        break;
    case 'q':
        printf("Choose module\n 1-8\n");
        printf("- Q-1:  Reduction of fractions;\n");
        printf("- Q-2:  Checking for an integer, if the rational number is\n        an integer, then yes, otherwise no;\n");
        printf("- Q-3:  Convert integer to fractional;\n");
        printf("- Q-4:  The conversion of fractional into an integer\n        (if the denominator is 1);\n");
        printf("- Q-5:  Addition of fractions;\n");
        printf("- Q-6:  Subtraction of fractions;\n");
        printf("- Q-7:  Multiplication of fractions;\n");
        printf("- Q-8:  The division of fractions (the divisor is\n        different from zero);\n");
        scanf("%d", &main_menu);
        getchar();
        while(main_menu!=0)
        {
            rational_sector(main_menu);
            printf("Choose again or 0 to go back\n");
            scanf("%d", &main_menu);
            getchar();
        }
        break;
    case 'p':
        printf("Choose module\n 1-13\n");
        printf("- P-1:  Addition of polynomials;\n");
        printf("- P-2:  Subtraction of polynomials;\n");
        printf("- P-3:  Multiplication of a polynomial by a rational number;\n");
        printf("- P-4:  Multiplication of a polynomial by x^k;\n");
        printf("- P-5:  The leading coefficient of the polynomial;\n");
        printf("- P-6:  The degree of a polynomial;\n");
        printf("- P-7:  The derivation from the LCM polynomial of the\n        denominators of the coefficients and the GCD of\n        the numerators;\n");
        printf("- P-8:  Multiplication of polynomials;\n");
        printf("- P-9:  Partial from dividing a polynomial into a polynomial\n        in division with a remainder;\n");
        printf("- P-10: The remainder of dividing the polynomial into a\n        polynomial in the division with the remainder;\n");
        printf("- P-11: GCD of polynomials;\n");
        printf("- P-12: The polynomial derivative;\n");
        printf("- P-13: Transformation of a polynomial - multiple roots\n        into simple;\n\n");
        printf("USE ONLY x AS VARIABLE\n");
        scanf("%d", &main_menu);
        getchar();
        while(main_menu!=0)
        {
            polynomial_sector(main_menu);
            printf("Choose again or 0 to go back\n");
            scanf("%d", &main_menu);
            getchar();

        }
        break;
    default:
        printf("Wrong menu value!\n");
    }
    printf("Choose group of modules\n n - for naturals\n z - for integers\n q - for rationals\n p - for polynomials \n or 0 to stop\n");
    scanf("%c", &sector_menu);
    getchar();
}
}
