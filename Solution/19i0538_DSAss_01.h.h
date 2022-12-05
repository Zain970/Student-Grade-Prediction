#include <iostream>
using namespace std;
#include<fstream>
#include<sstream>


////////////////////////////////////////////////////// 1st TEST CASE AND FIFTH TEST CASE /////////////////////////////////////////////////////////////

double** Load_Data(string path)
{
    std::string line[50][10];

    std::string row;              // for reading row by row from the file

    std::string word;

    // creating the file reading object
    ifstream obj;

    // opening the file
    obj.open(path);

    std::string courses[14] = { "MT104", "MT119","CS118","CL118","EE182","SL101","SS101","EE227","SS122","MT224","SS111","CS217",
        "EL227","CL217" };

     // for storing grades of 14 courses of 1800 students
    double** Grades;
    Grades = new double* [1800];
    for (int i = 0; i < 1800 ; ++i)
    {
        Grades[i] = new double[17];
    }
    		
    int count = 0;

    bool next = false;

    int student = 0;

    int previous = 0;

     // discarding first line
       getline(obj, row);



    for (int i = 0; !obj.eof(); i++)
    {
        getline(obj, row);

        count = count + 1;

        stringstream S(row);

        for (int j = 0; getline(S, word, ','); j++)
        {
            if (j == 0)
            {
                
                if (previous < std::stod(word))
                {
                    next = true;
                    break;
                }
            }

            line[i][j] = word;
        }

        if (next == true)
        {
            int id = 0;      // for courses id

            int k = 0;       // grade

            int l;

            Grades[student][14] = 0.0;                // for CGPA
            Grades[student][15] = 0.0;               // for WARNING
            Grades[student][16] = 0.0;               // for Data structure grade


            for (l = 0; id <= 13; l++)
            {

                if (l >= 1 && line[l][1] == "Spring 2017")
                {
                    // FOR CGPA
                    if (Grades[student][14] < stod(line[l][8]))
                    {
                        Grades[student][14] = std::stod(line[l][8]);
                    }
                }
                if (l >= 1)
                {
                    // FOR WARNING
                    if (Grades[student][15] < stod(line[l][9]))
                    {
                        Grades[student][15] = std::stod(line[l][9]);
                    }
                }

                    //  FOR DATA STRUCTURES GRADE
                if (line[l][2] == "CS201")
                {
                    Grades[student][16] = stod(line[l][6]);
                }

                if (line[l][2] == courses[id])
                {
                    Grades[student][k] = std::stod(line[l][6]);
                    int z = l + 1;

                    while (z < count)
                    {
                        if (line[z][2] == courses[id])
                        {
                            Grades[student][k] = std::stod(line[z][6]);
                        }
                        z = z + 1;
                    }

                    id = id + 1;          // moving to the next course

                    k = k + 1;           // moving to the student's next course grade

                    l = -1;

                }
            }

            previous = previous + 1;

            student = student + 1;           // to store next student grades

            next = false;

            // emptying the string to store record  of the next student(Next student turn)
            for (int x = 0; x < 50; x++)
            {
                for (int y = 0; y < 10; y++)
                {
                    line[x][y] = "";
                }
            }

            // store data for 0 here 
            i = 0;
            count = 0;

        }
    }
    Grades[student][14] = 0.0;                // for CGPA
    Grades[student][15] = 0.0;                // for WARNING
    Grades[student][16] = 0.0;                // for Data structure grade


    int id = 0;                               // for courses id

    int k = 0;                                // grade

    int l;

    for (l = 1; id <= 13; l++)
    {
        if (l >= 1 && line[l][1] == "Spring 2017")
        {
            // FOR CGPA
            if (Grades[student][14] < stod(line[l][8]))
            {
                Grades[student][14] = std::stod(line[l][8]);
            }
        }
        if (l >= 1)
        {
            // FOR WARNING
            if (Grades[student][15] < stod(line[l][9]))
            {
                Grades[student][15] = std::stod(line[l][9]);
            }
        }

        //  FOR DATA STRUCTURES GRADE
        if (line[l][2] == "CS201")
        {
            Grades[student][16] = stod(line[l][6]);
        }

        if (line[l][2] == courses[id])
        {
            Grades[student][k] = std::stod(line[l][6]);

            id = id + 1;          // moving to the next course

            k = k + 1;           // moving to the student's next course grade

            l = 0;
        }
    }
    double** Grades2;
    Grades2 = new double* [1780];

    for (int i = 0; i < 1780; i++)
    {
        Grades2[i] = new double[17];
    }

    int Y = 0;                            // students except -1 grade in data structures
    for (int i = 0; i < student; i++)
    {

        if (Grades[i][16] == -1)
        {
        }
        else
        {
            for (int j = 0; j < 17; j++)
            {
                Grades2[Y][j] = Grades[i][j];
            }
            Y = Y + 1;
        }
    }

    for (int i = 0; i < 1800; i++)
    {
        delete[] Grades[i];
    }
    delete[] Grades;

    return Grades2;
} 


