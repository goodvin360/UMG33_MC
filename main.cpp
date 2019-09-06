#include <iostream>
#include <fstream>
#include <iostream>
#include <cstdio>
#include <map>
#include <cmath>
#include <stdio.h>
#include <iomanip>
#include <string>
#include <locale>

using namespace::std;


int main() {

    setlocale(LC_ALL, "Russian");



/////////////////////////////////////////// F I L E     W I T H    M E A S U R E D    D A T A ////////////////////////////////////////////////////////////////


    int FileSize = 0;
    auto str = new char[1024];

    ifstream infile;

    infile.open("C:/Users/Admin/YandexDisk/UMG33/MC/excel-phs.txt");

    while (!infile.eof()) {
        infile.getline(str, 1024, '\n');
        FileSize++;
    }
    delete [] str;
    infile.close();

    float E, Cnt, Uncrt;


    auto phsEnergy = new float [FileSize];
    auto phsCounts = new float [FileSize];
    auto phsUncertains = new float [FileSize];

    ifstream infile1;
    infile1.open("C:/Users/Admin/YandexDisk/UMG33/MC/excel-phs.txt");

    for (int i=0; i<FileSize; i++)
    {
        infile1 >> E >> Cnt >> Uncrt;
        phsEnergy[i] = E;
        if(Cnt<=1E-1)
        {
            Cnt = 0;
        }

        if(Uncrt<=1E-1)
        {
            Uncrt = 0;
        }

        phsCounts[i] = Cnt;
        phsUncertains[i] = Uncrt;

    }
    infile1.close();

    fstream fout("C:/Users/Admin/YandexDisk/UMG33/MC/measured data.phs", ios::out);

    fout << "hB1802.299 EC=6.08856+3.34124*Ch Messung vom 18.2.00" << '\n'
         << 2 << " " << 1 << '\n'
         << 1 << " " << FileSize << " " << FileSize << " " << 15 <<'\n';

//    for (int i=0; i<FileSize; i++)
//    {
//        fout << setw(10) << left << phsEnergy[i] << "," << '\t' << setw(10) << phsCounts[i] << "," << '\t' << setw(10) << phsUncertains[i] << "," <<endl;
//        cout << setw(2) << left  << phsEnergy[i] << ", " << '\t' << setw(5) << left << phsCounts[i] << "," << '\t' << setw(5) << left << phsUncertains[i] << "," <<endl;
//    }

    char buff1_1[256];
    char buff1_2[256];
    char buff1_3[256];

    for (int i=0; i<FileSize; i++)
    {
        sprintf(buff1_1, "%e", phsEnergy[i]);
        sprintf(buff1_2, "%e", phsCounts[i]);
        sprintf(buff1_3, "%e", phsUncertains[i]);
        fout << left << "  " << left << buff1_1 << "! " << "  " << left << buff1_2 << "! " << "  " << left << buff1_3 << "! " << endl;
    }

    fout.close();


    /////////////////////////////////////////// F I L E     W I T H    R E S P O N S E    F U N C T I O N S ////////////////////////////////////////////////////////////////

    int FileSize2 = 0;
    auto str2 = new char[1024];

    const int N_of_files = 100;

    auto RespEnergy = new float [N_of_files];

    double Emax, EmaxResp;
    double Emin, EminResp;
    double Ewight;

    ifstream infile2;

    infile2.open("C:/Users/Admin/YandexDisk/G4/VMplayer/UMG3.3/diamond resp func/Res_1.txt");

    while (!infile2.eof()) {
        infile2.getline(str2, 1024, '\n');
        FileSize2++;
    }

    delete [] str2;
    infile2.close();

    FileSize2 = FileSize2-1;

    cout << FileSize2 << endl;

    EmaxResp = 15;
    EminResp = 13;

    for (int i=0; i<=N_of_files; i++)
    {
        RespEnergy[i] = EminResp+i*((EmaxResp-EminResp)/N_of_files);
        cout << RespEnergy[i] << endl;
    }



    Emax = 9;
    Emin = 7;
    Ewight = (Emax-Emin)/1000;

    cout << Ewight << endl;
    fstream fout2("C:/Users/Admin/YandexDisk/UMG33/MC/resp func2.rsp", ios::out);

    char buff2_1[256];
    char buff2_2[256];
    char buff2_3[256];
    char buff2_4[256];
    char buff2_5[256];
    char buff2_6[256];
    char buff2_7[256];
    char buff2_8[256];
    char buff2_9[256];
    char buff2_10[256];
    char buff2_11[256];

    char label1 [ ] = "C:/Users/Admin/YandexDisk/G4/VMplayer/UMG3.3/diamond resp func/Res_";

    char SpectraPath [256];

    auto *counts = new double [1000];


    sprintf(buff2_1, "%.5E", Ewight);
    sprintf(buff2_3, "%.5E", Emin);
    sprintf(buff2_4, "%.5E", Emax);

    fout2 << "  " << buff2_1 << '\n';

    for (int i = 0; i<=N_of_files; i++)
    {
        sprintf(buff2_2, "%.5E", RespEnergy[i]);
        fout2 << endl << "  " << buff2_2 << "  " << 1000 << "  " << buff2_3 << "  " << buff2_4 << endl;

        sprintf (SpectraPath, "%s%i%s", label1, i+1, ".txt");

        ifstream readFile;
        readFile.open(SpectraPath);

        double count =0;
        double garbage =0;

        for (int m=0; m < 1751; m++)
        {
            readFile >> count;
            garbage = count;
        }

        for (int j=0; j<=1000; j++)
        {
            readFile >> count;
            if(count <= 1E-13)
            {
                count = 0;
            }

            counts[j] = count;
        }
        readFile.close();

//        for (int k=0; k<1000-7; k=k+6)
//        {
//            sprintf(buff2_5, "%.4E", counts[k]);
//            sprintf(buff2_6, "%.4E", counts[k+1]);
//            sprintf(buff2_7, "%.4E", counts[k+2]);
//            sprintf(buff2_8, "%.4E", counts[k+3]);
//            sprintf(buff2_9, "%.4E", counts[k+4]);
//            sprintf(buff2_10, "%.4E", counts[k+5]);
//            sprintf(buff2_11, "%.4E", counts[k+6]);
//            fout2 << " " << buff2_5 << " " << buff2_6 << " " << buff2_7 << " " << buff2_8 << " " << buff2_9 << " " << buff2_10 << " " << buff2_11 << endl;
//        }


        for (int k=1; k<=1000; k++)
        {
            sprintf(buff2_5, "%.4E", counts[k]);
            fout2 << " " << buff2_5;
            if( k%7 == 0)
            {
                fout2 << endl;
            }
        }

    }

    fout2.close();

    double test = 5;
    char buff_test[256];
    sprintf(buff_test, "%.6E", test);
    cout << buff_test << endl;


    //////////////////////////////// M E M O R Y     C L E A N I N G /////////////////////////////////

    delete [] phsCounts;
    delete [] phsEnergy;
    delete [] phsUncertains;
    delete [] RespEnergy;
//    delete [] counts;



    return 0;
}