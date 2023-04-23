#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<utility>
#include<vector>
#include <sstream>
#include<stdlib.h>
#include <bitset>
#include <iomanip>

using namespace std;
#include "conv.cpp"
int negval;
int lctr=0;
int dupcount=0;
vector<string> operand;
map<string,int> littab;
map<string,bool> cntrltab;
map<string,string> opcodetab;
map<string,int> symtab1;
map<string,int> registers;
map<string,int> regtab;
map<string,int> variabletab;
struct symtab{
  string label;
  int count;
	int ans;
};
map<int,symtab> symmap;
void intialregtab()
{
	regtab["A"]=0;
	regtab["X"]=1;
	regtab["L"]=2;
	regtab["B"]=3;
	regtab["S"]=4;
	regtab["T"]=5;
	regtab["F"]=6;
	regtab["PC"]=8;
	regtab["SW"]=9;
}

/*initializes the opcode for all mnemonics and 00 for all assembler directives*/
void opcodeinitialize(){
 
		opcodetab["ADD"]="18";
		opcodetab["ADDF"]="58";
		opcodetab["ADDR"]="90";
		opcodetab["AND"]="40";
		opcodetab["CLEAR"]="B4";
		opcodetab["COMP"]="28";
		opcodetab["COMPF"]="88";
		opcodetab["COMPR"]="A0";
		opcodetab["DIV"]="24";
		opcodetab["DIVF"]="64";
		opcodetab["DIVR"]="9C";
		opcodetab["FIX"]="C4";
		opcodetab["FLOAT"]="C0";
		opcodetab["HIO"]="F4";
		opcodetab["J"]="3C";
		opcodetab["JEQ"]="30";
		opcodetab["JGT"]="34";
		opcodetab["JLT"]="38";
		opcodetab["JSUB"]="48";
		opcodetab["LDA"]="00";
		opcodetab["LDB"]="68";
		opcodetab["LDCH"]="50";
		opcodetab["LDF"]="70";
		opcodetab["LDL"]="08";
		opcodetab["LDS"]="6C";
		opcodetab["LDT"]="74";
		opcodetab["LDX"]="04";
		opcodetab["LPS"]="D0";
		opcodetab["MUL"]="20";
		opcodetab["MULF"]="60";
		opcodetab["MULR"]="98";
		opcodetab["NORM"]="C8";
		opcodetab["OR"]="44";
		opcodetab["RD"]="D8";
		opcodetab["RMO"]="AC";
		opcodetab["RSUB"]="4C";
		opcodetab["SHIFTL"]="A4";
		opcodetab["SHIFTR"]="A8";
		opcodetab["SIO"]="F0";
		opcodetab["SSK"]="EC";
		opcodetab["STA"]="0C";
		opcodetab["STB"]="78";
		opcodetab["STCH"]="54";
		opcodetab["STF"]="80";
		opcodetab["STI"]="D4";
		opcodetab["STL"]="14";    
		opcodetab["STS"]="7C";
		opcodetab["STSW"]="E8";
		opcodetab["STT"]="84";
		opcodetab["STX"]="10";
		opcodetab["SUB"]="1C";
		opcodetab["SUBF"]="5C";
		opcodetab["SUBR"]="94";
		opcodetab["SVC"]="B0";
		opcodetab["TD"]="E0";
		opcodetab["TIO"]="F8";
		opcodetab["TIX"]="2C";
		opcodetab["TIXR"]="B8";
		opcodetab["WD"]="DC";
                opcodetab["START"]=" ";
                opcodetab["BASE"]=" ";
                opcodetab["EXTREF"]=" ";
                opcodetab["EXTDEF"]=" ";
                opcodetab["BYTE"]=" ";
                opcodetab["WORD"]="00";
                opcodetab["RESB"]="00";
                opcodetab["RESW"]="00";
                opcodetab["END"]=" ";
                opcodetab["NOBASE"]=" ";
                opcodetab["LTORG"]=" ";
                opcodetab["ORG"]=" ";
                opcodetab["EQU"]=" ";
                opcodetab["*"]="00";
          }
