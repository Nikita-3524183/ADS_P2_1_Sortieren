#include "sorting.h"



namespace sorting {

	//************
	// QuickSort *
	//************     

	int partition(std::vector<int>& arr, int left, int right) 
	{
		int pivot = arr[right]; 
		int i = left-1;

		for (int j=left;j<=right-1;j++)	// Alle Elemente < Pivot links anordnen
		{
			if (arr[j] < pivot) 
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i+1], arr[right]);	// Position des Pivots korrigieren

		return i+1;
	}

	void QuickSort(vector<int>& arr, int left, int right)
	{
		int n0 = 100;

		// Insertion sort falls Array größer ist als Threshold
		if(right-left+1 <= n0)	
		{
			for(int i=left+1; i<=right; i++)
			{
				int tmp = arr[i];
				int j = i-1;
				while(j >= left && arr[j] > tmp)
				{
					arr[j+1] = arr[j];
					j--;
				}
				arr[j+1] = tmp;
			}
		}
		// Quicksort
		else				
		{
			// Array wird anhand eines Pivots sortiert
			int pivot = partition(arr,left,right);

			//Beide Subarrays rekursiv sortieren
			QuickSort(arr,left,pivot-1);	
			QuickSort(arr,pivot+1,right);
		}
	}

	//************
	// MergeSort *
	//************

	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		int lEnd = pivot-1;
		int bPos = low;
		int n = high-low+1;

		// Beide Subarrays mithilfe von b mergen
		while(low <= lEnd && pivot <= high)	
		{
			// Kleinstes Element wird b hinzugefügt
			if(a[low] <= a[pivot])	
			{
				b[bPos] = a[low];
				low++;
			}
			else
			{
				b[bPos] = a[pivot];
				pivot++;
			}

			bPos++;
		}

		// Kopieren der verbleibenden Elemente aus dem ersten Subarray, falls vorhanden
		while(low <= lEnd)	
			b[bPos++] = a[low++];
		
		// Kopieren der verbleibenden Elemente aus dem zweiten Subarray, falls vorhanden
		while(pivot <= high)
			b[bPos++] = a[pivot++];
		
		// Kopieren zurück in das ursprüngliche Array
		for(int i=high-n+1;i<=high;i++)
			a[i] = b[i];
		
	}

	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if(low < high)
		{
			int pivot = (low + high) / 2;
			MergeSort(a,b,low,pivot);		// Das Array wird rekursiv in zwei Subarrays geteilt
			MergeSort(a,b,pivot+1,high);
			Merge(a,b,low,pivot+1,high);
		}
	}

	void natMerge(vector<int> &a, vector<int> &b, int left, int middle, int right) 
	{
		int i = left;
		int j = middle + 1;
		int k = left;

		while (i <= middle && j <= right) 	// Beide subarrays mithilfe von b mergen
		{
			if (a[i] <= a[j])
				b[k++] = a[i++];
			else 
				b[k++] = a[j++];
		}

		// Kopieren der verbleibenden Elemente aus dem ersten Subarray, falls vorhanden
		while (i <= middle) 	
			b[k++] = a[i++];
		
		// Kopieren der verbleibenden Elemente aus dem zweiten Subarray, falls vorhanden
		while (j <= right) 		
			b[k++] = a[j++];
		

		// Kopieren zurück in das ursprüngliche Array
		for (int i = left; i <= right; i++)
			a[i] = b[i];
		
	}

	void natMergeSort(vector<int> &a, vector<int> &b)
	{
		int n = a.size();
		while (true) 
		{
			vector<int> runs;
			int i = 0;

			// Alle Runs im Array finden
			while (i < n) 
			{
				int j = i + 1;
				while (j < n && a[j] >= a[j - 1])
					j++;
				runs.push_back(j - i);
				i = j;
			}

			// Falls es nur ein Run gibt, ist das Array sortiert
			if (runs.size() == 1)
				return;

			vector<int> newRuns;

			// Benachbarte Runs mergen
			for (int i=0;i<runs.size();i+=2) 
			{
				int left = 0;
				for (int j=0;j<i;j++)
					left += runs[j];

				int middle = left + runs[i] - 1;
				int right = min(left + runs[i] + runs[i + 1] - 1, n - 1);

				natMerge(a, b, left, middle, right);
				newRuns.push_back(right - left + 1);
			}

			// Falls die Anzahl an Runs ungerade ist, wird die letzte auch hinzugefügt
			if (runs.size() % 2 != 0)
				newRuns.push_back(runs.back());

			runs = newRuns;
		}
	}

	//************
	// Heapsort  *
	//************

	void heapify(vector<int> &a, int n, int i)
	{
		int largest = i; // Initialisiere Root als i
		int l = 2 * i + 1; // left = 2*i + 1
		int r = 2 * i + 2; // right = 2*i + 2
	
		// Falls linkes Kindknoten größer als Root ist
		if (l < n && a[l] > a[largest])
			largest = l;
	
		// Falls rechtes Kindknoten größer ist
		if (r < n && a[r] > a[largest])
			largest = r;
	
		// Falls Root nicht das größte Element ist
		if (largest != i) 
		{
			swap(a[i], a[largest]);
	
			// Heapbedingungen rekursiv prüfen
			heapify(a, n, largest);
		}
	}

	void HeapSort(vector<int> &a, int n) 
	{
		for(int i=n/2-1;i>=0;i--)
		{
			heapify(a,n,i);
		}
		
		for(int i=n-1;i>0;i--)
		{
			swap(a[0],a[i]);
			heapify(a,i,0);
		}
	}

	//************
	// Shellsort *
	//************
	// Hier soll Hibbard implementiert werden
	
	void ShellSort_2n(vector<int> &a, int n)
	{

		int gap = 1;
		// Hibbard-Folge wird implementiert
		while (gap < n)
		{
			gap = 2*gap+1;
		}

		while (gap >= 1)
		{
			// Abstand wird der Hibbard-Folge entsprechend verkleinert
			gap = (gap-1)/2;

			// Insertion sort wird mit dem Abstand gap durchgeführt
			for (int i=gap;i<n;i++)
			{
				int key = a[i];
				int j = i;
				while (j>=gap && a[j-gap]>key)
				{
					a[j] = a[j-gap];
					j -= gap;
				}
				a[j] = key;
			}
		}

	}

	void ShellSort_3n(vector<int> &a, int n)
	{

		int gap = 1;
		while (gap < n)
		{
			gap = 3*gap+1;
		}

		while (gap >= 1)
		{
			gap = (gap-1)/3;

			for (int i=gap;i<n;i++)
			{
				int key = a[i];
				int j = i;
				while (j>=gap && a[j-gap]>key)
				{
					a[j] = a[j-gap];
					j -= gap;
				}
				a[j] = key;
			}
		}

	}

  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





