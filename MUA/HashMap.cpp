//����ļ��ṩһ����ϣ��

typedef struct SHashNode {
	char * key;
	void * data;
	struct SHashNode * next;
}HashNode;

typedef struct SHashMap {
	HashNode * data;
	int len;

}HashMap;

HashMap * createHashMap() {

}
	
void setElement(HashMap * hashMap, char * key, void * data) {

}

void * getElement(HashMap * hashMap, char * key) {

}

void removeElement(HashMap * hashMap) {

}