////////////////////////////////////////////////////// 2nd TEST CASE   //////////////////////////////////////////////////////////////////////////////////

double** Distance(double* predictedArray, int predictedArraySize,double** data , int dataRows, int dataCols)
{
    // MULTIPLYING THE CS COURSES BY 1.5 TO INCREASE THEIR WEIGHTAGE
    for (int i = 0; i <predictedArraySize ; i++)
    {
        if (i == 2 || i == 3 || i == 11 || i == 13)
        {
            predictedArray[i] = predictedArray[i] * 1.5;
        }
    }

    double** Distance;
    Distance = new double* [dataRows];
    for (int i = 0; i < dataRows; ++i)
    {
        Distance[i] = new double[2];
    }
   
    // multiplying THE CS COURSES BY 1.5 TO INCREASE THEIR WEIGHTAGE
    for (int i = 0; i < dataRows; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (j == 2 || j == 3 || j == 11 || j == 13)
            {
                data[i][j] = data[i][j] * 1.5;
            }
        }
    }

    double sum = 0.0;
    double Temp[14];

    for (int i = 0; i < dataRows; i++)
    {
        for (int j = 0; j < predictedArraySize; j++)
        {
            Temp[j] = predictedArray[j] - data[i][j];

            if (Temp[j] < 0)
            {
                Temp[j] = -(Temp[j]);
            }
            sum = sum + Temp[j];
        }
        Distance[i][0] =  (sum);
        sum = 0.0;
    }

    // ASSIGNING DS POINTS
    for (int i = 0; i < dataRows; i++)
    {
        Distance[i][1] = data[i][16];
    }

   
    return Distance;
}

////////////////////////////////////////////////////// 3rd TEST CASE   //////////////////////////////////////////////////////////////////////////////////

double** Sort_k_Dis(int k, double** distance, int distanceRows, int distanceCols)
{
    double** D;
    D = new double* [k];
    for (int i = 0; i < k; i++)
    {
        D[i] = new double[2];
    }

    double min;
    int index = 0;
    double temp;
    bool check = false;
    for (int i = 0; i < distanceRows-1; i++)
    {
        min = distance[i][0];

        for (int start = i + 1; start < distanceRows; start++)
        {
            if (min > distance[start][0])
            {
                min = distance[start][0];
                index = start;
                check = true;
            }
        }

        if (check == true)
        {
            // now swapping distances
            temp = distance[i][0];
            distance[i][0] = distance[index][0];
            distance[index][0] = temp;

            // now swaping ds grades
            temp = distance[i][1];
            distance[i][1] = distance[index][1];
            distance [index][1] = temp;
        }
        temp = 0.0;
        check = false;
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < distanceCols; j++)
        {
            D[i][j] = distance[i][j];
        }
    }

    return D;
}


//////////////////////////////////////////////////////// 4th TEST CASE   //////////////////////////////////////////////////////////////////////////////////

string Grade_Frequency(double** sortedKList, int sortedKListRows, int sortedKListCols)
{
    // searching for most frequent grade point in the array
    double* Grade = new double[sortedKListRows];
    for (int i = 0; i < sortedKListRows; i++)
    {
        Grade[i] = sortedKList[i][1];
    }
    double max_count = 1;
    double res = Grade[0];
    int curr_count = 1;
    for (int i = 1; i < sortedKListRows; i++)
    {
        if (Grade[i] == Grade[i - 1])
        {
            curr_count++;
        }
        else 
        {
            if (curr_count > max_count) 
            {
                max_count = curr_count;
                res = Grade[i - 1];
            }
            curr_count = 1;
        }
    }

    // If last element is most frequent 
    if (curr_count > max_count)
    {
        max_count = curr_count;
        res = Grade[sortedKListRows - 1];
    }

    // returning the string equal to grade point
    if (res == 0)
    {
        return "F";
    }
    else if (res == 1)
    {
        return "D";
    }
    else if (res == 1.33)
    {
        return "D+";
    }
    else if (res == 1.67)
    {
        return "C-";
    }
    else if (res == 2)
    {
        return "C";
    }
    else if (res == 2.33)
    {
        return "C+";
    }
    else if (res == 2.67)
    {
        return "B-";
    }
    else if (res == 3)
    {
        return "B";
    }
    else if (res == 3.33)
    {
        return "B+";
    }
    else if (res == 3.67)
    {
        return "A-";
    }
    else if (res == 4 )
    {
        return "A";
    }
    else
    {
        return "A";
    }
}

