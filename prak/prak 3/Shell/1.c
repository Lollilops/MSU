#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/file.h>

// ps; ls; (cd Shell_A; ls; ps) && ls && ps
// date; (ls -l|cat -n 1.c)>f.txt & pwd
// (cd ..;ls && ps); ls shell_A || ps
// <f.txt cat -n | cat -n | cat -n >b.txt
// sleep 40 & sleep 10;ps
// <f.txt ./proga >b.txt

char current_path[1000];

void predobr(char *s);

char **make_vector(char *s, int n) { 
	char *c = s;

	int bracketsCounter = 0;
	for (int i = 0; i < n;) {
		if (*c == '(')
			bracketsCounter += 1;
		if (*c == ')')
			bracketsCounter -= 1;
		if (*c == '|' && bracketsCounter == 0)
			i += 1;
		c += 1;
	}
	if (*c == '|') c += 1;

	char *d = c;
	// sort -r t.txt - 3 слова
	int argc = 0;
	while (*c == ' ')
		c += 1; 
	while (*c != '|' && *c != '\0') { 
		while (*c != '|' && *c != '\0' && *c != ' ') {
			c += 1;
		}
		while (*c == ' ')
			c += 1;
		argc += 1;
	}

	char **argv = (char**)malloc(sizeof(char *) * (argc + 1));
	argv[argc] = NULL;

	c = d;
	for (int i = 0; i < argc; i += 1) {
		while (*c == ' ')
			c += 1;
		d = c;
		while (*c != '|' && *c != '\0' && *c != ' ') {
			c += 1;
		}
		*c = '\0';
		argv[i] = strdup(d);
		c += 1;
	}

	return argv;
}

