//这个文件提供基本数据类型

//基本数据类型
typedef struct SListNode {
	ValueData data;
	struct SListNode * next;
}ListNode;

typedef struct SList {
	ListNode node;
}List;

typedef enum EValueType {
	boolean,integer,real,list,word
}ValueType;

typedef union UValueDate {
	long long integer;
	double real;
	char * word;
	List * list;
}ValueData;

typedef struct SValue {
	ValueType type;
	ValueData data;
}Value;
