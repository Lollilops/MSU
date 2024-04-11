#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>



char current_path[1000];
char prev_buf[1000];

/* если встретили cd*/
int MayBeCD(char *s) {
	char *c = s;
	while (*c == ' ')
		c += 1; // пробелы
	// это команда cd? если нет, то выходим из функции
	if ( *c != 'c' )
		return 2;
	c++;
	if ( *c != 'd' )
		return 2;
	c++;
	if ( *c != ' ' )
		return 2;
	while (*c == ' ')
		c++;
	// да, это cd
	// считаем, что она корректная и что у неё есть только один аргумент в виде пути,	
	// надо перекопировать имя новой директории
	char *d = c;
	while (*c != ' ' && *c != '\0')
		c++;
	char helper = *c;
	*c = '\0';
	d = strdup(d);
	*c = helper;
	// у cd есть два стандартных случая: если путь начинается с /, то он абсолютный,
	// если не начинается, то это добавка к тому пути, что есть
	// также есть два особенных случая: "." и "..", это секущая и родительская директория
	if ( strcmp(d,".") == 0 ) {
		free(d);
		return 0;
	}
	if ( strcmp(d,"..") == 0 ) {
		free(d);
		if ( strcmp(current_path,"/") == 0 )
			return 1; // корневой диалог не имеет родителя
		c = current_path + strlen(current_path);
		while (*c != '/')
			c--;
		*c = '\0';
		if ( strcmp(current_path,"") == 0 )
			strcpy(current_path,"/");
		return chdir(current_path);
	}
	if ( d[0] == '/' ) {
		int k = chdir(d);
		free(d);
		return k;
	} else {
		strcat(current_path,"/");
		strcat(current_path,d);
		free(d);
		return chdir(current_path);
	}
	return 0;
}

void first_iter(char *s);

char *input_string() {
	char *ptr = (char *)malloc(100);
	char c;
	int i = 0;
	c = getchar();
	while ((c != '\n') && (c != EOF)) {
		ptr[i] = c;
		c = getchar();
		i++;
	}
	ptr[i] = '\0';
	return ptr;
}

char **make_vector(char *s, int n) { 
	char *c = s; // 0 | => exec 1st son, 1 | => exec next son

	int bracketsCounter = 0;
	for (int i = 0; i < n;) {
		if (*c == '(')
			bracketsCounter += 1;
		if (*c == ')')
			bracketsCounter -= 1;
		if (*c == '|' && bracketsCounter == 0)
			i += 1; // пропускаем палки, пока не дойдем до команды, которую надо выполнить
		//но только те палки, которые не внутри скобок
		c += 1;
	}
	if (*c == '|') c += 1;

	char *d = c; // указатель на начало команды
	// посчитаем число СЛОВ
	// sort -r t.txt - 3 слова
	int argc = 0;
	while (*c == ' ')
		c += 1; // пробелы
	while (*c != '|' && *c != '\0') { // все слова в одной команде
		while (*c != '|' && *c != '\0' && *c != ' ') { // одно слово в выбранной команде
			c += 1; // все буквы в команде
		}
		while (*c == ' ')
			c += 1; // пробелы
		argc += 1;	// число слов
	}

	char **argv = (char**)malloc(sizeof(char *) * (argc + 1));
	argv[argc] = NULL;

	c = d; // c - указывает на начало команды
	for (int i = 0; i < argc; i += 1) {
		// strdup = malloc + strcpy
		while (*c == ' ')
			c += 1;
		d = c;
		// d - на начало слова
		while (*c != '|' && *c != '\0' && *c != ' ') {
			c += 1;
		}
		// с - на символ после слова
		*c = '\0';
		argv[i] = strdup(d); // d - слово в команде его первый символ
		c += 1;
	}

	return argv; // указатель на вектор аргументов
}

void Brackets_produce(char *s, int n) {
	// printf("Скобки\n");
	char *c = s; // 0 | => exec 1st son, 1 | => exec next son
	int bracketsCounter = 0;
	for (int i = 0; i < n;) {
		if (*c == '(')
			bracketsCounter += 1;
		if (*c == ')')
			bracketsCounter -= 1;
		if (*c == '|' && bracketsCounter == 0)
			i += 1; // пропускаем палки, пока не дойдем до команды, которую надо выполнить
		//но только те палки, которые не внутри скобок
		c += 1;
	}
	if (*c == '|') c += 1;
	
	while (*c == ' ')
		c += 1; // пробелы
	if ( *c == '(' ) {
		char *d = c+1;
		bracketsCounter = 1;
		while ( bracketsCounter > 0 ) {
			c += 1;
			if (*c == '(')
				bracketsCounter += 1;
			if (*c == ')')
				bracketsCounter -= 1;
		}
		*c = '\0';
		first_iter(d);
		exit(0);
	}
}

