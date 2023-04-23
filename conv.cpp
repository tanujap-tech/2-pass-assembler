#include<iostream>
#include <sstream>
#include<string>
#include<stdlib.h>
#include <bitset>
#include <iomanip>
#include <vector>
#include<math.h>
using namespace std;

vector<int> arr12;
vector<int> arr20;
vector<int> arr8;
int num[10];
char buffer[20];
int displength=0;
int toInt(string name)
{
	  std::size_t length = name.copy(buffer,name.length(),0);
  		buffer[length]='\0';
    //Storing the array values and converting it to integer element by element
		for(int k=0;k<length;k++)
		{
				num[k]=(int)buffer[k]-48;
		}
		//Converting the integer array to a whole number
int finalNumber=0;
   
for(int k=length-1,j=0;k>=0 && j<length;k--,j++)
{
    finalNumber+=pow(10,k)*num[j];
}
    return finalNumber;
}

int arrtoint(vector<int> binary)
{
	int decimal=0;
	for(int i=11;i>=0;i--)
	{
		decimal+=binary[i]*pow(2,i);
	}
 return (decimal+1);	
}
vector<int> decToBin12(int finalNumber)
{
	displength=1;    
	for(int k=11;k>=0;k--)
			{
			  arr12.insert(arr12.begin()+0,finalNumber &(1<<k)?1:0);
			}
			return arr12;
}

vector<int> decToBin20(int finalNumber)
{
	displength=2;    
	for(int k=19;k>=0;k--)
			{
			  arr20.insert(arr20.begin()+0,finalNumber &(1<<k)?1:0);
			}
			return arr20;
}

vector<int> decToBin8(int finalNumber)
{
    for(int k=7;k>=0;k--)
			{
			 arr8.insert(arr8.begin()+0,finalNumber &(1<<k)?1:0);
			}
			return arr8;
}
vector<int> OnesComp(vector<int> ans)
{
    for(int k=11;k>=0;k--)
		{
			if(ans[k]==0)
				ans[k]=1;
  		else if(ans[k]==1)
				ans[k]=0;
		}
		return ans;
}


int toDecDig1(char a)
{
    if(a=='0') return 0;
    if(a=='1') return 1;
    if(a=='2') return 2;
    if(a=='3') return 3;
    if(a=='4') return 4;
    if(a=='5') return 5;
    if(a=='6') return 6;
    if(a=='7') return 7;
    if(a=='8') return 8;
    if(a=='9') return 9;
    /*if(a=='A') return 10;
    if(a=='B') return 11;
    if(a=='C') return 12;
    if(a=='D') return 13;
    if(a=='E') return 14;
    if(a=='F') return 15;*/
}
int toDecDig(char a)
{
    if(a=='0') return 0;
    if(a=='1') return 1;
    if(a=='2') return 2;
    if(a=='3') return 3;
    if(a=='4') return 4;
    if(a=='5') return 5;
    if(a=='6') return 6;
    if(a=='7') return 7;
    if(a=='8') return 8;
    if(a=='9') return 9;
    if(a=='A' || a=='a') return 10;
    if(a=='B' || a=='b') return 11;
    if(a=='C' || a=='c') return 12;
    if(a=='D' || a=='d') return 13;
    if(a=='E' || a=='e') return 14;
    if(a=='F' || a=='f') return 15;
}


int toDec(string val)
{
    int l=val.length()-1,curr=1,res=0;
    while(l>=0)
    {
        res+=(toDecDig(val[l])*curr);
        curr*=16;
        --l;
    }
    return res;
}
int toDec1(string val)
{
    int l=val.length()-1,curr=1,res=0;
    while(l>=0)
    {
        res+=(toDecDig1(val[l])*curr);
        curr*=16;
        --l;
    }
    return res;
}

string binToHex(string bin)
{
    int result =0 ;
    for(size_t count = 0; count < bin.length() ; ++count)
    {
        result *=2;
        result += bin[count]=='1'? 1 :0;
    }

    stringstream ss;
    ss << hex << setw(1) << setfill('0')  << result;

    string hexVal(ss.str());
    return hexVal;
}

std::string IntToString ( int number )
{
  std::ostringstream oss;

  // Works just like cout
  oss<< number;

  // Return the underlying string
  return oss.str();
}
string assemble_obj(vector<int> op, int n,int i,int x,int b,int p,int e,vector<int> disp)
{
	string obj,obj1,obj2,obj3,obj4,obj5,obj6,obj7,obj8;
	obj1=IntToString (op[7]) + IntToString (op[6]) + IntToString (op[5]) + IntToString (op[4]);
	obj2=IntToString (op[3]) + IntToString (op[2]) + IntToString (n) + IntToString (i);
	obj3=IntToString (x) + IntToString (b) + IntToString (p) + IntToString (e);
	if(displength==1)
	{
	obj4=IntToString (disp[11]) + IntToString (disp[10]) + IntToString (disp[9]) + IntToString (disp[8]);
	obj5=IntToString (disp[7]) + IntToString (disp[6]) + IntToString (disp[5]) + IntToString (disp[4]);
	obj6=IntToString (disp[3]) + IntToString (disp[2]) + IntToString (disp[1]) + IntToString (disp[0]);
	obj=obj1+obj2+obj3+obj4+obj5+obj6;
	}
	else if(displength==2)
	{
	//cout<<"hello20";
	obj4=IntToString (disp[19]) + IntToString (disp[18]) + IntToString (disp[17]) + IntToString (disp[16]);
	obj5=IntToString (disp[15]) + IntToString (disp[14]) + IntToString (disp[13]) + IntToString (disp[12]);
	obj6=IntToString (disp[11]) + IntToString (disp[10]) + IntToString (disp[9]) + IntToString (disp[8]);
	obj7=IntToString (disp[7]) + IntToString (disp[6]) + IntToString (disp[5]) + IntToString (disp[4]);
	obj8=IntToString (disp[3]) + IntToString (disp[2]) + IntToString (disp[1]) + IntToString (disp[0]);
	obj=obj1+obj2+obj3+obj4+obj5+obj6+obj7+obj8;
	}
	return (binToHex(obj));
}

