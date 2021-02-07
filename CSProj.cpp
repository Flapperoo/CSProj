#include <cctype>      	
#include <string>		
#include <fstream>
#include <iostream>		
#include <cstdlib>
#include <stdio.h>
#include <algorithm>

using namespace std;

struct iteminv{
	string itemcode;
	string itemname;
	string itemdesc;
	float itemprice;
	int itemquan;
	string itemunit;
} itemdb[100], temp, display[100], result[100];

void loadfile(){
	ifstream input("itemdb.txt");
	
	if(!input.fail()){
		cout<<"Loading inventory..."<<endl;
		for(int i=0;i < 100;i++){
			input >> itemdb[i].itemcode;
			input >> itemdb[i].itemname;
			input >> itemdb[i].itemdesc;
			input >> itemdb[i].itemprice;
			input >> itemdb[i].itemquan;
			input >> itemdb[i].itemunit;
		}
		input.close();
	}
	else{
		cout<<"No existing inventory file available."<<endl<<"Creating..."<<endl;
	}
}

void errorinp(){
	cout<<"\nInvalid Input"<<endl;
	cin.clear();
	cin.ignore(100, '\n');
}

void save(iteminv voldata){
	ofstream output("itemdb.txt", ios::app);
	if(!output.fail()){
		cout<<"Saving..."<<endl;
		output<<voldata.itemcode<<"\t"<<voldata.itemname<<"\t"<<voldata.itemdesc<<"\t"<<voldata.itemprice<<"\t"<<voldata.itemquan<<"\t"<<voldata.itemunit<<"\t"<<endl;
	}
	else{
		cout<<"Save failed."<<endl;
	}	
}

void additem1(){
	bool itemchk;
	do{
		itemchk = false;
		cout<<"Input Item Code >> ";
		cin>>temp.itemcode;
		if((temp.itemcode.size() == 0) || (temp.itemcode.size() > 9)){
			itemchk = true;
			errorinp();
			cout<<"\nItem code cannot be null or more than 9 characters"<<endl;
		}
		else{
			for(int i=0;i<100;i++){
				if(temp.itemcode == itemdb[i].itemcode){
					itemchk = true;
					errorinp();
					cout<<"\nItem code already exists."<<endl;
					break;
				}
			}
		}
	}while(itemchk);
}

void additem2(){
	bool itemchk;
	do{
		itemchk = false;
		cout<<"Input Item Name >> ";
		cin>>temp.itemname;
		if(temp.itemname.size() == 0){
			itemchk = true;
			errorinp();
			cout<<"\nItem name cannot be null"<<endl;
		}
	}while(itemchk);
}

void additem3(){
	bool itemchk;
	do{
		itemchk = false;
		cout<<"Input Item Variety >> ";
		cin>>temp.itemdesc;
		if(temp.itemdesc.size() == 0){
			itemchk = true;
			errorinp();
			cout<<"\nItem variety cannot be null"<<endl;
		}
	}while(itemchk);
}

void additem4(){
	bool itemchk;
	do{
		itemchk = false;
		cout<<"Input Item Price >> ";
		cin>>temp.itemprice;
		if(temp.itemprice <= 0 || cin.fail()){
			itemchk = true;
			errorinp();
		}
	}while(itemchk);
}

void additem5(){
	bool itemchk;
	do{
		itemchk = false;
		cout<<"Input Item Quantity >> ";
		cin>>temp.itemquan;
		if(temp.itemquan <= 0 || cin.fail()){
			itemchk = true;
			errorinp();
		}
	}while(itemchk);
}

void additem6(){
	bool itemchk;
	do{
		itemchk = false;
		cout<<"Input Item Units >> ";
		cin>>temp.itemunit;
		if(temp.itemunit.size() == 0 || temp.itemunit.size() > 7 || cin.fail()){
			itemchk = true;
			errorinp();
			cout<<"\nItem Unit cannot be null"<<endl;
		}
	}while(itemchk);
}

void additem(){
	bool confirm;
	char ch;
	loadfile();
	ofstream output("itemdb.txt", ios::app);
	cout<<"-------------------- ADD ITEM --------------------"<<endl;
	additem1();
	additem2();
	additem3();
	additem4();
	additem5();
	additem6();
	do{
		system("cls");
		confirm = false;
		cout<<"-------------------- ADD ITEM --------------------"<<endl<<"\n[1] Item Code: "<<temp.itemcode<<endl<<"[2] Item Name: "<<temp.itemname<<endl<<"[3] Item Variety: "<<temp.itemdesc<<endl<<"[4] Item Price: "<<temp.itemprice<<endl<<"[5] Item Quantity: "<<temp.itemquan<<endl<<"[6] Item Units: "<<temp.itemunit<<endl<<"\n Press Y to Confirm, 1/2/3/4/5/6 to modify entry, and N to cancel >> ";
		cin>>ch;
		ch = tolower(ch);
		switch(ch){
			case '1':
				additem1();
				break;
			case '2':
				additem2();
				break;
			case '3':
				additem3();
				break;
			case '4':
				additem4();
				break;
			case '5':
				additem5();
				break;
			case '6':
				additem6();
				break;
			case 'y':
				confirm = true;
				break;
			case 'n':
				return;
				break;
		}
	}while(!confirm);
	save(temp);
}

