
while (ch1 != 4)
{
    while (ch2 != 0)
    {
        printMenu(ch1);
        cin >> ch2;
        switch (ch2)
        {
        case 0:
            break;
        case 1:
            MasterObj->createMaster();
            break;
        case 2:
            MasterObj->printMasterDB(MasterObj); //pass array of objs
            break;
        case 3:
            cout << "Enter Roll Number 1 to master count : ";
            cin >> t1;
            //MasterObj->displayMaster(MasterObj[t1 - 1]); //t1-1 as roll num from 1, but array from 0
            MasterObj[t1 - 1].displayMaster();
            break;
        case 4:
            cout << "Enter Roll Number to modify : ";
            cin >> t1;
            MasterObj[t1 - 1].modifyMaster();
        case 5:
            cout << "Enter roll id to update grades : ";
            cin >> t1;
            MasterObj[t1 - 1].updateMasterGrade();
            break;
        case 6:
            cout << "Enter roll ID for gender : ";
            cin >> t1;
            printGender(MasterObj[t1 - 1]);
            break;
        case 7:
            MasterObj->writeToFile_stud(MasterObj);
            break;
        default:
            break;
        }
    }
}
