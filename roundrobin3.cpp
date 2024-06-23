#include<bits/stdc++.h>/**/
using namespace std;/**/

struct process//Made Structure OF a process
{
    int id;
    int arrival_time;/**/
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;/**/
    int response_time;
    int start_time;
    int burst_remaining;/**/
}processes[100];

bool compare(struct process a,struct process b)//sorting acording to arrival time
{
    int x=a.arrival_time;
    int y=b.arrival_time;
    return x<y;
}

bool compareID(struct process a,struct process b)//sorting acording to ID
{
    int x=a.id;
    int y=b.id;
    return x<y;
}

int main()
{
    int n,index;
    int burst_remaining[100];
    int current_time=0;
    int completed=0,time_quantum;
    vector<bool>visited(100,false); //marking processes visited and not visited...
    bool first_process=true;
    queue<int> ready_queue;
    float sum_tat=0,sum_wt=0,sum_rt=0,sum_ct=0;

    cout<</**/"Enter The Number Of Process:"<<endl;
    cin>>n;
    cout<</**/"Set Time Quantum:"<<endl;
    cin>>time_quantum/**/;

    cout<<"Enter Process Details:"<<endl;
    for(int i=0;i<n;i++)
    {
        cout << "Process " << i + 1 << ":\n";
        processes[i].id = i;
        cout << "   Arrival Time: ";
        cin >> processes[i].arrival_time;
        cout << "   Burst Time: ";
        cin >> processes[i].burst_time;
        processes[i].burst_remaining=processes[i].burst_time;
    }

    sort(processes,processes+n,compare);//calling function for sorting

    ready_queue.push(0);
    visited[0]=true;//first process is marked true as it enters the queue...

    while (completed!=n/*Looping untill all preocessess are completed*/)
    {
        index=ready_queue.front();
        ready_queue.pop();

        if(processes[index].burst_remaining==processes[index].burst_time)
        {
            processes[index].start_time/**/ = max(current_time,processes[index].arrival_time);
            current_time/**/ = processes[index].start_time;
            first_process/**/ = false;
        }

        if(processes[index].burst_remaining>time_quantum)
        {
            processes[index].burst_remaining-=/**/time_quantum;
            current_time+=/**/time_quantum;
        }

        else
        {
            current_time/**/ += processes[index].burst_remaining;
            processes[index].burst_remaining/**/ = 0;
            completed++;//As process gets completed we increament the variable with 1...

            processes[index].completion_time/**/ = current_time;
            processes[index].turnaround_time/**/ = processes[index].completion_time - processes[index].arrival_time;
            processes[index].waiting_time/**/ = processes[index].turnaround_time - processes[index].burst_time;
            processes[index].response_time/**/ = processes[index].start_time - processes[index].arrival_time;
            //Calculating for Average Values...
            sum_tat +=/**/ processes[index].turnaround_time;
            sum_wt +=/**/ processes[index].waiting_time;
            sum_rt +=/**/ processes[index].response_time;
            sum_ct +=/**/ processes[index].completion_time;
        }

        for(int i=1;i<n;i++/**/)
        {
            if(processes[i].burst_remaining>0 and processes[i].arrival_time <=/**/ current_time and visited[i]==false)
            {
                /**/ready_queue.push(i);
                /**/visited[i]=true;
            }
        }
        
        if(processes[index].burst_remaining>0)
            ready_queue.push(index/**/);

        if(ready_queue.empty())
        {
            for(int i=1;i<n;i++)
            {
                if(processes[i].burst_remaining>/**/0)
                {
                    ready_queue.push(i);
                    visited[i]=/**/true;
                    break;
                }
            }
        }
    }
    sort(processes,processes+n,compareID/**/);
    //formatting for a table...
    cout<</**/"------------------------------------------------------------------------------------------"<<endl;
    cout<</**/"| Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time |"<<endl;
    cout<</**/"------------------------------------------------------------------------------------------"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"|    "<<processes[i].id/**/<<"    |      "<<processes[i].arrival_time/**/<<"      |      "
            <<processes[i].burst_time/**/<<"     |        "<<processes[i].completion_time/**/<<"        |        "
            <<processes[i].turnaround_time/**/<<"         |      "<<processes[i].waiting_time/**/<<"      |"<<endl;
    }
    cout<<"------------------------------------------------------------------------------------------"<<endl;
    cout<<"|    Average Turn Around Time    :   "<<sum_tat/n/**/<<"     |"<<endl;
    cout<<"|    Average Waiting Time        :   "<<sum_wt/n/**/<<"     |"<<endl;
    cout<<"|    Average Completion Time     :   "<<sum_ct/n/**/<<"     |"<<endl;
    cout<<"------------------------------------------------------------------------------------------"<<endl;

    
}