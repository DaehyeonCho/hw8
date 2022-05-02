/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */
#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("[----------------- [Cho Daehyeon] [2016039075] -----------------]\n");
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){

	if(h->rlink == h)	// 리스트에 노드가 하나밖에 없을 때
	{
		free(h);
		return 1;
	}

	listNode* p = h->rlink;

	listNode* prev = NULL;
	while(p != NULL && p != h) {	// 원형 리스트를 한 바퀴 돌면서 모든 노드 메모리 해제
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);	// 헤더 노드 메모리 해제
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {

	if (h == NULL) return -1;	// 오류 메시지 출력

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 삽입할 노드 생성
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->rlink == h) // 리스트의 첫 노드로 삽입
	{
		h->rlink = node;	// 헤더 노드와 삽입할 노드 잇기
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else {
		h->llink->rlink = node;	// 헤더 노드의 바로 뒤쪽에 삽입할 노드 연결
		node->llink = h->llink;	// 기존의 맨 뒤 노드와 새로 삽입한 노드 연결
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}

int deleteLast(listNode* h) {

	if (h->llink == h || h == NULL)	// 오류 메시지 출력
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink;

	nodetoremove->llink->rlink = h;	// 원형 리스트에서 맨 마지막 노드 연결 끊기
	h->llink = nodetoremove->llink;

	free(nodetoremove);	// 노드 삭제

	return 1;
}

int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 새로 삽입할 노드 생성
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;


	node->rlink = h->rlink;		// 헤더 노드와 맨 앞 노드 사이에 새로운 노드 삽입
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}

int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h)	// 오류 메시지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink;

	nodetoremove->rlink->llink = h;	// 원형 리스트에서 맨 앞 노드 연결 끊기
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);	// 맨 앞 노드 삭제

	return 1;

}

int invertList(listNode* h) {

	if(h->rlink == h || h == NULL) {	// 오류 메시지 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	h->llink = h->rlink;	// 헤더 노드의 좌우 링크 바꾸기

	while(n != NULL && n != h){	// 원형 리스트 한 바퀴 돌면서 수행
		trail = middle;	// trail 한 칸 앞으로 옮기기
		middle = n;		// middle 한 칸 앞으로 옮기기
		n = n->rlink;	// n 한 칸 앞으로 옮기기
		middle->rlink = trail;	// middle의 rlink가 왼쪽 노드를 가리키도록 바꾸기
		middle->llink = n;	// middle의 llink가 오른쪽 노드를 가리키도록 바꾸기
	}

	h->rlink = middle;	// 맨 뒷 노드를 첫 번째 노드로 변경

	return 0;
}

int insertNode(listNode* h, int key) {

	if(h == NULL) return -1;	// 오류 메시지 출력

	listNode* node = (listNode*)malloc(sizeof(listNode));	// 삽입할 노드 생성
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->rlink == h)		// 리스트에 노드가 없을 때
	{
		insertFirst(h, key);
		return 1;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {	
		if(n->key >= key) {		// 삽입하려는 노드의 키값과 리스트에 저장된 키값 비교
			if(n == h->rlink) {	// 맨 앞에 삽입할 때
				insertFirst(h, key);
			} else {			// 중간에 삽입할 때
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}
	insertLast(h, key);		// 맨 마지막에 삽입할 때
	return 0;
}

int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL)	// 오류 메시지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink;

	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { // 맨 앞 노드 삭제할 때
				deleteFirst(h);
			} else if (n->rlink == h){ // 맨 마지막 노드 삭제할 때
				deleteLast(h);
			} else { // 중간 노드 삭제할 때
				n->llink->rlink = n->rlink;	// 앞뒤 노드와 연결 끊기
				n->rlink->llink = n->llink;
				free(n);	// 노드 삭제
			}
			return 0;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);	// 삭제할 노드가 없을 때
	return 0;
}


