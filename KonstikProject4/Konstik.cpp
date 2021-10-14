#include <iostream>
#include <string>
#include <conio.h>
#include <fstream>
#include <windows.h>
#include "GTN.h"
#include "utilities.h"
using namespace std;

void PrintTitle(string title)
{
	cout << '\n' << ' ' << title << ' ';
	cout << endl;
}

int main()
{
	// Óñòàíàâëèâàåì ðóññêîÿçû÷íûé ââîä è âûâîä (www.cyberforum.ru/cpp-beginners/thread2574044.html)
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	GTN gtn = GTN();
	int edgeCount = 0;

	while (true)
	{
		PrintTitle("ÌÅÍÞ");
		cout << "1 - Äîáàâèòü òðóáó\n"
			<< "2 - Äîáàâèòü ÊÑ\n"
			<< "3 - Ïðîñìîòð âñåõ îáúåêòîâ\n"
			<< "4 - Ðåäàêòèðîâàòü òðóáó\n"
			<< "5 - Ðåäàêòèðîâàòü ÊÑ\n"
			<< "6 - Óäàëèòü òðóáó\n"
			<< "7 - Óäàëèòü ÊÑ\n"
			<< "8 - Ïîèñê òðóá\n"
			<< "9 - Ïîèñê ÊÑ\n"
			<< "10 - Ñîõðàíèòü\n"
			<< "11 - Çàãðóçèòü\n"
			<< "12 - Óñòàíîâèòü ñâÿçü\n"
			<< "13 - Óäàëèòü ñâÿçü\n"
			<< "14 - Âûâåñòè ãàçîòðàíñïîðòíóþ ñåòü\n"
			<< "15 - Âûïîëíèòü òîïîëîãè÷åñêóþ ñîðòèðîâêó\n"
			<< "16 - Íàéòè ìàêñèìàëüíûé ïîòîê\n"
			<< "17 - Íàéòè êðàò÷àéøèå ïóòè\n"
			<< "0 è ïð. - Âûõîä\n";

		int inputMenu;
		TryInput(inputMenu, "×òî Âû õîòèòå ñäåëàòü: ");

		switch (inputMenu)
		{
		case 1:
		{
			PrintTitle("ÄÎÁÀÂÈÒÜ ÒÐÓÁÓ");
			gtn.AddPipe();
			break;
		}
		case 2:
		{
			PrintTitle("ÄÎÁÀÂÈÒÜ ÊÑ");
			gtn.AddCs();
			break;
		}
		case 3:
		{
			PrintTitle("ÏÐÎÑÌÎÒÐ ÂÑÅÕ ÎÁÚÅÊÒÎÂ");
			cout << gtn;
			break;
		}
		case 4:
		{
			PrintTitle("ÐÅÄÀÊÒÈÐÎÂÀÒÜ ÒÐÓÁÓ");
			if (gtn.HasPipe())
				gtn.EditPipe();
			else
				cout << "Ó Âàñ íåò òðóá äëÿ ðåäàêòèðîâàíèÿ.\n";
			break;
		}
		case 5:
		{
			PrintTitle("ÐÅÄÀÊÒÈÐÎÂÀÒÜ ÊÑ");
			if (gtn.HasCs())
				gtn.EditCs();
			else
				cout << "Ó Âàñ íåò ÊÑ äëÿ ðåäàêòèðîâàíèÿ.\n";
			break;
		}
		case 6:
		{
			PrintTitle("ÓÄÀËÈÒÜ ÒÐÓÁÓ");
			if (gtn.HasPipe())
				gtn.DeletePipe();
			else
				cout << "Ó Âàñ íåò òðóáû äëÿ óäàëåíèÿ.\n";
			break;
		}
		case 7:
		{
			PrintTitle("ÓÄÀËÈÒÜ ÊÑ");
			if (gtn.HasCs())
				gtn.DeleteCs();
			else
				cout << "Ó Âàñ íåò ÊÑ äëÿ óäàëåíèÿ.\n";
			break;
		}
		case 8:
		{
			PrintTitle("ÏÎÈÑÊ ÒÐÓÁ");
			if (gtn.HasPipe())
				gtn.SearchPipes();
			else
				cout << "Ó Âàñ íåò òðóáû äëÿ ïîèñêà.\n";
			break;
		}
		case 9:
		{
			PrintTitle("ÏÎÈÑÊ ÊÑ");
			if (gtn.HasCs())
				gtn.SearchCss();
			else
				cout << "Ó Âàñ íåò ÊÑ äëÿ ïîèñêà.\n";
			break;
		}
		case 10:
		{
			PrintTitle("ÑÎÕÐÀÍÈÒÜ");
			if (gtn.HasPipe() == false && gtn.HasCs() == false)
			{
				cout << "Âíèìàíèå! Ó Âàñ íè îäíîé òðóáû è ÊÑ. Âû äåéñòâèòåëüíî õîòèòå ñîõðàíèòü äàííûå?\n";
				int input;
				TryInput(input, "(1 - äà, 0 è ïð. - íåò): ");
				if (input != 1)
				{
					cout << "Îòìåíà ñîõðàíåíèÿ...\n";
					break;
				}
			}
			string filename;
			cout << "Ââåäèòå èìÿ ôàéëà ñîõðàíåíèÿ (.txt): ";
			cin >> filename;
			ofstream fout;
			fout.open(filename + ".txt", ios::out);
			if (fout.is_open())
			{
				gtn.SaveToFile(fout);
				fout.close();
				cout << "Ôàéë óñïåøíî ñîõðàí¸í!\n";
			}
			else
			{
				cout << "Îøèáêà ñîõðàíåíèÿ ôàéëà!\n";
			}
			break;
		}
		case 11:
		{
			PrintTitle("ÇÀÃÐÓÇÈÒÜ");
			string filename;
			cout << "Ââåäèòå èìÿ ôàéëà çàãðóçêè (.txt): ";
			cin >> filename;
			ifstream fin;
			fin.open(filename + ".txt", ios::in);
			if (fin.is_open())
			{
				gtn = GTN(fin);
				fin.close();
				cout << "Ôàéë óñïåøíî çàãðóæåí!\n";
			}
			else
			{
				cout << "Îøèáêà ñîõðàíåíèÿ ôàéëà!\n";
			}
			break;
		}
		case 12:
		{
			PrintTitle("ÓÑÒÀÍÎÂÈÒÜ ÑÂßÇÜ");
			if (gtn.HasPipe() && gtn.HasCs(2))
				gtn.ConnectPipe();
			else
				cout << "Ó Âàñ íåò òðóá è ÊÑ äëÿ ñâÿçè.\n";
			break;
		}
		case 13:
		{
			PrintTitle("ÓÄÀËÈÒÜ ÑÂßÇÜ");
			if (gtn.HasPipe() && gtn.HasCs(2))
				gtn.ConnectPipe();
			else
				cout << "Ó Âàñ íåò ñâÿçåé\n";
			break;
		}
		case 14:
		{
			PrintTitle("ÃÀÇÎÒÐÀÍÑÏÎÐÒÍÀß ÑÅÒÜ");
			gtn.ShowNetwork();
			break;
		}
		case 15:
		{
			PrintTitle("ÒÎÏÎËÎÃÈ×ÅÑÊÀß ÑÎÐÒÈÐÎÂÊÀ");
			gtn.TopologicalSort();
			break;
		}
		case 16:
		{
			PrintTitle("ÍÀÉÒÈ ÌÀÊÑÈÌÀËÜÍÛÉ ÏÎÒÎÊ");
			gtn.FindMaxFlow();
			break;
		}
		case 17:
		{
			PrintTitle("ÍÀÉÒÈ ÊÐÀÒ×ÀÉØÈÅ ÏÓÒÈ");
			gtn.FindShortestPath();
			break;
		}
		default:
		{
			return 0;
		}
		}
	}
}