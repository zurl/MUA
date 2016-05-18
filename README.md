# MakeUp Programming Language  
���� : �ų���  

����Ŀ��������ʦ�Ŀγ̡�C�������ר�⡱����ҵ����MITЭ���¿�Դ��  
����Ŀȫ��ʹ��C������ɣ�����������Visual Studio 2015 community edition.
> δ�������ṩMakefile�ļ�  

δ��ɵĲ���
============================

* `//`��ע��
* `: <word>`����thing��ͬ
* `erase <word>`�����word���󶨵�ֵ
* `isname <word>`������word�Ƿ���һ������
* `read`������һ���ӱ�׼�����ȡ�����ֻ򵥴�
* `readlinst`������һ���ӱ�׼�����ȡ��һ�У�����һ���б�����ÿ���Կո�ָ��Ĳ�����list��һ��Ԫ��
* �����operator
	* `mod`��`<operator> <number> <number>`
	* `eq`, `gt`, `lt`��`<operator> <number|word> <number|word>`
	* `and`, `or`��`<operator> <bool> <bool>`
	* `not`��`not <bool>`
* `random <number>`������[0,number>��һ�������
* `sqrt <number>`������number��ƽ����
* `isnumber <value>`������value�Ƿ������� 
* `isword <value>`������value�Ƿ��ǵ���
* `islist <value>`������value�Ƿ����б� 
* `isbool <value>`������value�Ƿ��ǲ����� 
* `isempty <word|list>`: ����word��list�Ƿ��ǿ�
* `test <value>`������value�����Ǽ�
* `iftrue <list>`�����֮ǰ���һ��test���棬��ִ��list
* `iffalse <list>`�����֮ǰ���һ��test�Ǽ٣���ִ��list
* `word <word> <word|number|bool>`��������word�ϲ�Ϊһ��word���ڶ���ֵ������word��number��bool
* `list <list1> <list2>`����list1��list2�ϲ���һ���б������б��Ԫ�ز��У�list1����list2��ǰ��
* `join <list> <value>`����value��Ϊlist�����һ��Ԫ�ؼ��뵽list�У����value���б�������value��Ϊ�б�����һ��Ԫ�أ�
* `first <word|list>`������word�ĵ�һ���ַ�����list�ĵ�һ��Ԫ��
* `last <word|list>`������word�����һ���ַ���list�����һ��Ԫ��
* `butfirst <word|list>`�����س���һ��Ԫ����ʣ�µ��б������һ���ַ���ʣ�µĵ���
* `butlast <word|list>`�����س����һ��Ԫ����ʣ�µ��б�������һ���ַ���ʣ�µĵ���
* `item <number> <word|list>`������word���б��еĵ�number���ַ���Ԫ��
* `repeat <number> <list>`������list�еĴ���number��
* `stop`��ֹͣ��ǰ�����ִ�С���ǰ���������run��repeat��if�����еĴ���
* `wait <number>`���ȴ�number��ms
* `save <word>`�����浱ǰ�����ռ���word�ļ���
* `load <word>`����word�ļ���װ�����ݣ����뵱ǰ�����ռ�
* `erall`�������ǰ�����ռ��ȫ������
* `poall`���г���ǰ�����ռ��ȫ������
* `output <value>`���趨valueΪ���ظ������ߵ�ֵ�����ǲ�ִֹͣ��
* `stop`��ִֹͣ��
* `local <word>`���趨��wordΪ�������֡�����Ҳ�Ǳ�������
 
������ԭ��Ŀ
============================

# MakeUp Programming Language

## ������������value

����number������word���б�list������bool

* ���֣���[0~9]��'-'��ͷ��������������������
* ���ʣ���˫����"��ͷ�������ո񣬲���Unicode����
* �б��Է�����[]���������е�Ԫ���Կո�ָ���Ԫ�ؿ����������ͣ�Ԫ�����Ϳɲ�һ��

## ��������

������ʽ�������� ����

��������һ�������ո�Ĵʣ���������Կո�ָ������������ж��������������Կո�ָ���ÿ����������Ĳ���������ȷ���ģ����Բ���Ҫ���Ż�����������

��������

* `//`��ע��
* `make <word> <value>`�� ��value�󶨵�word�ϡ����������ĵ��ʲ������������word���󶨺��word�������֣�λ�������ռ�
* `thing <word>`������word���󶨵�ֵ
* `: <word>`����thing��ͬ
* `erase <word>`�����word���󶨵�ֵ
* `isname <word>`������word�Ƿ���һ������
* `print <value>`�����value
* `read`������һ���ӱ�׼�����ȡ�����ֻ򵥴�
* `readlinst`������һ���ӱ�׼�����ȡ��һ�У�����һ���б�����ÿ���Կո�ָ��Ĳ�����list��һ��Ԫ��
* �����operator
	* `add`, `sub`, `mul`, `div`, `mod`��`<operator> <number> <number>`
	* `eq`, `gt`, `lt`��`<operator> <number|word> <number|word>`
	* `and`, `or`��`<operator> <bool> <bool>`
	* `not`��`not <bool>`
* `random <number>`������[0,number>��һ�������
* `sqrt <number>`������number��ƽ����
* `isnumber <value>`������value�Ƿ������� 
* `isword <value>`������value�Ƿ��ǵ���
* `islist <value>`������value�Ƿ����б� 
* `isbool <value>`������value�Ƿ��ǲ����� 
* `isempty <word|list>`: ����word��list�Ƿ��ǿ�
* `test <value>`������value�����Ǽ�
* `iftrue <list>`�����֮ǰ���һ��test���棬��ִ��list
* `iffalse <list>`�����֮ǰ���һ��test�Ǽ٣���ִ��list
* `word <word> <word|number|bool>`��������word�ϲ�Ϊһ��word���ڶ���ֵ������word��number��bool
* `list <list1> <list2>`����list1��list2�ϲ���һ���б������б��Ԫ�ز��У�list1����list2��ǰ��
* `join <list> <value>`����value��Ϊlist�����һ��Ԫ�ؼ��뵽list�У����value���б�������value��Ϊ�б�����һ��Ԫ�أ�
* `first <word|list>`������word�ĵ�һ���ַ�����list�ĵ�һ��Ԫ��
* `last <word|list>`������word�����һ���ַ���list�����һ��Ԫ��
* `butfirst <word|list>`�����س���һ��Ԫ����ʣ�µ��б������һ���ַ���ʣ�µĵ���
* `butlast <word|list>`�����س����һ��Ԫ����ʣ�µ��б�������һ���ַ���ʣ�µĵ���
* `item <number> <word|list>`������word���б��еĵ�number���ַ���Ԫ��
* `repeat <number> <list>`������list�еĴ���number��
* `stop`��ֹͣ��ǰ�����ִ�С���ǰ���������run��repeat��if�����еĴ���
* `wait <number>`���ȴ�number��ms
* `save <word>`�����浱ǰ�����ռ���word�ļ���
* `load <word>`����word�ļ���װ�����ݣ����뵱ǰ�����ռ�
* `erall`�������ǰ�����ռ��ȫ������
* `poall`���г���ǰ�����ռ��ȫ������

## ��������͵���

### ����

		make <word> [<list1> <list2>]
			wordΪ������
			list1Ϊ�����б�
			list2Ϊ�����б�

### ����

		<functionName> <arglist>
			<functionName>Ϊmake�ж���ĺ�����������Ҫ˫����"
			<arglist>�ǲ����б�<arglist>�е�ֵ�ͺ�������ʱ��<list1>�����ֽ���һһ��Ӧ��

### ������صĲ���
			
* `output <value>`���趨valueΪ���ظ������ߵ�ֵ�����ǲ�ִֹͣ��
* `stop`��ִֹͣ��
* `local <word>`���趨��wordΪ�������֡�����Ҳ�Ǳ�������

## ��������

ϵͳ�ṩ��һЩ���õ��������������������ʵ�ֵ��ǳ��õĲ�������Ϊ���е����֡���Щ�����ǿ��Ա�ɾ����erase���ġ�

* `pi`��3.14159
* `if <bool> <list1> <list2>`�����boolΪ�棬��ִ��list1������ִ��list2��list������Ϊ�ձ�
* `run <list>`������list�еĴ���





