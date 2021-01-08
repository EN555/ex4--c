#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define NUM_LETTERS 26
char word[105];
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
    node -> count = (node -> count) + is_it_end;
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
	char wd[150];
	int count=0;
    while((c=getchar()) != EOF){
        if(c>= 65 && c<= 90){	// A --- Z
			c = c+32;
			wd[count++] = c;
		}
		else if(c>=97 && c<=122){	// a -- z
			wd[count++] = c;
		}
		else if(c==' ' || c=='\r' || c=='\n' || c=='\t' || c=='\0'){
			wd[count]= '\0';
			get_word(node, wd);
			count=0;
		}
		     
    }
	return 0;
    
}

void print_increase_words(Node *pi, int counter){    //print all the words in increasing lexicographical order 

    if(!pi)
        return;
    
    if((pi->count) != 0){    //we reach to the end of the tree
            word[counter++] = pi ->letter;
            word[counter] = '\0';
            printf("%s %d\n", word,  pi->count);   // pi->letter - represent the number of time that need to print
    }
    else{
        if(pi -> letter != ' '){
       word[counter++] = pi->letter;
        }
    }
    for(int i=0 ; i < NUM_LETTERS; i++){   // 0 - 1 - 2 
        if(pi-> children[i] != NULL){
        print_increase_words( pi -> children[i] ,counter);
       // printf("%s" ,word);
        }
    }
    return ;
}



int print_decrease_words(Node *pi, int counter){    //print all the words in increasing lexicographical order 

    if(!pi)
        return 0;

    if((pi->count) != 0 && pi -> num_of_child ==0 ){    //we reach to the end of the tree
            word[counter] = pi ->letter;
            counter+=1;
            word[counter] = '\0';
             printf("%s %d\n", word,  pi->count);   // pi->letter - represent the number of time that need to print    }
    }
    else{
        if(pi -> letter !=  ' '){
         word[counter] = pi ->letter;
         counter+=1;
        }
    }
    for(int i= NUM_LETTERS-1 ; i >= 0 ; i--){
        
        if(pi ->children[i] != NULL){
             pi -> num_of_child = (pi->num_of_child)-1;
             print_decrease_words(pi->children[i],counter);
            
             if((pi->count) != 0 && pi ->num_of_child == 0){    //we reach to the end of the tree
                word[counter] = '\0';
                 printf("%s %d\n", word,  pi->count);   // pi->letter - represent the number of time that need to print    }

                  }
        }

       
    } 


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
}
else if(!strcmp(argv[1],"r")){
print_decrease_words(&head, 0);
}

free_memory(&head);

 return 0;
}