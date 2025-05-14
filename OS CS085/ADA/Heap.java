class Heap{

    public static void heapify(int arr[], int n, int i){
        int parent = i;
        int left = (parent * 2) + 1;
        int right = left + 1;
        if(left<n && arr[left]>arr[parent]){
            parent = left;
        }
        if(right<n && arr[right]>arr[parent]){
            parent = right;
        }
        if(parent != i){
            int temp = arr[i];
            arr[i] = arr[parent];
            arr[parent] = temp;
            heapify(arr,n,parent);
        }
    }

    public static void HeapSort(int arr[]){

        for(int i=(arr.length-1)/2;i>=0;i--){
            heapify(arr,arr.length,i);
        }

        for(int i=arr.length-1;i>=1;i--){
            int temp = arr[i];
            arr[i] = arr[0];
            arr[0] = temp;
            heapify(arr, i, 0);
        }


    }
    public static void main(String args[]){
        int arr[] = {5,6,4,2,6,9,1,3};

        for(int i=0;i<arr.length;i++){
            System.out.print(arr[i] + " ");
        }
        System.out.println();

        HeapSort(arr);

        for(int i=0;i<arr.length;i++){
            System.out.print(arr[i] + " ");
        }
        System.out.println();

    }
}