char *get_input_file(char *s) {
	// after reading input name, меняем исходную строку (затираем пробелами)
	// поменяем строку - она поменяется везде
	// использовать s[i] = ' '
	int i = 0;
	while (s[i] != '\0' && s[i] != '<')
		i += 1;
	if (s[i] == '\0')
		return NULL;
	s[i] = ' '; // затереть < пробелом
	while (s[i] == ' ')
		i += 1; // пропускаем все пробелы, в том числе бывшего <
	int j = i;	// s[j] - первый символ имени файла
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|')
		i += 1;			// пропускаем имя файла
	// j - первый символ имени файла, i - первый символ после имени файла
	char helper = s[i]; // символ после слова
	s[i] = '\0';
	char *c = strdup(s + j); // указатель на 1й символ имени файла
	s[i] = helper;			 // вернули исходный символ

	while (j < i) { // затираем пробелами
		s[j] = ' ';
		j += 1;
	}
	return c;
}

char *get_output_file(char *s, int *append) {
	int i = 0;
	while (s[i] != '\0' && s[i] != '>')
		i += 1;
	if (s[i] == '\0')
		return NULL;
	s[i] = ' ';
	i += 1;
	if (s[i] == '>') {
		s[i] = ' ';	 // затираем пробелом
		*append = 1; // если двойная > => дозапись файла
	}
	while (s[i] == ' ')
		i += 1;
	int j = i;
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '|')
		i += 1;

	char helper = s[i];
	s[i] = '\0';
	char *c = strdup(s + j);
	s[i] = helper;

	while (j < i) {
		s[j] = ' ';
		j += 1;
	}

	return c;
}

int make_conv(char *s) { // для каждого конвейера
	// n - число | + 1 (amount of sons)
	// считаем сколько "|" => for (0, n-1) fork()
	// сын знает свой номер, он анализирует строку и формирует argv
	// по argv делаем exec
	char *fInput = get_input_file(s);
	int append = 0;	// если 1 - то файл будет дописываться
	char *fOutput = get_output_file(s, &append); // передаем по ссылке, чтобы он изменился

	int n = 1;
	char *c = s;
	int bracketsCounter = 0;
	while (*c != '\0') {
		if (*c == '(')
			bracketsCounter += 1;
		if (*c == ')')
			bracketsCounter -= 1;
		if (*c == '|' && bracketsCounter == 0)
			n += 1;
		c += 1;
	}
	
	if ( n == 1 ) {
		int k = MayBeCD(s);
		if (k == 0)
			return 0;
		if (k == 1)
			return 1;
		// do nothing if k == 2
	}
	
	int *sons = (int *)malloc(sizeof(int) * n); // PIDs of son processes

	int fd[2], prevpipe;

	for (int i = 0; i < n; i += 1) {
		if (i != n - 1) // 0..n-2 для последнего сына не пипируем
			pipe(fd);
		if ((sons[i] = fork()) == 0) {
			/* ВВОД */
			if (i != 0) { // для 1го сына STDIN
				dup2(prevpipe, 0); // вместо STDIN, дескриптор - prevpipe (каналы)
			} // дескриптор - есть файл, и где мы находимся в этом файле

			else {
				// первый - берёт из файла или из STDIN
				if (fInput != NULL) {
					int j = open(fInput, O_RDONLY);
					if (j == -1) { // нет такого файла
						j = open("/dev/null", O_RDONLY); // то вообще ничего не подаём на вход
					}
					dup2(j, 0); // стандартный ввод из файла fInput
				}
			}

			/* ВЫВОД */
			if (i != n - 1) { // для последнего сына STDOUT
				dup2(fd[1], 1); // вместо STDOUT, дескриптор - fd[1]
			}
			else {
				// первый - берёт из файла или из STDIN
				if (fOutput != NULL) {
					int j;
					if (append == 0) // перезаписываем файл
						j = open(fOutput, O_WRONLY | O_CREAT | O_TRUNC, 0777); // 0777 права доступа на чтения запись и exe
					else // дозаписываем в файл
						j = open(fOutput, O_WRONLY | O_CREAT | O_APPEND, 0777);
					dup2(j, 1); // стандартный вывод из файла fOutput
				}
			}
			/**/
			
			Brackets_produce(s,i);
			/* Если это скобки, то мы не вернёмся из Brackets_produce */
			char **argv = make_vector(s, i); // i - номер сына, у сына копия исходной строки => можем портить
			execvp(argv[0], argv); // -1 не нашел такой команды
			printf("Такой команды не существует: %s\n", argv[0]); // только при -1
			exit(1);
		}
		if (n != 1) { // если в конвейере 1 программа - не делаем pipe
			if (i == 0) { // 1й сын
				prevpipe = fd[0];
				close(fd[1]); // закрываем только вывод
			}
			else if (i == n - 1) { // последний сын
				close(prevpipe); // закрываем только ввод
			}
			else {
				close(prevpipe); // закрываем ввод
				prevpipe = fd[0];
				close(fd[1]); // закрываем вывод
			}
		}
	}

	int k;
	for (int i = 0; i < n; i += 1)
		waitpid(sons[i], &k, 0); // 0 - выполняйся так, как логичнее (флаги)
	free(sons);
	free(fInput);
	free(fOutput);
	return k;
}

