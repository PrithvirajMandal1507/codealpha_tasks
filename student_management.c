#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Student
{
    int rollNo;
    char name[100];
    int class;
};

int studentCheck(int Class, int Rollno);
int recordExists(int newClass, int newRollNo,
                 int oldClass, int oldRollNo);

int readInt(const char *prompt, int *value);
void clearInput(void);

int main()
{
    struct Student s;
    int choice;
    FILE *fp;

    printf("\n====================================\n");
    printf("       STUDENT MANAGEMENT SYSTEM\n");
    printf("====================================\n");

    do
    {
        printf("\n1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Search Student\n");
        printf("5. Display Students\n");
        printf("6. Exit\n");

        if (!readInt("\nEnter your choice: ", &choice))
        {
            printf("\nInvalid input! Please enter a number from 1 to 6.\n");
            continue;
        }

        switch (choice)
        {
            /* ================= ADD STUDENT ================= */
            case 1:
            {
                char Name[100];
                int Class;
                int Rollno;

                printf("\n========== ADD STUDENT ==========\n");

                printf("Enter student's name: ");

                if (fgets(Name, sizeof(Name), stdin) == NULL)
                {
                    printf("\nInvalid input!\n");
                    break;
                }

                Name[strcspn(Name, "\n")] = '\0';

                if (strlen(Name) == 0)
                {
                    printf("\nInvalid input! Name cannot be empty.\n");
                    break;
                }

                if (!readInt("Enter student's class: ", &Class))
                {
                    printf("\nInvalid input! Class must be a number between 1 and 12.\n");
                    break;
                }

                if (Class < 1 || Class > 12)
                {
                    printf("\nInvalid input! Class must be between 1 and 12.\n");
                    break;
                }

                if (!readInt("Enter student's roll number: ", &Rollno))
                {
                    printf("\nInvalid input! Roll number must be a positive number.\n");
                    break;
                }

                if (Rollno < 1)
                {
                    printf("\nInvalid input! Roll number must be positive.\n");
                    break;
                }

                if (studentCheck(Class, Rollno) == 1)
                {
                    printf("\nStudent with this class and roll number already exists!\n");
                    break;
                }

                fp = fopen("Student.txt", "ab");

                if (fp == NULL)
                {
                    printf("\nUnable to open file!\n");
                    break;
                }

                strcpy(s.name, Name);
                s.class = Class;
                s.rollNo = Rollno;

                if (fwrite(&s, sizeof(s), 1, fp) == 1)
                {
                    printf("\nStudent added successfully!\n");
                }
                else
                {
                    printf("\nError while saving student!\n");
                }

                fclose(fp);
                break;
            }

            /* ================= DELETE STUDENT ================= */
            case 2:
            {
                FILE *temp;
                int deleteClass;
                int deleteRollNo;
                int found = 0;

                printf("\n========== DELETE STUDENT ==========\n");

                if (!readInt("Enter student's class: ", &deleteClass))
                {
                    printf("\nInvalid input! Class must be a number.\n");
                    break;
                }

                if (!readInt("Enter student's roll number: ", &deleteRollNo))
                {
                    printf("\nInvalid input! Roll number must be a number.\n");
                    break;
                }

                fp = fopen("Student.txt", "rb");

                if (fp == NULL)
                {
                    printf("\nNo student records found. Add a student first!\n");
                    break;
                }

                temp = fopen("temp.txt", "wb");

                if (temp == NULL)
                {
                    printf("\nUnable to create temporary file!\n");
                    fclose(fp);
                    break;
                }

                while (fread(&s, sizeof(s), 1, fp) == 1)
                {
                    if (s.class == deleteClass &&
                        s.rollNo == deleteRollNo)
                    {
                        found = 1;

                        printf("\nStudent found:\n");
                        printf("Name        : %s\n", s.name);
                        printf("Class       : %d\n", s.class);
                        printf("Roll Number : %d\n", s.rollNo);

                        continue;
                    }

                    fwrite(&s, sizeof(s), 1, temp);
                }

                fclose(fp);
                fclose(temp);

                if (found == 0)
                {
                    printf("\nStudent not found!\n");
                    remove("temp.txt");
                }
                else
                {
                    remove("Student.txt");

                    if (rename("temp.txt", "Student.txt") == 0)
                    {
                        printf("\nStudent deleted successfully!\n");
                    }
                    else
                    {
                        printf("\nError while updating student file!\n");
                    }
                }

                break;
            }

            /* ================= UPDATE STUDENT ================= */
            case 3:
            {
                FILE *temp;
                int oldClass;
                int oldRollNo;
                int choice1;
                int found = 0;

                printf("\n========== UPDATE STUDENT ==========\n");

                if (!readInt("Enter student's class: ", &oldClass))
                {
                    printf("\nInvalid input! Class must be a number.\n");
                    break;
                }

                if (!readInt("Enter student's roll number: ", &oldRollNo))
                {
                    printf("\nInvalid input! Roll number must be a number.\n");
                    break;
                }

                fp = fopen("Student.txt", "rb");

                if (fp == NULL)
                {
                    printf("\nNo student records found. Add a student first!\n");
                    break;
                }

                temp = fopen("temp.txt", "wb");

                if (temp == NULL)
                {
                    printf("\nUnable to create temporary file!\n");
                    fclose(fp);
                    break;
                }

                while (fread(&s, sizeof(s), 1, fp) == 1)
                {
                    if (oldClass == s.class &&
                        oldRollNo == s.rollNo)
                    {
                        found = 1;

                        printf("\nStudent Found!\n");
                        printf("Name        : %s\n", s.name);
                        printf("Class       : %d\n", s.class);
                        printf("Roll Number : %d\n", s.rollNo);

                        printf("\nWhat do you want to update?\n");
                        printf("1. Update Name\n");
                        printf("2. Update Class\n");
                        printf("3. Update Roll Number\n");
                        printf("4. Update All\n");
                        printf("5. Cancel\n");

                        if (!readInt("Enter your choice: ", &choice1))
                        {
                            printf("\nInvalid input!\n");
                        }
                        else
                        {
                            switch (choice1)
                            {
                                /* -------- UPDATE NAME -------- */
                                case 1:
                                {
                                    printf("\nEnter new name: ");

                                    if (fgets(s.name,
                                              sizeof(s.name),
                                              stdin) != NULL)
                                    {
                                        s.name[strcspn(s.name, "\n")] = '\0';

                                        if (strlen(s.name) == 0)
                                        {
                                            printf("\nInvalid input! Name cannot be empty.\n");
                                        }
                                        else
                                        {
                                            printf("\nName updated successfully!\n");
                                        }
                                    }

                                    break;
                                }

                                /* -------- UPDATE CLASS -------- */
                                case 2:
                                {
                                    int newClass;

                                    if (!readInt("\nEnter new class: ",
                                                 &newClass))
                                    {
                                        printf("\nInvalid input! Class must be a number between 1 and 12.\n");
                                        break;
                                    }

                                    if (newClass < 1 || newClass > 12)
                                    {
                                        printf("\nInvalid input! Class must be between 1 and 12.\n");
                                        break;
                                    }

                                    if (recordExists(newClass,
                                                     oldRollNo,
                                                     oldClass,
                                                     oldRollNo))
                                    {
                                        printf("\nStudent with these class and roll number details already exists!\n");
                                    }
                                    else
                                    {
                                        s.class = newClass;

                                        printf("\nClass updated successfully!\n");
                                    }

                                    break;
                                }

                                /* -------- UPDATE ROLL NUMBER -------- */
                                case 3:
                                {
                                    int newRollNo;

                                    if (!readInt("\nEnter new roll number: ",
                                                 &newRollNo))
                                    {
                                        printf("\nInvalid input! Roll number must be a positive number.\n");
                                        break;
                                    }

                                    if (newRollNo < 1)
                                    {
                                        printf("\nInvalid input! Roll number must be positive.\n");
                                        break;
                                    }

                                    if (recordExists(oldClass,
                                                     newRollNo,
                                                     oldClass,
                                                     oldRollNo))
                                    {
                                        printf("\nStudent with these class and roll number details already exists!\n");
                                    }
                                    else
                                    {
                                        s.rollNo = newRollNo;

                                        printf("\nRoll number updated successfully!\n");
                                    }

                                    break;
                                }

                                /* -------- UPDATE ALL -------- */
                                case 4:
                                {
                                    int newClass;
                                    int newRollNo;
                                    char newName[100];

                                    printf("\nEnter new name: ");

                                    if (fgets(newName,
                                              sizeof(newName),
                                              stdin) == NULL)
                                    {
                                        printf("\nInvalid input!\n");
                                        break;
                                    }

                                    newName[strcspn(newName, "\n")] = '\0';

                                    if (strlen(newName) == 0)
                                    {
                                        printf("\nInvalid input! Name cannot be empty.\n");
                                        break;
                                    }

                                    if (!readInt("Enter new class: ",
                                                 &newClass))
                                    {
                                        printf("\nInvalid input! Class must be a number between 1 and 12.\n");
                                        break;
                                    }

                                    if (newClass < 1 || newClass > 12)
                                    {
                                        printf("\nInvalid input! Class must be between 1 and 12.\n");
                                        break;
                                    }

                                    if (!readInt("Enter new roll number: ",
                                                 &newRollNo))
                                    {
                                        printf("\nInvalid input! Roll number must be a positive number.\n");
                                        break;
                                    }

                                    if (newRollNo < 1)
                                    {
                                        printf("\nInvalid input! Roll number must be positive.\n");
                                        break;
                                    }

                                    if (recordExists(newClass,
                                                     newRollNo,
                                                     oldClass,
                                                     oldRollNo))
                                    {
                                        printf("\nStudent with these class and roll number details already exists!\n");
                                    }
                                    else
                                    {
                                        s.class = newClass;
                                        s.rollNo = newRollNo;
                                        strcpy(s.name, newName);

                                        printf("\nName, class and roll number updated successfully!\n");
                                    }

                                    break;
                                }

                                /* -------- CANCEL -------- */
                                case 5:
                                    printf("\nUpdate request cancelled!\n");
                                    break;

                                default:
                                    printf("\nWrong input!\n");
                                    break;
                            }
                        }
                    }

                    fwrite(&s, sizeof(s), 1, temp);
                }

                fclose(fp);
                fclose(temp);

                if (found == 0)
                {
                    printf("\nStudent not found!\n");
                    remove("temp.txt");
                }
                else
                {
                    remove("Student.txt");

                    if (rename("temp.txt", "Student.txt") != 0)
                    {
                        printf("\nError while updating student file!\n");
                    }
                }

                break;
            }

            /* ================= SEARCH STUDENT ================= */
            case 4:
            {
                int searchClass;
                int searchRollNo;
                int found = 0;

                printf("\n========== SEARCH STUDENT ==========\n");

                if (!readInt("Enter student's class: ",
                             &searchClass))
                {
                    printf("\nInvalid input! Class must be a number.\n");
                    break;
                }

                if (!readInt("Enter student's roll number: ",
                             &searchRollNo))
                {
                    printf("\nInvalid input! Roll number must be a number.\n");
                    break;
                }

                fp = fopen("Student.txt", "rb");

                if (fp == NULL)
                {
                    printf("\nNo student records found. Add a student first!\n");
                    break;
                }

                while (fread(&s, sizeof(s), 1, fp) == 1)
                {
                    if (s.class == searchClass &&
                        s.rollNo == searchRollNo)
                    {
                        found = 1;

                        printf("\nStudent Found!\n");
                        printf("Name        : %s\n", s.name);
                        printf("Class       : %d\n", s.class);
                        printf("Roll Number : %d\n", s.rollNo);

                        break;
                    }
                }

                fclose(fp);

                if (found == 0)
                {
                    printf("\nStudent not found!\n");
                }

                break;
            }

            /* ================= DISPLAY STUDENTS ================= */
            case 5:
            {
                int recordCount = 0;

                printf("\n========== ALL STUDENTS ==========\n");

                fp = fopen("Student.txt", "rb");

                if (fp == NULL)
                {
                    printf("\nNo student records found. Add a student first!\n");
                    break;
                }

                while (fread(&s, sizeof(s), 1, fp) == 1)
                {
                    recordCount++;

                    printf("\nStudent %d\n", recordCount);
                    printf("-----------------------------\n");
                    printf("Name        : %s\n", s.name);
                    printf("Class       : %d\n", s.class);
                    printf("Roll Number : %d\n", s.rollNo);
                }

                fclose(fp);

                if (recordCount == 0)
                {
                    printf("\nNo student records present in the file.\n");
                }

                break;
            }

            /* ================= EXIT ================= */
            case 6:
                printf("\nSuccessfully exited...\n");
                break;

            default:
                printf("\nInvalid choice! Please enter a number from 1 to 6.\n");
                break;
        }

    } while (choice != 6);

    return 0;
}