void delitem(){
	string delcode;
	bool repeat,delerr;
	char ch,ch2;
	do{
		loadfile();
		system("cls");
		repeat = false;
		cout<<"-------------------- DELETE ITEM --------------------"<<endl<<"\nInput Item Code to Delete >> ";
		cin>>delcode;
		//delcode = tolower(delcode);
		transform(delcode.begin(), delcode.end(), delcode.begin(), ::tolower);
		for(int i=0;i<100;i++){
			//temp.itemcode = tolower(itemdb[i].itemcode);
			temp.itemcode = itemdb[i].itemcode;
			transform(temp.itemcode.begin(), temp.itemcode.end(), temp.itemcode.begin(), ::tolower);
			if(delcode == temp.itemcode){
				do{
					delerr = false;
					cout<<"Item Code: "<<itemdb[i].itemcode<<endl<<"Item Name: "<<itemdb[i].itemname<<endl<<"Item Variety: "<<itemdb[i].itemdesc<<endl<<"Item Price: "<<itemdb[i].itemprice<<endl<<"Item Quantity: "<<itemdb[i].itemquan<<endl<<"Item Units: "<<itemdb[i].itemunit<<endl<<"\nDelete this entry? (Y to confirm/N to cancel) >> ";
					cin>>ch;
					ch = tolower(ch);
					if(ch == 'y'){
						remove("itemdb.txt");
						ofstream output("itemdb.txt");
						if(!output.fail()){
							cout<<"Deleting..."<<endl;
							for(int a=0;a<100;a++){
								if(itemdb[i].itemcode == itemdb[a].itemcode){
								}
								else if(itemdb[a].itemcode.size() == 0){
								}
								else{
									output<<itemdb[a].itemcode<<"\t"<<itemdb[a].itemname<<"\t"<<itemdb[a].itemdesc<<"\t"<<itemdb[a].itemprice<<"\t"<<itemdb[a].itemquan<<"\t"<<itemdb[a].itemunit<<endl;
								}
							}
						}
						else{
							cout<<"Process failed."<<endl;
						}	
					}
					else if(ch == 'n'){
					}
					else{
						errorinp();
						delerr = true;
					}
				}while(delerr);
				break;
			}
			if(i == 99){
				cout<<"Item Code not found"<<endl;
			}
		}
		cout<<"Press any key to repeat or (N/n) to return to menu >> ";
		cin>>ch2;
		ch2 = tolower(ch2);
		if(ch2 != 'n'){
			repeat = true;
		}
		cin.ignore(100, '\n')
	}while(repeat);
}

void moditem(){
	string modcode;
	bool repeat,modrep;
	char ch,ch2;

	do{
		repeat = false;
		loadfile();
		system("cls");
		cout<<"-------------------- MODIFY ITEM --------------------"<<endl<<"\nInput Item Code to Modify >> ";
		cin>>modcode;
		transform(modcode.begin(), modcode.end(), modcode.begin(), ::tolower);
		for(int i=0;i<100;i++){
			if(modcode == itemdb[i].itemcode){
				temp = itemdb[i];
				do{
					modrep = true;
					cout<<"[1] Item Code: "<<temp.itemcode<<endl<<"[2] Item Name: "<<temp.itemname<<endl<<"[3] Item Variety: "<<temp.itemdesc<<endl<<"[4] Item Price: "<<temp.itemprice<<endl<<"[5] Item Quantity: "<<temp.itemquan<<endl<<"[6] Item Units: "<<temp.itemunit<<endl<<"\nEnter [1/2/3/4/5/6] to modify entry, [Y/y] to Confirm Changes, [N/n] to Cancel >> ";
					cin>>ch;
					ch = tolower(ch);
					switch(ch){
						case '1':
							additem1();
							break;
						case '2':
							additem2();
							break;
						case '3':
							additem3();
							break;
						case '4':
							additem4();
							break;
						case '5':
							additem5();
							break;
						case '6':
							additem6();
							break;
						case 'y':{						
							itemdb[i] = temp;
							remove("itemdb.txt");
							ofstream output("itemdb.txt");
							if(!output.fail()){
								cout<<"Saving..."<<endl;
								for(int a=0;a<100;a++){
									if(itemdb[a].itemcode.size() == 0){
									}
									else{
										output<<itemdb[a].itemcode<<"\t"<<itemdb[a].itemname<<"\t"<<itemdb[a].itemdesc<<"\t"<<itemdb[a].itemprice<<"\t"<<itemdb[a].itemquan<<"\t"<<itemdb[a].itemunit<<endl;
									}
								}
							}
							else{
								cout<<"Process failed."<<endl;
							}
							modrep = false;
							break;
						}
						case 'n':
							modrep = false;
							break;
						default:
							errorinp();
							break;
					}
				}while(modrep);
				break;
			}
			if(i == 99){
				cout<<"Item Code not found"<<endl;
			}
		}
		cout<<"Press any key to repeat or (N/n) to return to menu >> ";
		cin>>ch2;
		ch2 = tolower(ch2);
		if(ch2 != 'n'){
			repeat = true;
		}
		cin.ignore(100, '\n')
	}while(repeat);
}