void pass1()
{
opcodeinitialize();
	intialregtab();
      	string line;//stores every instruction line in the input file
        string name;//operands stored 
        string temp,temp1;
        int flag=0,format;
        bool format_4=false,format_2=false,reg1=false;
        int segment=0;//segment 0-label segment 1-mnemonic segment 2-operand
        int blank=0,k=0;
        bool valid_mnemonic=false;
	ifstream infile;
	ofstream outfile;
        map<string,int>::iterator it1;
        
	infile.open ("example.txt");//input file
	outfile.open("intermediate.txt");
        string mnemonic;//stores mnemonic
        string copy;  //stores label
        cout<<"ERRORS\n";
        cout<<"---------------------------------------------\n";
	while(getline(infile,line))//open and fetch line by line from input file 
	{
                   
                for(int i=0;i<line.length();i++)
		{
                   	if(segment==0&&line[i]!=' ')
			{//label
                       		copy+=line[i];
                       		//char by char label is stored into copy
		   	}
		        else if(segment==1&&line[i]!=' ')
			{//mnemonic
		                    blank=0;
		                    mnemonic+=line[i];//char by char mnemonic stored into mnemonic
		         } 
                   	else if(segment==2&&line[i]!=' ')
			{//operand
		                 blank=0;
		                 name+=line[i];//char by char operand stored into name
		        }
                   	else
			{
                      		if(blank==0)
				{//checked to avoid considering spaces (i.e) skipping extra spaces
		                  segment++;
		                  blank++;
                          	}
                        }    
                }
                if(mnemonic=="EXTREF"||mnemonic=="EXTDEF")//multiple control section
                {
                           
                         for(int siz=0;siz<name.size();siz++)
         //if mnemonic is extref/extdef the operands seperated by comma are stored in cntrltab individually 
                         {
                                     if(name[siz]!=',')
                                           temp+=name[siz];
                                     else
				     {
		                             cntrltab[temp]=false;
		                             temp.clear();
                                     }
                          }
		           cntrltab[temp]=false;
		           temp.clear();
		}
		             
                else
		{
          //if mnemonic is not extref/extdef store the operand in operand vector only if it starts with alphabets
                      	if(mnemonic!="BYTE")
			{
                      		if(name[0]>='a'&&name[0]<='z'||name[0]>='A'&&name[0]<='Z'||name[0]=='@')
                           	{
                                     	if(name[0]=='@')name.erase(name.begin()+0,name.begin()+1);
                                	if(name=="A"||name=="S"||name=="B"||name=="T"||name=="X")
					{
						format_2=true;
                                       		registers[name]++;
					}
			      		else
					{
                                    		for(k=0;k<name.length();k++)
                                   		{
									   
						    if(name[k]!=',')
						      temp+=name[k];
				                    else 
                                        		break;
		             	    		}  
                                   		temp1=name[k+1];
                                  
						if(temp=="A"||temp=="B"||temp=="X"||temp=="T"||temp=="S")
				 		{
							 if(temp1=="A"||temp1=="B"||temp1=="X"||temp1=="T"||temp1=="S")
							      format_2=true;
						}
                                  
			 		}
					if(!format_2)	                  
				           operand.push_back(temp); 
                       		}
                        }

           //if operand starts with '=' store in littab and keep track of duplicate literals 
                      if(name[0]=='=')
                         littab[name]=0;
                            
                }
            //check if label in the given line is stored in cntrltab (i.e) operands are defined as labels ,then set the label to true 
                for(map<string,bool>::iterator it=cntrltab.begin();it!=cntrltab.end();it++)
		{
                       if(it->first==copy)
			{
		                it->second=true;
		                flag++;
		                break;
                         }
                }
                  
            //if flag is set to 0 , then the label is not in cntrltab , store the label into symtab and keep track of duplications
		if(copy=="*"||mnemonic=="*")
		{
                
                   for(it1=littab.begin();it1!=littab.end();it1++)
                   {
                           //  cout<<it1->second;
                           if(it1->second==0)
                              it1->second=lctr;
                    }
                    for(it1=variabletab.begin();it1!=variabletab.end();it1++)
                   {
                           //  cout<<it1->second;
                           if(it1->second==0)
                              it1->second=lctr;
                    }
                    
                }
          
                else
		{
		        if(flag==0&&!copy.empty())
			{
		             struct symtab p;
		             p.label=copy;
		             symtab1[copy]++;
		             p.count=symtab1[copy];
		             symmap[lctr]=p;
		          }
                 
                }
               
                if(mnemonic=="EQU"&&name=="*")
                  variabletab[copy]=0;
               //check if the mnemonic used in the line is valid 
              	if(mnemonic[0]=='+')
		{
                          format_4=true;
                          mnemonic.erase(mnemonic.begin(),mnemonic.begin()+1);
                                //cout<<mnemonic;                
}
                for(map<string,string>::iterator it=opcodetab.begin();it!=opcodetab.end();it++)
                                    if(it->first==mnemonic)valid_mnemonic=true;
		 //print hexadecimal value of lctr
                outfile<<hex<<lctr<<" ";       
               	outfile<<line<<" ";
               
              	if(valid_mnemonic==false)cout<<hex<<lctr<<""<<mnemonic<<" invalid mnemomic\n";//false if mnemonic not present in opcodetab
              	flag=0;         
		
                 valid_mnemonic=false;  //reset all values
                 segment=0;
                 blank=0;
                 if(mnemonic=="START"||mnemonic=="BASE"||mnemonic=="NOBASE"||mnemonic=="END"||mnemonic=="LTORG")
		 {
					  format=0;
					  lctr=lctr;
		 }
                 else if(opcodetab[mnemonic]==" ")
                 {
			format=1;
			lctr+=1;
		 }			   
                 else if(format_4==true)
		{
                      lctr+=4;
                      format_4=false;
                      format=4;
                 }
                 else if(format_2==true)
		{
                          lctr+=2;
                          format_2=false;
                          reg1=false;
                          format=2;
                 }
                 else
		{
			format=3;
                      	lctr=lctr+3;
		 }  
		 outfile<<format<<"\n";
                 copy.clear();
                 mnemonic.clear();
                 temp.clear();
                 name.clear();
	}
	//check if all operands in cntrltab are defined (i.e) all boolean values must be true...
	for(map<string,bool>::iterator it=cntrltab.begin();it!=cntrltab.end();it++)
	{
		 if(it->second==false)cout<<lctr<<" "<<it->first<<" undefined variable\n";
	}
	outfile.close();
	infile.close();
}


