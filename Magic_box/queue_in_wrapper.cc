	
/*CQueue * new_queue(){
	queue4 *queue1 = new queue4(); //initiating queue
	//queue<data1> *queue1 = new (nothrow) queue<data1>; //initiating queue
	return (CQueue *)queue1;
	}*/
/*CQueue * new_queue1(){
	queue4 *queue1 = new queue4(); //initiating queue
	//std::queue<data1> queue1; //initiating queue
	return (CQueue *)queue1;
	}*/	

/*
void enqueue2(CQueue * queue1,const CItem * item){
	printf("Test11\n");
	//queue4 *que1 = (queue4 *)malloc(sizeof(queue1)); 
	//memcpy(que1 ,(queue4 *)queue1,sizeof(queue1));
	queue4 *que1 = (queue4*)queue1;
	//queue<data1> *que1;
	//que1 =
	//data1 *n1 =(data1*)malloc(sizeof(item));
	//memcpy(n1 ,(data1*)item,sizeof(item));
	data1 *n1 = (data1*)item;
	printf("Test12\n");
	que1->enqueue4((*n1));
	printf("Test13\n");
	//memcpy(queue1 ,(CQueue *)que1,sizeof(que1));
	free(que1);
	printf("Test14\n");
	//que1->enqueue4(*n1);
	queue1 = (CQueue *)que1;
	//return (CQueue *)que1->enqueue4(*n1);
	}
	
void dequeue2( CQueue * queue1,CItem * item){
	printf("Test31\n");
	queue4 *que1 = (queue4 *)malloc(sizeof(queue1)); 
	memcpy(que1 ,(queue4 *)queue1,sizeof(queue1));
	//queue4 *que1 = (queue4*)queue1;
	//queue *que1 = (queue*)queue1; 
	printf("Test32\n");
	data1 *n1 = (data1*)malloc(sizeof(item));
	printf("Test33\n");
	memcpy(n1 ,(data1*)item,sizeof(item));
	//data1 *n1 = (data1*)item; //setting the type for pointer
	que1->dequeue4(*n1); //sending the pointer address
	printf("Test34\n");
	//item = (CItem *)n1; 
	memcpy(item ,(CItem *)n1,sizeof(n1));
	printf("Test35\n");
	queue1 = (CQueue *)que1;
	//memcpy(queue1 ,(CQueue *)que1,sizeof(que1));
	free(que1);
	printf("Test36\n");
	//return queue1; //sending the pointer address

}
/*
void enqueue3(CQueue * queue1,const CItem * item){
	queue4 *que1 = (queue4*)queue1;
	//queue<data1> *que1;
	//que1 =
	data1 *n1 = (data1*)item;
	que1->enqueue4(*n1);
	memcpy(queue1 ,(CQueue *)que1,sizeof((CQueue *)que1));
	//que1->enqueue4(*n1);
	//queue1 = (CQueue *)que1;
	//return (CQueue *)que1->enqueue4(*n1);
	}
	
void dequeue3( CQueue * queue1,CItem * item){
	queue4 *que1 = (queue4*)queue1;
	//queue *que1 = (queue*)queue1; 
	data1 *n1 = (data1*)item; //setting the type for pointer
	que1->dequeue4(*n1); //sending the pointer address
	//item = (CItem *)n1; 
	memcpy(item ,(CItem *)n1,sizeof((CItem *)n1));
	//queue1 = (CQueue *)que1;
	memcpy(queue1 ,(CQueue *)que1,sizeof((CQueue *)que1));
	//return queue1; //sending the pointer address

}*/
/*
int check_full(CQueue * queue1){
	int check = 0;
	queue4 *que1 = (queue4 *)queue1;
	check = que1->isfull();
	return check;
	}


int check_empty(CQueue * queue1){
	int check = 0;
	queue4 *que1 = (queue4 *)queue1;
	check = que1->isempty();
	return check;
	}


void delete_queue(CQueue * queue1){
	queue4 *que1 = (queue4 *)queue1;
	delete que1;
	}
}
*/