int MayBeCD(char *s) {
	char *c = s;
	while (*c == ' ')
		c += 1;
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
	char *d = c;
	while (*c != ' ' && *c != '\0')
		c++;
	char helper = *c;
	*c = '\0';
	d = strdup(d);
	*c = helper;
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

void br_implement(char *s, int n) {
	char *c = s; 
	int br_counter = 0;
	for (int i = 0; i < n;) {
		if (*c == '(')
			br_counter += 1;
		if (*c == ')')
			br_counter -= 1;
		if (*c == '|' && br_counter == 0)
			i += 1;
		c += 1;
	}
	if (*c == '|') c += 1;
	while (*c == ' ')
		c += 1; 
	if ( *c == '(' ) {
		char *d = c+1;
		br_counter = 1;
		while ( br_counter > 0 ) {
			c += 1;
			if (*c == '(')
				br_counter += 1;
			if (*c == ')')
				br_counter -= 1;
		}
		*c = '\0';
		predobr(d);
		exit(0);
	}
}

char *get_input_file(char *s) {
	int i = 0;
	while (s[i] != '\0' && s[i] != '<')
		i += 1;
	if (s[i] == '\0')
		return NULL;
	s[i] = ' ';
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

char *get_output_file(char *s, int *append) {
	int i = 0;
	while (s[i] != '\0' && s[i] != '>')
		i += 1;
	if (s[i] == '\0')
		return NULL;
	s[i] = ' ';
	i += 1;
	if (s[i] == '>') {
		s[i] = ' ';	
		*append = 1;
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

char *input_str() {
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

int implementation(char *s){

	char *fInput = get_input_file(s);
	int append = 0;
	char *fOutput = get_output_file(s, &append);


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
	}
	
	int *sons = (int *)malloc(sizeof(int) * n);

	int fd[2], prevpipe;

	for (int i = 0; i < n; i += 1) {
		if (i != n - 1)
			pipe(fd);
		if ((sons[i] = fork()) == 0) {
			/* ВВОД */
			if (i != 0) {
				dup2(prevpipe, 0);
			} 

			else {
				if (fInput != NULL) {
					int j = open(fInput, O_RDONLY);
					if (j == -1) {
						j = open("/dev/null", O_RDONLY);
					}
					dup2(j, 0);
				}
			}

			/* ВЫВОД */
			if (i != n - 1) {
				dup2(fd[1], 1);
			}
			else{
				if (fOutput != NULL) {
					int j;
					if (append == 0)
						j = open(fOutput, O_WRONLY | O_CREAT | O_TRUNC, 0777);
					else 
						j = open(fOutput, O_WRONLY | O_CREAT | O_APPEND, 0777);
					dup2(j, 1);
				}
			}
			/**/
			
			br_implement(s,i);
			char **argv = make_vector(s, i);
			execvp(argv[0], argv);
			printf("zsh: command not found: cmd %s\n", argv[0]);
			exit(1);
		}
		if (n != 1) { 
			if (i == 0) {
				prevpipe = fd[0];
				close(fd[1]);
			}
			else if (i == n - 1) { 
				close(prevpipe);
			}
			else {
				close(prevpipe);
				prevpipe = fd[0];
				close(fd[1]);
			}
		}
	}

	int k;
	for (int i = 0; i < n; i += 1)
		waitpid(sons[i], &k, 0);
	free(sons);
	free(fInput);
	free(fOutput);
	return k;
}

void choose_implementation(char *s){
	// printf("Получено: %s\n", s);
	char *c=s, helper;
	int br_count = 0;
	while(*c == ' '){
		br_count++;
	}
	while(*c != '\0'){
		while(*c != '\0'){
			if(*c == '('){
				br_count++;
			}
			if(*c == ')'){
				br_count--;
			}
			if(br_count == 0 && *c == '&' && *(c+1) == '&'){
				break;
			}
			if(br_count == 0 && *c == '|' && *(c+1) == '|'){
				break;
			}
			c++;
		}
		helper = *c;
		*c = '\0';
		// printf("Выполнение %s\n", s);// ps && (cd ..; ps)
		int status = implementation(s);
		// printf("Выполнил: %s\n", s);
		// обработка выполнения && и ||
		*c = helper;
		if (status != 0 && helper == '&')
			break; // && выполняется при успешном выполнении предыдущей команды
		if (status == 0 && helper == '|')
			// printf("ghgh\n");
			break;
		if (*c == '\0')
			break;
		c += 2;
		while (*c == ' ')
			c += 1;
		s = c;
	}
	// printf("Отдача: %s\n", s);
	return;
}

void predobr(char *s){
	char *c = s;// com1 && (com2; com3)
	while(*c == ' '){
		c ++;
	}
	int br_count = 0;
	while(*c != '\0'){
		while(*c != '\0'){
			if(*c == '('){
				br_count++;
			}
			if(*c == ')'){
				br_count--;
			}
			if(*c == ';' && br_count == 0){
				break;
			}
			if (*c == '&' && *(c + 1) != '&' && c - s != 0 && *(c - 1) != '&' && br_count == 0)
				break;
			c++;
		}

		char helper = *c;
		*c = '\0';
		if(helper == ';' || helper == '\0'){
			// printf("выполнение команды");
			choose_implementation(s);
		}
		else{// фоновый режим
			// printf("фоновый режим\n");
			int pid1 = fork();
			if(pid1 == 0){
				if(fork() == 0){
					signal(SIGINT, SIG_IGN);
					int f1 = open("/dev/null", O_RDONLY);
					dup2(f1, 0);
					close(f1);
					choose_implementation(s);
					exit(0);
				}
				exit(0); // делаем внука независимымs
			}
			waitpid(pid1, NULL, 0);
			
		}
		*c = helper;
		if(*c == '\0'){
			break;
		}
		c++;
		while(*c == ' '){
			c++;
		}
		s = c;
	}
	return;
}

int main(){
	while(1){
		getcwd(current_path, 1000);
		printf("%s %%", current_path);
		char *s = input_str();
		if ( strcmp(s,"exit") == 0 ) {
			free(s);
			return 0;
		}
		predobr(s);
	}
}