/*void TAPC()
{
	

}*/
int location(string mnemo)
{
map<int,symtab>::iterator it;
   //cout<<mnemo;
   for(it=symmap.begin();it!=symmap.end();it++)
       {
            if(it->second.label==mnemo)
                 break;
       }
  return it->first;
}

void pass2()
{
	string label, line, mnemonic, reg1,reg2,name1,imm1,indirect1,format,basen;
	int blank=0, segment=0,basel;
	int n,i,x,b,p,e, r1, r2;//format;
	string object_code;
	string opcode,buff,m,mn,reg;
	int op,val;
	ifstream infile;
	ofstream outfile;
	infile.open ("intermediate.txt");//input file
	outfile.open("object.txt");
	string copy;
	vector<int>convdisp;
  map<string,int>::iterator it1;
	map<int, symtab>::iterator it;
  int litlocation;
  
        while(getline(infile,line))//open and fetch line by line from input file 
	{

                   
                for(int j=0;j<line.length();j++)
                {
                   if(segment==0&&line[j]!=' ')
                   {//loctr
                       copy+=line[j];
                       blank=0;
                       //char by char loctr is stored into copy
		   }	
                   else if(segment==1&&line[j]!=' ')
		   {//label
                            blank=0;
                            label+=line[j];//char by char label stored into label
                   } 
                   else if(segment==2&&line[j]!=' ')
                   {//mnemonic
                         blank=0;
                         mnemonic+=line[j];//char by char mnemonic stored into mnemonic
                   }
                   else if(segment==3&&line[j]!=' ')
                   {//operand
                   	      blank=0;
                   	      name1+=line[j];//char by char operand is stored into name
		   }
		   else if(segment==4&&line[j]!=' ')
                   {
		                blank=0;
		                format=line[j];
		   }
                   else
                   {
                      if(blank==0)
                         {//checked to avoid considering spaces (i.e) skipping extra spaces
                          segment++;
                          blank++;
                         }
                       else if(blank==1)
                          segment++;
                        else
                        {}     
                   }    
                }
if(mnemonic=="BASE")
{
	basen=name1;
	for(it=symmap.begin(); it!=symmap.end(); it++)
	{
		if(it->second.label==name1)
				basel=it->first;
	}
}
 if(mnemonic[0]=='+')
   mnemonic.erase(mnemonic.begin(),mnemonic.begin()+1);

	opcode=opcodetab[mnemonic];
        op=toDec(opcode);
	
 // cout<<"Testing"<<mnemonic<<"\t"<<toDec(copy)<<"\n";
if(format=="0" || mnemonic=="LTORG" || mnemonic=="RESW"|| mnemonic=="RESB"|| mnemonic=="EQU")
outfile<<"\n";             
         else if(format=="1") //format1
  		{	
		  if(mnemonic=="BYTE")
			{	
				reg=name1[2];
				reg+=name1[3];
				//cout<<"reg1, reg2"<<name
	                	outfile<<"\n"<<reg;
	    }
			else
				outfile<<"\n"<<opcodetab[name1];
		}
	  else if(format=="2")
		{
	           	outfile<<'\n'<<opcodetab[mnemonic];
			if(name1.length()==3)
  			{    //outfile<<name1[0]<<name1[2];
				reg1=name1[0];
				reg2=name1[2];
				outfile<<regtab[reg1]<<regtab[reg2];			
			}	
	                else if(name1.length()==1)
	                {
			    reg1=name1;
			    outfile<<regtab[reg1]<<'0';
			}
		}	              		

		
	else if(format=="3" || format=="4")
	{
		if(basen==name1)
   { 
       if(mnemonic=="LDA" || mnemonic=="STA")
		   {	
				n=1;i=1;x=0;b=0;p=1;e=0;
				object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(location(name1)-(toDec(copy)+toInt(format))));
				outfile<<"\n"<<object_code;
			}
         else 
				{
					n=1;i=1;x=0;b=1;p=0;e=0;
				object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(location(name1)-location(basen)));
				outfile<<"\n"<<object_code;
           
				}		
    }
		else if(name1[0]=='#' && name1[1]>='0' && name1[1]<='9')
		{

				if(name1[0]=='#')
   name1.erase(name1.begin(),name1.begin()+1);
 
			 	 //outfile<<"Kutta\t"<<name1<<toInt("4096");
   if(0<=toInt(name1) && toInt(name1)<=4095)
		    {
   			n=0;i=1;x=0;b=0;p=0;e=0;
            		object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(toInt(name1)));
  	      		outfile<<"\n"<<object_code;		
        }
        	    else if(4096<=toInt(name1) && toInt(name1)<=1048575 && format=="4")
       		    {
			 	  n=0;i=1;x=0;b=0;p=0;e=1;
		   	  object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin20(toInt(name1)));
		    	 outfile<<"\n"<<object_code;
	            }
        	    /*else
        	    {
                	outfile<<"\nImmediate Address Value Error";
        	    }*/
    	       }
 else if(name1[0]=='#'&& ((name1[1]>='a' || name1[1]<='z') || (name1[1]>='A' || name1[1]<='Z')))

