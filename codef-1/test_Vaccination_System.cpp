#include <stdio.h>
#include <iostream>
#include <cstdlib>
using namespace std;
using std::string;
using std::cout;
using std::cin;
#include "Vaccination_System.cpp"

int main()
{
    int op;
    System system;
    system.Register(599206,"DominicLong",16834,1,1,0,0,2);
    system.Register(203183,	"TrumanSapir",	13294,	7,	7,	0,	1,	1);
    system.Transfer();
    system.Register(594855, "Devin_Gosse", 10295, 6, 6, 1, 0, 3);
    system.Register(897139, "Faithe_Herbert", 19254, 5, 5, 0, 0, 2);
    system.Register(585898, "Abel_Pansy", 14891, 3, 3, 2, 0, 1);
    system.Register(665107, "Salome_Jefferson", 12530, 2, 2, 0, 0, 3);
    system.Register(156497, "Leopold_Back", 16419, 3, 3, 1, 4, 3);
    system.Register(773826, "Robin_Ezekiel", 11764, 3, 3, 1, 0, 1);
    system.Register(285016, "Valentina_Quiller", 12069, 5, 5, 2, 3, 3);
    system.Register(742095, "Rodney_Dobbin", 17689, 5, 5, 0, 0, 2);
    system.Register(658781, "Nathaniel_Brewster", 15178, 2, 2, 0, 0, 3);
    system.Register(262627, "Calvin_Christiana", 16957, 3, 3, 3, 5, 3);
    system.Register(962263, "Bishop_Adam", 17728, 2, 2, 1, 1, 1);
    system.Register(408620, "Sabina_Frederick", 12462, 8, 8, 1, 0, 2);
    system.Register(867720, "Kenneth_Camp", 11100, 6, 6, 1, 0, 3);
    system.Register(967331, "Amos_Vaughan", 18198, 4, 4, 2, 0, 2);
    system.Register(765764, "Kyle_Dunbar", 16745, 6, 6, 2, 0, 3);
    system.Register(720947, "Payne_Frank", 18219, 3, 3, 0, 0, 1);
    system.Register(236769, "Theodore_Robin", 12826, 3, 3, 1, 4, 3);

    //system.Gen_Appointment();
    do
    {
        do
        {
            cout << "Choose an operation:\n";
            cout << "0: Quit\n";
            cout << "1: New registration\n";
            cout << "2: Half day past\n";
            cout << "3: Withdraw\n";
            cout << "4: Change status\n";
            cout << "5: Weekly report\n";
            cout << "6: Monthly report\n";
            cout << "7: Transfer\n";
            cout << "8: Gen_Appointment\n";
            cout << "9: print all data\n";
            cout << "10: system run time\n";
            cout << "11: n days past\n";
            cin >> op;
        }
        while ((op < 0) || (op > 11));
        switch (op)
        {
            case 0: return (0);
            case 1:
            {
                // generate a registration file based on the input data
                cout << "Please enter the information for the new registration in the following format:\n";
                cout << "id:\nname:\ncontact:\nprofession(1~8):\nage_group(1~7):\nrisk(0~3):\npriority letter date (0 if none):\nregistry(1~3):\n";
                int id, contact, profession, age_group, risk, letter, registry;
                string name;
                cin >> id >> name >> contact >> profession >> age_group >> risk >> letter >> registry;
                system.Register(id, name, contact, profession, age_group, risk, letter, registry);
                break;
            }
            case 2:
            {
                // half day past
                system.Half_Day_Pass();
                break;
            }
            case 3:
            {
                // withdraw from treatment
                cout << "Please enter the registration id for the registration file you wish to withdraw: reg_id= \n";
                int reg_id;
                cin >> reg_id;
                system.Withdraw(reg_id);
                break;
            }
            case 4:
            {
                // change status
                cout << "Please enter the registration id and the new profession and risk level in the following order: \n";
                cout << "reg_id:\nnew_profession:\nnew_risk:\n";
                int reg_id, new_profession, new_risk;
                cin >> reg_id >> new_profession >> new_risk;
                system.Change_Status(reg_id, new_profession, new_risk);
                break;
            }
            case 5:
            {
                // weekly report
                cout << "5\n";
                system.Weekly_Report();
                break;
            }
            case 6:
            {
                // monthly report
                cout << "6\n";
                system.Monthly_Report();
                break;
            }
            case 7:
            {
                // Transfer
                cout << "7\n";
                system.Transfer();
                break;
            }
            case 8:
            {
                // Gen_Appointment
                cout << "8\n";
                system.Gen_Appointment();
                break;
            }
            case 9:
            {
                // Print all data
                cout << "9\n";
                system.print();
                break;
            }
            case 10:
            {
                // system run time
                cout << "The system has run for " <<system.counter<< " half days\n";
                break;
            }
            case 11:
            {
                // Print all data
                cout << "Please enter a number n: ";
                int n;
                cin >> n;
                system.n_Day_Pass(n);
                break;
            }
            /*
            case 12:
            {
                // Print all data
                cout << "11\n";
                break;
            }*/
            default: return (0);
        }
    } while (op != 0);

    return 0;
}