/* =========================================================
   READ INTEGER SAFELY
   ========================================================= */

int readInt(const char *prompt, int *value)
{
    char input[100];
    char *end;
    long number;

    printf("%s", prompt);

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        return 0;
    }

    number = strtol(input, &end, 10);

    while (*end == ' ' || *end == '\t')
    {
        end++;
    }

    if (end == input || (*end != '\n' && *end != '\0'))
    {
        return 0;
    }

    if (number > 2147483647L || number < -2147483648L)
    {
        return 0;
    }

    *value = (int)number;

    return 1;
}


/* =========================================================
   STUDENT DUPLICATE CHECK
   ========================================================= */

int studentCheck(int Class, int Rollno)
{
    FILE *fp;
    struct Student temp;

    fp = fopen("Student.txt", "rb");

    if (fp == NULL)
    {
        return 0;
    }

    while (fread(&temp, sizeof(temp), 1, fp) == 1)
    {
        if (temp.class == Class &&
            temp.rollNo == Rollno)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);

    return 0;
}


/* =========================================================
   CHECK WHETHER NEW CLASS + ROLL NUMBER ALREADY EXISTS
   ========================================================= */

int recordExists(int newClass,
                 int newRollNo,
                 int oldClass,
                 int oldRollNo)
{
    FILE *check;
    struct Student temp;

    check = fopen("Student.txt", "rb");

    if (check == NULL)
    {
        return 0;
    }

    while (fread(&temp, sizeof(temp), 1, check) == 1)
    {
        if (temp.class == newClass &&
            temp.rollNo == newRollNo)
        {
            /*
               Ignore the student's own current record.
            */
            if (temp.class == oldClass &&
                temp.rollNo == oldRollNo)
            {
                continue;
            }

            fclose(check);
            return 1;
        }
    }

    fclose(check);

    return 0;
}
