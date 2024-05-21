#include "sorting.h"



namespace sorting {

	//************
	// QuickSort *
	//************     

	int partition(std::vector<int>& arr, int l, int r) 
	{
		int p = arr[r]; 
		int i = l-1;

		for (int j=l;j<=r-1;j++)	// Elemente die kleiner sind links von Pivot
		{
			if (arr[j] < p) 
			{
				i++;
				swap(arr[i], arr[j]);
			}
		}
		swap(arr[i+1], arr[r]);	// Pivot korrekt platzieren

		return i+1;
	}

	void QuickSort(vector<int>& arr, int l, int r)
	{
		int n = 100;

		// Insertion sort sobald schneller
		if(r-l+1 <= n)	
		{
			for(int i=l+1; i<=r; i++)
			{
				int tmp = arr[i];
				int j = i-1;
				while(j >= l && arr[j] > tmp)
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
			// Array am pivot sortieren
			int p = partition(arr,l,r);

			//Subarrays sortieren
			QuickSort(arr,l,p-1);	
			QuickSort(arr,p+1,r);
		}
	}

	//************
	// MergeSort *
	//************

	void Merge(vector<int>& a, vector<int>& b, int l, int p, int h)
	{
		int lEnd = p-1;
		int bPos = l;
		int n = h-l+1;

		// Subarray via b mergen
		while(l <= lEnd && p <= h)	
		{
			// kleineres Element wird in b geschrieben
			if(a[l] <= a[p])	
			{
				b[bPos] = a[l];
				l++;
			}
			else
			{
				b[bPos] = a[p];
				p++;
			}

			bPos++;
		}

		// koppieren der verbleibenden Elemente
		while(l <= lEnd)	
			b[bPos++] = a[l++];
	
		while(p <= h)
			b[bPos++] = a[p++];
		
		// ins ursprüngliche Array kopieren
		for(int i=h-n+1;i<=h;i++)
			a[i] = b[i];
		
	}

	void MergeSort(vector<int>& a, vector<int>& b, int l, int h)
	{
		if(l < h)
		{
			int pivot = (l + h) / 2;
			MergeSort(a,b,l,pivot);		// linke Hälfte sortieren
			MergeSort(a,b,pivot+1,h); 	// rechte Hälfte sortieren
			Merge(a,b,l,pivot+1,h); 	// beide Hälften mergen
		}
	}

	void natMerge(vector<int> &a, vector<int> &b, int l, int m, int r) 
	{
		int i = l;
		int j = m + 1;
		int k = l;

		while (i <= m && j <= r) 	//Merge von beiden Subarrays via b
		{
			if (a[i] <= a[j])
				b[k++] = a[i++];
			else 
				b[k++] = a[j++];
		}

		// Falls Elemente in einem Subarray übrig sind
		while (i <= m) 	
			b[k++] = a[i++];
		
		while (j <= r) 		
			b[k++] = a[j++];
		

		// Kopieren zurück in das ursprüngliche Array
		for (int i = l; i <= r; i++)
			a[i] = b[i];
		
	}

	void natMergeSort(vector<int> &a, vector<int> &b)
	{
		int n = a.size();
		while (true) 
		{
			vector<int> runs;
			int i = 0;

			// Alle Teil-Sortierten Runs finden und speichern
			while (i < n) 
			{
				int j = i + 1;
				while (j < n && a[j] >= a[j - 1])
					j++;
				runs.push_back(j - i);
				i = j;
			}

			// vector bereits sortiert
			if (runs.size() == 1)
				return;

			vector<int> newRuns;

			// Runs mergen / +2 da immer 2 Runs zusammengeführt werden
			for (int i=0;i<runs.size();i+=2) 
			{
				int left = 0;
				// start für jetzigen Run-Merge berechnen
				for (int j=0;j<i;j++)
					left += runs[j];

				int middle = left + runs[i] - 1;
				int right = min(left + runs[i] + runs[i + 1] - 1, n - 1);

				// Mergen der Runs und speichern der neuen Run-Länge
				natMerge(a, b, left, middle, right);
				newRuns.push_back(right - left + 1);
			}

			// Falls die Anzahl an Runs ungerade ist, wird die letzte auch hinzugefügt da sie nicht gemerged wurde
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
	
		// Falls linker Kindknoten größer als Root ist
		if (l < n && a[l] > a[largest])
			largest = l;
	
		// Falls rechter Kindknoten größer ist
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
		// Erstelle Max-Heap
		for(int i=n/2-1;i>=0;i--)
		{
			heapify(a,n,i);
		}
		
		// Entferne Elemente aus dem Heap und füge sie ans Ende des Arrays ein
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
		// gap wird der Hibbard-Folge entsprechend vergrößert, größe des Arrays wird nicht überschritten
		while (gap < n)
		{
			gap = 2*gap+1;
		}

		while (gap >= 1)
		{
			// Abbstand verkleinern
			gap = (gap-1)/2;

			// Insertion Sort mit gap
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