{
				if(format=="3")
			{		
       name1.erase(name1.begin(),name1.begin()+1);
 					 n=0,i=1,x=0,b=0,p=1,e=0;
					object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12((location(name1)-(toDec(copy)+toInt(format)))));
 					outfile<<"\n"<<object_code;
	     }
				if(format=="4")
				{
					name1.erase(name1.begin(),name1.begin()+1);
					n=0;i=1;x=0;b=0;p=0;e=1;
				object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin20(location(name1)));
				outfile<<"\n"<<object_code;

				}   
}
else if(name1[0]=='@')
{
name1.erase(name1.begin(),name1.begin()+1);
n=1,i=0,x=0,b=0,p=1,e=0;
object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12((location(name1)-(toDec(copy)+toInt(format)))));
 					outfile<<"\n"<<object_code;
}
    	else if(mnemonic=="*")
	    {
			for(int k=3;k<name1.length()-1;k++)
				mn+=name1[k];
			outfile<<"\n";
			for(int k=0;k<mn.length();k++)
			{
				m=mn[k];
				val=toDec1(m);
				outfile<<hex<<val;		
			}
			mn.clear();
	  	}	
else if(name1[0]=='=')
{
  for(it1=littab.begin();it1!=littab.end();it1++)
      {
					n=1;i=1;x=0;b=0;p=1;e=0;
           if(it1->first==name1)litlocation=it1->second;
              
      }     
		object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(litlocation-(toDec(copy)+toInt(format))));
						outfile<<"\n"<<object_code; 
}	

