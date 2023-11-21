//***************************************************************
//                   FILE HEADER YANG DIGUNAKAN DALAM PROYEK
//****************************************************************

#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
using namespace std;

//***************************************************************
//                   KELAS YANG DIGUNAKAN DALAM PROYEK
//****************************************************************


class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void create_account();	//berfungsi untuk mengambil data dari pengguna
	void show_account() const;	//berfungsi untuk menampilkan data di layar
	void modify();	//berfungsi untuk menambahkan data baru
	void dep(int);	//berfungsi untuk menerima jumlah dan menambah jumlah saldo
	void draw(int);	//berfungsi untuk menerima jumlah dan mengurangi jumlah saldo
	void report() const;	//berfungsi untuk menampilkan data dalam format tabel
	int retacno() const;	//berfungsi untuk mengembalikan nomor rekening
	int retdeposit() const;	//berfungsi untuk mengembalikan jumlah saldo
	char rettype() const;	//berfungsi untuk mengembalikan jenis akun
};         //kelas berakhir di sini

void account::create_account()
{
	cout<<"\nMasukkan Nomor Rekening :";
	cin>>acno;
	cout<<"\n\nMasukkan Nama Pemilik Rekening :";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nMasukkan Jenis Akun (C/S):";
	cin>>type;
	type=toupper(type);
	cout<<"\nMasukkan Jumlah Awal (>=500 untuk Tabungan dan >=1000 untuk saat ini ): ";
	cin>>deposit;
	cout<<"\n\n\nAkun telah dibuat..";
}

void account::show_account() const
{
	cout<<"\nNo rekening. :"<<acno;
	cout<<"\nNama pemilik akun :";
	cout<<name;
	cout<<"\nTipe akun :"<<type;
	cout<<"\nJumlah saldo : "<<deposit;
}


void account::modify()
{
	cout<<"\nNo rekening. :"<<acno;
	cout<<"\nUbah Nama Pemilik Akun : ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nUbah Jenis Akun : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nUbah jumlah Saldo :";
	cin>>deposit;
}

	
void account::dep(int x)
{
	deposit+=x;
}
	
void account::draw(int x)
{
	deposit-=x;
}
	
void account::report() const
{
	cout<<acno<<setw(10)<<" "<<name<<setw(10)<<" "<<type<<setw(6)<<deposit<<endl;
}

	
int account::retacno() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}


//***************************************************************
//    	deklarasi fungsi
//****************************************************************
void write_account();	//berfungsi untuk menulis record dalam file biner
void display_sp(int);	//berfungsi untuk menampilkan detail akun yang diberikan oleh pengguna
void modify_account(int);	//berfungsi untuk mengubah catatan file
void delete_account(int);	//function to delete record of file
void display_all();		//berfungsi untuk menampilkan semua detail akun
void deposit_withdraw(int, int); // berfungsi untuk menyetor/menarik jumlah untuk akun tertentu
void intro();	//fungsi layar pengantar

//***************************************************************
//    	FUNGSI UTAMA PROGRAM
//****************************************************************


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. AKUN BARU";
		cout<<"\n\n\t02. JUMLAH DEPOSIT";
		cout<<"\n\n\t03. JUMLAH PENARIKAN";
		cout<<"\n\n\t04. PERTANYAAN SALDO";
		cout<<"\n\n\t05. SEMUA DAFTAR PEMEGANG AKUN";
		cout<<"\n\n\t06. TUTUP AKUN";
		cout<<"\n\n\t07. MODIFIKASI AKUN";
		cout<<"\n\n\t08. KELUAR";
		cout<<"\n\n\tPilih Opsi Anda (1-8)";
		cin>>ch;
		system("cls");
		switch(ch)
		{
		case '1':
			write_account();
			break;
		case '2':
			cout<<"\n\n\tMasukkan Nomor Rekening : "; cin>>num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout<<"\n\n\tMasukkan Nomor Rekening : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
		case '4': 
			cout<<"\n\n\tMasukkan Nomor Rekening : "; cin>>num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout<<"\n\n\tMasukkan Nomor Rekening : "; cin>>num;
			delete_account(num);
			break;
		 case '7':
			cout<<"\n\n\tMasukkan Nomor Rekening : "; cin>>num;
			modify_account(num);
			break;
		 case '8':
			cout<<"\n\n\tTerima kasih telah menggunakan sistem manajemen bank";
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
	}while(ch!='8');
	return 0;
}