//////////////////////////////////////////////////////// 6th TEST CASE   //////////////////////////////////////////////////////////////////////////////////

double* all_means(double** Data, int dataRows, int dataCols)
{
    double* U = new double[dataRows];

    double Total = 0.0;

    double Grade_Points[12] = { 13,11,10,9,8,7,6,5,4,3,2,1 };

    for (int i = 0; i < dataRows; i++)
    {
        for (int j = 0; j < 14; j++)
        {
            if (Data[i][j] == 4)
            {
                Total = Total + Grade_Points[0];
            }
            else if (Data[i][j] >= 3.67 && Data[i][j] <= 3.77)
            {
                Total = Total + Grade_Points[1];
            }
            else if (Data [i][j] >= (3.32) && Data[i][j] <= 3.34)
            {
                Total = Total + Grade_Points[2];
            }
            else if (Data[i][j] == 3)
            {
                Total = Total + Grade_Points[3];
            }
            else if (Data[i][j] >= 2.66 && Data[i][j] <= 2.68)
            {
                Total = Total + Grade_Points[4];
            }
            else if (Data[i][j] >= 2.32 && Data[i][j] <= 2.34)
            {
                Total = Total + Grade_Points[5];
            }
            else if (Data[i][j] == 2)
            {
                Total = Total + Grade_Points[6];
            }
            else if (Data[i][j] >= 1.66 && Data[i][j] <= 1.68)
            {
                Total = Total + Grade_Points[7];
            }
            else if (Data[i][j] >= 1.32 && Data[i][j] <= 1.34)
            {
                Total = Total + Grade_Points[8];
            }
            else if (Data[i][j] == 1)
            {
                Total = Total + Grade_Points[9];
            }
            else if (Data[i][j] >= 0.66 && Data[i][j] <= 0.68)
            {
                Total = Total + Grade_Points[10];
            }
            else if (Data[i][j] == 0)
            {
                Total = Total + Grade_Points[11];
            }
        }
        U[i] = Total;
        Total = 0.0;
    }

    return U;
}

double* initia_k_Means(int k, double * allMeans, int allMeansSize)
{
    double* P = new double[k];
    for (int i = 0; i < k; i++)
    {
        P[i] = allMeans[i];
    }
    return P;

}


double* Dist(double* allMeans, int allMeansSize, double* clusterMeans, int clusterMeansSize)
{
    double A3[2][5];

    for (int i = 0; i < clusterMeansSize; i++)
    {
        for (int j = 0; j < allMeansSize; j++)
        {
            A3[i][j] = clusterMeans[i] - allMeans[j];
        }
    }

    for (int i = 0; i < clusterMeansSize; i++)
    {
        for (int j = 0; j < allMeansSize; j++)
        {
            if (A3[i][j] < 0)
            {
                A3[i][j] = -(A3[i][j]);
            }
        }
    }

    double min = 0;

    double MIN[5];
    for (int i = 0; i < allMeansSize; i++)  // columns
    {
        min = A3[0][i];
        for (int j = 0; j < clusterMeansSize; j++)
        {
            if (min > A3[j][i])
            {
                min = A3[j][i];
            }
        }
        MIN[i] = min;
    }
    double* cluster = new double[clusterMeansSize];
    double sum = 0;
    int count = 0;
    for (int k = 0; k < clusterMeansSize; k++)
    {
        for (int j = 0; j < allMeansSize; j++)
        {
            if (MIN[j] == A3[k][j])
            {
                count = count + 1;
                sum = sum + allMeans[j];
            }
        }
        cluster[k] = sum / count;
        sum = 0;
        count = 0;
    }
    return cluster;
}

// return True if both means are same otherwise return false 
bool  Accuracy(double* oldClusterMeans, int oldClusterMeansSize, double* newClusterMeans, int newClusterMeansSize)
{
    bool check = true;
    for (int i = 0; i < oldClusterMeansSize; i++)
    {
        if (oldClusterMeans[i] != newClusterMeans[i])
        {
            check = false;
            return check;
        }
    }
    return check;
}


string Prediction(double newData, double * meansOfClustors,int meansOfClustorsSize)
{
    double* P = new double[meansOfClustorsSize];
    for (int i = 0; i < meansOfClustorsSize; i++)
    {
        P[i] = meansOfClustors[i] - newData;
    }

    double min = P[0];

    for (int i = 1; i < meansOfClustorsSize; i++)
    {
        if (min > P[i])
        {
            min = P[i];
        }
    }

    if (min >= 80 && min <= 100)
    {
        return "A";
    }
    if (min >=70  && min <80 )
    {
        return "B";
    }
    if (min >= 60 && min < 70)
    {
        return "C";
    }
    if (min >= 50 && min < 60)
    {
        return "D";
    }
    else 
    {
        return "F";
    }
}