else if(mnemonic=="RSUB")
			{
			outfile<<"\n"<<"4f0000";
			}
else if((name1[name1.length()-2])==',')
{
n=1;i=1;x=1;b=1;p=0;e=0;
for(int z=0;z<name1.length();z++)
{
    if(name1[z]!=',')
      buff+=name1[z];
     else
       break;

}
 object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(location(buff)-location(basen)));
outfile<<"\nbbbb"<<object_code;

}
			//outfile<<"\naaaaaaaa"<<mnemonic;
    //cout<<location(name1);
		else if(!name1.empty())
		{
						
			if(format=="4")
			{
				n=1;i=1;x=0;b=0;p=0;e=1;
				object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin20(location(name1)));
				outfile<<"\n"<<object_code;
			}
		
	   
		else if((-2048<=(location(name1)-(toDec(copy)+toInt(format)))) && (location(name1)-(toDec(copy)+toInt(format))<=2047))
			{
				n=1;i=1;x=0;b=0;p=1;e=0;
				if(location(name1)-(toDec(copy)+toInt(format))>0)
				{				
				object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(location(name1)-(toDec(copy)+toInt(format))));
					outfile<<"\n"<<object_code;
				}
				else if(location(name1)-(toDec(copy)+toInt(format))<0)
				{
 					
					int abs_val=abs(location(name1)-(toDec(copy)+toInt(format)));
					convdisp=decToBin12(abs_val);
					convdisp=OnesComp(convdisp);
					object_code=assemble_obj(decToBin8(op),n,i,x,b,p,e,decToBin12(arrtoint(convdisp)));
					outfile<<"\n"<<object_code;
				}
			 
				else {}
				
			}
      
		}
                
		
else{}
}	
segment=0;
mnemonic.clear();
copy.clear();
label.clear();
name1.clear();
buff.clear();
}
infile.close();
outfile.close();
}



//displays contents of all tables
void display()
{
		ofstream outfile;
	outfile.open("table.txt");
	
outfile<<"SYMBOL TABLE CONTENTS\n";
     outfile<<"---------------------------------------------\n";
     for(map<int,symtab>::iterator it=symmap.begin();it!=symmap.end();it++){
        
               outfile<<hex<<it->first<<"\t";
               outfile<<it->second.label<<"\t"<<it->second.count<<"\n";
     }
     outfile<<"OPERAND TABLE CONTENTS\n";
     outfile<<"---------------------------------------------\n";
     for(int i=0;i<operand.size();i++){
        
               outfile<<operand[i]<<"\n";
     }
     outfile<<"CONTROL TABLE CONTENTS\n";
     outfile<<"---------------------------------------------\n";
     for(map<string,bool>::iterator it=cntrltab.begin();it!=cntrltab.end();it++){
        
               outfile<<it->first<<"\t";
               outfile<<it->second<<"\n";
     }
     outfile<<"LITERAL TABLE CONTENTS\n";
     outfile<<"---------------------------------------------\n";
     for(map<string,int>::iterator it=littab.begin();it!=littab.end();it++){
        
               outfile<<it->first<<"\t";
               outfile<<it->second<<"\n";
     }
     outfile<<"VARIABLE TABLE CONTENTS\n";
     outfile<<"---------------------------------------------\n";
     for(map<string,int>::iterator it=variabletab.begin();it!=variabletab.end();it++){
        
               outfile<<it->first<<"\t";
               outfile<<it->second<<"\n";
     }
  outfile.close();
}
int main()
{
  		string tan="500";
		   cout<<"tan\t"<<toInt(tan);
       pass1();
       display();
       pass2();
       return 0;

}