void seaitem(){
	string seacode,tempcode;
	int cnt=0,cntinner,searchcnt;
	bool repeat;
	char ch;

	system("cls");
	loadfile();
	for(int i=0;i<100;i++){
		if(itemdb[i].itemcode.size() == 0){
		}
		else if(itemdb[i].itemquan <= 5){
			display[cnt] = itemdb[i];
			cnt++;
		}
	}
	for(int i=0;i<100;i++){
		cntinner = cnt;
		for(int a=0;a<=cntinner;a++){
			if(itemdb[i].itemcode == display[a].itemcode){
				break;
			}
			else if(a == cntinner){
				display[cnt] = itemdb[i];
				cnt++;
			}
		}
	}

	do{
		repeat = false;
		searchcnt = 0;
		cout<<"-------------------- SEARCH ITEM --------------------"<<endl<<"\nItem Code // Item Name // Item Variety // Item Price // Item Quantity // Item Unit"<<endl;
		for(int i=0;i<cnt;i++){
			cout<<display[i].itemcode<<"\t"<<display[i].itemname<<"\t"<<display[i].itemdesc<<"\t"<<display[i].itemprice<<"\t"<<display[i].itemquan<<"\t"<<display[i].itemunit<<endl;
		}
		cout<<"Input Item Name to search >> ";
		cin>>seacode;
		transform(seacode.begin(), seacode.end(), seacode.begin(), ::tolower);
		for(int i=0;i<cnt;i++){
			tempcode = display[i].itemname;
			transform(tempcode.begin(), tempcode.end(), tempcode.begin(), ::tolower);
			if(tempcode.find(seacode) != string::npos){
				result[searchcnt] = display[i];
				searchcnt++;
			}
		}
		system("cls");
		cout<<"\n Found "<<searchcnt<<" items containing the string '"<<seacode<<"'."<<endl;
		cout<<"-------------------- SEARCH ITEM --------------------"<<endl<<"\nItem Code // Item Name // Item Variety // Item Price // Item Quantity // Item Unit"<<endl;
		for(int i=0;i<searchcnt;i++){
			cout<<"["<<i+1<<"] "<<result[i].itemcode<<"\t"<<result[i].itemname<<"\t"<<result[i].itemdesc<<"\t"<<result[i].itemprice<<"\t"<<result[i].itemquan<<"\t"<<result[i].itemunit<<endl;
		}
		cout<<"\n Press any key to search again and [N/n] to return to menu >> ";
		cin>>ch;
		ch = tolower(ch);
		if(ch != 'n'){
			repeat = true;
		}
		cin.ignore(100, '\n')
		system("cls");
	}while(repeat);
}

int main(){
	bool repeat = true;
	int choice;
	
	do{
		cout<<"-------------------- INVENTORY MENU --------------------"<<endl<<"\n[1] Add New Item to Inventory"<<endl<<"[2] Clear Item from Inventory"<<endl<<"[3] Modify Existing Item Entry"<<endl<<"[4] Search/Display Item in Inventory"<<endl<<"[5] Exit"<<endl<<"Action >> ";
		cin>>choice;
		switch(choice){
			case 1:
				additem();
				system("cls");
				break;
			case 2:
				delitem();
				system("cls");
				break;
			case 3:
				moditem();
				system("cls");
				break;
			case 4:
				seaitem();
				system("cls");
				break;
			case 5:
				exit(0);
			default:
				errorinp();
				break;
		}
	}while(repeat);
}