void second_iter(char *s) {
	// printf("Получено: %s\n", s);
	char *c = s;
	char helper;
	while (*c == ' ')
		c += 1;

	while (*c != '\0') { // вся str
		int bracketsCounter = 0;
		while (*c != '\0') { // берет целый CONV(N)
			// надо поймать double && или ||
			if (*c == '(')
				bracketsCounter += 1;
			if (*c == ')')
				bracketsCounter -= 1;
			if (*c == '|' && *(c + 1) == '|' && bracketsCounter == 0)
				break;
			if (*c == '&' && *(c + 1) == '&' && bracketsCounter == 0)
				break; // в (с-1) можно заглядывать т.к. изначально s+1
			c += 1;
		}
		helper = *c;
		*c = '\0';
		// printf("Выполнение %s\n", s);
		int status = make_conv(s); // 0 - завершилась хорошо, otherwise bad
		// printf("Выполнил: %s\n", s);
		*c = helper; // начало краевых условий (LOGN ;    \0) or (LONG\0)
		/**/
		if (status != 0 && helper == '&')
			break; // && выполняется при успешном выполнении предыдущей команды
		if (status == 0 && helper == '|')
			break; // при неуспешном выполнении
		/**/
		if (*c == '\0')
			break;
		c += 2; // двойные операнды
		while (*c == ' ')
			c += 1;
		s = c; // конец краевых условий
	}
	// printf("Отдача: %s\n", s);
	return;
}

void first_iter(char *s) {
	char *c = s + 1; // s - начало каждой str, c - указатель на текущей символ,
	char helper;
	while (*c == ' ') // пропускаем пробелы
		c += 1;
	int bracketsCounter = 0;
	/* считает сбалансированность скобок */
	if ( *s == '(' )
		bracketsCounter += 1;

	while (*c != '\0') {
		while (*c != '\0') { // берет целый LOGN
			// надо поймать одинарную & или ;
			if (*c == '(')
				bracketsCounter += 1;
			if (*c == ')')
				bracketsCounter -= 1;
			if (*c == ';' && bracketsCounter == 0)
				break;
			if (*c == '&' && *(c + 1) != '&' && *(c - 1) != '&' && bracketsCounter == 0)
				break; // в (с-1) можно заглядывать т.к. изначально s+1
			c += 1;
		}

		helper = *c;
		*c = '\0';
		if (helper == ';' || helper == '\0') {
			second_iter(s);
		}
		else {
			// если сын - фоновый процесс, то после выполнения он станет зомби тк предок метрв
			// а если отец ждет - то это не фоновый процесс
			int k = fork(); // создается сын
			if (k == 0) {
				if (fork() == 0) { // создается внук
					signal(SIGINT, SIG_IGN); // игнорим ctrl-C
					// фоновый процесс не должен читать с STDIN
					int fd = open("/dev/null", O_RDONLY);
					dup2(fd, 0); // дескриптор номер 0 (сейчас STDIN) заменить на fd
					// внук считает своим стандартном вводом dev/null, но он выдает EOF
					close(fd);
					second_iter(s);
					exit(0);
				}
				exit(0); // убиваем сына
			}
			waitpid(k, NULL, 0); // ловим сына, чтобы не стал зомби
		}

		*c = helper; // начало строки (STR ;    \0) or (STR\0)
		if (*c == '\0')
			break;
		c += 1;
		while (*c == ' ')
			c += 1;// пробелы в самом конце строки
		s = c;// теперь следующей функции подаётся строка с новым началом
	}
	return;
}

int main(int argc, char **argv) {
	while (1) {
		getcwd(current_path,1000);
		printf("%s:~$ ",current_path);
		char *s = input_string();
		if ( strcmp(s,"exit") == 0 ) {
			free(s);
			return 0;
		}
		first_iter(s);
		free(s);
	}
}
