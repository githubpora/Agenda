// http://blog.csdn.net/u010667082/article/details/47003813
#include <iostream>

using namespace std;
// construct the node of the queue
struct QUEUENode {
	char data;
	QUEUENode *next;
};
// construct the class of queue
class QUEUE {
	public:
		QUEUE() {
			front = rear = new QUEUENode;
			front->next = NULL;
		}
		~QUEUE() {
			QUEUENode *cur;
			while (front != rear) {
				cur = front->next;
				front->next = cur->next;
				delete cur;
			}
			delete front;
			delete rear;
		}
		// pop the first pushed element of the queue
		void popqueue() {
			if (!queue_empty()) {
				QUEUENode* cur = front->next;
				if (front->next == rear) {
					rear = front;
				}
				front->next = cur->next;
				delete cur;
			}
		}
		// push an element to the queue
		void pushqueue(char element) {
			QUEUENode* que = new QUEUENode;
			que->data = element;
			que->next = NULL;
			rear->next = que;
			rear = que;
		}
		// judge the queue whether is empty or not
		bool queue_empty() {
			if (front == rear) return true;
			else return false;
		}
		// get the top element of the queue.
		char get_queue_top() {
			if (!queue_empty()) {
				return front->next->data;
			}
		}
	protected:
		// the pointer that point to the head element of the queue
		QUEUENode *front;
		// the pointer that point to the final element of the queue
		QUEUENode *rear;
};


struct STACKNode {
	char data;
	STACKNode *next;
};
class STACK {
	public:
		STACK() {
			head = new STACKNode;
			head->next = NULL;
		}
		~STACK() {
			STACKNode *cur;
			while (head->next) {
				cur = head->next;
				head->next = cur->next;
				delete cur;
			}
			delete head;
		}
		void popstack() {
		    if (!stack_empty()) {
                STACKNode* cur = head->next;
                if (cur->next) {
                    head->next = cur->next;
                }
                head->next = NULL;
                delete cur;

		    }
		}
		void pushstack(char element) {
			STACKNode* cur = new STACKNode;
			cur->data = element;
			cur->next = NULL;
			head->next = cur;
			delete cur;
		}
		bool stack_empty() {
			if (!head->next){
				return false;
			}
			return true;
		}
		char get_stack_top_element() {
			if (!stack_empty()) {
				return head->next->data;
			}
		}
	protected:
		STACKNode *head;
};

int main() {
	cout<<"链式存储结构实现队列的入队和出队"<<endl;
	QUEUE myQueue;
	for(int i=0;i<10;i++)
	{
	   char a;
	   cin >> a;
	   myQueue.pushqueue(a);
	}
	cout<<myQueue.get_queue_top()<<endl;
	myQueue.popqueue();
	cout<<myQueue.get_queue_top()<<endl;

    cout<<"链式存储结构实现栈的入栈和出栈"<<endl;
    STACK myStack;
    for(int i=0;i<10;i++)
    {
       char a;
	   cin >> a;
	   myStack.pushstack(a);
    }
    cout<<myStack.get_stack_top_element()<<endl;
    myStack.popstack();
    cout<<myStack.get_stack_top_element()<<endl;

}