//***************************************************************
//    	berfungsi untuk menulis dalam file
//****************************************************************

void write_account()
{
	account ac;
	ofstream outFile;
	outFile.open("akun.dat",ios::binary|ios::app);
	ac.create_account();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

//***************************************************************
//    	berfungsi untuk membaca catatan tertentu dari file
//****************************************************************

void display_sp(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("akun.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File tidak dapat dibuka!! Tekan tombol apa saja...";
		return;
	}
	cout<<"\nDETAIL SALDO\n";

    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()==n)
		{
			ac.show_account();
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nNomor rekening tidak ada";
}


//***************************************************************
//    	berfungsi untuk mengubah catatan file
//****************************************************************

void modify_account(int n)
{
	bool found=false;
	account ac;
	fstream File;
	File.open("akun.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File tidak dapat dibuka!! Tekan tombol apa saja...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			cout<<"\n\nMasukkan Detail Akun Baru"<<endl;
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Rekam Diperbarui";
			found=true;
		  }
	}
	File.close();
	if(found==false)
		cout<<"\n\n Rekaman tidak ditemukan ";
}

//***************************************************************
//    	berfungsi untuk menghapus catatan file
//****************************************************************


void delete_account(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("akun.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File tidak dapat dibuka!! Tekan tombol apa saja...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retacno()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	inFile.close();
	outFile.close();
	remove("akun.dat");
	rename("Temp.dat","akun.dat");
	cout<<"\n\n\tRecord Deleted ..";
}

//***************************************************************
//    	berfungsi untuk menampilkan daftar deposit seluruh rekening
//****************************************************************

void display_all()
{
	account ac;
	ifstream inFile;
	inFile.open("akun.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File tidak dapat dibuka!! Tekan tombol apa saja...";
		return;
	}
	cout<<"\n\n\t\tDAFTAR PEMEGANG AKUN\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.      NAME           jenis  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		ac.report();
	}
	inFile.close();
}

//***************************************************************
//    	berfungsi untuk menyetor dan menarik sejumlah uang
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
	File.open("akun.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File tidak dapat dibuka!! Tekan tombol apa saja...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retacno()==n)
		{
			ac.show_account();
			if(option==1)
			{
				cout<<"\n\n\tUNTUK DEPOSIT JUMLAH ";
				cout<<"\n\nMasukkan Jumlah yang akan disetorkan";
				cin>>amt;
				ac.dep(amt);
			}
			if(option==2)
			{
				cout<<"\n\n\tUNTUK MENARIK JUMLAH ";
				cout<<"\n\nMasukkan Jumlah yang akan ditarik";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if((bal<500 && ac.rettype()=='S') || (bal<1000 && ac.rettype()=='C'))
					cout<<"Keseimbangan tidak mencukupi";
				else
					ac.draw(amt);
			}
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout<<"\n\n\t Rekam Diperbarui";
			found=true;
	       }
         }
	File.close();
	if(found==false)
		cout<<"\n\n Rekaman tidak ditemukan ";
}


//***************************************************************
//    	FUNGSI PENDAHULUAN
//****************************************************************


void intro()
{
	cout<<"\n\n\n\t  BANK";
	cout<<"\n\n\tPENGELOLAAN";
	cout<<"\n\n\t  SISTEM";
	cout<<"\n\n\n\nDIBUAT OLEH : YUDA PRATAMA";
	cout<<"\n\nSEKOLAH : UNIVERSITAS MH TAMRIN";
	cin.get();
}

//***************************************************************
//    			AKHIR PROYEK
//***************************************************************
	