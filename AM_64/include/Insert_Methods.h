typedef struct Header
{
    char key_value_type;
    int key_value_length;
    char data_value_type;
    int data_value_length;
    int root_index;
}Header;

Header *H;

typedef struct Open_Scan{
  int op;
  int fileDesc;
  void *value;
  void *data;
  int block_num;
  int index;
}Open_Scan;

typedef struct Open_Index{
  int fileDesc;
  Header HEAD;
  int open_scans;
}Open_Index;


typedef struct Search_Node      //|  key  |blockindex|
{
	void* key;
	int block_index;

}Search_Node;

typedef struct Block_Data   //|bloctype|size|
{
	char blocktype;
	int size;  //size

}Block_Data;

typedef struct Data_Node
{                           //|key|  data   |
	void* key;
	void* data;

} Data_Node;

typedef struct Data_Block
{                               //|Block_Data|DataNode|DataNode|DataNode|DataNode|DataNode|...|datablock_index --->Data_Block

	Block_Data D;
	Data_Node* Data_N;
	int datablock_index;

}Data_Block;

typedef struct Search_Block
{
	Block_Data D;              //|firstblock_index|Search_Node|Search_Node|Search_Node|Search_Node|Search_Node|
	int firstblock_index;
	Search_Node* Search_N;

}Search_Block;

int Read_HeaderFromBlockFile(const int, Header*);

Data_Block IncreaseDataBlockSize(Data_Block);

Search_Block Read_SearchBlock_From_BlockFile(BF_Block *);

Data_Block Read_DataBlock_From_BlockFile(BF_Block *);

void free_Read_SearchBlock_From_BlockFile(Search_Block S);

void free_Read_DataBlock_From_BlockFile(Data_Block DB);

void Write_SearchBlock_To_BlockFile(Search_Block S,BF_Block*);

void Create_New_Root(Search_Node,const int);

void Write_DataBlock_To_BlockFile(Data_Block ,BF_Block*);

Search_Node SplitAndInsert_Search_Node(const int,BF_Block *,Search_Node,Search_Block);

Search_Node SplitAndInsert_Data_Node(const int,BF_Block *,Data_Node,Data_Block);

void Insert_Search_Node(Search_Node ,BF_Block *,Search_Block);

void Insert_Data_Node(Data_Node ,BF_Block* ,Data_Block);
//PATCH
int Case_Too_ManySameValuesInSearch(Search_Block S,int index);
int Case_Too_ManySameValuesInData(Data_Block D,int index);
//PATCH
int Is_More_Than(void* ,void* );

BF_Block* Get_Next_Block(int ,void* ,BF_Block* );

int safe_Get_Next_Block(int fileDesc,void* key_value,BF_Block* B);

Search_Node* Rec_Insert_Entry(const int ,Data_Node ,BF_Block*);
