import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Optimization {

    public static void main(String[] args) throws FileNotFoundException {
        //Scanner for data input
        File file =
                new File("C:\\Users\\12396\\IdeaProjects\\301 Final Project code\\Sample input.txt");
        // create scanner to read file
        Scanner sc = new Scanner(file);
        //Initialization
        int objectNum = sc.nextInt();
        task[] tasks = new task[objectNum]; //array of tasks in order to store task 1 to n.

        for (int i = 0; i < objectNum; i++) {
            tasks[i] = new task(sc.nextInt(), sc.nextInt(), sc.nextInt());
        }

        //sort tasks so that their deadlines are in increasing order
        quickSort(tasks, 0, objectNum-1);

        //initialization
        int T;  //limitation of deadline in order to limit any deadline of task above this T to be T
        int[][] prof = new int[objectNum][tasks[objectNum-1].getDeadline()+1];  //matrix representing the maximum profit for
                                                                                //task 1~j and for limiting deadline T.

        for (T = 0; T <= tasks[objectNum-1].getDeadline(); T ++){   //Initialization of the first line (task 1) and 0 <= T
                                                                    // <= the latest deadline
            if (tasks[0].getTime() <= T){       //if T >= task1's deadline, we get the profit
                prof[0][T] = tasks[0].getProfit();
            }
            else {prof[0][T] = 0;}              //if T < task1's deadline, we don't get the profit
        }

        for (int j = 1; j < objectNum; j ++){                           //Write-in of the other lines (task 2 to objectNum)
            for (T = 0; T <= tasks[objectNum-1].getDeadline(); T ++){   //Go through T from 0 to objectNum.

                if (T < tasks[j].getTime()){                            //if T < time to finish task j
                    prof[j][T] = prof[j-1][T];                          //we don't get the profit of task j
                }

                else if (tasks[j].getTime() <= T && T <= tasks[j].getDeadline()){               //if T <= task1's deadline but
                                                                                                //T >= time to finish task j
                    if (prof[j-1][T-tasks[j].getTime()]+tasks[j].getProfit() >= prof[j-1][T]){
                        prof[j][T] = prof[j-1][T-tasks[j].getTime()]+tasks[j].getProfit();
                    }
                    else {
                        prof[j][T] = prof[j-1][T];
                    }
                }

                else if (T > tasks[j].getDeadline()){                                               //if T > task1's deadline
                    if (prof[j-1][tasks[j].getDeadline() - tasks[j].getTime()]+tasks[j].getProfit() >= prof[j-1][T]){
                        prof[j][T] = prof[j-1][tasks[j].getDeadline() - tasks[j].getTime()]+tasks[j].getProfit();
                    }
                    else {
                        prof[j][T] = prof[j-1][T];
                    }
                }
            }
        }


        //illustration
        for (int i = 0; i < objectNum; i++)
        {
            for (int j = 0; j <= tasks[objectNum-1].getDeadline(); j ++){
                System.out.print(prof[i][j] + " ");
            }
            System.out.println("");
        }

        //return result
        System.out.println("The optimal solution is: " + prof[objectNum-1][tasks[objectNum-1].getDeadline()]);

    }



    public static void quickSort(task[] i, int low, int high){  //quicksort to sort tasks based on their deadline (from sooner to later)
        if (low < high){
            int pi = partition(i, low, high);

            quickSort(i, low, pi-1);
            quickSort(i, pi+1, high);
        }
    }

    public static int partition(task[] i, int low, int high){       //method used in partition
        int pivot = i[high].getDeadline();

        int k = (low - 1);  // Index of smaller element

        for (int j = low; j <= high - 1; j++)
        {
            // If current element is smaller than the pivot
            if (i[j].getDeadline() < pivot)
            {
                k++;    // increment index of smaller element

                //swap i[k] and i[j]
                task temp = i[j];
                i[j] = i[k];
                i[k]= temp;
            }
        }
        task temp1 = i[high];
        i[high] = i[k+1];
        i[k+1]= temp1;

        return (k + 1);
    }

}


class task{
    //parameters
    int t;
    int d;
    int p;

    //constructor
    public task(){
        t = 0;
        d = 0;
        p = 0;
    }

    public task(int time, int deadline, int profit){
        t = time;
        d = deadline;
        p = profit;
    }

    public int getTime(){
        return t;
    }

    public int getDeadline(){
        return d;
    }

    public int getProfit(){
        return p;
    }
}

