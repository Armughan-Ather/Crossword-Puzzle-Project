#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <chrono>
#include<bits/stdc++.h>
#include <iomanip> 
#include<windows.h>
#define FOREGROUND_BLACK       0x00

using namespace std;
using namespace chrono;

const int GRID_SIZE =33;
const int numWords = 6;
void setColor(int colorCode) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, colorCode);
}

void resetColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7); 
}
class User{
	public:
		string name[101];
		float time_u[101];
		int size_u;
		
		User()
		{
			size_u=0;	
			time_u[0]=-1;
		}
		
		void insert_min_user(float value,string str){
			size_u=size_u+1;
			int i=size_u;
			name[i]=str;
			time_u[i]=value;
			
			while(i>1){
				int temp=i/2;
				if(time_u[temp]>time_u[i]){
					swap(time_u[temp],time_u[i]);
					swap(name[temp],name[i]);
					i=temp;
				}
				else{
					 return;
				}
			}
		}
		
		void user_min_sort(int n){
			while(n>1){
				swap(time_u[1],time_u[n]);
				swap(name[1],name[n]);
				n--;
				heapify_min(1,n);
			}
		}
		
		void heapify_min(int index,int num){
			int large=index;
			int left=2*index;
			int right=2*index +1;
			
			if(left<=num && time_u[large]<time_u[left]){
				large=left;
			}
			if(right<=num && time_u[large]<time_u[right]){
				large=right;
			}
			
			if(large!=index){
				swap(time_u[large],time_u[index]);
				swap(name[large],name[index]);
				
				heapify_min(large,num);
			}
			return;
		}
		
