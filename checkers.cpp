#include<iostream>
#include<locale.h>
#include <windows.h>
using namespace std;

int cp=0,cp2=0;

void Stampa(int v[][8]){
	cp=0;cp2=0;
	cout<<"  1 2 3 4 5 6 7 8"<<endl<<"-----------------"<<endl;
	for(int i=0;i<8;i++){
		cout<<i+1<<"|";
		for(int j=0;j<8;j++){
			if(v[i][j]==1){
				cout<<"X"<<"|";
				cp++;
			}
			else{
				if(v[i][j]==3){
					cp++;
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
					cout<<"X";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					cout<<"|";
				}
				else{
					if(v[i][j]==6){
						cp2++;
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
						cout<<"O";
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
						cout<<"|";
					}
					else{
						if(v[i][j]==2){
							cout<<"O"<<"|";
							cp2++;
						}
						else cout<<" "<<"|";
					}
				}
			}
		}
		cout<<endl<<"-----------------"<<endl;
	}
}

void Set(int v[][8]){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if((i+j)%2!=0){
				if(i<3) v[i][j]=2;
				else if(i>4) v[i][j]=1;
				else v[i][j]=0;
			}
			else v[i][j]=0;
		}
	}




}

void input(int v[][8],int g,int g2){
	int i,j,d=1;
	bool b=false;
	
	do{
		cout<<"Inserisci la riga della pedina:";
		cin>>i;
		cout<<"Inserisci la colonna della pedina:";
		cin>>j;
		i--;j--;
		if(v[i][j]==g){
			cout<<"Inserisci 1 per andare a destra e 2 per andare a sinistra:";
			cin>>d;
		}
		if(g==1 and v[i][j]==g){
			if(d==1){
				if(j+1>7 or v[i-1][j+1]==g or (v[i-1][j+1]!=0 and v[i-2][j+2]!=0) or v[i-1][j+1]==g2*3){
					b=true;
					cout<<"Impossibile andare a destra!\n";
				}
				else b=false;
			}
			if(d==2){
				if(j-1<0 or v[i-1][j-1]==g or (v[i-1][j-1]!=0 and v[i-2][j-2]!=0) or v[i-1][j-1]==g2*3){
					b=true;
					cout<<"Impossibile andare a sinistra!\n";
				}
				else b=false;
			}
		}
		else{
			if(v[i][j]==g){
				if(d==1){
					if(j+1>7 or v[i+1][j+1]==g or (v[i+1][j+1]!=0 and v[i+2][j+2]!=0) or v[i+1][j+1]==g2*3){
						b=true;
						cout<<"Impossibile andare a destra!\n";
					}
					else b=false;
				}
				if(d==2){
					if(j-1<0 or v[i+1][j-1]==g or (v[i+1][j-1]!=0 and v[i+2][j-2]!=0) or v[i-1][j+1]==g2*3){
						b=true;
						cout<<"Impossibile andare a sinistra!\n";
					}
					else b=false;
				}
			}
		}
	}while((v[i][j]!=g and v[i][j]!=g*3) or i>=8 or j>=8 or i<0 or j<0 or (d!=1 and d!=2 or b));
	
	if(v[i][j]==g*3){
		do{
			do{
				cout<<"Inserire 1 per andare in alto a sinistra 2 in alto a destra 3 in basso a destra 4 in basso a sinistra:";
				cin>>d;
			}while(d!=1 and d!=2 and d!=3 and d!=4);
			switch(d){
				case 1:
					if((v[i-1][j-1]==g2*3 or v[i-1][j-1]==g2) and v[i-2][j-2]==0){
						b=false;
						v[i][j]=0;
						v[i-1][j-1]=0;
						v[i-2][j-2]=g*3;
						i-=2;j-=2;
						if((v[i-1][j+1]==g2*3 or v[i-1][j+1]==g2) and v[i-2][j+2]==0){
							if(v[i-1][j-1]==0 or ((v[i-1][j-1]==g2 and v[i-2][j-2]!=0) or (v[i-1][j-1]==g2*3)and v[i-2][j-2]!=0)){
								v[i][j]=0;
								v[i-1][j+1]=0;
								v[i-2][j+2]=g*3;
								i-=2;j+=2;
							}
							else{
								Stampa(v);
								do{
									cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
									cin>>d;
								}while(d!=1 and d!=2);
								if(d==1){
									v[i][j]=0;
									v[i-1][j+1]=0;
									v[i-2][j+2]=g*3;
									i-=2;j+=2;
								}
								else{
									v[i][j]=0;
									v[i-1][j-1]=0;
									v[i-2][j-2]=g*3;
									i-=2;j-=2;
								}
									
							}
						}
						else{
							if((v[i-1][j-1]==g2 or v[i-1][j-1]==g2*3) and v[i-2][j-2]==0){
								v[i][j]=0;
								v[i-1][j-1]=0;
								v[i-2][j-2]=g*3;
								i-=2;j-=2;
							}
						}
					}
					else{
						if(v[i-1][j-1]==0){
							v[i][j]=0;
							v[i-1][j-1]=g*3;
							i--;j--;
						}
						else b=true;
					}
					if(b) cout<<"Mossa non valida\n";
					break;
				case 2:
					if((v[i-1][j+1]==g2*3 or v[i-1][j+1]==g2) and v[i-2][j+2]==0){
						b=false;
						v[i][j]=0;
						v[i-1][j+1]=0;
						v[i-2][j+2]=g*3;
						i-=2;j+=2;
						if((v[i-1][j+1]==g2*3 or v[i-1][j+1]==g2) and v[i-2][j+2]==0){
							if(v[i-1][j-1]==0 or ((v[i-1][j-1]==g2 and v[i-2][j-2]==g2) or (v[i-1][j-1]==g2*3)and v[i-2][j-2]!=0)){
								v[i][j]=0;
								v[i-1][j+1]=0;
								v[i-2][j+2]=g;
								i-=2;j+=2;
							}
							else{
								Stampa(v);
								do{
									cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
									cin>>d;
								}while(d!=1 and d!=2);
								if(d==1){
									v[i][j]=0;
									v[i-1][j+1]=0;
									v[i-2][j+2]=g;
									i-=2;j+=2;
								}
								else{
									v[i][j]=0;
									v[i-1][j-1]=0;
									v[i-2][j-2]=g;
									i-=2;j-=2;
								}
									
							}
						}
						else{
							if((v[i-1][j-1]==g2 or v[i-1][j-1]==g2*3) and v[i-2][j-2]==0){
								v[i][j]=0;
								v[i-1][j-1]=0;
								v[i-2][j-2]=g*3;
								i-=2;j-=2;
							}
						}
					}
					else{
						if(v[i-1][j+1]==0){
							v[i][j]=0;
							v[i-1][j+1]=g*3;
							i--;j++;
						}
						else b=true;
					}
					if(b) cout<<"Mossa non valida\n";
					break;
				case 3:
					if((v[i+1][j+1]==g2*3 or v[i+1][j+1]==g2) and v[i+2][j+2]==0){
						b=false;
						v[i][j]=0;
						v[i+1][j+1]=0;
						v[i+2][j+2]=g*3;
						i+=2;j+=2;
						if((v[i+1][j+1]==g2*3 or v[i+1][j+1]==g2) and v[i+2][j+2]==0){
							if(v[i+1][j-1]==0 or ((v[i+1][j-1]==g2 and v[i+2][j-2]==g2) or (v[i+1][j-1]==g2*3)and v[i+2][j-2]!=0)){
								v[i][j]=0;
								v[i+1][j+1]=0;
								v[i+2][j+2]=g;
								i+=2;j+=2;
							}
							else{
								Stampa(v);
								do{
									cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
									cin>>d;
								}while(d!=1 and d!=2);
								if(d==1){
									v[i][j]=0;
									v[i+1][j+1]=0;
									v[i+2][j+2]=g;
									i+=2;j+=2;
								}
								else{
									v[i][j]=0;
									v[i+1][j-1]=0;
									v[i+2][j-2]=g;
									i+=2;j-=2;
								}
								
							}
						}
						else{
							if((v[i+1][j-1]==g2 or v[i-1][j-1]==g2*3) and v[i-2][j-2]==0){
								v[i][j]=0;
								v[i+1][j-1]=0;
								v[i+2][j-2]=g*3;
								i+=2;j-=2;
							}
						}
					}
					else{
						if(v[i+1][j+1]==0){
							v[i][j]=0;
							v[i+1][j+1]=g*3;
							i++;j++;
						}
						else b=true;
					}
					if(b) cout<<"Mossa non valida\n";
					break;
				case 4:
					if((v[i+1][j-1]==g2*3 or v[i+1][j-1]==g2) and v[i+2][j-2]==0){
						b=false;
						v[i][j]=0;
						v[i+1][j-1]=0;
						v[i+2][j-2]=g*3;
						i+=2;j-=2;
						if((v[i+1][j+1]==g2*3 or v[i+1][j+1]==g2) and v[i+2][j+2]==0){
							if(v[i+1][j-1]==0 or ((v[i+1][j-1]==g2 and v[i+2][j-2]==g2) or (v[i+1][j-1]==g2*3)and v[i+2][j-2]!=0)){
								v[i][j]=0;
								v[i+1][j+1]=0;
								v[i+2][j+2]=g;
								i+=2;j+=2;
							}
							else{
								Stampa(v);
								do{
									cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
									cin>>d;
								}while(d!=1 and d!=2);
								if(d==1){
									v[i][j]=0;
									v[i+1][j+1]=0;
									v[i+2][j+2]=g;
									i+=2;j+=2;
								}
								else{
									v[i][j]=0;
									v[i+1][j-1]=0;
									v[i+2][j-2]=g;
									i+=2;j-=2;
								}
								
							}
						}
						else{
							if((v[i+1][j-1]==g2 or v[i+1][j-1]==g2*3) and v[i+2][j-2]==0){
								v[i][j]=0;
								v[i+1][j-1]=0;
								v[i+2][j-2]=g*3;
								i+=2;j-=2;
							}
						}
					}
					else{
						if(v[i+1][j-1]==0){
							v[i][j]=0;
							v[i+1][j-1]=g*3;
							i--;j--;
						}
						else b=true;
					}
					if(b) cout<<"Mossa non valida\n";
					break;
			}
		}while(b);
			
	}
	else{
		if(g==1){
			if(d==1){
				if(v[i-1][j+1]==g2){
					v[i][j]=0;
					v[i-1][j+1]=0;
					v[i-2][j+2]=g;
					i-=2;j+=2;
					if(v[i-1][j+1]==g2 and v[i-2][j+2]==0){
						if(v[i-1][j-1]==0 or (v[i-1][j-1]==g2 and v[i-2][j-2]==g2)){
							v[i][j]=0;
							v[i-1][j+1]=0;
							v[i-2][j+2]=g;
							i-=2;j+=2;
						}
						else{
							Stampa(v);
							do{
								cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
								cin>>d;
							}while(d!=1 and d!=2);
							if(d==1){
								v[i][j]=0;
								v[i-1][j+1]=0;
								v[i-2][j+2]=g;
								i-=2;j+=2;
							}
							else{
								v[i][j]=0;
								v[i-1][j-1]=0;
								v[i-2][j-2]=g;
								i-=2;j-=2;
							}
							
						}
					}
					else{
						if(v[i-1][j-1]==g2 and v[i-2][j-2]==0){
							v[i][j]=0;
							v[i-1][j-1]=0;
							v[i-2][j-2]=g;
							i-=2;j-=2;
						}
					}
				}
				else {
					v[i][j]=0;
					v[i-1][j+1]=g;
					i--;j++;
				}
			}
			else{
				if(v[i-1][j-1]==g2){
						v[i][j]=0;
						v[i-1][j-1]=0;
						v[i-2][j-2]=g;
						i-=2;j-=2;
						if(v[i-1][j+1]==g2 and v[i-2][j+2]==0){
							if(v[i-1][j-1]==0 or (v[i-1][j-1]==g2 and v[i-2][j-2]!=0)){
								v[i][j]=0;
								v[i-1][j+1]=0;
								v[i-2][j+2]=g;
								i-=2;j+=2;
							}
							else{
								Stampa(v);
								do{
									cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
									cin>>d;
								}while(d!=1 and d!=2);
								if(d==1){
									v[i][j]=0;
									v[i-1][j+1]=0;
									v[i-2][j+2]=g;
									i-=2;j+=2;
								}
								else{
									v[i][j]=0;
									v[i-1][j-1]=0;
									v[i-2][j-2]=g;
									i-=2;j-=2;
								}
								
							}
						}
						else{
							if(v[i-1][j-1]==g2 and v[i-2][j-2]==0){
								v[i][j]=0;
								v[i-1][j-1]=0;
								v[i-2][j-2]=g;
								i-=2;j-=2;
							}
						}
				}
				else{
					v[i][j]=0;
					v[i-1][j-1]=g;
					i--;j--;
				}
					
			}
			if(i==0 and v[i][j]<2)v[i][j]*=3;
		}
		else{
			if(d==1){
				if(v[i+1][j+1]==g2){
					v[i][j]=0;
					v[i+1][j+1]=0;
					v[i+2][j+2]=g;
					i+=2;j+=2;
					if(v[i+1][j+1]==g2 and v[i+2][j+2]==0){
						if(v[i+1][j-1]==0 or (v[i-1][j-1]==g2 and v[i-2][j-2]!=0)){
							v[i][j]=0;
							v[i+1][j+1]=0;
							v[i+2][j+2]=g;
							i+=2;j+=2;
						}
						else{
							Stampa(v);
							do{
								cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
								cin>>d;
							}while(d!=1 and d!=2);
							if(d==1){
								v[i][j]=0;
								v[i+1][j+1]=0;
								v[i+2][j+2]=g;
								i+=2;j+=2;
							}
							else{
								v[i][j]=0;
								v[i+1][j-1]=0;
								v[i+2][j-2]=g;
								i+=2;j-=2;
							}
							
						}
					}
					else{
						if(v[i+1][j-1]==g2 and v[i-2][j-2]==0){
							v[i][j]=0;
							v[i+1][j-1]=0;
							v[i+2][j-2]=g;
							i+=2;j-=2;
						}
					}
				}
				else{
					v[i][j]=0;
					v[i+1][j+1]=g;
					i++;j++;
				}
			}
			else{
				if(v[i+1][j-1]==g2){
						v[i][j]=0;
						v[i+1][j-1]=0;
						v[i+2][j-2]=g;
						i+=2;j-=2;
						if(v[i+1][j+1]==g2 and v[i+2][j+2]==0){
							if(v[i+1][j-1]==0 or (v[i+1][j-1]==g2 and v[i+2][j-2]==g2)){
								v[i][j]=0;
								v[i+1][j+1]=0;
								v[i+2][j+2]=g;
								i+=2;j+=2;
							}
							else{
								Stampa(v);
								do{
									cout<<"Inserire di nuovo se andare a destra o sinistra(1,2):";
									cin>>d;
								}while(d!=1 and d!=2);
								if(d==1){
									v[i][j]=0;
									v[i+1][j+1]=0;
									v[i+2][j+2]=g;
									i+=2;j+=2;
								}
								else{
									v[i][j]=0;
									v[i+1][j-1]=0;
									v[i+2][j-2]=g;
									i+=2;j-=2;
								}
								
							}
						}
						else{
							if(v[i+1][j-1]==g2 and v[i+2][j-2]==0){
								v[i][j]=0;
								v[i+1][j-1]=0;
								v[i+2][j-2]=g;
								i+=2;j-=2;
							}
						}
				}
				else{
					v[i][j]=0;
					v[i+1][j-1]=g;
					i++;j--;
				}
					
			}
			if(i==7 and v[i][j]==2) v[i][j]*=3;
		}
	}
	
	
}



main(){
	setlocale(LC_ALL,"");
	int v[8][8],g=1;
	Set(v);
	v[4][1]=6;
	while(true){
		(g%2!=0)?cout<<"Giocatore 1 (X):\n":cout<<"Giocatore 2 (O):\n";
		Stampa(v);
		(g%2!=0)?input(v,1,2):input(v,2,1);
		if(cp==0){
			cout<<"Giocatore 2 (O) ha vinto!";
			break;
		}
		if(cp2==0){
			cout<<"Giocatore 1 (X) ha vinto!";
			break;
		}
		g++;
	}
}
