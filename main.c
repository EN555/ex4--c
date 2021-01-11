#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUM_LETTERS 26
char *word = NULL;
int num_words =0;
int counter=0;



typedef struct Node{

char letter;
int count;
int num_of_child;
char *word;
struct Node * children[NUM_LETTERS];

} Node;

struct Node* new_node(char ch, int is_it_end){  //create new struct

    struct Node* node= (struct Node*)malloc(sizeof(struct Node));
    node -> letter = ch;
	node -> count = 0;
	node -> num_of_child =0;
    node -> count = (node -> count) + is_it_end;
	node -> word = NULL;
    for(int i=0; i< NUM_LETTERS; i++){
        node ->children[i]= NULL;
    }
    return node;
}


void get_word(struct Node* node,char *word){
    char *pn = word;
    while(*pn){     //move on the word          
        
        if(node -> children[*pn -97]){
                if(strlen(pn) == 1){    //stay else one char
                    node = node -> children[*pn -97] ;
                    node -> count= (node ->count) +1;
                    pn++;
                }
                else{
                      node = node -> children[*pn -97] ;
                      pn++;
                }
            }
          else{       //create new node and insert him to this node
              if(strlen(pn) == 1){
                node->num_of_child =  (node->num_of_child) +1;
                 node->children[*pn -97] = new_node(*pn ,1);
                    node = node->children[*pn -97];
                      pn++;    
              }
              else{
                    node->children[*pn -97] = new_node(*pn ,0);
                    node->num_of_child =  (node->num_of_child) +1;
                    node = node->children[*pn -97];
                     pn++;            
              }
             }
        } 

    return;
        
}

int create_tree(Node * node){  //read the text according to the assighnment
    
    char c;
	char *wd =NULL; //the word
	int count=0;
    while((c=getchar()) != EOF){

        if(c>=97 && c<=122){	// a -- z
			char * tp= NULL;
			if(count ==0){	//if it's the first char in the word
				wd = (char *)malloc((count+2)*sizeof(char));
				*(wd+count) =c;
				*(wd+count+1)= '\0';
				count++;
			}
			else{
				tp = wd;
				wd = (char *)malloc((count+2)*sizeof(char));
				strcpy(wd , tp);
				*(wd+count)= c;
				*(wd+count+1)= '\0';
				free(tp);
				count++;	
			}
		}
		else if(c>= 65 && c<= 90){	// A --- Z
			c = c+32;
			char * tp= NULL;
			if(count==0){		
			    wd = (char *)malloc((count+2)*sizeof(char));
				*(wd+count) =c;
				*(wd+count+1)= '\0';
				count++;	
			}
			else{	
				tp = wd;
				wd = (char *)malloc((count+2)*sizeof(char));
				strcpy(wd , tp);
				*(wd+count)= c;
				*(wd+count+1)= '\0';
				free(tp);
				count++;				
			}
		}
		else if(c==' ' || c=='\r' || c=='\n' || c=='\t' || c=='\0'){	//add '\0' to the end of the word
			if(count != 0){
				get_word(node, wd);
				free(wd);
			}
			count=0;
		}
		     
    }

	return 0;
    
}

void print_increase_words(Node *pi, int counter){    //print all the words in increasing lexicographical order 

    if(!pi){
        return;
	}
    
    if((pi->letter) != ' '){    //we reach to the end of the tree
			char *tp = NULL;
			tp = word;
			word =(char *)malloc(2+ counter*sizeof(char));
			if(tp){strcpy(word,tp);}
			free(tp);
			*(word+counter) = pi ->letter;
			*(word+counter+1)= '\0';
			counter++;
			if(pi -> count !=0 ){printf("%s %d\n", word,  pi->count);}   // pi->letter - represent the number of time that need to print
	}

    for(int i=0 ; i < NUM_LETTERS; i++){   // 0 - 1 - 2 
        if(pi-> children[i] != NULL){
        print_increase_words( pi -> children[i] ,counter);
        }

    }

    return ;
}

int print_decrease_words(Node *pi, int counter){    //print all the words in increasing lexicographical order 

    if(!pi){
        return 0;
	}

    if((pi->count) != 0 && pi -> num_of_child ==0 ){    //we reach to the end of the tree
            char *tp = NULL;
			tp = word;
			word =(char *)malloc(2+ counter*sizeof(char));
			if(tp){strcpy(word,tp);}
			if(tp){free(tp);}
			*(word+counter) = pi ->letter;
			*(word+counter+1)= '\0';
            counter+=2;
            printf("%s %d\n", word,  pi->count);   // pi->letter - represent the number of time that need to print    }
			pi -> word = word;
	}
    else{
        if(pi -> letter !=  ' '){
				char *tp = NULL;
				tp = word;
				word =(char *)malloc(2+ counter*sizeof(char));	//add 2 empy places 
				if(tp){strcpy(word, tp);}
				*(word+counter) = pi ->letter;
				*(word+counter+1) = '\0';
				free(tp);
				counter++;
        }
    }
	
    for(int i= NUM_LETTERS-1 ; i >= 0 ; i--){
        
        if(pi ->children[i] != NULL){
             pi -> num_of_child = (pi->num_of_child)-1;
			 print_decrease_words(pi->children[i],counter);
        }
    } 
	

    return 0;
}
int free_last(){
free(word);
return 0;	
}
void free_memory(Node *node){

	if(!node)
		return;
	
	for(int i=0; i< NUM_LETTERS; i++){
		
		if(node-> children[i] != NULL){
			free_memory(node-> children[i]);
			free(node-> children[i]);
		}
	}	
	
	
}


int main(int argc , char* argv[]){
 
Node head;
head.letter = ' ';
head.count =0;
head.num_of_child=0;
for(int i=0; i< NUM_LETTERS; i++){
    head.children[i]= NULL;
}

create_tree(&head);

if(argc==1){
print_increase_words(&head, 0);
free_last();
}
else if(!strcmp(argv[1],"r")){
print_decrease_words(&head, 0);
free_last();
}
else{
printf("This option is incorrect!\n");	
}

free_memory(&head);

 return 0;
}