		void print_score(){
			setColor(FOREGROUND_BLUE|FOREGROUND_INTENSITY);
			cout << "\n\n\t\t*SCORE CARD\t\t\n\n";
			cout << "Names\t\tTime\n\n";
			
			for(int i=1;i<=size_u;i++){
				cout << name[i] << "\t\t" << time_u[i] << " seconds\n";
			}
			cout << endl;
			resetColor();
		}
		
};
int HintCounter=0;
class Node{
	public:
		int key;
		string Word;
		string Hint;
		Node *next;
		bool used;
		int index;
		Node(int k,string word,string hint,int ind)
		{
			key=k;
			Word=word;
			Hint=hint;
			next=NULL;
			used=false;
			index=ind;
		}
		Node(int k,string word,string hint)
		{
			key=k;
			Word=word;
			Hint=hint;
			next=NULL;
			used=false;
			index=-1;
		}
		Node()
		{
			next=NULL;
			key=0;
			Word="";
			Hint="";
			used=false;
			index=-1;
		}
};
class HashMap{
	private:
		Node **htable;
		int size;
	public:
		HashMap(int size)
		{
			this->size=size;
			htable=new Node*[size];
			for (int i=0;i<size;i++)
				htable[i] = NULL;
		}
		int generateKey(string str)
		{
			int key=0;
			int p=0;
			for(int i=0;i<str.length();i++,p++)
			{
				char c=str[i]-96;
				key=key+pow(c,p);
			}
			return key;
		}
		int HashFunc(string str)
		{
			char c=str[0]-97;
			return c%26;
		}
		void Insert(string word,string hint)
		{
			int key=generateKey(word);
			Node *newNode=new Node(key,word,hint);
			int i=HashFunc(word);
			if(htable[i]==NULL)
			{
				htable[i]=newNode;
			}
			else
			{
				Node *ptr=htable[i];
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=newNode;
			}
		}
		void Insert(string word,string hint,int ind)
		{
			int key=generateKey(word);
			Node *newNode=new Node(key,word,hint,ind);
			int i=HashFunc(word);
			if(htable[i]==NULL)
			{
				htable[i]=newNode;
			}
			else
			{
				Node *ptr=htable[i];
				while(ptr->next!=NULL)
				{
					ptr=ptr->next;
				}
				ptr->next=newNode;
			}
		}
		int SearchWithIndex(string str)
		{
			int i=HashFunc(str);
			int k=generateKey(str);
			Node *ptr=htable[i];
			int val=-1;
			while(ptr!=NULL)
			{
				if(k==ptr->key)
				{
					val=ptr->index;
				}
				ptr=ptr->next;
			}
			ptr=NULL;
			return val;
			
		}
		bool Search(string str)
		{
			int i=HashFunc(str);
			int k=generateKey(str);
			Node *ptr=htable[i];
			while(ptr!=NULL)
			{
				if(k==ptr->key)
				{
					return true;
				}
				ptr=ptr->next;
			}
			ptr=NULL;
			return false;
		}
		Node* getNewWord(char c)
		{
			int i=c-97;
			Node *ptr=htable[i];
			string val="";
			int count=0;
			while(ptr!=NULL)
			{
				count++;
				ptr=ptr->next;
			}
			ptr=htable[i];
			rep:
			int random=rand()%count;
			for(int i=0;i<random;i++)
			{
				ptr=ptr->next;
			}
			if(ptr->used==true)
			{
				goto rep;
			}
			Node *temp=ptr;
			ptr->used=true;
			return temp;
		}
	void clearTable()
    {
        for(int i=0;i<size;++i)
        {
            Node *current=htable[i];
            while(current!=NULL)
            {
                Node* next=current->next;
                delete current;
                current=next;
            }
            htable[i]=NULL;
        }
    }
    void DeleteAndInsertUsed(HashMap &h)
    {
    	for(int i=0;i<size;i++)
    	{
    		Node *ptr=h.htable[i];
    		while(ptr!=NULL)
			{
				if(ptr->Word!="")
				{
					Delete(ptr->Word);
					Insert(ptr->Word,ptr->Hint);	
				}
				
				ptr=ptr->next;
			}
			ptr=NULL;	
		}
		
	}
		void Delete(string str)
		{
		    
			if(Search(str))
			{
				int i=HashFunc(str);
				int k=generateKey(str);
				Node *ptr=htable[i];
				if(ptr->key==k)
				{
					Node *temp=ptr;
					ptr=ptr->next;
					delete temp;
					htable[i]=ptr;
				}
				else
				{
					Node *ptr=htable[i];
					Node *prev=htable[i];
					while(ptr->key!=k)
					{
						prev=ptr;
						ptr=ptr->next;	
					}	
					prev->next=ptr->next;
					Node *temp=ptr;
					delete temp;
				}
			}
			else
			{
				cout<<"Key Not Found!\n";
			}
			
		}		
};
void printGrid(char grid[GRID_SIZE][GRID_SIZE]) 
{
    for (int i=0;i<GRID_SIZE;++i) 
	{
        for (int j=0;j<GRID_SIZE;++j) 
		{
            if(grid[i][j]>='A' && grid[i][j]<='Z' || grid[i][j]>='a' && grid[i][j]<='z')
            {
            	setColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            	cout<<grid[i][j]<< " ";
            	resetColor();
            	
			}
			else{
				cout<<grid[i][j]<< " ";	
			}
			
        }
        cout << endl;
    }
    cout << endl;
}
void CopyGrid(char grid[GRID_SIZE][GRID_SIZE],char grid2[GRID_SIZE][GRID_SIZE])
{
	for (int i=0;i<GRID_SIZE;++i) 
	{
        for (int j=0;j<GRID_SIZE;++j) 
		{
            if(grid[i][j]>='A' && grid[i][j]<='Z' || grid[i][j]>='a' && grid[i][j]<='z')
            {
            	grid2[i][j]='-';
			}
        }
    }
}
bool CompareGrids(char grid[GRID_SIZE][GRID_SIZE],char grid2[GRID_SIZE][GRID_SIZE])
{
	bool flag=true;
	for (int i=0; i<GRID_SIZE;++i) 
	{
        for (int j=0;j< GRID_SIZE;++j) 
		{
            if(grid[i][j]!=grid2[i][j])
            {
            	flag=false;
			}
        }
    }
	return flag;
}
bool isValid(int row,int col) 
{
    return (row>=0 && row<GRID_SIZE && col>=0 && col<GRID_SIZE);
}
bool HorizontalUpdate(char grid[][GRID_SIZE],string str,char grid2[][GRID_SIZE],int row,int col,int index) 
{
    if(index==str.length()-2) 
	{
		if(grid2[row][col]==grid[row][col] && grid2[row][col+1]==grid[row][col+1])
		{
			return false;
		}
        grid2[row][col]=grid[row][col];
        grid2[row][col+1]=grid[row][col+1];
        resetColor();
        return true;
    }
	if(isValid(row,col) && grid[row][col]==str[index]) 
	{
        char temp=grid2[row][col];
        setColor(32);
        grid2[row][col]=grid[row][col];
        if(HorizontalUpdate(grid,str,grid2,row,col+1,index+1)) 
		{
            return true;
        }
        resetColor();
		grid2[row][col]=temp;
    }
    return false;
}
bool VerticalUpdate(char grid[][GRID_SIZE],string str,char grid2[][GRID_SIZE],int row,int col,int index) 
{
    if (index==str.length()-2) 
	{
		if(grid2[row][col]==grid[row][col] && grid2[row+1][col]==grid[row+1][col])
		{
			return false;
		}
		grid2[row][col]=grid[row][col];
		grid2[row+1][col]=grid[row+1][col];
		resetColor();
    	return true;
	}
    if(isValid(row,col) && grid[row][col]==str[index]) 
	{
		char temp=grid2[row][col];
		setColor(32); 
        grid2[row][col]=grid[row][col];
        if(VerticalUpdate(grid,str,grid2,row+1,col,index+1)) 
		{
            return true;
        }
        resetColor();
    	grid2[row][col]=temp;
	}
    return false;
}
bool HorizontalVerticalUpdate(char grid[][GRID_SIZE],string str,char grid2[][GRID_SIZE],int row, int col,int index) 
{
    if(HorizontalUpdate(grid,str,grid2,row,col,index)) 
	{
        return true;
    }
    if(VerticalUpdate(grid,str,grid2,row,col,index)) 
	{
        return true;
    }
    return false;
}
void updateDisplayGrid(char grid[GRID_SIZE][GRID_SIZE],char grid2[GRID_SIZE][GRID_SIZE],string str)
{
    bool found=false;
    for (int i=0;i<GRID_SIZE;++i) 
	{
        for (int j=0;j<GRID_SIZE;++j) 
		{
            if(HorizontalVerticalUpdate(grid,str,grid2,i,j,0)) 
			{
                found=true;
                break;
            }
        }
        if(found) 
		{
            break;
        }
    }
}
void EmptyHints(string *hints2,int n,int *index)
{
	for(int i=0;i<n;i++)
	{
		hints2[i]="";
		index[i]=-1;
	}
	HintCounter=0;
}
void HintsDisplayer(string *hints2,int *index)
{
	setColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	cout<<"HINTS : \n";
	resetColor();
	for(int i=0;i<HintCounter;i++)
	{
		if(index[i]!=-1)
		{
			setColor(FOREGROUND_BLACK | FOREGROUND_INTENSITY);
			cout<<i+1<<". "<<hints2[i]<<endl;	
			resetColor();
		}
		else
		{
			cout<<i+1<<". "<<hints2[i]<<endl;
		}
		
	}
	
}
void generateCrossword(char grid[GRID_SIZE][GRID_SIZE],string *words,string *hints,int n,HashMap h,HashMap h2,string *hints2)
{
	
	srand(time(0));
	
	bool isHorizontal=false;
	int randomIndex = rand() % n;
    
	string currentWord = words[randomIndex];
	hints2[HintCounter]=hints[randomIndex];
	
	h2.Insert(currentWord,hints[randomIndex],HintCounter);
    HintCounter++;
	int startRow=0;
    int startCol=0;
    char randomChar=currentWord[(rand() % (currentWord.length()-1))+1];
    int iIndex;
    int jIndex;
	for (int i=0;i<currentWord.length();++i) 
	{
        if(currentWord[i]==randomChar)
        {
            iIndex=0;
            jIndex=startCol+i;
        }
        grid[startRow][startCol+i]=currentWord[i];
    }
    
    for (int wordCount=1; wordCount<numWords;++wordCount) 
	{
		Node *temp=h.getNewWord(randomChar);
		currentWord=temp->Word;
		
		hints2[HintCounter]=temp->Hint;
    	h2.Insert(currentWord,temp->Hint,HintCounter);
        
		HintCounter++;
        
		startRow =iIndex;
        startCol=jIndex;
        randomChar=currentWord[(rand() % (currentWord.length()-1))+1];
        for (int i=0; i < currentWord.length(); ++i) {
            if(isHorizontal)
            {
                if(i==0)
                {
                    jIndex++;
                    continue;
                }
                if(currentWord[i]==randomChar)
                {
                    jIndex=startCol + i;
                }
                grid[startRow][startCol+i]=currentWord[i];
            }
            else
            {
                if(i==0)
                {
                    iIndex++;
                    continue;
                }
                if(currentWord[i]==randomChar)
                {
                    iIndex=startRow+i;
                }
                grid[startRow+i][startCol]=currentWord[i];
            }
            
        }
        if(isHorizontal)
        {
            isHorizontal=false;
        }
        else
        {
            isHorizontal=true;
        }
    }
    //printGrid(grid);
}
void EmptyGrid(char GRID[GRID_SIZE][GRID_SIZE],int n)
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			GRID[i][j]=' ';
		}
	}
}
int main() {
	HashMap h(26);
    HashMap h2(26);
    string hints2[numWords]={""};
    int index[numWords];
    char grid[GRID_SIZE][GRID_SIZE];
    char  grid2[GRID_SIZE][GRID_SIZE];
    
    for(int i=0; i<GRID_SIZE;++i) {
        for (int j=0;j<GRID_SIZE;++j) {
            grid[i][j]=' ';
            grid2[i][j]=' ';
        }
    }
    
    string words[] = {
        "apple", "banana", "cherry", "dog", "elephant",
        "flower", "guitar", "happy", "icecream", "jungle",
        "kangaroo", "lemon", "mountain", "notebook", "orange",
        "penguin", "quasar", "rainbow", "sunflower", "turtle",
        "umbrella", "violin", "watermelon", "xylophone", "zebra",
        "astronomy", "butterfly", "caterpillar", "dolphin", "earth",
        "fireworks", "galaxy", "happiness", "island", "jigsaw",
        "kite", "lighthouse", "moonlight", "novel", "ocean",
        "paradise", "quilt", "rocket", "starlight", "telescope",
        "universe", "volcano", "whale", "xray", "yellow",
        "zoo", "breeze", "carousel", "dandelion", "effervescent",
        "fountain", "gentle", "harmony", "illusion", "journey",
        "kaleidoscope", "lullaby", "marvel", "nostalgia", "overture",
        "paradox", "quintessence", "serendipity", "tranquil", "unique",
        "vivid", "whimsical", "xanadu", "yearning", "zenith",
        "ballet", "comet", "delight", "ethereal", "fantasy",
        "graceful", "hologram", "innocence", "jubilation", "kismet",
        "labyrinth", "mystical", "nebula", "opulent", "perennial",
        "quicksilver", "resplendent", "serenity", "twilight", "utopia",
        "velvet", "wonder", "xenon", "yearn", "zephyr"
    };
    
    string hints[] = {
        "A common fruit with a red or green skin.", 
        "A yellow fruit that is peeled before eating.",
        "A small, round fruit with a pit inside.",
        "A domesticated, loyal animal often kept as a pet.",
        "A large mammal known for its long trunk and tusks.",
        "A colorful and fragrant bloom.",
        "A musical instrument with strings.",
        "An emotion characterized by joy and contentment.",
        "A frozen dessert often enjoyed on a hot day.",
        "A dense and overgrown forest.",
        "A marsupial native to Australia.",
        "A citrus fruit with a sour taste.",
        "A towering landform with rocky peaks.",
        "A notebook for writing and recording information.",
        "A citrus fruit with a sweet and tangy flavor.",
        "A flightless bird with distinctive black and white feathers.",
        "A celestial object emitting powerful energy.",
        "A spectrum of colors in the sky after rain.",
        "A bright and cheerful flower.",
        "A reptile with a hard shell.",
        "A device to protect from rain.",
        "A string instrument played with a bow.",
        "A large, juicy fruit with green rind and red flesh.",
        "A percussion instrument with wooden bars.",
        "A black and white striped mammal.",
        "The scientific study of celestial objects and phenomena.",
        "An insect with colorful wings.",
        "The larval stage of a butterfly.",
        "A marine mammal known for its intelligence.",
        "The third planet from the sun.",
        "Explosive and colorful pyrotechnic displays.",
        "A vast system of stars, gas, and dust.",
        "A state of well-being and contentment.",
        "A landmass surrounded by water.",
        "A puzzle with irregularly shaped pieces.",
        "A flying toy tethered to a string.",
        "A tall structure with a light to guide ships.",
        "Soft, natural light from the moon.",
        "A long fictional prose narrative.",
        "A large body of saltwater.",
        "A place of perfect happiness and bliss.",
        "A bed cover made of stitched fabric.",
        "A vehicle that travels into space.",
        "Light from stars at night.",
        "An optical instrument for viewing distant objects.",
        "All that exists, including stars, galaxies, and space.",
        "A mountain that spews lava and ash.",
        "A large marine mammal.",
        "A form of electromagnetic radiation.",
        "The color of ripe lemons.",
        "A place where animals are kept for public exhibition.",
        "A gentle wind.",
        "A rotating machine with seats for amusement.",
        "A wildflower with fluffy seed heads.",
        "Bubbly, fizzy, and sparkling.",
        "A stream of water usually shot upward.",
        "Soft and mild, not harsh.",
        "A state of peaceful coexistence.",
        "Something that deceives the senses.",
        "A journey or trip.",
        "A constantly changing pattern or sequence.",
        "A soothing song to help sleep.",
        "Something causing wonder or astonishment.",
        "A feeling of pleasure mixed with sadness.",
        "An introductory musical composition.",
        "A statement or situation that contradicts itself.",
        "The most perfect or typical example of something.",
        "An unexpected and fortunate discovery.",
        "Calm and peaceful.",
        "Being the only one of its kind.",
        "Clear, detailed, and bright.",
        "Playfully quaint or fanciful.",
        "An idealized place of great beauty and contentment.",
        "A form of Japanese poetry with three lines.",
        "A celestial object with a bright tail of gas and dust.",
        "A great source of joy and delight.",
        "Extremely delicate and light in a way that seems not to be of this world.",
        "An imagined world or sequence of events.",
        "Graceful and elegant in form or movement.",
        "A three-dimensional image created by laser beams.",
        "The state of being free from guilt or sin.",
        "A feeling of great happiness and triumph.",
        "A winding and confusing network.",
        "Having a spiritual significance or symbolism.",
        "A luminous patch of gas or dust in the night sky.",
        "Richly and impressively splendid.",
        "The state of being calm and peaceful.",
        "The soft, diffused light from the sky when the sun is below the horizon.",
        "An imagined perfect place or state of things.",
        "A soft fabric with a smooth and dense pile.",
        "A feeling of amazement and admiration.",
        "A chemical element often used in lights.",
        "To have an intense desire or longing for something.",
        "A gentle, mild wind."
    };
    int n=sizeof(words)/sizeof(words[0]);
    for(int i=0;i<n;i++)
    {
    	h.Insert(words[i],hints[i]);
	}
	srand(time(0));
	string ptr;
	int choice;
	
	User u;
	int count=0;
	while(1)
	{
		EmptyHints(hints2,sizeof(hints2)/sizeof(hints2[0]),index);
		EmptyGrid(grid,27);
		EmptyGrid(grid2,27);
		h.DeleteAndInsertUsed(h2);
		h2.clearTable();
		cout << "\n\nEnter User Name: ";
		fflush(stdin);
		getline(cin,ptr);
		cout << "\n\n";
		
		generateCrossword(grid,words,hints,sizeof(words)/sizeof(words[0]),h,h2,hints2);
		CopyGrid(grid,grid2);
		auto start_time=high_resolution_clock::now();  			
		
		while(1){
			printGrid(grid2);
			HintsDisplayer(hints2,index);
			if(CompareGrids(grid,grid2))
			{
				break;
			}
			
			string str;
			cout << "\nEnter Word To Fill Crossword: ";
			cin >> str;
			
			if(h2.Search(str))
			{
				int ind=h2.SearchWithIndex(str);
				if(ind!=-1)
				{
					index[ind]=ind;
				}
			    updateDisplayGrid(grid,grid2,str);
			}
			else{
				cout << "\nIncorrect\n\n";
			}
			 
		}
		auto end_time=high_resolution_clock::now(); 		
		auto duration_user=duration_cast<seconds>(end_time - start_time).count();  
		
		u.insert_min_user(duration_user,ptr);
		int temp=u.size_u;
		for(int i=temp/2;i>0;i--){
			u.heapify_min(i,temp);   
		}	
		u.user_min_sort(u.size_u);
		
		cout << "\nEnter 1 to play another game \nEnter 2 to exit\n";
		cin >> choice;
		cout << endl;
		while(1){
			if(choice==1)
			{
				u.print_score();
				break;
			}
			else if(choice==2){
				u.print_score();
				exit(1);
			}
			else{
				cout << "\n\t** Invalid Input **\n\nEnter Again: ";
				cin >> choice;
				cout << endl;
			}
		}
		
	
	}
	u.print_score();
	
	return 0;
}
