#include<iostream>
#include<vector>

using namespace std;

void printVector(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << arr[i] << " ";
    cout << endl;
}
/*
////////////////////////////////////bubble sort/////////////////////////////////////;
void BubbleSort(vector<int> &nums)
{
    int pivot;
    for(int y = 0; y<nums.size(); y++)
    {
        for(int x = 0; x < nums.size() - 1; x++)
        {
            if(nums[x] > nums[y])
            {
                pivot = nums[y];
                nums[y] = nums[x];
                nums[x] = pivot;
            }
        }
    }
}
*/
/*
////////////////////////////////////selection sort/////////////////////////////////////;
void Selection_Sort(vector<int> &nums)
{
    int pivot;
    for(int i = 0; i < nums.size(); i++)
    {
        for(int j = i; j<nums.size(); j++)
        {
            if(nums[j] < nums[i])
            {
                pivot = nums[i];
                nums[i] = nums[j];
                nums[j] = pivot;
            }
        }
    }
}
*/
////////////////////////////////////insertion sort/////////////////////////////////////;
/*
void Insertion_Sort(vector<int> &nums)
{
    for(int i = 1; i < nums.size(); i++)
    {
        int compared_num = nums[i];
        int j = i - 1;
        while(j >= 0 && nums[j] > compared_num)
        {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = compared_num;
    }
}
*/
////////////////////////////////////ShellSort/////////////////////////////////////;
/*
void ShellSort(vector<int> &nums)
{
    int n = nums.size();
    int compared_num;
    int index;
    for(int gap = n/2; gap > 0; gap/=2)
    {
        for(int i = gap; i < n; i++)
        {
            compared_num = nums[i];
            index = i;
            while(index >= gap && nums[index - gap] > compared_num)
            {
                nums[index] = nums[index - gap];
                index -= gap;
            }
            nums[index] = compared_num;
        }
    }
}
*/
////////////////////////////////////Divide_Array_Recursively/////////////////////////////////////;
/*
void Divide_Array_Recursively(vector<int> &nums, int begining, int ending)
{
    if(begining == ending)
        return;
    int mid = (begining + ending) / 2;
    cout<<"begining: "<<nums[begining]<<"\nending: "<<nums[ending]<<"\n";
    Divide_Array_Recursively(nums, begining, mid);
    Divide_Array_Recursively(nums, mid+1, ending);
}
*/
////////////////////////////////////MergeSort/////////////////////////////////////;
/*
void Merge(vector<int> &nums, int beginning, int mid, int ending)
{
    int n1 = mid - beginning + 1;
    int n2 = ending - mid;

    //Temporary vectors;
    vector<int> left(n1);
    vector<int> right(n2);

    //Copy data to temporary vectors;
    for (int i = 0; i < n1; i++)
        left[i] = nums[beginning + i];
    for (int j = 0; j < n2; j++)
        right[j] = nums[mid + 1 + j];

    int i = 0, j = 0, k = beginning;

    // Merge temporary vectors in nums[beginning...ending];
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            nums[k] = left[i];
            i++;
        } else {
            nums[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        nums[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        nums[k] = right[j];
        j++;
        k++;
    }
}

void MergeSort(vector<int> &nums, int beginning, int ending)
{
    if (beginning >= ending)
        return;
//recursively part
    int mid = beginning + (ending - beginning) / 2;
    MergeSort(nums, beginning, mid);
    MergeSort(nums, mid + 1, ending);
//end of the recursevily part
    Merge(nums, beginning, mid, ending);
}
*/
int main()
{
    vector<int> arr = { 12, 11, 13, 5, 6, 7, 1};
    int n = arr.size();
    cout << "Given vector is \n";
    printVector(arr);
    MergeSort(arr, 0, n - 1);
    cout << "\nSorted vector is \n";
    printVector(arr);
    return 0;
}
